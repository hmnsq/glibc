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

#define TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#define RETURN_TYPE ವರ್ಣ *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((ಶೂನ್ಯ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#define CHECK_EOL (1)
#define RET0_IF_0(a) ಯದಿ (!a) ಗಚ್ಛ ret0
#define CANON_ELEMENT(c) TOLOWER (c)
#define CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ಧ್ರುವ ವರ್ಣ *) (p1), (ಧ್ರುವ ವರ್ಣ *) (p2), l)
#ಅನ್ತರ್ಭಾವ "str-two-way.h"

#undef strcasestr
#undef __strcasestr

#ifndef STRCASESTR
#define STRCASESTR __strcasestr
#endif


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
ವರ್ಣ *
STRCASESTR (ಧ್ರುವ ವರ್ಣ *haystack, ಧ್ರುವ ವರ್ಣ *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  ಯದಿ (needle[0] == '\0')
    ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = strlen (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  ಯದಿ (haystack_len < needle_len)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  ಯದಿ (needle_len < LONG_NEEDLE_THRESHOLD)
    ಪ್ರತ್ಯಾಗಮ two_way_short_needle ((ಧ್ರುವ unsigned ವರ್ಣ *) haystack,
				 haystack_len,
				 (ಧ್ರುವ unsigned ವರ್ಣ *) needle,
				 needle_len);
  ಪ್ರತ್ಯಾಗಮ two_way_long_needle ((ಧ್ರುವ unsigned ವರ್ಣ *) haystack, haystack_len,
			      (ಧ್ರುವ unsigned ವರ್ಣ *) needle,
			      needle_len);
}

#undef LONG_NEEDLE_THRESHOLD

#ifndef NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#endif
