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

#അന്തര്ഭാവ <unistd.h>

ശൂന്യം
swab (സ്ഥിരം ശൂന്യം *bfrom, ശൂന്യം *bto, ssize_t n)
{
  സ്ഥിരം അക്ഷരം *from = (സ്ഥിരം അക്ഷരം *) bfrom;
  അക്ഷരം *to = (അക്ഷരം *) bto;

  n &= ~((ssize_t) 1);
  ആകുമ്പോൾ (n > 1)
    {
      സ്ഥിരം അക്ഷരം b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}
