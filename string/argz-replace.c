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
str_append (حرف **منزل, size_t *منزل_len, ثابت حرف *buf, ثابت size_t buf_len)
{
  size_t new_len = *منزل_len + buf_len;
  حرف *new_منزل = realloc (*منزل, new_len + 1);

  إذا (new_منزل)
    {
      *((حرف *) __mempcpy (new_منزل + *منزل_len, buf, buf_len)) = '\0';
      *منزل = new_منزل;
      *منزل_len = new_len;
    }
  وإلا
    {
      حرر (*منزل);
      *منزل = عدم;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (حرف **argz, size_t *argz_len, ثابت حرف *str, ثابت حرف *with,
		بنانشان *replace_ڳڻپ)
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
      size_t str_len = لڙي_ڊيگهه (str), with_len = لڙي_ڊيگهه (with);

      طالما (!err && (arg = argz_ايندڙ (src, src_len, arg)))
	{
	  حرف *ميلاپ = لڙي_ڳولا (arg, str);
	  إذا (ميلاپ)
	    {
	      حرف *from = ميلاپ + str_len;
	      size_t منزل_len = ميلاپ - arg;
	      حرف *منزل = __strndup (arg, منزل_len);

	      طالما (منزل && from)
		{
		  str_append (&منزل, &منزل_len, with, with_len);
		  إذا (منزل)
		    {
		      ميلاپ = لڙي_ڳولا (from, str);
		      إذا (ميلاپ)
			{
			  str_append (&منزل, &منزل_len, from, ميلاپ - from);
			  from = ميلاپ + str_len;
			}
		      وإلا
			{
			  str_append (&منزل, &منزل_len, from, لڙي_ڊيگهه (from));
			  from = عدم;
			}
		    }
		}

	      إذا (منزل)
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
		    err = __argz_add (&dst, &dst_len, منزل);
		  حرر (منزل);
		}
	      وإلا
		err = ENOMEM;

	      إذا (replace_ڳڻپ)
		(*replace_ڳڻپ)++;
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
