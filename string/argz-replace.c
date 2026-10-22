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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
স্থির শূন্য
str_append (অক্ষর **to, size_t *to_len, ধ্রুবক অক্ষর *buf, ধ্রুবক size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  অক্ষর *new_to = realloc (*to, new_len + 1);

  যদি (new_to)
    {
      *((অক্ষর *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  অন্যথা
    {
      মুক্ত (*to);
      *to = ফাঁকা;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (অক্ষর **argz, size_t *argz_len, ধ্রুবক অক্ষর *str, ধ্রুবক অক্ষর *with,
		unsigned *replace_গুনতি)
{
  error_t err = 0;

  যদি (str && *str)
    {
      অক্ষর *arg = ফাঁকা;
      অক্ষর *src = *argz;
      size_t src_len = *argz_len;
      অক্ষর *dst = ফাঁকা;
      size_t dst_len = 0;
      পূর্ণসংখ্যা delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      যখন (!err && (arg = argz_পরবর্তী (src, src_len, arg)))
	{
	  অক্ষর *match = strstr (arg, str);
	  যদি (match)
	    {
	      অক্ষর *from = match + str_len;
	      size_t to_len = match - arg;
	      অক্ষর *to = __strndup (arg, to_len);

	      যখন (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  যদি (to)
		    {
		      match = strstr (from, str);
		      যদি (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      অন্যথা
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = ফাঁকা;
			}
		    }
		}

	      যদি (to)
		{
		  যদি (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      যদি (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  যদি (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  মুক্ত (to);
		}
	      অন্যথা
		err = ENOMEM;

	      যদি (replace_গুনতি)
		(*replace_গুনতি)++;
	    }
	  অন্যথা যদি (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      যদি (! err)
	{
	  যদি (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      মুক্ত (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      অন্যথা যদি (dst_len > 0)
	মুক্ত (dst);
    }

  ফেরত err;
}
weak_alias (__argz_replace, argz_replace)
