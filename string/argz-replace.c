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
str_append (वर्ण **गन्तव्यम्, size_t *गन्तव्यम्_len, ध्रुव वर्ण *buf, ध्रुव size_t buf_len)
{
  size_t new_len = *गन्तव्यम्_len + buf_len;
  वर्ण *new_गन्तव्यम् = realloc (*गन्तव्यम्, new_len + 1);

  यदि (new_गन्तव्यम्)
    {
      *((वर्ण *) __mempcpy (new_गन्तव्यम् + *गन्तव्यम्_len, buf, buf_len)) = '\0';
      *गन्तव्यम् = new_गन्तव्यम्;
      *गन्तव्यम्_len = new_len;
    }
  अन्यथा
    {
      मुक्त (*गन्तव्यम्);
      *गन्तव्यम् = रिक्त;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (वर्ण **argz, size_t *argz_len, ध्रुव वर्ण *str, ध्रुव वर्ण *with,
		अचिह्नित *replace_गणनम्)
{
  error_t err = 0;

  यदि (str && *str)
    {
      वर्ण *arg = रिक्त;
      वर्ण *src = *argz;
      size_t src_len = *argz_len;
      वर्ण *dst = रिक्त;
      size_t dst_len = 0;
      पूर्णाङ्क delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = वाक्यदैर्घ्यम् (str), with_len = वाक्यदैर्घ्यम् (with);

      यावत् (!err && (arg = argz_अग्र (src, src_len, arg)))
	{
	  वर्ण *मेलनम् = वाक्ये_अन्विष (arg, str);
	  यदि (मेलनम्)
	    {
	      वर्ण *from = मेलनम् + str_len;
	      size_t गन्तव्यम्_len = मेलनम् - arg;
	      वर्ण *गन्तव्यम् = __strndup (arg, गन्तव्यम्_len);

	      यावत् (गन्तव्यम् && from)
		{
		  str_append (&गन्तव्यम्, &गन्तव्यम्_len, with, with_len);
		  यदि (गन्तव्यम्)
		    {
		      मेलनम् = वाक्ये_अन्विष (from, str);
		      यदि (मेलनम्)
			{
			  str_append (&गन्तव्यम्, &गन्तव्यम्_len, from, मेलनम् - from);
			  from = मेलनम् + str_len;
			}
		      अन्यथा
			{
			  str_append (&गन्तव्यम्, &गन्तव्यम्_len, from, वाक्यदैर्घ्यम् (from));
			  from = रिक्त;
			}
		    }
		}

	      यदि (गन्तव्यम्)
		{
		  यदि (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      यदि (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  यदि (! err)
		    err = __argz_add (&dst, &dst_len, गन्तव्यम्);
		  मुक्त (गन्तव्यम्);
		}
	      अन्यथा
		err = ENOMEM;

	      यदि (replace_गणनम्)
		(*replace_गणनम्)++;
	    }
	  अन्यथा यदि (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      यदि (! err)
	{
	  यदि (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      मुक्त (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      अन्यथा यदि (dst_len > 0)
	मुक्त (dst);
    }

  प्रत्यागम err;
}
weak_alias (__argz_replace, argz_replace)
