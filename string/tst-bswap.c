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

#अन्तर्भाव <byteswap.h>
#अन्तर्भाव <stdio.h>

बाह्य अचिन्हित दीर्घ दीर्घ पूर्णांक wash (अचिन्हित दीर्घ दीर्घ पूर्णांक a);

पूर्णांक
do_test (शून्य)
{
  पूर्णांक result = 0;

  /* Test the functions with constant arguments.  */
  जर (bswap_16 (0x1234) != 0x3412)
    {
      माला_दो ("bswap_16 (constant) flunked");
      result = 1;
    }
  जर (bswap_32 (0x12345678) != 0x78563412)
    {
      माला_दो ("bswap_32 (constant) flunked");
      result = 1;
    }
  जर (bswap_64 (0x1234567890abcdefULL) != 0xefcdab9078563412ULL)
    {
      माला_दो ("bswap_64 (constant) flunked");
      result = 1;
    }

  /* Test the functions with non-constant arguments.  */
  जर (bswap_16 (wash (0x1234)) != 0x3412)
    {
      माला_दो ("bswap_16 (non-constant) flunked");
      result = 1;
    }
  जर (bswap_32 (wash (0x12345678)) != 0x78563412)
    {
      माला_दो ("bswap_32 (non-constant) flunked");
      result = 1;
    }
  जर (bswap_64 (wash (0x1234567890abcdefULL)) != 0xefcdab9078563412ULL)
    {
      माला_दो ("bswap_64 (non-constant) flunked");
      result = 1;
    }

  परत result;
}


अचिन्हित दीर्घ दीर्घ पूर्णांक
wash (अचिन्हित दीर्घ दीर्घ पूर्णांक a)
{
  /* Do nothing.  This function simply exists to avoid that the compiler
     regards the argument to the bswap_*() functions as constant.  */
  परत a + 0;
}

#अन्तर्भाव <support/test-driver.c>
