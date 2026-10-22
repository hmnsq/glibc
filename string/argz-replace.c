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
str_append (বর্ণ **to, size_t *to_len, ধ্রুব বর্ণ *buf, ধ্রুব size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  বর্ণ *new_to = realloc (*to, new_len + 1);

  যদি (new_to)
    {
      *((বর্ণ *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  অন্যথা
    {
      মুক্ত (*to);
      *to = রিক্ত;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (বর্ণ **argz, size_t *argz_len, ধ্রুব বর্ণ *str, ধ্রুব বর্ণ *with,
		unsigned *replace_গুনতি)
{
  error_t err = 0;

  যদি (str && *str)
    {
      বর্ণ *arg = রিক্ত;
      বর্ণ *src = *argz;
      size_t src_len = *argz_len;
      বর্ণ *dst = রিক্ত;
      size_t dst_len = 0;
      পূর্ণাঙ্ক delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      যাবত্ (!err && (arg = argz_next (src, src_len, arg)))
	{
	  বর্ণ *match = strstr (arg, str);
	  যদি (match)
	    {
	      বর্ণ *from = match + str_len;
	      size_t to_len = match - arg;
	      বর্ণ *to = __strndup (arg, to_len);

	      যাবত্ (to && from)
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
			  from = রিক্ত;
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

  প্রত্যাগম err;
}
weak_alias (__argz_replace, argz_replace)
