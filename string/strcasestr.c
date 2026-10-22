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
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ <ctype.h>
#അന്തര്ഭാവ <stdbool.h>
#അന്തര്ഭാവ <strings.h>

#define TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#define RETURN_TYPE അക്ഷരം *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((ശൂന്യം*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#define CHECK_EOL (1)
#define RET0_IF_0(a) എങ്കിൽ (!a) പോകുക ret0
#define CANON_ELEMENT(c) TOLOWER (c)
#define CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((സ്ഥിരം അക്ഷരം *) (p1), (സ്ഥിരം അക്ഷരം *) (p2), l)
#അന്തര്ഭാവ "str-two-way.h"

#undef strcasestr
#undef __strcasestr

#ifndef STRCASESTR
#define STRCASESTR __strcasestr
#endif


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
അക്ഷരം *
STRCASESTR (സ്ഥിരം അക്ഷരം *haystack, സ്ഥിരം അക്ഷരം *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  എങ്കിൽ (needle[0] == '\0')
    തിരികെ (അക്ഷരം *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = strlen (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  എങ്കിൽ (haystack_len < needle_len)
    തിരികെ ശൂന്യ;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  എങ്കിൽ (needle_len < LONG_NEEDLE_THRESHOLD)
    തിരികെ two_way_short_needle ((സ്ഥിരം unsigned അക്ഷരം *) haystack,
				 haystack_len,
				 (സ്ഥിരം unsigned അക്ഷരം *) needle,
				 needle_len);
  തിരികെ two_way_long_needle ((സ്ഥിരം unsigned അക്ഷരം *) haystack, haystack_len,
			      (സ്ഥിരം unsigned അക്ഷരം *) needle,
			      needle_len);
}

#undef LONG_NEEDLE_THRESHOLD

#ifndef NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#endif
