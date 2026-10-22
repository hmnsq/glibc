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
#समावेश <string.h>

#समावेश <ctype.h>
#समावेश <stdbool.h>
#समावेश <strings.h>

#घोषणा TOLOWER(Ch) छोटे (Ch)

/* Two-Way algorithm.  */
#घोषणा RETURN_TYPE अक्षर *
#घोषणा AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((व्योम*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#घोषणा CHECK_EOL (1)
#घोषणा RET0_IF_0(a) अगर (!a) जाओ ret0
#घोषणा CANON_ELEMENT(c) TOLOWER (c)
#घोषणा CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((स्थिर अक्षर *) (p1), (स्थिर अक्षर *) (p2), l)
#समावेश "str-two-way.h"

#अघोषित strcasestr
#अघोषित __strcasestr

#अगर_अघोषित STRCASESTR
#घोषणा STRCASESTR __strcasestr
#पूर्ण_अगर


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
अक्षर *
STRCASESTR (स्थिर अक्षर *haystack, स्थिर अक्षर *needle)
{
  माप_प्रकार needle_len; /* Length of NEEDLE.  */
  माप_प्रकार haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  अगर (needle[0] == '\0')
    वापस (अक्षर *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = म_माप (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  अगर (haystack_len < needle_len)
    वापस शून्य;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  अगर (needle_len < LONG_NEEDLE_THRESHOLD)
    वापस two_way_short_needle ((स्थिर अचिन्हित अक्षर *) haystack,
				 haystack_len,
				 (स्थिर अचिन्हित अक्षर *) needle,
				 needle_len);
  वापस two_way_long_needle ((स्थिर अचिन्हित अक्षर *) haystack, haystack_len,
			      (स्थिर अचिन्हित अक्षर *) needle,
			      needle_len);
}

#अघोषित LONG_NEEDLE_THRESHOLD

#अगर_अघोषित NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#पूर्ण_अगर
