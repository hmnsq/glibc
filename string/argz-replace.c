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

#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
நிலையான வெறுமை
str_append (எழுத்து **to, size_t *to_len, மாறிலி எழுத்து *buf, மாறிலி size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  எழுத்து *new_to = realloc (*to, new_len + 1);

  எனில் (new_to)
    {
      *((எழுத்து *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  இல்லையெனில்
    {
      விடுவி (*to);
      *to = வெற்று;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (எழுத்து **argz, size_t *argz_len, மாறிலி எழுத்து *str, மாறிலி எழுத்து *with,
		unsigned *replace_மொத்தம்)
{
  error_t err = 0;

  எனில் (str && *str)
    {
      எழுத்து *arg = வெற்று;
      எழுத்து *src = *argz;
      size_t src_len = *argz_len;
      எழுத்து *dst = வெற்று;
      size_t dst_len = 0;
      முழு delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      போது (!err && (arg = argz_next (src, src_len, arg)))
	{
	  எழுத்து *match = strstr (arg, str);
	  எனில் (match)
	    {
	      எழுத்து *from = match + str_len;
	      size_t to_len = match - arg;
	      எழுத்து *to = __strndup (arg, to_len);

	      போது (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  எனில் (to)
		    {
		      match = strstr (from, str);
		      எனில் (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      இல்லையெனில்
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = வெற்று;
			}
		    }
		}

	      எனில் (to)
		{
		  எனில் (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      எனில் (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  எனில் (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  விடுவி (to);
		}
	      இல்லையெனில்
		err = ENOMEM;

	      எனில் (replace_மொத்தம்)
		(*replace_மொத்தம்)++;
	    }
	  இல்லையெனில் எனில் (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      எனில் (! err)
	{
	  எனில் (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      விடுவி (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      இல்லையெனில் எனில் (dst_len > 0)
	விடுவி (dst);
    }

  திரும்பு err;
}
weak_alias (__argz_replace, argz_replace)
