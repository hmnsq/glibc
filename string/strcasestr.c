/* Return the offset of one string within another.
   Copyright (C) 1994-2026 Free Software Foundation, Inc.
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

/*
 * My personal strstr() implementation that beats most other algorithms.
 * Until someone tells me otherwise, I assume that this is the
 * fastest implementation of strstr() in C.
 * I deliberately chose not to comment it.  You should have at least
 * as much fun trying to understand it, as I had to write it :-).
 *
 * Stephen R. van den Berg, berg@pool.informatik.rwth-aachen.de	*/

/* Specification.  */
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <ctype.h>
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಅನ್ತರ್ಭಾವ <strings.h>

#ವ್ಯಾಖ್ಯಾನಿಸು TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#ವ್ಯಾಖ್ಯಾನಿಸು RETURN_TYPE ಅಕ್ಷರ *
#ವ್ಯಾಖ್ಯಾನಿಸು ಲಭ್ಯ(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((ಶೂನ್ಯ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_EOL (1)
#ವ್ಯಾಖ್ಯಾನಿಸು RET0_IF_0(a) ಆದರೆ (!a) ಹೋಗು ret0
#ವ್ಯಾಖ್ಯಾನಿಸು CANON_ELEMENT(c) TOLOWER (c)
#ವ್ಯಾಖ್ಯಾನಿಸು CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (p1), (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (p2), l)
#ಅನ್ತರ್ಭಾವ "str-two-way.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು strcasestr
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __strcasestr

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ STRCASESTR
#ವ್ಯಾಖ್ಯಾನಿಸು STRCASESTR __strcasestr
#ಆದರೆ_ಅಂತ್ಯ


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
ಅಕ್ಷರ *
STRCASESTR (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  ಆದರೆ (needle[0] == '\0')
    ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  ಆದರೆ (haystack_len < needle_len)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  ಆದರೆ (needle_len < LONG_NEEDLE_ಮಿತಿ)
    ಹಿಂತಿರುಗಿ two_way_short_needle ((ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) haystack,
				 haystack_len,
				 (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) needle,
				 needle_len);
  ಹಿಂತಿರುಗಿ two_way_long_needle ((ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) haystack, haystack_len,
			      (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) needle,
			      needle_len);
}

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LONG_NEEDLE_ಮಿತಿ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#ಆದರೆ_ಅಂತ್ಯ
