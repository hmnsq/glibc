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
#ضمن <string.h>

#ضمن <ctype.h>
#ضمن <stdbool.h>
#ضمن <strings.h>

#وصف_ڪريو TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#وصف_ڪريو RETURN_TYPE حرف *
#وصف_ڪريو موجود(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((فراغ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#وصف_ڪريو CHECK_EOL (1)
#وصف_ڪريو RET0_IF_0(a) إذا (!a) اذهب ret0
#وصف_ڪريو CANON_ELEMENT(c) TOLOWER (c)
#وصف_ڪريو CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ثابت حرف *) (p1), (ثابت حرف *) (p2), l)
#ضمن "str-two-way.h"

#وصف_رد strcasestr
#وصف_رد __strcasestr

#جيڪڏهن_وصف_نه_ٿيل STRCASESTR
#وصف_ڪريو STRCASESTR __strcasestr
#جيڪڏهن_پورو


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
حرف *
STRCASESTR (ثابت حرف *haystack, ثابت حرف *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  إذا (needle[0] == '\0')
    أرجع (حرف *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = لڙي_ڊيگهه (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  إذا (haystack_len < needle_len)
    أرجع عدم;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  إذا (needle_len < LONG_NEEDLE_حد)
    أرجع two_way_short_needle ((ثابت بنانشان حرف *) haystack,
				 haystack_len,
				 (ثابت بنانشان حرف *) needle,
				 needle_len);
  أرجع two_way_long_needle ((ثابت بنانشان حرف *) haystack, haystack_len,
			      (ثابت بنانشان حرف *) needle,
			      needle_len);
}

#وصف_رد LONG_NEEDLE_حد

#جيڪڏهن_وصف_نه_ٿيل NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#جيڪڏهن_پورو
