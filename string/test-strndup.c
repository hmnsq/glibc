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

#परिभाषय TEST_MAIN
#अन्तर्भाव "test-string.h"

स्थिर शून्य
do_one_test (ध्रुव वर्ण *src, size_t len, size_t n)
{
  वर्ण *dst = strndup (src, n);
  size_t s = (len > n ? n: len) * परिमाण (वर्ण);

  TEST_COMPARE_BLOB (dst, s, src, s);

  मुक्त (dst);
}

स्थिर शून्य
do_test (size_t align1, size_t align2, size_t len, size_t n, पूर्णाङ्क max_char)
{
  size_t i;
  वर्ण *s1;

  align1 &= 7;
  यदि ((align1 + len) * परिमाण (वर्ण) >= page_आकार)
    प्रत्यागम;

  align2 &= 7;
  यदि ((align2 + len) * परिमाण (वर्ण) >= page_आकार)
    प्रत्यागम;

  s1 = (वर्ण *) (buf1) + align1;

  प्रति (i = 0; i < len; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len] = 0;
  प्रति (i = len + 1; (i + align1) * परिमाण (वर्ण) < page_आकार && i < len + 64;
       ++i)
    s1[i] = 32 + 32 * i % (max_char - 32);

  do_one_test (s1, len, n);
}

स्थिर शून्य
do_page_tests (शून्य)
{
  वर्ण *s1;
  ध्रुव size_t maxoffset = 64;

  /* Put s1 at the maxoffset from the edge of buf1's last page.  */
  s1 = (वर्ण *) buf1 + BUF1_पृष्ठानि * page_आकार / परिमाण (वर्ण) - maxoffset;

  स्मृतिं_पूरय (s1, 'a', maxoffset - 1);
  s1[maxoffset - 1] = '\0';

  /* Both strings are bounded to a page with read/write access and the next
     page is protected with PROT_NONE (meaning that any access outside of the
     page regions will trigger an invalid memory access).

     The loop copies the string s1 for all possible offsets up to maxoffset
     for both inputs with a size larger than s1 (so memory access outside the
     expected memory regions might trigger invalid access).  */

  प्रति (size_t off1 = 0; off1 < maxoffset; off1++)
    प्रति (size_t off2 = 0; off2 < maxoffset; off2++)
      do_one_test (s1 + off1, maxoffset - off1 - 1,
		   maxoffset + (maxoffset - off2));
}

स्थिर शून्य
do_random_tests (शून्य)
{
  size_t i, j, n, align1, align2, len, आकार, बहुलकम्;
  वर्ण *p1 = (वर्ण *) (buf1 + page_आकार) - 512;
  वर्ण *res;

  प्रति (n = 0; n < ITERATIONS; n++)
    {
      बहुलकम् = random ();
      यदि (बहुलकम् & 1)
	{
	  आकार = random () & 255;
	  align1 = 512 - आकार - (random () & 15);
	  यदि (बहुलकम् & 2)
	    align2 = align1 - (random () & 24);
	  अन्यथा
	    align2 = align1 - (random () & 31);
	  यदि (बहुलकम् & 4)
	    {
	      j = align1;
	      align1 = align2;
	      align2 = j;
	    }
	  यदि (बहुलकम् & 8)
	    len = आकार - (random () & 31);
	  अन्यथा
	    len = 512;
	  यदि (len >= 512)
	    len = random () & 511;
	}
      अन्यथा
	{
	  align1 = random () & 31;
	  यदि (बहुलकम् & 2)
	    align2 = random () & 31;
	  अन्यथा
	    align2 = align1 + (random () & 24);
	  len = random () & 511;
	  j = align1;
	  यदि (align2 > j)
	    j = align2;
	  यदि (बहुलकम् & 4)
	    {
	      आकार = random () & 511;
	      यदि (आकार + j > 512)
		आकार = 512 - j - (random () & 31);
	    }
	  अन्यथा
	    आकार = 512 - j;
	  यदि ((बहुलकम् & 8) && len + j >= 512)
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
	      p1[i] = random () & CHAR_MAX;
	      यदि (i >= align1 && i < len + align1 && !p1[i])
		p1[i] = (random () & 127) + 3;
	    }
	}

	res = (वर्ण *) strndup ((वर्ण *) (p1 + align1), आकार);
	j = len + 1;
	यदि (आकार < j)
	  j = आकार;
	TEST_COMPARE_BLOB (res, j, (वर्ण *) (p1 + align1), j);
	मुक्त (res);
    }
}

पूर्णाङ्क
test_main (शून्य)
{
  size_t i;

  test_init ();

  प्रारूप_लिख ("%28s", "");
  प्रारूप_लिख ("\t%s", "strndup");
  अक्षरं_लिख ('\n');

  प्रति (i = 1; i < 8; ++i)
    {
      do_test (i, i, 16, 16, 127);
      do_test (i, i, 16, 16, CHAR_MAX);
      do_test (i, 2 * i, 16, 16, 127);
      do_test (2 * i, i, 16, 16, CHAR_MAX);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, 127);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, 127);
      do_test (8 - i, 2 * i, 1 << i, 2 << i, CHAR_MAX);
      do_test (2 * i, 8 - i, 2 << i, 1 << i, CHAR_MAX);
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
