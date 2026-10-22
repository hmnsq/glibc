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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <strings.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RETURN_TYPE ਅੱਖਰ *
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਉਪਲਬਧ(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((ਖਾਲੀ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_EOL (1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RET0_IF_0(a) ਜੇ (!a) ਜਾਓ ret0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CANON_ELEMENT(c) TOLOWER (c)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ਅਚਲ ਅੱਖਰ *) (p1), (ਅਚਲ ਅੱਖਰ *) (p2), l)
#ਅਨ੍ਤਰ੍ਭਾਵ "str-two-way.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ strcasestr
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __strcasestr

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ STRCASESTR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRCASESTR __strcasestr
#ਜੇ_ਅੰਤ


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
ਅੱਖਰ *
STRCASESTR (ਅਚਲ ਅੱਖਰ *haystack, ਅਚਲ ਅੱਖਰ *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  ਜੇ (needle[0] == '\0')
    ਵਾਪਸ (ਅੱਖਰ *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = ਲੜੀ_ਲੰਬਾਈ (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  ਜੇ (haystack_len < needle_len)
    ਵਾਪਸ ਨਿਰਾ;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  ਜੇ (needle_len < LONG_NEEDLE_ਹੱਦ)
    ਵਾਪਸ two_way_short_needle ((ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) haystack,
				 haystack_len,
				 (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) needle,
				 needle_len);
  ਵਾਪਸ two_way_long_needle ((ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) haystack, haystack_len,
			      (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) needle,
			      needle_len);
}

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LONG_NEEDLE_ਹੱਦ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#ਜੇ_ਅੰਤ
