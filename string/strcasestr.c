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
#అన్తర్భావ <string.h>

#అన్తర్భావ <ctype.h>
#అన్తర్భావ <stdbool.h>
#అన్తర్భావ <strings.h>

#నిర్వచించు TOLOWER(Ch) tolower (Ch)

/* Two-Way algorithm.  */
#నిర్వచించు RETURN_TYPE అక్షరం *
#నిర్వచించు అందుబాటు(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((శూన్య*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#నిర్వచించు CHECK_EOL (1)
#నిర్వచించు RET0_IF_0(a) ఒకవేళ (!a) వెళ్ళు ret0
#నిర్వచించు CANON_ELEMENT(c) TOLOWER (c)
#నిర్వచించు CMP_FUNC(p1, p2, l)				\
  __strncasecmp ((స్థిరరాశి అక్షరం *) (p1), (స్థిరరాశి అక్షరం *) (p2), l)
#అన్తర్భావ "str-two-way.h"

#నిర్వచనం_రద్దు strcasestr
#నిర్వచనం_రద్దు __strcasestr

#నిర్వచితం_కాకపోతే STRCASESTR
#నిర్వచించు STRCASESTR __strcasestr
#అయితే_ముగింపు


/* Find the first occurrence of NEEDLE in HAYSTACK, using
   case-insensitive comparison.  This function gives unspecified
   results in multibyte locales.  */
అక్షరం *
STRCASESTR (స్థిరరాశి అక్షరం *haystack, స్థిరరాశి అక్షరం *needle)
{
  size_t needle_len; /* Length of NEEDLE.  */
  size_t haystack_len; /* Known minimum length of HAYSTACK.  */

  /* Handle empty NEEDLE special case.  */
  ఒకవేళ (needle[0] == '\0')
    తిరిగి (అక్షరం *) haystack;

  /* Ensure HAYSTACK length is at least as long as NEEDLE length.
     Since a match may occur early on in a huge HAYSTACK, use strnlen
     and read ahead a few cachelines for improved performance.  */
  needle_len = అక్షరశ్రేణి_పొడవు (needle);
  haystack_len = __strnlen (haystack, needle_len + 256);
  ఒకవేళ (haystack_len < needle_len)
    తిరిగి ఖాళీ;

  /* Perform the search.  Abstract memory is considered to be an array
     of 'unsigned char' values, not an array of 'char' values.  See
     ISO C 99 section 6.2.6.1.  */
  ఒకవేళ (needle_len < LONG_NEEDLE_పరిమితి)
    తిరిగి two_way_short_needle ((స్థిరరాశి గుర్తులేని అక్షరం *) haystack,
				 haystack_len,
				 (స్థిరరాశి గుర్తులేని అక్షరం *) needle,
				 needle_len);
  తిరిగి two_way_long_needle ((స్థిరరాశి గుర్తులేని అక్షరం *) haystack, haystack_len,
			      (స్థిరరాశి గుర్తులేని అక్షరం *) needle,
			      needle_len);
}

#నిర్వచనం_రద్దు LONG_NEEDLE_పరిమితి

#నిర్వచితం_కాకపోతే NO_ALIAS
weak_alias (__strcasestr, strcasestr)
#అయితే_ముగింపు
