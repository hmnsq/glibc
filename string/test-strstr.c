/* Test and measure strstr functions.
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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strstr"
# define TEST_FUNC strstr
#অন্যথা
# define TEST_NAME "wcsstr"
# define TEST_FUNC wcsstr
#endif

#ifndef WIDE
# define CHAR বর্ণ
# define STRLEN strlen
# define STRCPY strcpy
# define MEMCPY memcpy
# define MEMSET memset
# define MEMPCPY mempcpy
# define L(s) s
#অন্যথা
# include <wchar.h>
# define CHAR wchar_t
# define STRLEN wcslen
# define STRCPY wcscpy
# define MEMCPY wmemcpy
# define MEMSET wmemset
# define MEMPCPY wmempcpy
# define L(s) L ## s
/* The test requires up to 8191 characters, so allocate at least 32Kb
   (considering 4kb page size).  */
# define BUF1PAGES 4
#endif

#অন্তর্ভাব "test-string.h"

#ifndef WIDE
# define STRSTR c_strstr
# define libc_hidden_builtin_def(arg) /* nothing */
# define __strnlen strnlen
# include "strstr.c"
# define C_IMPL STRSTR
#অন্যথা
# undef weak_alias
# define weak_alias(a, b)
# define WCSSTR c_wcsstr
# define __wmemcmp wmemcmp
# define __wcsnlen wcsnlen
# define __wcslen wcslen
# include "wcsstr.c"
# define C_IMPL WCSSTR
#endif

/* Naive implementation to verify results.  */
স্থির CHAR *
simple_strstr (ধ্রুব CHAR *s1, ধ্রুব CHAR *s2)
{
  ssize_t s1len = STRLEN (s1);
  ssize_t s2len = STRLEN (s2);

  যদি (s2len > s1len)
    প্রত্যাগম রিক্ত;

  প্রতি (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      প্রতি (j = 0; j < s2len; ++j)
	যদি (s1[i + j] != s2[j])
	  ভঙ্গ;
      যদি (j == s2len)
	প্রত্যাগম (CHAR *) s1 + i;
    }

  প্রত্যাগম রিক্ত;
}


প্রকারনির্দেশ CHAR *(*proto_t) (ধ্রুব CHAR *, ধ্রুব CHAR *);

IMPL (C_IMPL, 1)
IMPL (TEST_FUNC, 1)

স্থির পূর্ণাঙ্ক
check_result (impl_t *impl, ধ্রুব CHAR *s1, ধ্রুব CHAR *s2,
	      CHAR *exp_result)
{
  CHAR *result = CALL (impl, s1, s2);
  যদি (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     result, exp_result);
      ret = 1;
      প্রত্যাগম -1;
    }

  প্রত্যাগম 0;
}

স্থির শূন্য
do_one_test (impl_t *impl, ধ্রুব CHAR *s1, ধ্রুব CHAR *s2, CHAR *exp_result)
{
  যদি (check_result (impl, s1, s2, exp_result) < 0)
    প্রত্যাগম;
}


স্থির শূন্য
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 পূর্ণাঙ্ক fail)
{
  align1 = align1 * পরিমাণ (CHAR);
  align2 = align2 * পরিমাণ (CHAR);

  CHAR *s1 = (CHAR *) (buf1 + align1);
  CHAR *s2 = (CHAR *) (buf2 + align2);

  স্থির ধ্রুব CHAR d[] = L("1234567890abcdef");
  ধ্রুব size_t dl = STRLEN (d);
  CHAR *ss2 = s2;
  প্রতি (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = MEMPCPY (ss2, d, t);
    }
  s2[len2] = '\0';

  যদি (fail)
    {
      CHAR *ss1 = s1;
      প্রতি (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  MEMCPY (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  অন্যথা
    {
      MEMSET (s1, '0', len1);
      MEMCPY (s1 + len1 - len2, s2, len2);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? রিক্ত : s1 + len1 - len2);
}

স্থির শূন্য
check1 (শূন্য)
{
  ধ্রুব CHAR s1[] =
    L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD");
  ধ্রুব CHAR s2[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
  CHAR *exp_result;

  exp_result = simple_strstr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

স্থির শূন্য
check2 (শূন্য)
{
  ধ্রুব CHAR s1_স্তূপ[] = L(", enable_static, \0, enable_shared, ");
  ধ্রুব size_t s1_char_গুনতি = 18;
  ধ্রুব size_t s1_byte_len = 18 * পরিমাণ (CHAR);
  ধ্রুব CHAR *s2_স্তূপ = &(s1_স্তূপ[s1_char_গুনতি]);
  ধ্রুব size_t s2_byte_len = 18 * পরিমাণ (CHAR);
  CHAR *exp_result;
  ধ্রুব size_t page_size_real = getpagesize ();

  /* Haystack at end of page.  The following page is protected.  */
  CHAR *s1_page_end = (শূন্য *) buf1 + page_size - s1_byte_len;
  STRCPY (s1_page_end, s1_স্তূপ);

  /* Haystack which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s1_page_cross = (শূন্য *) buf1 + page_size_real - 8;
  STRCPY (s1_page_cross, s1_স্তূপ);

  /* Needle at end of page.  The following page is protected.  */
  CHAR *s2_page_end = (শূন্য *) buf2 + page_size - s2_byte_len;
  STRCPY (s2_page_end, s2_স্তূপ);

  /* Needle which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s2_page_cross = (শূন্য *) buf2 + page_size_real - 8;
  STRCPY (s2_page_cross, s2_স্তূপ);

  exp_result = simple_strstr (s1_স্তূপ, s2_স্তূপ);
  FOR_EACH_IMPL (impl, 0)
    {
      check_result (impl, s1_স্তূপ, s2_স্তূপ, exp_result);
      check_result (impl, s1_স্তূপ, s2_page_end, exp_result);
      check_result (impl, s1_স্তূপ, s2_page_cross, exp_result);

      check_result (impl, s1_page_end, s2_স্তূপ, exp_result);
      check_result (impl, s1_page_end, s2_page_end, exp_result);
      check_result (impl, s1_page_end, s2_page_cross, exp_result);

      check_result (impl, s1_page_cross, s2_স্তূপ, exp_result);
      check_result (impl, s1_page_cross, s2_page_end, exp_result);
      check_result (impl, s1_page_cross, s2_page_cross, exp_result);
    }
}

স্থির শূন্য
check3 (শূন্য)
{
  /* Check that a long periodic needle does not cause false positives.  */
  {
    ধ্রুব CHAR প্রবেশ[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_A7_20_EF_BF_BD");
    ধ্রুব CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, প্রবেশ, need, রিক্ত);
  }

  {
    ধ্রুব CHAR প্রবেশ[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20"
			   "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    ধ্রুব CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, প্রবেশ, need, (CHAR *) প্রবেশ + 115);
  }
}


#define N 1024

স্থির শূন্য
pr23637 (শূন্য)
{
  CHAR *h = (CHAR*) buf1;
  CHAR *n = (CHAR*) buf2;

  প্রতি (পূর্ণাঙ্ক i = 0; i < N; i++)
    {
      n[i] = 'x';
      h[i] = ' ';
      h[i + N] = 'x';
    }

  n[N] = '\0';
  h[N * 2] = '\0';

  /* Ensure we don't match at the first 'x'.  */
  h[0] = 'x';

  CHAR *exp_result = simple_strstr (h, n);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, h, n, exp_result);
}

স্থির শূন্য
pr23865 (শূন্য)
{
  /* Check that a very long haystack is handled quickly if the needle is
     short and occurs near the beginning.  */
  {
    size_t m = 1000000;
    ধ্রুব CHAR *needle =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    CHAR *haystack = xmalloc ((m + 1) * পরিমাণ (CHAR));
    MEMSET (haystack, L('A'), m);
    haystack[0] = L('B');
    haystack[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + 1);

    মুক্ত (haystack);
  }

  /* Check that a very long needle is discarded quickly if the haystack is
     short.  */
  {
    size_t m = 1000000;
    ধ্রুব CHAR *haystack =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    CHAR *needle = xmalloc ((m + 1) * পরিমাণ (CHAR));
    MEMSET (needle, L'A', m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, রিক্ত);

    মুক্ত (needle);
  }

  /* Check that the asymptotic worst-case complexity is not quadratic.  */
  {
    size_t m = 1000000;
    CHAR *haystack = xmalloc ((2 * m + 2) * পরিমাণ (CHAR));
    CHAR *needle = xmalloc ((m + 2) * পরিমাণ (CHAR));

    MEMSET (haystack, L('A'), 2 * m);
    haystack[2 * m] = L('B');
    haystack[2 * m + 1] = L('\0');

    MEMSET (needle, L('A'), m);
    needle[m] = L('B');
    needle[m + 1] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + m);

    মুক্ত (needle);
    মুক্ত (haystack);
  }

  {
    /* Ensure that with a barely periodic "short" needle, STRSTR's
       search does not mistakenly skip just past the match point.  */
    ধ্রুব CHAR *haystack =
      L("\n"
       "with_build_libsubdir\n"
       "with_local_prefix\n"
       "with_gxx_include_dir\n"
       "with_cpp_install_dir\n"
       "enable_generated_files_in_srcdir\n"
       "with_gnu_ld\n"
       "with_ld\n"
       "with_demangler_in_ld\n"
       "with_gnu_as\n"
       "with_as\n"
       "enable_largefile\n"
       "enable_werror_always\n"
       "enable_checking\n"
       "enable_coverage\n"
       "enable_gather_detailed_mem_stats\n"
       "enable_build_with_cxx\n"
       "with_stabs\n"
       "enable_multilib\n"
       "enable___cxa_atexit\n"
       "enable_decimal_float\n"
       "enable_fixed_point\n"
       "enable_threads\n"
       "enable_tls\n"
       "enable_objc_gc\n"
       "with_dwarf2\n"
       "enable_shared\n"
       "with_build_sysroot\n"
       "with_sysroot\n"
       "with_specs\n"
       "with_pkgversion\n"
       "with_bugurl\n"
       "enable_languages\n"
       "with_multilib_list\n");
    ধ্রুব CHAR *needle =
      L("\n"
       "with_gnu_ld\n");

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, (CHAR*) haystack + 114);
  }

  {
    /* Same bug, shorter trigger.  */
    ধ্রুব CHAR *haystack = L("..wi.d.");
    ধ্রুব CHAR *needle = L(".d.");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, (CHAR*) haystack + 4);
  }

  /* Test case from Yves Bastide.
     <https://www.openwall.com/lists/musl/2014/04/18/2>  */
  {
    ধ্রুব CHAR *প্রবেশ = L("playing play play play always");
    ধ্রুব CHAR *needle = L("play play play");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, প্রবেশ, needle, (CHAR*) প্রবেশ + 8);
  }

  /* Test long needles.  */
  {
    size_t m = 1024;
    CHAR *haystack = xmalloc ((2 * m + 1) * পরিমাণ (CHAR));
    CHAR *needle = xmalloc ((m + 1) * পরিমাণ (CHAR));
    haystack[0] = L('x');
    MEMSET (haystack + 1, L(' '), m - 1);
    MEMSET (haystack + m, L('x'), m);
    haystack[2 * m] = L('\0');
    MEMSET (needle, L('x'), m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + m);

    মুক্ত (needle);
    মুক্ত (haystack);
  }
}

স্থির পূর্ণাঙ্ক
test_main (শূন্য)
{
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  pr23637 ();
  pr23865 ();

  printf ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    printf ("\t%s", impl->name);
  putchar ('\n');

  প্রতি (size_t klen = 2; klen < 32; ++klen)
    প্রতি (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

	do_test (15, 15, hlen + klen * 4, klen * 4, 0);
	do_test (15, 15, hlen + klen * 4, klen * 4, 1);
      }

  do_test (0, 0, page_size - 1, 16, 0);
  do_test (0, 0, page_size - 1, 16, 1);

  প্রত্যাগম ret;
}

#অন্তর্ভাব <support/test-driver.c>
