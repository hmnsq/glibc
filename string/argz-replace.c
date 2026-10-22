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
str_append (حرف **مقصد, size_t *مقصد_len, ثابت حرف *buf, ثابت size_t buf_len)
{
  size_t new_len = *مقصد_len + buf_len;
  حرف *new_مقصد = realloc (*مقصد, new_len + 1);

  إذا (new_مقصد)
    {
      *((حرف *) __mempcpy (new_مقصد + *مقصد_len, buf, buf_len)) = '\0';
      *مقصد = new_مقصد;
      *مقصد_len = new_len;
    }
  وإلا
    {
      حرر (*مقصد);
      *مقصد = عدم;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (حرف **argz, size_t *argz_len, ثابت حرف *str, ثابت حرف *with,
		بیعلامت *replace_شمار)
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
      size_t str_len = طول_رشته (str), with_len = طول_رشته (with);

      طالما (!err && (arg = argz_بعدی (src, src_len, arg)))
	{
	  حرف *تطابق = جستجوی_رشته (arg, str);
	  إذا (تطابق)
	    {
	      حرف *from = تطابق + str_len;
	      size_t مقصد_len = تطابق - arg;
	      حرف *مقصد = __strndup (arg, مقصد_len);

	      طالما (مقصد && from)
		{
		  str_append (&مقصد, &مقصد_len, with, with_len);
		  إذا (مقصد)
		    {
		      تطابق = جستجوی_رشته (from, str);
		      إذا (تطابق)
			{
			  str_append (&مقصد, &مقصد_len, from, تطابق - from);
			  from = تطابق + str_len;
			}
		      وإلا
			{
			  str_append (&مقصد, &مقصد_len, from, طول_رشته (from));
			  from = عدم;
			}
		    }
		}

	      إذا (مقصد)
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
		    err = __argz_add (&dst, &dst_len, مقصد);
		  حرر (مقصد);
		}
	      وإلا
		err = ENOMEM;

	      إذا (replace_شمار)
		(*replace_شمار)++;
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

  أرجع err;
}
weak_alias (__argz_replace, argz_replace)
