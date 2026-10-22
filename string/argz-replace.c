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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
ਸਥਿਰ ਖਾਲੀ
str_append (ਅੱਖਰ **ਮੰਜ਼ਿਲ, size_t *ਮੰਜ਼ਿਲ_len, ਅਚਲ ਅੱਖਰ *buf, ਅਚਲ size_t buf_len)
{
  size_t new_len = *ਮੰਜ਼ਿਲ_len + buf_len;
  ਅੱਖਰ *new_ਮੰਜ਼ਿਲ = realloc (*ਮੰਜ਼ਿਲ, new_len + 1);

  ਜੇ (new_ਮੰਜ਼ਿਲ)
    {
      *((ਅੱਖਰ *) __mempcpy (new_ਮੰਜ਼ਿਲ + *ਮੰਜ਼ਿਲ_len, buf, buf_len)) = '\0';
      *ਮੰਜ਼ਿਲ = new_ਮੰਜ਼ਿਲ;
      *ਮੰਜ਼ਿਲ_len = new_len;
    }
  ਨਹੀਂਤਾਂ
    {
      ਮੁਕਤ (*ਮੰਜ਼ਿਲ);
      *ਮੰਜ਼ਿਲ = ਨਿਰਾ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (ਅੱਖਰ **argz, size_t *argz_len, ਅਚਲ ਅੱਖਰ *str, ਅਚਲ ਅੱਖਰ *with,
		ਬਿਨਾਨਿਸ਼ਾਨੀ *replace_ਗਿਣਤੀ)
{
  error_t err = 0;

  ਜੇ (str && *str)
    {
      ਅੱਖਰ *arg = ਨਿਰਾ;
      ਅੱਖਰ *src = *argz;
      size_t src_len = *argz_len;
      ਅੱਖਰ *dst = ਨਿਰਾ;
      size_t dst_len = 0;
      ਪੂਰਨ delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = ਲੜੀ_ਲੰਬਾਈ (str), with_len = ਲੜੀ_ਲੰਬਾਈ (with);

      ਜਦੋਂ (!err && (arg = argz_ਅਗਲਾ (src, src_len, arg)))
	{
	  ਅੱਖਰ *ਮੇਲ = ਲੜੀ_ਖੋਜ (arg, str);
	  ਜੇ (ਮੇਲ)
	    {
	      ਅੱਖਰ *from = ਮੇਲ + str_len;
	      size_t ਮੰਜ਼ਿਲ_len = ਮੇਲ - arg;
	      ਅੱਖਰ *ਮੰਜ਼ਿਲ = __strndup (arg, ਮੰਜ਼ਿਲ_len);

	      ਜਦੋਂ (ਮੰਜ਼ਿਲ && from)
		{
		  str_append (&ਮੰਜ਼ਿਲ, &ਮੰਜ਼ਿਲ_len, with, with_len);
		  ਜੇ (ਮੰਜ਼ਿਲ)
		    {
		      ਮੇਲ = ਲੜੀ_ਖੋਜ (from, str);
		      ਜੇ (ਮੇਲ)
			{
			  str_append (&ਮੰਜ਼ਿਲ, &ਮੰਜ਼ਿਲ_len, from, ਮੇਲ - from);
			  from = ਮੇਲ + str_len;
			}
		      ਨਹੀਂਤਾਂ
			{
			  str_append (&ਮੰਜ਼ਿਲ, &ਮੰਜ਼ਿਲ_len, from, ਲੜੀ_ਲੰਬਾਈ (from));
			  from = ਨਿਰਾ;
			}
		    }
		}

	      ਜੇ (ਮੰਜ਼ਿਲ)
		{
		  ਜੇ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ਜੇ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ਜੇ (! err)
		    err = __argz_add (&dst, &dst_len, ਮੰਜ਼ਿਲ);
		  ਮੁਕਤ (ਮੰਜ਼ਿਲ);
		}
	      ਨਹੀਂਤਾਂ
		err = ENOMEM;

	      ਜੇ (replace_ਗਿਣਤੀ)
		(*replace_ਗਿਣਤੀ)++;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ਜੇ (! err)
	{
	  ਜੇ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      ਮੁਕਤ (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (dst_len > 0)
	ਮੁਕਤ (dst);
    }

  ਵਾਪਸ err;
}
weak_alias (__argz_replace, argz_replace)
