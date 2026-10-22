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
str_append (ಅಕ್ಷರ **ಗಮ್ಯ, size_t *ಗಮ್ಯ_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *buf, ಸ್ಥಿರಾಂಕ size_t buf_len)
{
  size_t new_len = *ಗಮ್ಯ_len + buf_len;
  ಅಕ್ಷರ *new_ಗಮ್ಯ = realloc (*ಗಮ್ಯ, new_len + 1);

  ಆದರೆ (new_ಗಮ್ಯ)
    {
      *((ಅಕ್ಷರ *) __mempcpy (new_ಗಮ್ಯ + *ಗಮ್ಯ_len, buf, buf_len)) = '\0';
      *ಗಮ್ಯ = new_ಗಮ್ಯ;
      *ಗಮ್ಯ_len = new_len;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಬಿಡುಗಡೆ (*ಗಮ್ಯ);
      *ಗಮ್ಯ = ಖಾಲಿ;
    }
}

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary.  If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed.  */
error_t
__argz_replace (ಅಕ್ಷರ **argz, size_t *argz_len, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *with,
		ಚಿಹ್ನೆರಹಿತ *replace_ಎಣಿಕೆ)
{
  error_t err = 0;

  ಆದರೆ (str && *str)
    {
      ಅಕ್ಷರ *arg = ಖಾಲಿ;
      ಅಕ್ಷರ *src = *argz;
      size_t src_len = *argz_len;
      ಅಕ್ಷರ *dst = ಖಾಲಿ;
      size_t dst_len = 0;
      ಪೂರ್ಣಾಂಕ delayed_copy = 1;	/* True while we've avoided copying anything.  */
      size_t str_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (str), with_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (with);

      ಆಗ (!err && (arg = argz_ಮುಂದಿನ (src, src_len, arg)))
	{
	  ಅಕ್ಷರ *ಹೊಂದಿಕೆ = ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (arg, str);
	  ಆದರೆ (ಹೊಂದಿಕೆ)
	    {
	      ಅಕ್ಷರ *from = ಹೊಂದಿಕೆ + str_len;
	      size_t ಗಮ್ಯ_len = ಹೊಂದಿಕೆ - arg;
	      ಅಕ್ಷರ *ಗಮ್ಯ = __strndup (arg, ಗಮ್ಯ_len);

	      ಆಗ (ಗಮ್ಯ && from)
		{
		  str_append (&ಗಮ್ಯ, &ಗಮ್ಯ_len, with, with_len);
		  ಆದರೆ (ಗಮ್ಯ)
		    {
		      ಹೊಂದಿಕೆ = ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (from, str);
		      ಆದರೆ (ಹೊಂದಿಕೆ)
			{
			  str_append (&ಗಮ್ಯ, &ಗಮ್ಯ_len, from, ಹೊಂದಿಕೆ - from);
			  from = ಹೊಂದಿಕೆ + str_len;
			}
		      ಇಲ್ಲದಿದ್ದರೆ
			{
			  str_append (&ಗಮ್ಯ, &ಗಮ್ಯ_len, from, ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (from));
			  from = ಖಾಲಿ;
			}
		    }
		}

	      ಆದರೆ (ಗಮ್ಯ)
		{
		  ಆದರೆ (delayed_copy)
		    /* We avoided copying SRC to DST until we found a match;
                       now that we've done so, copy everything from the start
                       of SRC.  */
		    {
		      ಆದರೆ (arg > src)
			err = __argz_append (&dst, &dst_len, src, (arg - src));
		      delayed_copy = 0;
		    }
		  ಆದರೆ (! err)
		    err = __argz_add (&dst, &dst_len, ಗಮ್ಯ);
		  ಬಿಡುಗಡೆ (ಗಮ್ಯ);
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		err = ENOMEM;

	      ಆದರೆ (replace_ಎಣಿಕೆ)
		(*replace_ಎಣಿಕೆ)++;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! delayed_copy)
	    err = __argz_add (&dst, &dst_len, arg);
	}

      ಆದರೆ (! err)
	{
	  ಆದರೆ (! delayed_copy)
	    /* We never found any instances of str.  */
	    {
	      ಬಿಡುಗಡೆ (src);
	      *argz = dst;
	      *argz_len = dst_len;
	    }
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst_len > 0)
	ಬಿಡುಗಡೆ (dst);
    }

  ಹಿಂತಿರುಗಿ err;
}
weak_alias (__argz_replace, argz_replace)
