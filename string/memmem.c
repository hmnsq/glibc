/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#अगर_अघोषित _LIBC
# include <config.h>
#पूर्ण_अगर

#समावेश <string.h>

#अगर_अघोषित _LIBC
# define __memmem	memmem
#पूर्ण_अगर

#घोषणा RETURN_TYPE व्योम *
#घोषणा AVAILABLE(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#घोषणा FASTSEARCH(S,C,N) (व्योम*) स_प्रथम ((व्योम *)(S), (C), (N))
#समावेश "str-two-way.h"

#अघोषित memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#घोषणा hash2(p) (((माप_प्रकार)(p)[0] - ((माप_प्रकार)(p)[-1] << 3)) % माप (shift))

/* Fast memmem algorithm with guaranteed linear-time performance.
   Small needles up to size 2 use a dedicated linear search.  Longer needles
   up to size 256 use a novel modified Horspool algorithm.  It hashes pairs
   of characters to quickly skip past mismatches.  The main search loop only
   exits if the last 2 characters match, avoiding unnecessary calls to memcmp
   and allowing for a larger skip if there is no match.  A self-adapting
   filtering check is used to quickly detect mismatches in long needles.
   By limiting the needle length to 256, the shift table can be reduced to 8
   bits per entry, lowering preprocessing overhead and minimizing cache effects.
   The limit also implies worst-case performance is linear.
   Needles larger than 256 characters use the linear-time Two-Way algorithm.  */
व्योम *
__memmem (स्थिर व्योम *haystack, माप_प्रकार hs_len,
	  स्थिर व्योम *needle, माप_प्रकार ne_len)
{
  स्थिर अचिन्हित अक्षर *hs = (स्थिर अचिन्हित अक्षर *) haystack;
  स्थिर अचिन्हित अक्षर *ne = (स्थिर अचिन्हित अक्षर *) needle;

  अगर (ne_len == 0)
    वापस (व्योम *) hs;
  अगर (ne_len == 1)
    वापस (व्योम *) स_प्रथम (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  अगर (hs_len < ne_len)
    वापस शून्य;

  स्थिर अचिन्हित अक्षर *end = hs + hs_len - ne_len;

  अगर (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      क्रम (hs++; hs <= end && hw != nw; )
	hw = hw << 16 | *++hs;
      वापस hw == nw ? (व्योम *)hs - 1 : शून्य;
    }

  /* Use Two-Way algorithm for very long needles.  */
  अगर (__builtin_expect (ne_len > 256, 0))
    वापस two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t shift[256];
  माप_प्रकार tmp, shift1;
  माप_प्रकार m1 = ne_len - 1;
  माप_प्रकार offset = 0;

  स_रखो (shift, 0, माप (shift));
  क्रम (पूर्णांक i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  क्रम ( ; hs <= end; )
    {
      /* Skip past character pairs not in the needle.  */
      करो
	{
	  hs += m1;
	  tmp = shift[hash2 (hs)];
	}
      जबतक (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      अगर (tmp < m1)
	जारी;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      अगर (m1 < 15 || स_भेद (hs + offset, ne + offset, 8) == 0)
	{
	  अगर (स_भेद (hs, ne, m1) == 0)
	    वापस (व्योम *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  वापस शून्य;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
