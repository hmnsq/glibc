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

#تعریف_کن TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#تعریف_کن RETURN_TYPE حرف *
#تعریف_کن موجود(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((فراغ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#تعریف_کن CHECK_EOL (1)
#تعریف_کن RET0_IF_0(a) إذا (!a) اذهب ret0
#تعریف_کن CANON_ELEMENT(c) TOLOWER (c)
#تعریف_کن CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((ثابت حرف *) (p1), (ثابت حرف *) (p2), l)
#ضمن "str-two-way.h"

#لغو_تعریف strcasestr
#لغو_تعریف __strcasestr

#اگر_تعریف_نشده STRCASESTR
#تعریف_کن STRCASESTR __strcasestr
#پایان_اگر


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
  needle_len = طول_رشته (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  إذا (haystack_len < needle_len)
    أرجع عدم;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  إذا (needle_len < LONG_NEEDLE_آستانه)
    أرجع two_way_short_needle ((ثابت بیعلامت حرف *) haystack,
				 haystack_len,
				 (ثابت بیعلامت حرف *) needle,
				 needle_len);
  أرجع two_way_long_needle ((ثابت بیعلامت حرف *) haystack, haystack_len,
			      (ثابت بیعلامت حرف *) needle,
			      needle_len);
}

#لغو_تعریف LONG_NEEDLE_آستانه

#اگر_تعریف_نشده NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#پایان_اگر
