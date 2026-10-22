/* Test and measure memcpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

/* test-memcpy-support.h contains all test functions.  */
#അന്തര്ഭാവ "test-memcpy-support.h"

സ്ഥിതം ശൂന്യം
do_random_large_tests (ശൂന്യം)
{
  size_t i, align1, align2, size;
  വേണ്ടി (i = 0; i < 32; ++i)
    {
      align1 = random ();
      align2 = random ();
      size = (random () % 0x1000000) + 0x200000;
      do_test1 (align1, align2, size);
    }

  വേണ്ടി (i = 0; i < 128; ++i)
    {
      align1 = random ();
      align2 = random ();
      size = (random () % 32768) + 4096;
      do_test1 (align1, align2, size);
    }
}

പൂർണ്ണസംഖ്യ
test_main (ശൂന്യം)
{
  size_t i, j;

  test_init ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  printf ("\t%s", impl->name);
  putchar ('\n');

  do_test (0, 0, getpagesize () - 1);

  വേണ്ടി (i = 0x200000; i <= 0x2000000; i += i)
    {
      വേണ്ടി (j = 64; j <= 1024; j <<= 1)
        {
          do_test1 (0, j, i);
          do_test1 (4095, j, i);
          do_test1 (4096 - j, 0, i);

          do_test1 (0, j - 1, i);
          do_test1 (4095, j - 1, i);
          do_test1 (4096 - j - 1, 0, i);

          do_test1 (0, j + 1, i);
          do_test1 (4095, j + 1, i);
          do_test1 (4096 - j, 1, i);

          do_test1 (0, j, i + 1);
          do_test1 (4095, j, i + 1);
          do_test1 (4096 - j, 0, i + 1);

          do_test1 (0, j - 1, i + 1);
          do_test1 (4095, j - 1, i + 1);
          do_test1 (4096 - j - 1, 0, i + 1);

          do_test1 (0, j + 1, i + 1);
          do_test1 (4095, j + 1, i + 1);
          do_test1 (4096 - j, 1, i + 1);

          do_test1 (0, j, i - 1);
          do_test1 (4095, j, i - 1);
          do_test1 (4096 - j, 0, i - 1);

          do_test1 (0, j - 1, i - 1);
          do_test1 (4095, j - 1, i - 1);
          do_test1 (4096 - j - 1, 0, i - 1);

          do_test1 (0, j + 1, i - 1);
          do_test1 (4095, j + 1, i - 1);
          do_test1 (4096 - j, 1, i - 1);
        }
    }

  do_random_large_tests ();
  തിരികെ ret;
}

#അന്തര്ഭാവ <support/test-driver.c>
