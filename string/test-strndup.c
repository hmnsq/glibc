/* Test strndup functions.
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

#समावेश <support/check.h>

#घोषणा TEST_MAIN
#समावेश "test-string.h"

अटल व्योम
do_one_test (स्थिर अक्षर *src, माप_प्रकार len, माप_प्रकार n)
{
  अक्षर *dst = strndup (src, n);
  माप_प्रकार s = (len > n ? n: len) * माप (अक्षर);

  TEST_COMPARE_BLOB (dst, s, src, s);

  मुक्त (dst);
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक max_char)
{
  माप_प्रकार i;
  अक्षर *s1;

  align1 &= 7;
  अगर ((align1 + len) * माप (अक्षर) >= page_आकार)
    वापस;

  align2 &= 7;
  अगर ((align2 + len) * माप (अक्षर) >= page_आकार)
    वापस;

  s1 = (अक्षर *) (buf1) + align1;

  क्रम (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  क्रम (i = len + 1; (i + align1) * माप (अक्षर) < page_आकार && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

अटल व्योम
do_page_tests (व्योम)
{
  अक्षर *s1;
  स्थिर माप_प्रकार maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (अक्षर *) buf1 + BUF1PAGES * page_आकार / माप (अक्षर) - maxoffset;

  स_रखो (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  क्रम (माप_प्रकार off1 = 0; off1 < maxoffset; off1++)
    क्रम (माप_प्रकार off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, len, आकार, mode;
  अक्षर *p1 = (अक्षर *) (buf1 + page_आकार) - 512;
  अक्षर *res;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      अगर (mode & 1)
	{
	  आकार = random () & 255;
	  align1 = 512 - आकार - (random () & 15);
	  अगर (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  अगर (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  अगर (mode & 8)
	    len = आकार - (random () & 31);
	  अन्यथा
	    len = 512;
	  अगर (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  अगर (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  अगर (align2 > j)
	    j = align2;
	  अगर (mode & 4)
	    {
	      आकार = random () & 511;
	      अगर (आकार + j > 512)
		आकार = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    आकार = 512 - j;
	  अगर ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; i++)
	{
	  अगर (i == len + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & अक्षर_उच्च;
	      अगर (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (अक्षर *) strndup ((अक्षर *) (p1 + align1), आकार);
	j = len + 1;
	अगर (आकार < j)
	  j = आकार;
	TEST_COMPARE_BLOB (res, j, (अक्षर *) (p1 + align1), j);
	मुक्त (res);
    }
}

पूर्णांक
test_main (व्योम)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  म_लिखो ("\t%s", "strndup");
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, 127);
      do_test (i, i, 16, 16, अक्षर_उच्च);
      do_test (i, 2 * i, 16, 16, 127);
      do_test (2 * i, i, 16, 16, अक्षर_उच्च);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, अक्षर_उच्च);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, अक्षर_उच्च);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  वापस ret;
}

#समावेश <support/test-driver.c>
