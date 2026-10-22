/* Test and measure strcasecmp functions.
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

#अन्तर्भाव <locale.h>
#अन्तर्भाव <ctype.h>
#अन्तर्भाव <assert.h>
#define TEST_LEN (getpagesize () * 3)
#define MIN_PAGE_SIZE (TEST_LEN + 2 * getpagesize ())

#define TEST_MAIN
#define TEST_NAME "strcasecmp"
#अन्तर्भाव "test-string.h"

प्रकारव्याख्या पूर्णांक (*proto_t) (स्थिरांक अक्षर *, स्थिरांक अक्षर *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
पूर्णांक
simple_strcasecmp (स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2)
{
  पूर्णांक ret;

  पर्यंत ((ret = ((अचिन्हित अक्षर) छोटे (*s1)
		 - (अचिन्हित अक्षर) छोटे (*s2))) == 0
	 && *s1++)
    ++s2;
  परत ret;
}

स्थिर शून्य
do_one_test (impl_t *impl, स्थिरांक अक्षर *s1, स्थिरांक अक्षर *s2, पूर्णांक exp_result)
{
  पूर्णांक result = CALL (impl, s1, s2);
  जर ((exp_result == 0 && result != 0)
      || (exp_result < 0 && result >= 0)
      || (exp_result > 0 && result <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     result, exp_result);
      ret = 1;
      परत;
    }
}

स्थिर शून्य
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char,
	 पूर्णांक exp_result)
{
  माप_प्रकार i;
  अक्षर *s1, *s2;

  जर (len == 0)
    परत;


  align1 &= getpagesize () - 1;
  जर (align1 + (len + 1) >= page_size)
    परत;

  align2 &= getpagesize () - 1;
  जर (align2 + (len + 1) >= page_size)
    परत;

  s1 = (अक्षर *) (buf1 + align1);
  s2 = (अक्षर *) (buf2 + align2);

  साठी (i = 0; i < len; i++)
    {
      s1[i] = बड़े (1 + 23 * i % max_char);
      s2[i] = छोटे (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_result;

  जर ((s2[len - 1] == 'z' && exp_result == -1)
      || (s2[len - 1] == 'a' && exp_result == 1))
    s1[len - 1] += exp_result;
  अन्यथा जर ((s1[len - 1] == 'Z' + 1 && exp_result == 1)
           || (s1[len - 1] == 'A' - 1 && exp_result == -1))
    s1[len - 1] = छोटे (s2[len - 1]) + exp_result;
  अन्यथा
    s2[len - 1] -= exp_result;

  /* For some locals this is not guaranteed yet.  */
  जर (छोटे (s1[len - 1]) - छोटे (s2[len - 1]) != exp_result)
    {
      जर (exp_result == -1)
        {
          s1[len - 1] = छोटे ('a');
          s2[len - 1] = बड़े (छोटे ('a') - 1);
        }
      अन्यथा जर (exp_result == 0)
        s1[len - 1] = बड़े (s2[len - 1]);
      अन्यथा
        {
          s1[len - 1] = छोटे ('a');
          s2[len - 1] = बड़े (छोटे ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_result);
}

स्थिर शून्य
do_random_tests (शून्य)
{
  माप_प्रकार i, j, n, align1, align2, pos, len1, len2;
  पूर्णांक result;
  दीर्घ r;
  अचिन्हित अक्षर *p1 = buf1 + page_size - 512;
  अचिन्हित अक्षर *p2 = buf2 + page_size - 512;

  साठी (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      जर (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      जर (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      जर (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      जर (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      जर (pos >= len1)
	len2 = len1;
      अन्यथा
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      जर (j > 512)
	j = 512;
      साठी (i = 0; i < j; ++i)
	{
	  p1[i] = छोटे (random () & 255);
	  जर (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = छोटे (random () & 255);
	      जर (!p1[i])
		p1[i] = छोटे (1 + (random () & 127));
	    }
	}
      साठी (i = 0; i < j; ++i)
	{
	  p2[i] = बड़े (random () & 255);
	  जर (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = बड़े (random () & 255);
	      जर (!p2[i])
		बड़े (p2[i] = 1 + (random () & 127));
	    }
	}

      result = 0;
      स_नकल (p2 + align2, p1 + align1, pos);
      जर (pos < len1)
	{
	  जर (छोटे (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = बड़े (random () & 255);
	      जर (छोटे (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = बड़े (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  जर (p1[align1 + pos] < छोटे (p2[align2 + pos]))
	    result = -1;
	  अन्यथा
	    result = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (अक्षर *) (p1 + align1), (अक्षर *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  यंत्र ("" : "=g" (r) : "0" (r));
	  जर ((r == 0 && result)
	      || (r < 0 && result >= 0)
	      || (r > 0 && result <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, result, p1, p2);
	      ret = 1;
	    }
	}
    }
}

स्थिर शून्य
test_locale (स्थिरांक अक्षर *locale, पूर्णांक extra_tests)
{
  माप_प्रकार i, j, k;
  स्थिरांक माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  जर (रखो_क्षेत्र (LC_CTYPE, locale) == रिक्त)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  म_लिखो ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  साठी (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  साठी (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  साठी (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  साठी (j = 0; extra_tests && j < 160; ++j)
    {
      साठी (i = 0; i < test_len;)
        {
          do_test (getpagesize () - j - 1, 0, i, 127, 0);
          do_test (getpagesize () - j - 1, 0, i, 127, 1);
          do_test (getpagesize () - j - 1, 0, i, 127, -1);

          do_test (getpagesize () - j - 1, j, i, 127, 0);
          do_test (getpagesize () - j - 1, j, i, 127, 1);
          do_test (getpagesize () - j - 1, j, i, 127, -1);

          do_test (0, getpagesize () - j - 1, i, 127, 0);
          do_test (0, getpagesize () - j - 1, i, 127, 1);
          do_test (0, getpagesize () - j - 1, i, 127, -1);

          do_test (j, getpagesize () - j - 1, i, 127, 0);
          do_test (j, getpagesize () - j - 1, i, 127, 1);
          do_test (j, getpagesize () - j - 1, i, 127, -1);

          साठी (k = 2; k <= 128; k += k)
            {
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 0);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       0);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, 1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       1);
              do_test (getpagesize () - k, getpagesize () - j - 1, i, 127, -1);
              do_test (getpagesize () - k - 1, getpagesize () - j - 1, i, 127,
                       -1);
            }

          जर (i < 32)
            {
              i += 1;
            }
          अन्यथा जर (i < 161)
            {
              i += 7;
            }
          अन्यथा जर (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              जर (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा जर (i + 32 < test_len)
            {
              i += 7;
            }
          अन्यथा
            {
              i += 1;
            }
        }
    }

  do_random_tests ();
}

पूर्णांक
test_main (शून्य)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  परत ret;
}

#अन्तर्भाव <support/test-driver.c>
