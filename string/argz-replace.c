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
str_append (अक्षर **to, माप_प्रकार *to_len, स्थिरांक अक्षर *buf, स्थिरांक माप_प्रकार buf_len)
{
  माप_प्रकार new_len = *to_len + buf_len;
  अक्षर *new_to = पुनः_स्मृति (*to, new_len + 1);

  जर (new_to)
    {
      *((अक्षर *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
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
__argz_replace (अक्षर **argz, माप_प्रकार *argz_len, स्थिरांक अक्षर *str, स्थिरांक अक्षर *with,
		अचिन्हित *replace_मोजणी)
{
  error_t err = 0;

  जर (str && *str)
    {
      अक्षर *arg = रिक्त;
      अक्षर *src = *argz;
      माप_प्रकार src_len = *argz_len;
      अक्षर *dst = रिक्त;
      माप_प्रकार dst_len = 0;
      पूर्णांक delayed_copy = 1;	/* True while we've avoided copying anything.  */
      माप_प्रकार str_len = म_माप (str), with_len = म_माप (with);

      पर्यंत (!err && (arg = argz_next (src, src_len, arg)))
	{
	  अक्षर *match = म_माला (arg, str);
	  जर (match)
	    {
	      अक्षर *from = match + str_len;
	      माप_प्रकार to_len = match - arg;
	      अक्षर *to = __strndup (arg, to_len);

	      पर्यंत (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  जर (to)
		    {
		      match = म_माला (from, str);
		      जर (match)
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

	      जर (to)
		{
		  जर (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      जर (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  जर (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  मुक्त (to);
		}
	      अन्यथा
		err = ENOMEM;

	      जर (replace_मोजणी)
		(*replace_मोजणी)++;
	    }
	  अन्यथा जर (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      जर (! err)
	{
	  जर (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      मुक्त (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      अन्यथा जर (dst_len > 0)
	मुक्त (dst);
    }

  परत err;
}
weak_alias (__argz_replace, argz_replace)
