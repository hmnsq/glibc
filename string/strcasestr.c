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
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <ctype.h>
#অন্তর্ভাব <stdbool.h>
#অন্তর্ভাব <strings.h>

#define TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#define RETURN_TYPE অক্ষর *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((শূন্য*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#define CHECK_EOL (1)
#define RET0_IF_0(a) যদি (!a) যাও ret0
#define CANON_ELEMENT(c) TOLOWER (c)
#define CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ধ্রুবক অক্ষর *) (p1), (ধ্রুবক অক্ষর *) (p2), l)
#অন্তর্ভাব "str-two-way.h"

#undef strcasestr
#undef __strcasestr

#ifndef STRCASESTR
#define STRCASESTR __strcasestr
#endif


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
অক্ষর *
STRCASESTR (ধ্রুবক অক্ষর *haystack, ধ্রুবক অক্ষর *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  যদি (needle[0] == '\0')
    ফেরত (অক্ষর *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = strlen (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  যদি (haystack_len < needle_len)
    ফেরত ফাঁকা;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  যদি (needle_len < LONG_NEEDLE_THRESHOLD)
    ফেরত two_way_short_needle ((ধ্রুবক unsigned অক্ষর *) haystack,
				 haystack_len,
				 (ধ্রুবক unsigned অক্ষর *) needle,
				 needle_len);
  ফেরত two_way_long_needle ((ধ্রুবক unsigned অক্ষর *) haystack, haystack_len,
			      (ধ্রুবক unsigned অক্ষর *) needle,
			      needle_len);
}

#undef LONG_NEEDLE_THRESHOLD

#ifndef NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#endif
