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

#समावेश <locale.h>
#समावेश <ctype.h>
#समावेश <assert.h>
#घोषणा TEST_LEN (getpagesize () * 3)
#घोषणा MIN_PAGE_आकार (TEST_LEN + 2 * getpagesize ())

#घोषणा TEST_MAIN
#घोषणा TEST_NAME "strcasecmp"
#समावेश "test-string.h"

प्रकार पूर्णांक (*proto_t) (स्थिर अक्षर *, स्थिर अक्षर *);

IMPL (strcasecmp, 1)

/* Naive implementation to verify results.  */
पूर्णांक
simple_strcasecmp (स्थिर अक्षर *s1, स्थिर अक्षर *s2)
{
  पूर्णांक ret;

  जबतक ((ret = ((अचिन्हित अक्षर) छोटे (*s1)
		 - (अचिन्हित अक्षर) छोटे (*s2))) == 0
	 && *s1++)
    ++s2;
  वापस ret;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर अक्षर *s1, स्थिर अक्षर *s2, पूर्णांक exp_परिणाम)
{
  पूर्णांक परिणाम = CALL (impl, s1, s2);
  अगर ((exp_परिणाम == 0 && परिणाम != 0)
      || (exp_परिणाम < 0 && परिणाम >= 0)
      || (exp_परिणाम > 0 && परिणाम <= 0))
    {
      error (0, 0, "Wrong result in function %s %d %d", impl->name,
	     परिणाम, exp_परिणाम);
      ret = 1;
      वापस;
    }
}

अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len, पूर्णांक max_char,
	 पूर्णांक exp_परिणाम)
{
  माप_प्रकार i;
  अक्षर *s1, *s2;

  अगर (len == 0)
    वापस;


  align1 &= getpagesize () - 1;
  अगर (align1 + (len + 1) >= page_आकार)
    वापस;

  align2 &= getpagesize () - 1;
  अगर (align2 + (len + 1) >= page_आकार)
    वापस;

  s1 = (अक्षर *) (buf1 + align1);
  s2 = (अक्षर *) (buf2 + align2);

  क्रम (i = 0; i < len; i++)
    {
      s1[i] = बड़े (1 + 23 * i % max_char);
      s2[i] = छोटे (s1[i]);
    }

  s1[len] = s2[len] = 0;
  s1[len + 1] = 23;
  s2[len + 1] = 24 + exp_परिणाम;

  अगर ((s2[len - 1] == 'z' && exp_परिणाम == -1)
      || (s2[len - 1] == 'a' && exp_परिणाम == 1))
    s1[len - 1] += exp_परिणाम;
  अन्यथा अगर ((s1[len - 1] == 'Z' + 1 && exp_परिणाम == 1)
           || (s1[len - 1] == 'A' - 1 && exp_परिणाम == -1))
    s1[len - 1] = छोटे (s2[len - 1]) + exp_परिणाम;
  अन्यथा
    s2[len - 1] -= exp_परिणाम;

  /* For some locals this is not guaranteed yet.  */
  अगर (छोटे (s1[len - 1]) - छोटे (s2[len - 1]) != exp_परिणाम)
    {
      अगर (exp_परिणाम == -1)
        {
          s1[len - 1] = छोटे ('a');
          s2[len - 1] = बड़े (छोटे ('a') - 1);
        }
      अन्यथा अगर (exp_परिणाम == 0)
        s1[len - 1] = बड़े (s2[len - 1]);
      अन्यथा
        {
          s1[len - 1] = छोटे ('a');
          s2[len - 1] = बड़े (छोटे ('a') + 1);
        }
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, exp_परिणाम);
}

अटल व्योम
do_random_tests (व्योम)
{
  माप_प्रकार i, j, n, align1, align2, pos, len1, len2;
  पूर्णांक परिणाम;
  दीर्घ r;
  अचिन्हित अक्षर *p1 = buf1 + page_आकार - 512;
  अचिन्हित अक्षर *p2 = buf2 + page_आकार - 512;

  क्रम (n = 0; n < ITERATIONS; n++)
    {
      align1 = random () & 31;
      अगर (random () & 1)
	align2 = random () & 31;
      अन्यथा
	align2 = align1 + (random () & 24);
      pos = random () & 511;
      j = align1 > align2 ? align1 : align2;
      अगर (pos + j >= 511)
	pos = 510 - j - (random () & 7);
      len1 = random () & 511;
      अगर (pos >= len1 && (random () & 1))
	len1 = pos + (random () & 7);
      अगर (len1 + j >= 512)
	len1 = 511 - j - (random () & 7);
      अगर (pos >= len1)
	len2 = len1;
      अन्यथा
	len2 = len1 + (len1 != 511 - j ? random () % (511 - j - len1) : 0);
      j = (pos > len2 ? pos : len2) + align1 + 64;
      अगर (j > 512)
	j = 512;
      क्रम (i = 0; i < j; ++i)
	{
	  p1[i] = छोटे (random () & 255);
	  अगर (i < len1 + align1 && !p1[i])
	    {
	      p1[i] = छोटे (random () & 255);
	      अगर (!p1[i])
		p1[i] = छोटे (1 + (random () & 127));
	    }
	}
      क्रम (i = 0; i < j; ++i)
	{
	  p2[i] = बड़े (random () & 255);
	  अगर (i < len2 + align2 && !p2[i])
	    {
	      p2[i] = बड़े (random () & 255);
	      अगर (!p2[i])
		बड़े (p2[i] = 1 + (random () & 127));
	    }
	}

      परिणाम = 0;
      स_नकल (p2 + align2, p1 + align1, pos);
      अगर (pos < len1)
	{
	  अगर (छोटे (p2[align2 + pos]) == p1[align1 + pos])
	    {
	      p2[align2 + pos] = बड़े (random () & 255);
	      अगर (छोटे (p2[align2 + pos]) == p1[align1 + pos])
		p2[align2 + pos] = बड़े (p1[align1 + pos]
					    + 3 + (random () & 127));
	    }

	  अगर (p1[align1 + pos] < छोटे (p2[align2 + pos]))
	    परिणाम = -1;
	  अन्यथा
	    परिणाम = 1;
	}
      p1[len1 + align1] = 0;
      p2[len2 + align2] = 0;

      FOR_EACH_IMPL (impl, 1)
	{
	  r = CALL (impl, (अक्षर *) (p1 + align1), (अक्षर *) (p2 + align2));
	  /* Test whether on 64-bit architectures where ABI requires
	     callee to promote has the promotion been done.  */
	  यंत्र ("" : "=g" (r) : "0" (r));
	  अगर ((r == 0 && परिणाम)
	      || (r < 0 && परिणाम >= 0)
	      || (r > 0 && परिणाम <= 0))
	    {
	      error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %zd, %zd, %zd, %zd) %ld != %d, p1 %p p2 %p",
		     n, impl->name, align1, align2, len1, len2, pos, r, परिणाम, p1, p2);
	      ret = 1;
	    }
	}
    }
}

अटल व्योम
test_locale (स्थिर अक्षर *locale, पूर्णांक extra_tests)
{
  माप_प्रकार i, j, k;
  स्थिर माप_प्रकार test_len = MIN(TEST_LEN, 3 * 4096);
  अगर (रखो_क्षेत्र (LC_CTYPE, locale) == शून्य)
    {
      error (0, 0, "cannot set locale \"%s\"", locale);
      ret = 1;
    }

  म_लिखो ("%-23s", locale);
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (i = 1; i < 16; ++i)
    {
      do_test (i, i, i, 127, 0);
      do_test (i, i, i, 127, 1);
      do_test (i, i, i, 127, -1);
    }

  क्रम (i = 1; i < 10; ++i)
    {
      do_test (0, 0, 2 << i, 127, 0);
      do_test (0, 0, 2 << i, 254, 0);
      do_test (0, 0, 2 << i, 127, 1);
      do_test (0, 0, 2 << i, 254, 1);
      do_test (0, 0, 2 << i, 127, -1);
      do_test (0, 0, 2 << i, 254, -1);
    }

  क्रम (i = 1; i < 8; ++i)
    {
      do_test (i, 2 * i, 8 << i, 127, 0);
      do_test (2 * i, i, 8 << i, 254, 0);
      do_test (i, 2 * i, 8 << i, 127, 1);
      do_test (2 * i, i, 8 << i, 254, 1);
      do_test (i, 2 * i, 8 << i, 127, -1);
      do_test (2 * i, i, 8 << i, 254, -1);
    }

  क्रम (j = 0; extra_tests && j < 160; ++j)
    {
      क्रम (i = 0; i < test_len;)
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

          क्रम (k = 2; k <= 128; k += k)
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

          अगर (i < 32)
            {
              i += 1;
            }
          अन्यथा अगर (i < 161)
            {
              i += 7;
            }
          अन्यथा अगर (i + 161 < test_len)
            {
              i += 31;
              i *= 17;
              i /= 16;
              अगर (i + 161 > test_len)
                {
                  i = test_len - 160;
                }
            }
          अन्यथा अगर (i + 32 < test_len)
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
test_main (व्योम)
{
  test_init ();

  test_locale ("C", 1);
  test_locale ("en_US.ISO-8859-1", 0);
  test_locale ("en_US.UTF-8", 0);
  test_locale ("tr_TR.ISO-8859-9", 0);
  test_locale ("tr_TR.UTF-8", 0);

  वापस ret;
}

#समावेश <support/test-driver.c>
