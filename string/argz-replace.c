/* String replacement in an argz vector
   Copyright (C) 1997-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
स्थिर शून्य
str_append (वर्ण **to, size_t *to_len, ध्रुव वर्ण *buf, ध्रुव size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  वर्ण *new_to = realloc (*to, new_len + 1);

  सचे (new_to)
    {
      *((वर्ण *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  अञ्ञथा
    {
      मुक्त (*to);
      *to = रिक्त;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (वर्ण **argz, size_t *argz_len, ध्रुव वर्ण *str, ध्रुव वर्ण *with,
		unsigned *replace_गणनम्)
{
  error_t err = 0;

  सचे (str && *str)
    {
      वर्ण *arg = रिक्त;
      वर्ण *src = *argz;
      size_t src_len = *argz_len;
      वर्ण *dst = रिक्त;
      size_t dst_len = 0;
      पूर्णाङ्क delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      याव (!err && (arg = argz_next (src, src_len, arg)))
	{
	  वर्ण *match = strstr (arg, str);
	  सचे (match)
	    {
	      वर्ण *from = match + str_len;
	      size_t to_len = match - arg;
	      वर्ण *to = __strndup (arg, to_len);

	      याव (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  सचे (to)
		    {
		      match = strstr (from, str);
		      सचे (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      अञ्ञथा
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = रिक्त;
			}
		    }
		}

	      सचे (to)
		{
		  सचे (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      सचे (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  सचे (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  मुक्त (to);
		}
	      अञ्ञथा
		err = ENOMEM;

	      सचे (replace_गणनम्)
		(*replace_गणनम्)++;
	    }
	  अञ्ञथा सचे (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      सचे (! err)
	{
	  सचे (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      मुक्त (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      अञ्ञथा सचे (dst_len > 0)
	मुक्त (dst);
    }

  पटिनिवत्त err;
}
weak_alias (__argz_replace, argz_replace)
