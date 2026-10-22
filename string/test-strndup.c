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
do_one_test (ध्रुव वर्ण *src, माप_प्रकार len, माप_प्रकार n)
{
  वर्ण *dst = strndup (src, n);
  माप_प्रकार s = (len > n ? n: len) * परिमाण (वर्ण);

  TEST_COMPARE_BLOB (dst, s, src, s);

  मुक्त (dst);
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, माप_प्रकार n, पूर्णाङ्क max_char)
{
  माप_प्रकार i;
  वर्ण *s1;

  align1 &= 7;
  यदि ((align1 + len) * परिमाण (वर्ण) >= page_size)
    प्रत्यागम;

  align2 &= 7;
  यदि ((align2 + len) * परिमाण (वर्ण) >= page_size)
    प्रत्यागम;

  s1 = (वर्ण *) (buf1) + align1;

  प्रति (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  प्रति (i = len + 1; (i + align1) * परिमाण (वर्ण) < page_size && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

स्थिर शून्य
do_page_tests (शून्य)
{
  वर्ण *s1;
  ध्रुव माप_प्रकार maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (वर्ण *) buf1 + BUF1PAGES * page_size / परिमाण (वर्ण) - maxoffset;

  स_रखो (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  प्रति (माप_प्रकार off1 = 0; off1 < maxoffset; off1++)
    प्रति (माप_प्रकार off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, len, size, mode;
  वर्ण *p1 = (वर्ण *) (buf1 + page_size) - 512;
  वर्ण *res;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      mode = random ();
      यदि (mode & 1)
	{
	  size = random () & 255;
	  align1 = 512 - size - (random () & 15);
	  यदि (mode & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  यदि (mode & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  यदि (mode & 8)
	    len = size - (random () & 31);
	  अन्यथा
	    len = 512;
	  यदि (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  यदि (mode & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  यदि (align2 > j)
	    j = align2;
	  यदि (mode & 4)
	    {
	      size = random () & 511;
	      यदि (size + j > 512)
		size = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    size = 512 - j;
	  यदि ((mode & 8) && len + j >= 512)
	    len = 512 - j - (random () & 7);
	}
      j = len + align1 + 64;
      यदि (j > 512)
	j = 512;
      प्रति (i = 0; i < j; i++)
	{
	  यदि (i == len + align1)
	    p1[i] = 0;
	  अन्यथा
	    {
	      p1[i] = random () & अक्षर_उच्च;
	      यदि (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (वर्ण *) strndup ((वर्ण *) (p1 + align1), size);
	j = len + 1;
	यदि (size < j)
	  j = size;
	TEST_COMPARE_BLOB (res, j, (वर्ण *) (p1 + align1), j);
	मुक्त (res);
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  माप_प्रकार i;

  test_init ();

  म_लिखो ("%28s", "");
  म_लिखो ("\t%s", "strndup");
  अक्षर_दो ('\n');

  प्रति (i = 1; i < 8; ++i)
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

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (0, 0, 4 << i, 8 << i, 127);
      do_test (0, 0, 16 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 4 << i, 8 << i, 127);
      do_test (8 - i, 2 * i, 16 << i, 8 << i, 127);
    }

  do_random_tests ();
  do_page_tests ();
  प्रत्यागम ret;
}

#अन्तर्भाव <support/test-driver.c>
