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
#இல்லையெனில்
# define TEST_NAME "wcsstr"
# define TEST_FUNC wcsstr
#endif

#ifndef WIDE
# define CHAR எழுத்து
# define STRLEN strlen
# define STRCPY strcpy
# define MEMCPY memcpy
# define MEMSET memset
# define MEMPCPY mempcpy
# define L(s) s
#இல்லையெனில்
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

#அந்தர்பாவ "test-string.h"

#ifndef WIDE
# define STRSTR c_strstr
# define libc_hidden_builtin_def(arg) /* nothing */
# define __strnlen strnlen
# include "strstr.c"
# define C_IMPL STRSTR
#இல்லையெனில்
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
நிலையான CHAR *
simple_strstr (மாறிலி CHAR *s1, மாறிலி CHAR *s2)
{
  ssize_t s1len = STRLEN (s1);
  ssize_t s2len = STRLEN (s2);

  எனில் (s2len > s1len)
    திரும்பு வெற்று;

  க்கு (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      க்கு (j = 0; j < s2len; ++j)
	எனில் (s1[i + j] != s2[j])
	  நிறுத்து;
      எனில் (j == s2len)
	திரும்பு (CHAR *) s1 + i;
    }

  திரும்பு வெற்று;
}


வகைவரை CHAR *(*proto_t) (மாறிலி CHAR *, மாறிலி CHAR *);

IMPL (C_IMPL, 1)
IMPL (TEST_FUNC, 1)

நிலையான முழு
check_result (impl_t *impl, மாறிலி CHAR *s1, மாறிலி CHAR *s2,
	      CHAR *exp_result)
{
  CHAR *result = CALL (impl, s1, s2);
  எனில் (result != exp_result)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     result, exp_result);
      ret = 1;
      திரும்பு -1;
    }

  திரும்பு 0;
}

நிலையான வெறுமை
do_one_test (impl_t *impl, மாறிலி CHAR *s1, மாறிலி CHAR *s2, CHAR *exp_result)
{
  எனில் (check_result (impl, s1, s2, exp_result) < 0)
    திரும்பு;
}


நிலையான வெறுமை
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 முழு fail)
{
  align1 = align1 * அளவு (CHAR);
  align2 = align2 * அளவு (CHAR);

  CHAR *s1 = (CHAR *) (buf1 + align1);
  CHAR *s2 = (CHAR *) (buf2 + align2);

  நிலையான மாறிலி CHAR d[] = L("1234567890abcdef");
  மாறிலி size_t dl = STRLEN (d);
  CHAR *ss2 = s2;
  க்கு (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = MEMPCPY (ss2, d, t);
    }
  s2[len2] = '\0';

  எனில் (fail)
    {
      CHAR *ss1 = s1;
      க்கு (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  MEMCPY (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  இல்லையெனில்
    {
      MEMSET (s1, '0', len1);
      MEMCPY (s1 + len1 - len2, s2, len2);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? வெற்று : s1 + len1 - len2);
}

நிலையான வெறுமை
check1 (வெறுமை)
{
  மாறிலி CHAR s1[] =
    L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD");
  மாறிலி CHAR s2[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
  CHAR *exp_result;

  exp_result = simple_strstr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_result (impl, s1, s2, exp_result);
}

நிலையான வெறுமை
check2 (வெறுமை)
{
  மாறிலி CHAR s1_அடுக்கு[] = L(", enable_static, \0, enable_shared, ");
  மாறிலி size_t s1_char_மொத்தம் = 18;
  மாறிலி size_t s1_byte_len = 18 * அளவு (CHAR);
  மாறிலி CHAR *s2_அடுக்கு = &(s1_அடுக்கு[s1_char_மொத்தம்]);
  மாறிலி size_t s2_byte_len = 18 * அளவு (CHAR);
  CHAR *exp_result;
  மாறிலி size_t page_size_real = getpagesize ();

  /* Haystack at end of page.  The following page is protected.  */
  CHAR *s1_page_end = (வெறுமை *) buf1 + page_size - s1_byte_len;
  STRCPY (s1_page_end, s1_அடுக்கு);

  /* Haystack which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s1_page_cross = (வெறுமை *) buf1 + page_size_real - 8;
  STRCPY (s1_page_cross, s1_அடுக்கு);

  /* Needle at end of page.  The following page is protected.  */
  CHAR *s2_page_end = (வெறுமை *) buf2 + page_size - s2_byte_len;
  STRCPY (s2_page_end, s2_அடுக்கு);

  /* Needle which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s2_page_cross = (வெறுமை *) buf2 + page_size_real - 8;
  STRCPY (s2_page_cross, s2_அடுக்கு);

  exp_result = simple_strstr (s1_அடுக்கு, s2_அடுக்கு);
  FOR_EACH_IMPL (impl, 0)
    {
      check_result (impl, s1_அடுக்கு, s2_அடுக்கு, exp_result);
      check_result (impl, s1_அடுக்கு, s2_page_end, exp_result);
      check_result (impl, s1_அடுக்கு, s2_page_cross, exp_result);

      check_result (impl, s1_page_end, s2_அடுக்கு, exp_result);
      check_result (impl, s1_page_end, s2_page_end, exp_result);
      check_result (impl, s1_page_end, s2_page_cross, exp_result);

      check_result (impl, s1_page_cross, s2_அடுக்கு, exp_result);
      check_result (impl, s1_page_cross, s2_page_end, exp_result);
      check_result (impl, s1_page_cross, s2_page_cross, exp_result);
    }
}

நிலையான வெறுமை
check3 (வெறுமை)
{
  /* Check that a long periodic needle does not cause false positives.  */
  {
    மாறிலி CHAR உள்ளீடு[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_A7_20_EF_BF_BD");
    மாறிலி CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, உள்ளீடு, need, வெற்று);
  }

  {
    மாறிலி CHAR உள்ளீடு[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20"
			   "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    மாறிலி CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, உள்ளீடு, need, (CHAR *) உள்ளீடு + 115);
  }
}


#define N 1024

நிலையான வெறுமை
pr23637 (வெறுமை)
{
  CHAR *h = (CHAR*) buf1;
  CHAR *n = (CHAR*) buf2;

  க்கு (முழு i = 0; i < N; i++)
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

நிலையான வெறுமை
pr23865 (வெறுமை)
{
  /* Check that a very long haystack is handled quickly if the needle is
     short and occurs near the beginning.  */
  {
    size_t m = 1000000;
    மாறிலி CHAR *needle =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    CHAR *haystack = xmalloc ((m + 1) * அளவு (CHAR));
    MEMSET (haystack, L('A'), m);
    haystack[0] = L('B');
    haystack[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + 1);

    விடுவி (haystack);
  }

  /* Check that a very long needle is discarded quickly if the haystack is
     short.  */
  {
    size_t m = 1000000;
    மாறிலி CHAR *haystack =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    CHAR *needle = xmalloc ((m + 1) * அளவு (CHAR));
    MEMSET (needle, L'A', m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, வெற்று);

    விடுவி (needle);
  }

  /* Check that the asymptotic worst-case complexity is not quadratic.  */
  {
    size_t m = 1000000;
    CHAR *haystack = xmalloc ((2 * m + 2) * அளவு (CHAR));
    CHAR *needle = xmalloc ((m + 2) * அளவு (CHAR));

    MEMSET (haystack, L('A'), 2 * m);
    haystack[2 * m] = L('B');
    haystack[2 * m + 1] = L('\0');

    MEMSET (needle, L('A'), m);
    needle[m] = L('B');
    needle[m + 1] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + m);

    விடுவி (needle);
    விடுவி (haystack);
  }

  {
    /* Ensure that with a barely periodic "short" needle, STRSTR's
       search does not mistakenly skip just past the match point.  */
    மாறிலி CHAR *haystack =
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
    மாறிலி CHAR *needle =
      L("\n"
       "with_gnu_ld\n");

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, (CHAR*) haystack + 114);
  }

  {
    /* Same bug, shorter trigger.  */
    மாறிலி CHAR *haystack = L("..wi.d.");
    மாறிலி CHAR *needle = L(".d.");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, (CHAR*) haystack + 4);
  }

  /* Test case from Yves Bastide.
     <https://www.openwall.com/lists/musl/2014/04/18/2>  */
  {
    மாறிலி CHAR *உள்ளீடு = L("playing play play play always");
    மாறிலி CHAR *needle = L("play play play");
    FOR_EACH_IMPL (impl, 0)
      check_result (impl, உள்ளீடு, needle, (CHAR*) உள்ளீடு + 8);
  }

  /* Test long needles.  */
  {
    size_t m = 1024;
    CHAR *haystack = xmalloc ((2 * m + 1) * அளவு (CHAR));
    CHAR *needle = xmalloc ((m + 1) * அளவு (CHAR));
    haystack[0] = L('x');
    MEMSET (haystack + 1, L(' '), m - 1);
    MEMSET (haystack + m, L('x'), m);
    haystack[2 * m] = L('\0');
    MEMSET (needle, L('x'), m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_result (impl, haystack, needle, haystack + m);

    விடுவி (needle);
    விடுவி (haystack);
  }
}

நிலையான முழு
test_main (வெறுமை)
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

  க்கு (size_t klen = 2; klen < 32; ++klen)
    க்கு (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  திரும்பு ret;
}

#அந்தர்பாவ <support/test-driver.c>
