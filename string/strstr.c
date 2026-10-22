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

#جيڪڏهن_وصف_نه_ٿيل _LIBC
# include <config.h>
#جيڪڏهن_پورو

#ضمن <string.h>

#وصف_ڪريو RETURN_TYPE حرف *
#وصف_ڪريو موجود(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((فراغ*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#ضمن "str-two-way.h"

#وصف_رد لڙي_ڳولا

#جيڪڏهن_وصف_نه_ٿيل STRSTR
#وصف_ڪريو STRSTR لڙي_ڳولا
#جيڪڏهن_پورو

ساكن مضمن حرف *
strstr2 (ثابت بنانشان حرف *hs, ثابت بنانشان حرف *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  لكل (صحيح c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  أرجع h1 == h2 ? (حرف *)hs - 2 : عدم;
}

ساكن مضمن حرف *
strstr3 (ثابت بنانشان حرف *hs, ثابت بنانشان حرف *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  لكل (صحيح c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  أرجع h1 == h2 ? (حرف *)hs - 3 : عدم;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#وصف_ڪريو hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % حجم (سرڪايو))

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
حرف *
STRSTR (ثابت حرف *haystack, ثابت حرف *needle)
{
  ثابت بنانشان حرف *hs = (ثابت بنانشان حرف *) haystack;
  ثابت بنانشان حرف *ne = (ثابت بنانشان حرف *) needle;

  /* Handle short needle special cases first.  */
  إذا (ne[0] == '\0')
    أرجع (حرف *)hs;
  hs = (ثابت بنانشان حرف *)strchr ((ثابت حرف*)hs, ne[0]);
  إذا (hs == عدم || ne[1] == '\0')
    أرجع (حرف*)hs;
  إذا (ne[2] == '\0')
    أرجع strstr2 (hs, ne);
  إذا (ne[3] == '\0')
    أرجع strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = لڙي_ڊيگهه ((ثابت حرف*)ne);
  size_t hs_len = __strnlen ((ثابت حرف*)hs, ne_len | 512);
  إذا (hs_len < ne_len)
    أرجع عدم;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  إذا (memcmp (hs, ne, ne_len) == 0)
    أرجع (حرف *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  إذا (__glibc_unlikely (ne_len > 256))
    أرجع two_way_long_needle (hs, hs_len, ne, ne_len);

  ثابت بنانشان حرف *پڇاڙي = hs + hs_len - ne_len;
  uint8_t سرڪايو[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t وٿي = 0;

  /* Initialize bad character shift hash table.  */
  memset (سرڪايو, 0, حجم (سرڪايو));
  لكل (صحيح i = 1; i < m1; i++)
    سرڪايو[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - سرڪايو[hash2 (ne + m1)];
  سرڪايو[hash2 (ne + m1)] = m1;

  طالما (1)
    {
      إذا (__glibc_unlikely (hs > پڇاڙي))
	{
	  پڇاڙي += __strnlen ((ثابت حرف*)پڇاڙي + m1 + 1, 2048);
	  إذا (hs > پڇاڙي)
	    أرجع عدم;
	}

      /* Skip past character pairs not in the needle.  */
      افعل
	{
	  hs += m1;
	  tmp = سرڪايو[hash2 (hs)];
	}
      طالما (tmp == 0 && hs <= پڇاڙي);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      إذا (tmp < m1)
	استمر;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      إذا (m1 < 15 || memcmp (hs + وٿي, ne + وٿي, 8) == 0)
	{
	  إذا (memcmp (hs, ne, m1) == 0)
	    أرجع (فراغ *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  وٿي = (وٿي >= 8 ? وٿي : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
}
libc_hidden_builtin_def (لڙي_ڳولا)
