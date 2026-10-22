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

#اگر_غیر_تعریف_شدہ _LIBC
# include <config.h>
#اگر_ختم

#شامل <string.h>

#تعریف_کرو RETURN_TYPE حرف *
#تعریف_کرو دستیاب(h, h_l, j, n_l)			\
  (((j) + (n_l) <= (h_l)) \
   || ((h_l) += __strnlen ((خالی*)((h) + (h_l)), (n_l) + 512), \
       (j) + (n_l) <= (h_l)))
#شامل "str-two-way.h"

#تعریف_منسوخ لڑی_تلاش

#اگر_غیر_تعریف_شدہ STRSTR
#تعریف_کرو STRSTR لڑی_تلاش
#اگر_ختم

ساکن اندرونی حرف *
strstr2 (ثابت غیرعلامتی حرف *hs, ثابت غیرعلامتی حرف *ne)
{
  uint32_t h1 = (ne[0] << 16) | ne[1];
  uint32_t h2 = 0;
  برائے (صحیح c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 << 16) | c;
  واپس h1 == h2 ? (حرف *)hs - 2 : تہی;
}

ساکن اندرونی حرف *
strstr3 (ثابت غیرعلامتی حرف *hs, ثابت غیرعلامتی حرف *ne)
{
  uint32_t h1 = ((uint32_t)ne[0] << 24) | (ne[1] << 16) | (ne[2] << 8);
  uint32_t h2 = 0;
  برائے (صحیح c = hs[0]; h1 != h2 && c != 0; c = *++hs)
      h2 = (h2 | c) << 8;
  واپس h1 == h2 ? (حرف *)hs - 3 : تہی;
}

/* Hash character pairs so a small shift table can be used.  All bits of
   p[0] are included, but not all bits from p[-1].  So if two equal hashes
   match on p[-1], p[0] matches too.  Hash collisions are harmless and result
   in smaller shifts.  */
#تعریف_کرو hash2(p) (((size_t)(p)[0] - ((size_t)(p)[-1] << 3)) % حجم (سرکاؤ))

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
  ثابت غیرعلامتی حرف *hs = (ثابت غیرعلامتی حرف *) haystack;
  ثابت غیرعلامتی حرف *ne = (ثابت غیرعلامتی حرف *) needle;

  /* Handle short needle special cases first.  */
  اگر (ne[0] == '\0')
    واپس (حرف *)hs;
  hs = (ثابت غیرعلامتی حرف *)strchr ((ثابت حرف*)hs, ne[0]);
  اگر (hs == تہی || ne[1] == '\0')
    واپس (حرف*)hs;
  اگر (ne[2] == '\0')
    واپس strstr2 (hs, ne);
  اگر (ne[3] == '\0')
    واپس strstr3 (hs, ne);

  /* Ensure haystack length is at least as long as needle length.
     Since a match may occur early on in a huge haystack, use strnlen
     and read ahead a few cachelines for improved performance.  */
  size_t ne_len = لڑی_لمبائی ((ثابت حرف*)ne);
  size_t hs_len = __strnlen ((ثابت حرف*)hs, ne_len | 512);
  اگر (hs_len < ne_len)
    واپس تہی;

  /* Check whether we have a match.  This improves performance since we
     avoid initialization overheads.  */
  اگر (memcmp (hs, ne, ne_len) == 0)
    واپس (حرف *) hs;

  /* Use Two-Way algorithm for very long needles.  */
  اگر (__glibc_unlikely (ne_len > 256))
    واپس two_way_long_needle (hs, hs_len, ne, ne_len);

  ثابت غیرعلامتی حرف *انتہا = hs + hs_len - ne_len;
  uint8_t سرکاؤ[256];
  size_t tmp, shift1;
  size_t m1 = ne_len - 1;
  size_t انحراف = 0;

  /* Initialize bad character shift hash table.  */
  memset (سرکاؤ, 0, حجم (سرکاؤ));
  برائے (صحیح i = 1; i < m1; i++)
    سرکاؤ[hash2 (ne + i)] = i;
  /* Shift1 is the amount we can skip after matching the hash of the
     needle end but not the full needle.  */
  shift1 = m1 - سرکاؤ[hash2 (ne + m1)];
  سرکاؤ[hash2 (ne + m1)] = m1;

  جب (1)
    {
      اگر (__glibc_unlikely (hs > انتہا))
	{
	  انتہا += __strnlen ((ثابت حرف*)انتہا + m1 + 1, 2048);
	  اگر (hs > انتہا)
	    واپس تہی;
	}

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
}
libc_hidden_builtin_def (لڑی_تلاش)
