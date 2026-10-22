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

#समावेश <string.h>
#समावेश <support/check.h>
#समावेश <memswap.h>

#घोषणा TEST_MAIN
#घोषणा BUF1PAGES 3
#समावेश "test-string.h"

अटल अचिन्हित अक्षर *ref1;
अटल अचिन्हित अक्षर *ref2;

अटल व्योम
do_one_test (अचिन्हित अक्षर *p1, अचिन्हित अक्षर *ref1, अचिन्हित अक्षर *p2,
	     अचिन्हित अक्षर *ref2, माप_प्रकार len)
{
  __memswap (p1, p2, len);

  TEST_COMPARE_BLOB (p1, len, ref2, len);
  TEST_COMPARE_BLOB (p2, len, ref1, len);
}

अटल अंतरभूत व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len)
{
  align1 &= page_आकार;
  अगर (align1 + len >= page_आकार)
    वापस;

  align2 &= page_आकार;
  अगर (align2 + len >= page_आकार)
    वापस;

  अचिन्हित अक्षर *p1 = buf1 + align1;
  अचिन्हित अक्षर *p2 = buf2 + align2;
  क्रम (माप_प्रकार repeats = 0; repeats < 2; ++repeats)
    {
      माप_प्रकार i, j;
      क्रम (i = 0, j = 1; i < len; i++, j += 23)
	{
	  ref1[i] = p1[i] = j;
	  ref2[i] = p2[i] = अच_अक्षर_उच्च - j;
	}

      do_one_test (p1, ref1, p2, ref2, len);
    }
}

अटल व्योम
do_random_tests (व्योम)
{
  क्रम (माप_प्रकार n = 0; n < ITERATIONS; n++)
    {
      माप_प्रकार len, आकार, size1, size2, align1, align2;

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
          माप_प्रकार i = random ();
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
      अचिन्हित अक्षर *p1 = buf1 + page_आकार - size1;
      अचिन्हित अक्षर *p2 = buf2 + page_आकार - size2;
      माप_प्रकार j = align1 + len + 256;
      अगर (j > size1)
        j = size1;
      क्रम (माप_प्रकार i = 0; i < j; ++i)
	ref1[i] = p1[i] = random () & 255;

      j = align2 + len + 256;
      अगर (j > size2)
	j = size2;

      क्रम (माप_प्रकार i = 0; i < j; ++i)
	ref2[i] = p2[i] = random () & 255;

      do_one_test (p1 + align1, ref1 + align1, p2 + align2, ref2 + align2, len);
    }
}

अटल पूर्णांक
test_main (व्योम)
{
  test_init ();
  /* Use the start of buf1 for reference buffers.  */
  ref1 = buf1;
  ref2 = buf1 + page_आकार;
  buf1 = ref2 + page_आकार;

  म_लिखो ("%23s", "");
  म_लिखो ("\t__memswap\n");

  क्रम (माप_प्रकार i = 0; i < 18; ++i)
    {
      do_test (0, 0, 1 << i);
      do_test (i, 0, 1 << i);
      do_test (0, i, 1 << i);
      do_test (i, i, 1 << i);
    }

  क्रम (माप_प्रकार i = 0; i < 32; ++i)
    {
      do_test (0, 0, i);
      do_test (i, 0, i);
      do_test (0, i, i);
      do_test (i, i, i);
    }

  क्रम (माप_प्रकार i = 3; i < 32; ++i)
    {
      अगर ((i & (i - 1)) == 0)
        जारी;
      do_test (0, 0, 16 * i);
      do_test (i, 0, 16 * i);
      do_test (0, i, 16 * i);
      do_test (i, i, 16 * i);
    }

  क्रम (माप_प्रकार i = 19; i <= 25; ++i)
    {
      do_test (255, 0, 1 << i);
      do_test (0, 4000, 1 << i);
      do_test (0, 255, i);
      do_test (0, 4000, i);
    }

  do_test (0, 0, getpagesize ());

  do_random_tests ();

  वापस 0;
}

#समावेश <support/test-driver.c>
