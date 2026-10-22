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

#अन्तर्भाव <support/check.h>

#define TEST_MAIN
#अन्तर्भाव "test-string.h"

स्थिर शून्य
do_one_test (स्थिरांक अक्षर *src, माप_प्रकार len, माप_प्रकार n)
{
  अक्षर *dst = strndup (src, n);
  माप_प्रकार s = (len > n ? n: len) * आकार (अक्षर);

  TEST_COMPARE_BLOB (dst, s, src, s);

  मुक्त (dst);
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णांक max_char)
{
  माप_प्रकार i;
  अक्षर *s1;

  align1 &= 7;
  जर ((align1 + len) * आकार (अक्षर) >= page_size)
    परत;

  align2 &= 7;
  जर ((align2 + len) * आकार (अक्षर) >= page_size)
    परत;

  s1 = (अक्षर *) (buf1) + align1;

  साठी (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  साठी (i = len + 1; (i + align1) * आकार (अक्षर) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

स्थिर शून्य
do_page_tests (शून्य)
{
  अक्षर *s1;
  स्थिरांक माप_प्रकार maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (अक्षर *) buf1 + BUF1PAGES * page_size / आकार (अक्षर) - maxoffset;

  स_रखो (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  साठी (माप_प्रकार off1 = 0; off1 < maxoffset; off1++)
    साठी (माप_प्रकार off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, len, size, mode;
  अक्षर *p1 = (अक्षर *) (buf1 + page_size) - 512;
  अक्षर *res;

  साठी (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      जर (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  जर (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  जर (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  जर (mode & 8)
	    len = size - (random () & 31);
	  अन्यथा
	    len = 512;
	  जर (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  जर (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  जर (align2 > j)
	    j = align2;
	  जर (mode & 4)
	    {
	      size = random () & 511;
	      जर (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    size = 512 - j;
	  जर ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      जर (j > 512)
	j = 512;
      साठी (i = 0; i < j; i++)
	{
	  जर (i == len + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & अक्षर_उच्च;
	      जर (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (अक्षर *) strndup ((अक्षर *) (p1 + align1), size);
	j = len + 1;
	जर (size < j)
	  j = size;
	TEST_COMPARE_BLOB (res, j, (अक्षर *) (p1 + align1), j);
	मुक्त (res);
    }
}

पूर्णांक
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  म_लिखो ("\t%s", "strndup");
  अक्षर_दो ('\n');

  साठी (i = 1; i < 8; ++i)
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

  साठी (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
