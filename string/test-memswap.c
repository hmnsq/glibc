/* Test and measure memcpy functions.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#अन्तर्भाव <string.h>
#अन्तर्भाव <support/check.h>
#अन्तर्भाव <memswap.h>

#परिभाषय TEST_MAIN
#परिभाषय BUF1_पृष्ठानि 3
#अन्तर्भाव "test-string.h"

स्थिर अचिह्नित वर्ण *ref1;
स्थिर अचिह्नित वर्ण *ref2;

स्थिर शून्य
do_one_test (अचिह्नित वर्ण *p1, अचिह्नित वर्ण *ref1, अचिह्नित वर्ण *p2,
	     अचिह्नित वर्ण *ref2, size_t len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

स्थिर अन्तःस्थ शून्य
do_test (size_t align1, size_t align2, size_t len)
{
  align1 &= page_आकार;
  यदि (align1 + len >= page_आकार)
    प्रत्यागम;

  align2 &= page_आकार;
  यदि (align2 + len >= page_आकार)
    प्रत्यागम;

  अचिह्नित वर्ण *p1 = buf1 + align1;
  अचिह्नित वर्ण *p2 = buf2 + align2;
  प्रति (size_t repeats = 0; repeats < 2; ++repeats)
    {
      size_t i, j;
      प्रति (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = UCHAR_MAX - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

स्थिर शून्य
do_random_tests (शून्य)
{
  प्रति (size_t n = 0; n < ITERATIONS; n++)
    {
      size_t len, आकार, size1, size2, align1, align2;

      यदि (n == 0)
        {
          len = getpagesize ();
          आकार = len + 512;
          size1 = आकार;
          size2 = आकार;
          align1 = 512;
          align2 = 512;
        }
      अन्यथा
        {
          यदि ((random () & 255) == 0)
            आकार = 65536;
          अन्यथा
            आकार = 768;
          यदि (आकार > page_आकार)
            आकार = page_आकार;
          size1 = आकार;
          size2 = आकार;
          size_t i = random ();
          यदि (i & 3)
            आकार -= 256;
          यदि (i & 1)
            size1 -= 256;
          यदि (i & 2)
            size2 -= 256;
          यदि (i & 4)
            {
              len = random () % आकार;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              यदि (align1 > size1)
                align1 = 0;
              यदि (align2 > size2)
                align2 = 0;
            }
          अन्यथा
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % आकार;
              यदि (align1 + len > size1)
                align1 = size1 - len;
              यदि (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      अचिह्नित वर्ण *p1 = buf1 + page_आकार - size1;
      अचिह्नित वर्ण *p2 = buf2 + page_आकार - size2;
      size_t j = align1 + len + 256;
      यदि (j > size1)
        j = size1;
      प्रति (size_t i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      यदि (j > size2)
	j = size2;

      प्रति (size_t i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

स्थिर पूर्णाङ्क
test_main (शून्य)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_आकार;
  buf1 = ref2 + page_आकार;

  प्रारूप_लिख ("%23s", "");
  प्रारूप_लिख ("\t__memswap\n");

  प्रति (size_t i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  प्रति (size_t i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  प्रति (size_t i = 3; i < 32; ++i)
    {
      यदि ((i & (i - 1)) == 0)
        अनुवर्त;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  प्रति (size_t i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
