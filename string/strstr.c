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

#ifndef _LIBC
# include <config.h>
#endif

#अन्तर्भाव <string.h>

#define RETURN_TYPE अक्षर *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((शून्य*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#अन्तर्भाव "str-two-way.h"

#undef म_माला

#ifndef STRSTR
#define STRSTR म_माला
#endif

स्थिर ओळीत अक्षर *
strstr2 (स्थिरांक अचिन्हित अक्षर *hs, स्थिरांक अचिन्हित अक्षर *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  साठी (पूर्णांक c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  परत h1 == h2 ? (अक्षर *)hs - 2 : रिक्त;
}

स्थिर ओळीत अक्षर *
strstr3 (स्थिरांक अचिन्हित अक्षर *hs, स्थिरांक अचिन्हित अक्षर *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  साठी (पूर्णांक c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  परत h1 == h2 ? (अक्षर *)hs - 3 : रिक्त;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((माप_प्रकार)(p)[0] - ((माप_प्रकार)(p)[-1] << 3)) % आकार (shift))

/* Fast strstr algorithm with guaranteed linear-time performance.
   Small needles up to size 3 use a dedicated linear search.  Longer needles
   up to size 256 use a novel modified Horspool algorithm.  It hashes pairs
   of characters to quickly skip past mismatches.  The main search loop only
   exits if the last 2 characters match, avoiding unnecessary calls to memcmp
   and allowing for a larger skip if there is no match.  A self-adapting
   filtering check is used to quickly detect mismatches in long needles.
   By limiting the needle length to 256, the shift table can be reduced to 8
   bits per entry, lowering preprocessing overhead and minimizing cache effects.
   The limit also implies worst-case performance is linear.
   Needles larger than 256 characters use the linear-time Two-Way algorithm.  */
अक्षर *
STRSTR (स्थिरांक अक्षर *haystack, स्थिरांक अक्षर *needle)
{
  स्थिरांक अचिन्हित अक्षर *hs = (स्थिरांक अचिन्हित अक्षर *) haystack;
  स्थिरांक अचिन्हित अक्षर *ne = (स्थिरांक अचिन्हित अक्षर *) needle;

  /* Handle short needle special cases first.  */
  जर (ne[0] == '\0')
    परत (अक्षर *)hs;
  hs = (स्थिरांक अचिन्हित अक्षर *)म_अक्षर ((स्थिरांक अक्षर*)hs, ne[0]);
  जर (hs == रिक्त || ne[1] == '\0')
    परत (अक्षर*)hs;
  जर (ne[2] == '\0')
    परत strstr2 (hs, ne);
  जर (ne[3] == '\0')
    परत strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  माप_प्रकार ne_len = म_माप ((स्थिरांक अक्षर*)ne);
  माप_प्रकार hs_len = __strnlen ((स्थिरांक अक्षर*)hs, ne_len | 512);
  जर (hs_len < ne_len)
    परत रिक्त;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  जर (स_भेद (hs, ne, ne_len) == 0)
    परत (अक्षर *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  जर (__glibc_unlikely (ne_len > 256))
    परत two_way_long_needle (hs, hs_len, ne, ne_len);

  स्थिरांक अचिन्हित अक्षर *end = hs + hs_len - ne_len;
  uint8_t shift[256];
  माप_प्रकार tmp, shift1;
  माप_प्रकार m1 = ne_len - 1;
  माप_प्रकार offset = 0;

  /* Initialize bad character shift hash table.  */
  स_रखो (shift, 0, आकार (shift));
  साठी (पूर्णांक i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  पर्यंत (1)
    {
      जर (__glibc_unlikely (hs > end))
	{
	  end += __strnlen ((स्थिरांक अक्षर*)end + m1 + 1, 2048);
	  जर (hs > end)
	    परत रिक्त;
	}

      /* Skip past character pairs not in the needle.  */
      करा
	{
	  hs += m1;
	  tmp = shift[hash2 (hs)];
	}
      पर्यंत (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      जर (tmp < m1)
	सुरूठेवा;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      जर (m1 < 15 || स_भेद (hs + offset, ne + offset, 8) == 0)
	{
	  जर (स_भेद (hs, ne, m1) == 0)
	    परत (शून्य *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (म_माला)
