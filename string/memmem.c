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

#اگر_غیر_تعریف_شدہ _LIBC
# include <config.h>
#اگر_ختم

#شامل <string.h>

#اگر_غیر_تعریف_شدہ _LIBC
# define __memmem	memmem
#اگر_ختم

#تعریف_کرو RETURN_TYPE خالی *
#تعریف_کرو دستیاب(h, h_l, j, n_l) ((j) <= (h_l) - (n_l))
#تعریف_کرو FASTSEARCH(S,C,N) (خالی*) memchr ((خالی *)(S), (C), (N))
#شامل "str-two-way.h"

#تعریف_منسوخ memmem

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#تعریف_کرو hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % حجم (سرکاؤ))

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
خالی *
__memmem (ثابت خالی *haystack, size_t hs_len,
	  ثابت خالی *needle, size_t ne_len)
{
  ثابت غیرعلامتی حرف *hs = (ثابت غیرعلامتی حرف *) haystack;
  ثابت غیرعلامتی حرف *ne = (ثابت غیرعلامتی حرف *) needle;

  اگر (ne_len == 0)
    واپس (خالی *) hs;
  اگر (ne_len == 1)
    واپس (خالی *) memchr (hs, ne[0], hs_len);

  /* Ensure haystack length is >= needle length.  */
  اگر (hs_len < ne_len)
    واپس تہی;

  ثابت غیرعلامتی حرف *انتہا = hs + hs_len - ne_len;

  اگر (ne_len == 2)
    {
      uint32_t nw = ne[0] << 16 | ne[1], hw = hs[0] << 16 | hs[1];
      برائے (hs++; hs <= انتہا && hw != nw; )
	hw = hw << 16 | *++hs;
      واپس hw == nw ? (خالی *)hs - 1 : تہی;
    }

  /* Use Two-Way algorithm for very long needles.  */
  اگر (__builtin_expect (ne_len > 256, 0))
    واپس two_way_long_needle (hs, hs_len, ne, ne_len);

  uint8_t سرکاؤ[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t انحراف = 0;

  memset (سرکاؤ, 0, حجم (سرکاؤ));
  برائے (صحیح i = 1; i < m1; i++)
    سرکاؤ[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - سرکاؤ[hash2 (ne + m1)];
  سرکاؤ[hash2 (ne + m1)] = m1;

  برائے ( ; hs <= انتہا; )
    {
      /* Skip past character pairs not in the needle.  */
      کرو
	{
	  hs += m1;
	  tmp = سرکاؤ[hash2 (hs)];
	}
      جب (tmp == 0 && hs <= انتہا);

      /* If the match is not at the end of the needle, shift to the end
	 and continue until we match the hash of the needle end.  */
      hs -= tmp;
      اگر (tmp < m1)
	جاری;

      /* Hash of the last 2 characters matches.  If the needle is long,
	 try to quickly filter out mismatches.  */
      اگر (m1 < 15 || memcmp (hs + انحراف, ne + انحراف, 8) == 0)
	{
	  اگر (memcmp (hs, ne, m1) == 0)
	    واپس (خالی *) hs;

	  /* Adjust filter offset when it doesn't find the mismatch.  */
	  انحراف = (انحراف >= 8 ? انحراف : m1) - 8;
	}

      /* Skip based on matching the hash of the needle end.  */
      hs += shift1;
    }
  واپس تہی;
}
libc_hidden_def (__memmem)
static_weak_alias (__memmem, memmem)
libc_hidden_weak (memmem)
