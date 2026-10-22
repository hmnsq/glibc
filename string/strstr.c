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

#define RETURN_TYPE वर्ण *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((शून्य*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#अन्तर्भाव "str-two-way.h"

#undef म_माला

#ifndef STRSTR
#define STRSTR म_माला
#endif

स्थिर अन्तःस्थ वर्ण *
strstr2 (अचर अचिन्हित वर्ण *hs, अचर अचिन्हित वर्ण *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  लागि (पूर्णाङ्क c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  फर्काऊ h1 == h2 ? (वर्ण *)hs - 2 : रिक्त;
}

स्थिर अन्तःस्थ वर्ण *
strstr3 (अचर अचिन्हित वर्ण *hs, अचर अचिन्हित वर्ण *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  लागि (पूर्णाङ्क c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  फर्काऊ h1 == h2 ? (वर्ण *)hs - 3 : रिक्त;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((माप_प्रकार)(p)[0] - ((माप_प्रकार)(p)[-1] << 3)) % परिमाण (shift))

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
वर्ण *
STRSTR (अचर वर्ण *haystack, अचर वर्ण *needle)
{
  अचर अचिन्हित वर्ण *hs = (अचर अचिन्हित वर्ण *) haystack;
  अचर अचिन्हित वर्ण *ne = (अचर अचिन्हित वर्ण *) needle;

  /* Handle short needle special cases first.  */
  यदि (ne[0] == '\0')
    फर्काऊ (वर्ण *)hs;
  hs = (अचर अचिन्हित वर्ण *)म_अक्षर ((अचर वर्ण*)hs, ne[0]);
  यदि (hs == रिक्त || ne[1] == '\0')
    फर्काऊ (वर्ण*)hs;
  यदि (ne[2] == '\0')
    फर्काऊ strstr2 (hs, ne);
  यदि (ne[3] == '\0')
    फर्काऊ strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  माप_प्रकार ne_len = म_माप ((अचर वर्ण*)ne);
  माप_प्रकार hs_len = __strnlen ((अचर वर्ण*)hs, ne_len | 512);
  यदि (hs_len < ne_len)
    फर्काऊ रिक्त;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  यदि (स_भेद (hs, ne, ne_len) == 0)
    फर्काऊ (वर्ण *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  यदि (__glibc_unlikely (ne_len > 256))
    फर्काऊ two_way_long_needle (hs, hs_len, ne, ne_len);

  अचर अचिन्हित वर्ण *end = hs + hs_len - ne_len;
  uint8_t shift[256];
  माप_प्रकार tmp, shift1;
  माप_प्रकार m1 = ne_len - 1;
  माप_प्रकार offset = 0;

  /* Initialize bad character shift hash table.  */
  स_रखो (shift, 0, परिमाण (shift));
  लागि (पूर्णाङ्क i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  जबसम्म (1)
    {
      यदि (__glibc_unlikely (hs > end))
	{
	  end += __strnlen ((अचर वर्ण*)end + m1 + 1, 2048);
	  यदि (hs > end)
	    फर्काऊ रिक्त;
	}

      /* Skip past character pairs not in the needle.  */
      गर
	{
	  hs += m1;
	  tmp = shift[hash2 (hs)];
	}
      जबसम्म (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      यदि (tmp < m1)
	जारी;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      यदि (m1 < 15 || स_भेद (hs + offset, ne + offset, 8) == 0)
	{
	  यदि (स_भेद (hs, ne, m1) == 0)
	    फर्काऊ (शून्य *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (म_माला)
