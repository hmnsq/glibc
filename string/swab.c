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

#ଅନ୍ତର୍ଭାଵ <unistd.h>

ଶୂନ୍ୟ
swab (ଅଚଳ ଶୂନ୍ୟ *bfrom, ଶୂନ୍ୟ *bto, ssize_t n)
{
  ଅଚଳ ଅକ୍ଷର *from = (ଅଚଳ ଅକ୍ଷର *) bfrom;
  ଅକ୍ଷର *to = (ଅକ୍ଷର *) bto;

  n &= ~((ssize_t) 1);
  ଯେତେବେଳେ (n > 1)
    {
      ଅଚଳ ଅକ୍ଷର b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}
