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
str_append (वर्ण **to, माप_प्रकार *to_len, अचर वर्ण *buf, अचर माप_प्रकार buf_len)
{
  माप_प्रकार new_len = *to_len + buf_len;
  वर्ण *new_to = पुनः_स्मृति (*to, new_len + 1);

  यदि (new_to)
    {
      *((वर्ण *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  अन्यथा
    {
      मुक्त (*to);
      *to = रिक्त;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (वर्ण **argz, माप_प्रकार *argz_len, अचर वर्ण *str, अचर वर्ण *with,
		अचिन्हित *replace_गन्ती)
{
  error_t err = 0;

  यदि (str && *str)
    {
      वर्ण *arg = रिक्त;
      वर्ण *src = *argz;
      माप_प्रकार src_len = *argz_len;
      वर्ण *dst = रिक्त;
      माप_प्रकार dst_len = 0;
      पूर्णाङ्क delayed_copy = 1;	/* True while we've avoided copying anything.  */
      माप_प्रकार str_len = म_माप (str), with_len = म_माप (with);

      जबसम्म (!err && (arg = argz_next (src, src_len, arg)))
	{
	  वर्ण *match = म_माला (arg, str);
	  यदि (match)
	    {
	      वर्ण *from = match + str_len;
	      माप_प्रकार to_len = match - arg;
	      वर्ण *to = __strndup (arg, to_len);

	      जबसम्म (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  यदि (to)
		    {
		      match = म_माला (from, str);
		      यदि (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      अन्यथा
			{
			  str_append (&to, &to_len, from, म_माप (from));
			  from = रिक्त;
			}
		    }
		}

	      यदि (to)
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
		    err = __argz_add (&dst, &dst_len, to);
		  मुक्त (to);
		}
	      अन्यथा
		err = ENOMEM;

	      यदि (replace_गन्ती)
		(*replace_गन्ती)++;
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

  फर्काऊ err;
}
weak_alias (__argz_replace, argz_replace)
