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

#অন্তর্ভাৱ <string.h>

#define RETURN_TYPE ৱর্ণ *
#define AVAILABLE(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((শূন্য*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#অন্তর্ভাৱ "str-two-way.h"

#undef strstr

#ifndef STRSTR
#define STRSTR strstr
#endif

স্থির অন্তঃস্থ ৱর্ণ *
strstr2 (ধ্রুৱ unsigned ৱর্ণ *hs, ধ্রুৱ unsigned ৱর্ণ *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  বাবে (পূর্ণাঙ্ক c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  ঘূৰাই h1 == h2 ? (ৱর্ণ *)hs - 2 : রিক্ত;
}

স্থির অন্তঃস্থ ৱর্ণ *
strstr3 (ধ্রুৱ unsigned ৱর্ণ *hs, ধ্রুৱ unsigned ৱর্ণ *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  বাবে (পূর্ণাঙ্ক c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  ঘূৰাই h1 == h2 ? (ৱর্ণ *)hs - 3 : রিক্ত;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#define hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % পরিমাণ (shift))

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
ৱর্ণ *
STRSTR (ধ্রুৱ ৱর্ণ *haystack, ধ্রুৱ ৱর্ণ *needle)
{
  ধ্রুৱ unsigned ৱর্ণ *hs = (ধ্রুৱ unsigned ৱর্ণ *) haystack;
  ধ্রুৱ unsigned ৱর্ণ *ne = (ধ্রুৱ unsigned ৱর্ণ *) needle;

  /* Handle short needle special cases first.  */
  যদি (ne[0] == '\0')
    ঘূৰাই (ৱর্ণ *)hs;
  hs = (ধ্রুৱ unsigned ৱর্ণ *)strchr ((ধ্রুৱ ৱর্ণ*)hs, ne[0]);
  যদি (hs == রিক্ত || ne[1] == '\0')
    ঘূৰাই (ৱর্ণ*)hs;
  যদি (ne[2] == '\0')
    ঘূৰাই strstr2 (hs, ne);
  যদি (ne[3] == '\0')
    ঘূৰাই strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = strlen ((ধ্রুৱ ৱর্ণ*)ne);
  size_t hs_len = __strnlen ((ধ্রুৱ ৱর্ণ*)hs, ne_len | 512);
  যদি (hs_len < ne_len)
    ঘূৰাই রিক্ত;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  যদি (memcmp (hs, ne, ne_len) == 0)
    ঘূৰাই (ৱর্ণ *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  যদি (__glibc_unlikely (ne_len > 256))
    ঘূৰাই two_way_long_needle (hs, hs_len, ne, ne_len);

  ধ্রুৱ unsigned ৱর্ণ *end = hs + hs_len - ne_len;
  uint8_t shift[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t offset = 0;

  /* Initialize bad character shift hash table.  */
  memset (shift, 0, পরিমাণ (shift));
  বাবে (পূর্ণাঙ্ক i = 1; i < m1; i++)
    shift[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - shift[hash2 (ne + m1)];
  shift[hash2 (ne + m1)] = m1;

  যেতিয়ালৈ (1)
    {
      যদি (__glibc_unlikely (hs > end))
	{
	  end += __strnlen ((ধ্রুৱ ৱর্ণ*)end + m1 + 1, 2048);
	  যদি (hs > end)
	    ঘূৰাই রিক্ত;
	}

      /* Skip past character pairs not in the needle.  */
      কৰা
	{
	  hs += m1;
	  tmp = shift[hash2 (hs)];
	}
      যেতিয়ালৈ (tmp == 0 && hs <= end);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      যদি (tmp < m1)
	অনুৱর্ত;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      যদি (m1 < 15 || memcmp (hs + offset, ne + offset, 8) == 0)
	{
	  যদি (memcmp (hs, ne, m1) == 0)
	    ঘূৰাই (শূন্য *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  offset = (offset >= 8 ? offset : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (strstr)
