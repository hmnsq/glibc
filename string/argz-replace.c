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

#شامل <stdlib.h>
#شامل <string.h>
#شامل <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
ایستا تهی
str_append (نویسه **to, size_t *to_len, ثابت نویسه *buf, ثابت size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  نویسه *new_to = realloc (*to, new_len + 1);

  اگر (new_to)
    {
      *((نویسه *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  وگرنه
    {
      آزاد (*to);
      *to = پوچ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (نویسه **argz, size_t *argz_len, ثابت نویسه *str, ثابت نویسه *with,
		unsigned *replace_شمار)
{
  error_t err = 0;

  اگر (str && *str)
    {
      نویسه *arg = پوچ;
      نویسه *src = *argz;
      size_t src_len = *argz_len;
      نویسه *dst = پوچ;
      size_t dst_len = 0;
      صحیح delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      وقتی (!err && (arg = argz_next (src, src_len, arg)))
	{
	  نویسه *match = strstr (arg, str);
	  اگر (match)
	    {
	      نویسه *from = match + str_len;
	      size_t to_len = match - arg;
	      نویسه *to = __strndup (arg, to_len);

	      وقتی (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  اگر (to)
		    {
		      match = strstr (from, str);
		      اگر (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      وگرنه
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = پوچ;
			}
		    }
		}

	      اگر (to)
		{
		  اگر (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      اگر (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  اگر (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  آزاد (to);
		}
	      وگرنه
		err = ENOMEM;

	      اگر (replace_شمار)
		(*replace_شمار)++;
	    }
	  وگرنه اگر (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      اگر (! err)
	{
	  اگر (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      آزاد (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      وگرنه اگر (dst_len > 0)
	آزاد (dst);
    }

  بازگشت err;
}
weak_alias (__argz_replace, argz_replace)
