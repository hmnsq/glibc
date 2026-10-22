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
#अन्तर्भाव "test-memcpy-support.h"

स्थिर शून्य
do_random_large_tests (शून्य)
{
  size_t i, align1, align2, आकार;
  प्रति (i = 0; i < 32; ++i)
    {
      align1 = random ();
      align2 = random ();
      आकार = (random () % 0x1000000) + 0x200000;
      do_test1 (align1, align2, आकार);
    }

  प्रति (i = 0; i < 128; ++i)
    {
      align1 = random ();
      align2 = random ();
      आकार = (random () % 32768) + 4096;
      do_test1 (align1, align2, आकार);
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i, j;

  test_init ();

  प्रारूप_लिख ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  प्रारूप_लिख ("\t%s", impl->name);
  अक्षरं_लिख ('\n');

  do_test (0, 0, getpagesize () - 1);

  प्रति (i = 0x200000; i <= 0x2000000; i += i)
    {
      प्रति (j = 64; j <= 1024; j <<= 1)
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
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
