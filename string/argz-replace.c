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

#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
ساكن فراغ
str_append (حرف **to, size_t *to_len, ثابت حرف *buf, ثابت size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  حرف *new_to = realloc (*to, new_len + 1);

  إذا (new_to)
    {
      *((حرف *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  وإلا
    {
      حرر (*to);
      *to = عدم;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (حرف **argz, size_t *argz_len, ثابت حرف *str, ثابت حرف *with,
		unsigned *replace_تعداد)
{
  error_t err = 0;

  إذا (str && *str)
    {
      حرف *arg = عدم;
      حرف *src = *argz;
      size_t src_len = *argz_len;
      حرف *dst = عدم;
      size_t dst_len = 0;
      صحيح delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      بينما (!err && (arg = argz_next (src, src_len, arg)))
	{
	  حرف *match = strstr (arg, str);
	  إذا (match)
	    {
	      حرف *from = match + str_len;
	      size_t to_len = match - arg;
	      حرف *to = __strndup (arg, to_len);

	      بينما (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  إذا (to)
		    {
		      match = strstr (from, str);
		      إذا (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      وإلا
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = عدم;
			}
		    }
		}

	      إذا (to)
		{
		  إذا (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      إذا (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  إذا (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  حرر (to);
		}
	      وإلا
		err = ENOMEM;

	      إذا (replace_تعداد)
		(*replace_تعداد)++;
	    }
	  وإلا إذا (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      إذا (! err)
	{
	  إذا (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      حرر (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      وإلا إذا (dst_len > 0)
	حرر (dst);
    }

  إرجاع err;
}
weak_alias (__argz_replace, argz_replace)
