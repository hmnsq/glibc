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

ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ wash (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ a);

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  /* Test the functions with constant arguments.  */
  ಆದರೆ (bswap_16 (0x1234) != 0x3412)
    {
      puts ("bswap_16 (constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }
  ಆದರೆ (bswap_32 (0x12345678) != 0x78563412)
    {
      puts ("bswap_32 (constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }
  ಆದರೆ (bswap_64 (0x1234567890abcdefULL) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }

  /* Test the functions with non-constant arguments.  */
  ಆದರೆ (bswap_16 (wash (0x1234)) != 0x3412)
    {
      puts ("bswap_16 (non-constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }
  ಆದರೆ (bswap_32 (wash (0x12345678)) != 0x78563412)
    {
      puts ("bswap_32 (non-constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }
  ಆದರೆ (bswap_64 (wash (0x1234567890abcdefULL)) != 0xefcdab9078563412ULL)
    {
      puts ("bswap_64 (non-constant) flunked");
      ಫಲಿತಾಂಶ = 1;
    }

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}


ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ
wash (ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ a)
{
  /* Do nothing.  This function simply exists to avoid that the compiler
     regards the argument to the bswap_*() functions as constant.  */
  ಹಿಂತಿರುಗಿ a + 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
