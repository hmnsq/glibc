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

#அந்தர்பாவ <unistd.h>

வெறுமை
swab (மாறிலி வெறுமை *bfrom, வெறுமை *bto, ssize_t n)
{
  மாறிலி எழுத்து *from = (மாறிலி எழுத்து *) bfrom;
  எழுத்து *to = (எழுத்து *) bto;

  n &= ~((ssize_t) 1);
  போது (n > 1)
    {
      மாறிலி எழுத்து b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}
