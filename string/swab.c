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

#ಅನ್ತರ್ಭಾವ <unistd.h>

ಶೂನ್ಯ
swab (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *bfrom, ಶೂನ್ಯ *bto, ssize_t n)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *from = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) bfrom;
  ಅಕ್ಷರ *ಗಮ್ಯ = (ಅಕ್ಷರ *) bto;

  n &= ~((ssize_t) 1);
  ಆಗ (n > 1)
    {
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ b0 = from[--n], b1 = from[--n];
      ಗಮ್ಯ[n] = b0;
      ಗಮ್ಯ[n + 1] = b1;
    }
}
