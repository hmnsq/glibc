/* Test and measure strcasestr functions.
   Copyright (C) 2010-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "strcasestr"
#ಅನ್ತರ್ಭಾವ "test-string.h"


#ವ್ಯಾಖ್ಯಾನಿಸು STRCASESTR c_strcasestr
#ವ್ಯಾಖ್ಯಾನಿಸು NO_ALIAS
#ವ್ಯಾಖ್ಯಾನಿಸು __strncasecmp strncasecmp
#ವ್ಯಾಖ್ಯಾನಿಸು __strnlen strnlen
#ಅನ್ತರ್ಭಾವ "strcasestr.c"

/* Naive implementation to verify results.  */
ಸ್ಥಿರ ಅಕ್ಷರ *
simple_strcasestr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2)
{
  ssize_t s1len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (s1);
  ssize_t s2len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (s2);

  ಆದರೆ (s2len > s1len)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಗಾಗಿ (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      ಗಾಗಿ (j = 0; j < s2len; ++j)
	ಆದರೆ (tolower (s1[i + j]) != tolower (s2[j]))
	  ನಿಲ್ಲಿಸು;
      ಆದರೆ (j == s2len)
	ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ *) s1 + i;
    }

  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ *(*proto_t) (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

IMPL (c_strcasestr, 0)
IMPL (strcasestr, 1)


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
check_ಫಲಿತಾಂಶ (impl_t *impl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2,
	      ಅಕ್ಷರ *exp_ಫಲಿತಾಂಶ)
{
  ಅಕ್ಷರ *ಫಲಿತಾಂಶ = CALL (impl, s1, s2);
  ಆದರೆ (ಫಲಿತಾಂಶ != exp_ಫಲಿತಾಂಶ)
    {
      error (0, 0, "Wrong result in function %s %s %s", impl->name,
	     (ಫಲಿತಾಂಶ == ಖಾಲಿ) ? "(null)" : ಫಲಿತಾಂಶ,
	     (exp_ಫಲಿತಾಂಶ == ಖಾಲಿ) ? "(null)" : exp_ಫಲಿತಾಂಶ);
      ret = 1;
      ಹಿಂತಿರುಗಿ -1;
    }
  ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ
do_one_test (impl_t *impl, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s2, ಅಕ್ಷರ *exp_ಫಲಿತಾಂಶ)
{
  ಆದರೆ (check_ಫಲಿತಾಂಶ (impl, s1, s2, exp_ಫಲಿತಾಂಶ) < 0)
    ಹಿಂತಿರುಗಿ;
}


ಸ್ಥಿರ ಶೂನ್ಯ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 ಪೂರ್ಣಾಂಕ fail)
{
  ಅಕ್ಷರ *s1 = (ಅಕ್ಷರ *) (buf1 + align1);
  ಅಕ್ಷರ *s2 = (ಅಕ್ಷರ *) (buf2 + align2);

  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ d[] = "1234567890abcxyz";
#ವ್ಯಾಖ್ಯಾನಿಸು dl (ಗಾತ್ರ (d) - 1)
  ಅಕ್ಷರ *ss2 = s2;
  ಗಾಗಿ (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = mempcpy (ss2, d, t);
    }
  s2[len2] = '\0';

  ಆದರೆ (fail)
    {
      ಅಕ್ಷರ *ss1 = s1;
      ಗಾಗಿ (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  ಸ್ಮರಣೆ_ನಕಲು (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      memset (s1, '0', len1);
      ಗಾಗಿ (size_t i = 0; i < len2; ++i)
	s1[len1 - len2 + i] = ದೊಡ್ಡ_ಅಕ್ಷರ (s2[i]);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ಖಾಲಿ : s1 + len1 - len2);
}

ಸ್ಥಿರ ಶೂನ್ಯ
check1 (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ s1[] = "AOKB";
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ s2[] = "OK";
  ಅಕ್ಷರ *exp_ಫಲಿತಾಂಶ;

  exp_ಫಲಿತಾಂಶ = simple_strcasestr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ಫಲಿತಾಂಶ (impl, s1, s2, exp_ಫಲಿತಾಂಶ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
test_main (ಶೂನ್ಯ)
{
  test_init ();

  check1 ();

  ಬರೆ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ಬರೆ ("\t%s", impl->name);
  ಅಕ್ಷರ_ಬರೆ ('\n');

  ಗಾಗಿ (size_t klen = 2; klen < 32; ++klen)
    ಗಾಗಿ (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
      {
	do_test (0, 0, hlen, klen, 0);
	do_test (0, 0, hlen, klen, 1);
	do_test (0, 3, hlen, klen, 0);
	do_test (0, 3, hlen, klen, 1);
	do_test (0, 9, hlen, klen, 0);
	do_test (0, 9, hlen, klen, 1);
	do_test (0, 15, hlen, klen, 0);
	do_test (0, 15, hlen, klen, 1);

	do_test (3, 0, hlen, klen, 0);
	do_test (3, 0, hlen, klen, 1);
	do_test (3, 3, hlen, klen, 0);
	do_test (3, 3, hlen, klen, 1);
	do_test (3, 9, hlen, klen, 0);
	do_test (3, 9, hlen, klen, 1);
	do_test (3, 15, hlen, klen, 0);
	do_test (3, 15, hlen, klen, 1);

	do_test (9, 0, hlen, klen, 0);
	do_test (9, 0, hlen, klen, 1);
	do_test (9, 3, hlen, klen, 0);
	do_test (9, 3, hlen, klen, 1);
	do_test (9, 9, hlen, klen, 0);
	do_test (9, 9, hlen, klen, 1);
	do_test (9, 15, hlen, klen, 0);
	do_test (9, 15, hlen, klen, 1);

	do_test (15, 0, hlen, klen, 0);
	do_test (15, 0, hlen, klen, 1);
	do_test (15, 3, hlen, klen, 0);
	do_test (15, 3, hlen, klen, 1);
	do_test (15, 9, hlen, klen, 0);
	do_test (15, 9, hlen, klen, 1);
	do_test (15, 15, hlen, klen, 0);
	do_test (15, 15, hlen, klen, 1);
      }

  do_test (0, 0, ಪುಟ_ಗಾತ್ರ - 1, 16, 0);
  do_test (0, 0, ಪುಟ_ಗಾತ್ರ - 1, 16, 1);

  ಹಿಂತಿರುಗಿ ret;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
