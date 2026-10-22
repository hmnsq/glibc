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

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <argz.h>

/* Append BUF, of length BUF_LEN to *TO, of length *TO_LEN, reallocating and
   updating *TO & *TO_LEN appropriately.  If an allocation error occurs,
   *TO's old value is freed, and *TO is set to 0.  */
ಸ್ಥಿರ ಶೂನ್ಯ
str_append (ವರ್ಣ **to, size_t *to_len, ಧ್ರುವ ವರ್ಣ *buf, ಧ್ರುವ size_t buf_len)
{
  size_t new_len = *to_len + buf_len;
  ವರ್ಣ *new_to = realloc (*to, new_len + 1);

  ಯದಿ (new_to)
    {
      *((ವರ್ಣ *) __mempcpy (new_to + *to_len, buf, buf_len)) = '\0';
      *to = new_to;
      *to_len = new_len;
    }
  ಅನ್ಯಥಾ
    {
      ಮುಕ್ತ (*to);
      *to = ರಿಕ್ತ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (ವರ್ಣ **argz, size_t *argz_len, ಧ್ರುವ ವರ್ಣ *str, ಧ್ರುವ ವರ್ಣ *with,
		unsigned *replace_ಎಣಿಕೆ)
{
  error_t err = 0;

  ಯದಿ (str && *str)
    {
      ವರ್ಣ *arg = ರಿಕ್ತ;
      ವರ್ಣ *src = *argz;
      size_t src_len = *argz_len;
      ವರ್ಣ *dst = ರಿಕ್ತ;
      size_t dst_len = 0;
      ಪೂರ್ಣಾಙ್ಕ delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = strlen (str), with_len = strlen (with);

      ಯಾವತ್ (!err && (arg = argz_next (src, src_len, arg)))
	{
	  ವರ್ಣ *match = strstr (arg, str);
	  ಯದಿ (match)
	    {
	      ವರ್ಣ *from = match + str_len;
	      size_t to_len = match - arg;
	      ವರ್ಣ *to = __strndup (arg, to_len);

	      ಯಾವತ್ (to && from)
		{
		  str_append (&to, &to_len, with, with_len);
		  ಯದಿ (to)
		    {
		      match = strstr (from, str);
		      ಯದಿ (match)
			{
			  str_append (&to, &to_len, from, match - from);
			  from = match + str_len;
			}
		      ಅನ್ಯಥಾ
			{
			  str_append (&to, &to_len, from, strlen (from));
			  from = ರಿಕ್ತ;
			}
		    }
		}

	      ಯದಿ (to)
		{
		  ಯದಿ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ಯದಿ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ಯದಿ (! err)
		    err = __argz_add (&dst, &dst_len, to);
		  ಮುಕ್ತ (to);
		}
	      ಅನ್ಯಥಾ
		err = ENOMEM;

	      ಯದಿ (replace_ಎಣಿಕೆ)
		(*replace_ಎಣಿಕೆ)++;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ಯದಿ (! err)
	{
	  ಯದಿ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      ಮುಕ್ತ (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (dst_len > 0)
	ಮುಕ್ತ (dst);
    }

  ಪ್ರತ್ಯಾಗಮ err;
}
weak_alias (__argz_replace, argz_replace)
