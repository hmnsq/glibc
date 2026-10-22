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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "strstr"
# define TEST_FUNC ਲੜੀ_ਖੋਜ
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcsstr"
# define TEST_FUNC wcsstr
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define CHAR ਅੱਖਰ
# define STRLEN ਲੜੀ_ਲੰਬਾਈ
# define STRCPY strcpy
# define MEMCPY ਸਮ੍ਰਿਤੀ_ਨਕਲ
# define MEMSET memset
# define MEMPCPY mempcpy
# define L(s) s
#ਨਹੀਂਤਾਂ
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
# define BUF1_ਪੰਨੇ 4
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STRSTR c_strstr
# define libc_hidden_builtin_def(arg) /* nothing */
# define __strnlen strnlen
# include "strstr.c"
# define C_IMPL STRSTR
#ਨਹੀਂਤਾਂ
# undef weak_alias
# define weak_alias(a, b)
# define WCSSTR c_wcsstr
# define __wmemcmp wmemcmp
# define __wcsnlen wcsnlen
# define __wcslen wcslen
# include "wcsstr.c"
# define C_IMPL WCSSTR
#ਜੇ_ਅੰਤ

/* Naive implementation to verify results.  */
ਸਥਿਰ CHAR *
simple_strstr (ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2)
{
  ssize_t s1len = STRLEN (s1);
  ssize_t s2len = STRLEN (s2);

  ਜੇ (s2len > s1len)
    ਵਾਪਸ ਨਿਰਾ;

  ਲਈ (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      ਲਈ (j = 0; j < s2len; ++j)
	ਜੇ (s1[i + j] != s2[j])
	  ਰੋਕੋ;
      ਜੇ (j == s2len)
	ਵਾਪਸ (CHAR *) s1 + i;
    }

  ਵਾਪਸ ਨਿਰਾ;
}


ਕਿਸਮਪਰਿਭਾਸ਼ਾ CHAR *(*proto_t) (ਅਚਲ CHAR *, ਅਚਲ CHAR *);

IMPL (C_IMPL, 1)
IMPL (TEST_FUNC, 1)

ਸਥਿਰ ਪੂਰਨ
check_ਨਤੀਜਾ (impl_t *impl, ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2,
	      CHAR *exp_ਨਤੀਜਾ)
{
  CHAR *ਨਤੀਜਾ = CALL (impl, s1, s2);
  ਜੇ (ਨਤੀਜਾ != exp_ਨਤੀਜਾ)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     ਨਤੀਜਾ, exp_ਨਤੀਜਾ);
      ret = 1;
      ਵਾਪਸ -1;
    }

  ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ
do_one_test (impl_t *impl, ਅਚਲ CHAR *s1, ਅਚਲ CHAR *s2, CHAR *exp_ਨਤੀਜਾ)
{
  ਜੇ (check_ਨਤੀਜਾ (impl, s1, s2, exp_ਨਤੀਜਾ) < 0)
    ਵਾਪਸ;
}


ਸਥਿਰ ਖਾਲੀ
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 ਪੂਰਨ fail)
{
  align1 = align1 * ਆਕਾਰ (CHAR);
  align2 = align2 * ਆਕਾਰ (CHAR);

  CHAR *s1 = (CHAR *) (buf1 + align1);
  CHAR *s2 = (CHAR *) (buf2 + align2);

  ਸਥਿਰ ਅਚਲ CHAR d[] = L("1234567890abcdef");
  ਅਚਲ size_t dl = STRLEN (d);
  CHAR *ss2 = s2;
  ਲਈ (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = MEMPCPY (ss2, d, t);
    }
  s2[len2] = '\0';

  ਜੇ (fail)
    {
      CHAR *ss1 = s1;
      ਲਈ (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  MEMCPY (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      MEMSET (s1, '0', len1);
      MEMCPY (s1 + len1 - len2, s2, len2);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ਨਿਰਾ : s1 + len1 - len2);
}

ਸਥਿਰ ਖਾਲੀ
check1 (ਖਾਲੀ)
{
  ਅਚਲ CHAR s1[] =
    L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD");
  ਅਚਲ CHAR s2[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
  CHAR *exp_ਨਤੀਜਾ;

  exp_ਨਤੀਜਾ = simple_strstr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, s1, s2, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
check2 (ਖਾਲੀ)
{
  ਅਚਲ CHAR s1_ਢੇਰ[] = L(", enable_static, \0, enable_shared, ");
  ਅਚਲ size_t s1_char_ਗਿਣਤੀ = 18;
  ਅਚਲ size_t s1_byte_len = 18 * ਆਕਾਰ (CHAR);
  ਅਚਲ CHAR *s2_ਢੇਰ = &(s1_ਢੇਰ[s1_char_ਗਿਣਤੀ]);
  ਅਚਲ size_t s2_byte_len = 18 * ਆਕਾਰ (CHAR);
  CHAR *exp_ਨਤੀਜਾ;
  ਅਚਲ size_t ਪੰਨਾ_ਮਾਪ_real = getpagesize ();

  /* Haystack at end of page.  The following page is protected.  */
  CHAR *s1_ਪੰਨਾ_ਸਿਰਾ = (ਖਾਲੀ *) buf1 + ਪੰਨਾ_ਮਾਪ - s1_byte_len;
  STRCPY (s1_ਪੰਨਾ_ਸਿਰਾ, s1_ਢੇਰ);

  /* Haystack which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s1_ਪੰਨਾ_cross = (ਖਾਲੀ *) buf1 + ਪੰਨਾ_ਮਾਪ_real - 8;
  STRCPY (s1_ਪੰਨਾ_cross, s1_ਢੇਰ);

  /* Needle at end of page.  The following page is protected.  */
  CHAR *s2_ਪੰਨਾ_ਸਿਰਾ = (ਖਾਲੀ *) buf2 + ਪੰਨਾ_ਮਾਪ - s2_byte_len;
  STRCPY (s2_ਪੰਨਾ_ਸਿਰਾ, s2_ਢੇਰ);

  /* Needle which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s2_ਪੰਨਾ_cross = (ਖਾਲੀ *) buf2 + ਪੰਨਾ_ਮਾਪ_real - 8;
  STRCPY (s2_ਪੰਨਾ_cross, s2_ਢੇਰ);

  exp_ਨਤੀਜਾ = simple_strstr (s1_ਢੇਰ, s2_ਢੇਰ);
  FOR_EACH_IMPL (impl, 0)
    {
      check_ਨਤੀਜਾ (impl, s1_ਢੇਰ, s2_ਢੇਰ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਢੇਰ, s2_ਪੰਨਾ_ਸਿਰਾ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਢੇਰ, s2_ਪੰਨਾ_cross, exp_ਨਤੀਜਾ);

      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_ਸਿਰਾ, s2_ਢੇਰ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_ਸਿਰਾ, s2_ਪੰਨਾ_ਸਿਰਾ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_ਸਿਰਾ, s2_ਪੰਨਾ_cross, exp_ਨਤੀਜਾ);

      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_cross, s2_ਢੇਰ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_cross, s2_ਪੰਨਾ_ਸਿਰਾ, exp_ਨਤੀਜਾ);
      check_ਨਤੀਜਾ (impl, s1_ਪੰਨਾ_cross, s2_ਪੰਨਾ_cross, exp_ਨਤੀਜਾ);
    }
}

ਸਥਿਰ ਖਾਲੀ
check3 (ਖਾਲੀ)
{
  /* Check that a long periodic needle does not cause false positives.  */
  {
    ਅਚਲ CHAR ਨਿਵੇਸ਼[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_A7_20_EF_BF_BD");
    ਅਚਲ CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, ਨਿਵੇਸ਼, need, ਨਿਰਾ);
  }

  {
    ਅਚਲ CHAR ਨਿਵੇਸ਼[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20"
			   "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    ਅਚਲ CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, ਨਿਵੇਸ਼, need, (CHAR *) ਨਿਵੇਸ਼ + 115);
  }
}


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ N 1024

ਸਥਿਰ ਖਾਲੀ
pr23637 (ਖਾਲੀ)
{
  CHAR *h = (CHAR*) buf1;
  CHAR *n = (CHAR*) buf2;

  ਲਈ (ਪੂਰਨ i = 0; i < N; i++)
    {
      n[i] = 'x';
      h[i] = ' ';
      h[i + N] = 'x';
    }

  n[N] = '\0';
  h[N * 2] = '\0';

  /* Ensure we don't match at the first 'x'.  */
  h[0] = 'x';

  CHAR *exp_ਨਤੀਜਾ = simple_strstr (h, n);
  FOR_EACH_IMPL (impl, 0)
    check_ਨਤੀਜਾ (impl, h, n, exp_ਨਤੀਜਾ);
}

ਸਥਿਰ ਖਾਲੀ
pr23865 (ਖਾਲੀ)
{
  /* Check that a very long haystack is handled quickly if the needle is
     short and occurs near the beginning.  */
  {
    size_t m = 1000000;
    ਅਚਲ CHAR *needle =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    CHAR *haystack = xmalloc ((m + 1) * ਆਕਾਰ (CHAR));
    MEMSET (haystack, L('A'), m);
    haystack[0] = L('B');
    haystack[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, haystack + 1);

    ਮੁਕਤ (haystack);
  }

  /* Check that a very long needle is discarded quickly if the haystack is
     short.  */
  {
    size_t m = 1000000;
    ਅਚਲ CHAR *haystack =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    CHAR *needle = xmalloc ((m + 1) * ਆਕਾਰ (CHAR));
    MEMSET (needle, L'A', m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, ਨਿਰਾ);

    ਮੁਕਤ (needle);
  }

  /* Check that the asymptotic worst-case complexity is not quadratic.  */
  {
    size_t m = 1000000;
    CHAR *haystack = xmalloc ((2 * m + 2) * ਆਕਾਰ (CHAR));
    CHAR *needle = xmalloc ((m + 2) * ਆਕਾਰ (CHAR));

    MEMSET (haystack, L('A'), 2 * m);
    haystack[2 * m] = L('B');
    haystack[2 * m + 1] = L('\0');

    MEMSET (needle, L('A'), m);
    needle[m] = L('B');
    needle[m + 1] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, haystack + m);

    ਮੁਕਤ (needle);
    ਮੁਕਤ (haystack);
  }

  {
    /* Ensure that with a barely periodic "short" needle, STRSTR's
       search does not mistakenly skip just past the match point.  */
    ਅਚਲ CHAR *haystack =
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
    ਅਚਲ CHAR *needle =
      L("\n"
       "with_gnu_ld\n");

    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, (CHAR*) haystack + 114);
  }

  {
    /* Same bug, shorter trigger.  */
    ਅਚਲ CHAR *haystack = L("..wi.d.");
    ਅਚਲ CHAR *needle = L(".d.");
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, (CHAR*) haystack + 4);
  }

  /* Test case from Yves Bastide.
     <https://www.openwall.com/lists/musl/2014/04/18/2>  */
  {
    ਅਚਲ CHAR *ਨਿਵੇਸ਼ = L("playing play play play always");
    ਅਚਲ CHAR *needle = L("play play play");
    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, ਨਿਵੇਸ਼, needle, (CHAR*) ਨਿਵੇਸ਼ + 8);
  }

  /* Test long needles.  */
  {
    size_t m = 1024;
    CHAR *haystack = xmalloc ((2 * m + 1) * ਆਕਾਰ (CHAR));
    CHAR *needle = xmalloc ((m + 1) * ਆਕਾਰ (CHAR));
    haystack[0] = L('x');
    MEMSET (haystack + 1, L(' '), m - 1);
    MEMSET (haystack + m, L('x'), m);
    haystack[2 * m] = L('\0');
    MEMSET (needle, L('x'), m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ਨਤੀਜਾ (impl, haystack, needle, haystack + m);

    ਮੁਕਤ (needle);
    ਮੁਕਤ (haystack);
  }
}

ਸਥਿਰ ਪੂਰਨ
test_main (ਖਾਲੀ)
{
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  pr23637 ();
  pr23865 ();

  ਲਿਖੋ ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    ਲਿਖੋ ("\t%s", impl->name);
  ਅੱਖਰ_ਲਿਖੋ ('\n');

  ਲਈ (size_t klen = 2; klen < 32; ++klen)
    ਲਈ (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, ਪੰਨਾ_ਮਾਪ - 1, 16, 0);
  do_test (0, 0, ਪੰਨਾ_ਮਾਪ - 1, 16, 1);

  ਵਾਪਸ ret;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
