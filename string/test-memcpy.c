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
#समावेश "test-memcpy-support.h"

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len, size1, size2, आकार;
  पूर्णांक c;
  अचिन्हित अक्षर *p1, *p2;
  अचिन्हित अक्षर *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      अगर (n == 0)
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
          अगर ((random () & 255) == 0)
            आकार = 65536;
          अन्यथा
            आकार = 768;
          अगर (आकार > page_आकार)
            आकार = page_आकार;
          size1 = आकार;
          size2 = आकार;
          i = random ();
          अगर (i & 3)
            आकार -= 256;
          अगर (i & 1)
            size1 -= 256;
          अगर (i & 2)
            size2 -= 256;
          अगर (i & 4)
            {
              len = random () % आकार;
              align1 = size1 - len - (random () & 31);
              align2 = size2 - len - (random () & 31);
              अगर (align1 > size1)
                align1 = 0;
              अगर (align2 > size2)
                align2 = 0;
            }
          अन्यथा
            {
              align1 = random () & 63;
              align2 = random () & 63;
              len = random () % आकार;
              अगर (align1 + len > size1)
                align1 = size1 - len;
              अगर (align2 + len > size2)
                align2 = size2 - len;
            }
        }
      p1 = buf1 + page_आकार - size1;
      p2 = buf2 + page_आकार - size2;
      c = random () & 255;
      j = align1 + len + 256;
      अगर (j > size1)
        j = size1;
      क्रम (i = 0; i < j; ++i)
        p1[i] = random () & 255;

      FOR_EACH_IMPL (impl, 1)
      {
        j = align2 + len + 256;
        अगर (j > size2)
          j = size2;
        स_रखो (p2, c, j);
        res = (अचिन्हित अक्षर *)CALL (impl, (अक्षर *)(p2 + align2),
                                     (अक्षर *)(p1 + align1), len);
        अगर (res != MEMCPY_परिणाम (p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - wrong result in function %s (%zd, %zd, "
                   "%zd) %p != %p",
                   n, impl->name, align1, align2, len, res,
                   MEMCPY_परिणाम (p2 + align2, len));
            ret = 1;
          }
        क्रम (i = 0; i < align2; ++i)
          {
            अगर (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage before, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                अवरोध;
              }
          }
        क्रम (i = align2 + len; i < j; ++i)
          {
            अगर (p2[i] != c)
              {
                error (0, 0,
                       "Iteration %zd - garbage after, %s (%zd, %zd, %zd)", n,
                       impl->name, align1, align2, len);
                ret = 1;
                अवरोध;
              }
          }
        अगर (स_भेद (p1 + align1, p2 + align2, len))
          {
            error (0, 0,
                   "Iteration %zd - different strings, %s (%zd, %zd, %zd)", n,
                   impl->name, align1, align2, len);
            ret = 1;
          }
      }
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i, j;

  test_init ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
  म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }
  क्रम (i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  क्रम (i = 3; i < 32; ++i)
    {
      अगर ((i & (i - 1)) == 0)
        जारी;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  क्रम (i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());
  do_random_tests ();

  do_test1 (0, 0, 0x100000);
  do_test1 (0, 0, 0x2000000);

  क्रम (i = 4096; i < 32768; i += 4096)
    {
      क्रम (j = 1; j <= 1024; j <<= 1)
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
        }
    }

  क्रम (i = 0x300000; i < 0x2000000; i += 0x235689)
    {
      क्रम (j = 64; j <= 1024; j <<= 1)
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
        }
    }

  वापस ret;
}

#समावेश <support/test-driver.c>
