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

#অন্তর্ভাব <unistd.h>

শূন্য
swab (ধ্রুবক শূন্য *bfrom, শূন্য *bto, ssize_t n)
{
  ধ্রুবক অক্ষর *from = (ধ্রুবক অক্ষর *) bfrom;
  অক্ষর *to = (অক্ষর *) bto;

  n &= ~((ssize_t) 1);
  যখন (n > 1)
    {
      ধ্রুবক অক্ষর b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}
