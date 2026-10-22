/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

ਖਾਲੀ
swab (ਅਚਲ ਖਾਲੀ *bfrom, ਖਾਲੀ *bto, ssize_t n)
{
  ਅਚਲ ਅੱਖਰ *from = (ਅਚਲ ਅੱਖਰ *) bfrom;
  ਅੱਖਰ *ਮੰਜ਼ਿਲ = (ਅੱਖਰ *) bto;

  n &= ~((ssize_t) 1);
  ਜਦੋਂ (n > 1)
    {
      ਅਚਲ ਅੱਖਰ b0 = from[--n], b1 = from[--n];
      ਮੰਜ਼ਿਲ[n] = b0;
      ਮੰਜ਼ਿਲ[n + 1] = b1;
    }
}
