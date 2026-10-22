/* Copyright (C) 2000-2026 Free Software Foundation, Inc.
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

#ಅನ್ತರ್ಭಾವ <byteswap.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

ಬಾಹ್ಯ unsigned long long ಪೂರ್ಣಾಙ್ಕ wash (unsigned long long ಪೂರ್ಣಾಙ್ಕ a);

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  /* Test the functions with constant arguments.  */
  ಯದಿ (bswap_16 (0x1234) != 0x3412)
    {
      puts ("bswap_16 (constant) flunked");
      result = 1;
    }
  ಯದಿ (bswap_32 (0x12345678) != 0x78563412)
    {
      puts ("bswap_32 (constant) flunked");
      result = 1;
    }
  ಯದಿ (bswap_64 (0x1234567890abcdefULL) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (constant) flunked");
      result = 1;
    }

  /* Test the functions with non-constant arguments.  */
  ಯದಿ (bswap_16 (wash (0x1234)) != 0x3412)
    {
      puts ("bswap_16 (non-constant) flunked");
      result = 1;
    }
  ಯದಿ (bswap_32 (wash (0x12345678)) != 0x78563412)
    {
      puts ("bswap_32 (non-constant) flunked");
      result = 1;
    }
  ಯದಿ (bswap_64 (wash (0x1234567890abcdefULL)) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (non-constant) flunked");
      result = 1;
    }

  ಪ್ರತ್ಯಾಗಮ result;
}


unsigned long long ಪೂರ್ಣಾಙ್ಕ
wash (unsigned long long ಪೂರ್ಣಾಙ್ಕ a)
{
  /* Do nothing.  This function simply exists to avoid that the compiler
     regards the argument to the bswap_*() functions as constant.  */
  ಪ್ರತ್ಯಾಗಮ a + 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
