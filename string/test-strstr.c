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

#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "strstr"
# define TEST_FUNC అక్షరశ్రేణి_శోధన
#లేకపోతే
# define TEST_NAME "wcsstr"
# define TEST_FUNC wcsstr
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే WIDE
# define CHAR అక్షరం
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STRCPY strcpy
# define MEMCPY జ్ఞాపకం_నకలు
# define MEMSET memset
# define MEMPCPY mempcpy
# define L(s) s
#లేకపోతే
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
# define BUF1_పుటలు 4
#అయితే_ముగింపు

#అన్తర్భావ "test-string.h"

#నిర్వచితం_కాకపోతే WIDE
# define STRSTR c_strstr
# define libc_hidden_builtin_def(arg) /* nothing */
# define __strnlen strnlen
# include "strstr.c"
# define C_IMPL STRSTR
#లేకపోతే
# undef weak_alias
# define weak_alias(a, b)
# define WCSSTR c_wcsstr
# define __wmemcmp wmemcmp
# define __wcsnlen wcsnlen
# define __wcslen wcslen
# include "wcsstr.c"
# define C_IMPL WCSSTR
#అయితే_ముగింపు

/* Naive implementation to verify results.  */
స్థిర CHAR *
simple_strstr (స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2)
{
  ssize_t s1len = STRLEN (s1);
  ssize_t s2len = STRLEN (s2);

  ఒకవేళ (s2len > s1len)
    తిరిగి ఖాళీ;

  కొరకు (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      size_t j;
      కొరకు (j = 0; j < s2len; ++j)
	ఒకవేళ (s1[i + j] != s2[j])
	  ఆపు;
      ఒకవేళ (j == s2len)
	తిరిగి (CHAR *) s1 + i;
    }

  తిరిగి ఖాళీ;
}


రకనిర్వచనం CHAR *(*proto_t) (స్థిరరాశి CHAR *, స్థిరరాశి CHAR *);

IMPL (C_IMPL, 1)
IMPL (TEST_FUNC, 1)

స్థిర పూర్ణాంకం
check_ఫలితం (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2,
	      CHAR *exp_ఫలితం)
{
  CHAR *ఫలితం = CALL (impl, s1, s2);
  ఒకవేళ (ఫలితం != exp_ఫలితం)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     ఫలితం, exp_ఫలితం);
      ret = 1;
      తిరిగి -1;
    }

  తిరిగి 0;
}

స్థిర శూన్య
do_one_test (impl_t *impl, స్థిరరాశి CHAR *s1, స్థిరరాశి CHAR *s2, CHAR *exp_ఫలితం)
{
  ఒకవేళ (check_ఫలితం (impl, s1, s2, exp_ఫలితం) < 0)
    తిరిగి;
}


స్థిర శూన్య
do_test (size_t align1, size_t align2, size_t len1, size_t len2,
	 పూర్ణాంకం fail)
{
  align1 = align1 * పరిమాణం (CHAR);
  align2 = align2 * పరిమాణం (CHAR);

  CHAR *s1 = (CHAR *) (buf1 + align1);
  CHAR *s2 = (CHAR *) (buf2 + align2);

  స్థిర స్థిరరాశి CHAR d[] = L("1234567890abcdef");
  స్థిరరాశి size_t dl = STRLEN (d);
  CHAR *ss2 = s2;
  కొరకు (size_t l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      size_t t = l > dl ? dl : l;
      ss2 = MEMPCPY (ss2, d, t);
    }
  s2[len2] = '\0';

  ఒకవేళ (fail)
    {
      CHAR *ss1 = s1;
      కొరకు (size_t l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  size_t t = l > dl ? dl : l;
	  MEMCPY (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  లేకపోతే
    {
      MEMSET (s1, '0', len1);
      MEMCPY (s1 + len1 - len2, s2, len2);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? ఖాళీ : s1 + len1 - len2);
}

స్థిర శూన్య
check1 (శూన్య)
{
  స్థిరరాశి CHAR s1[] =
    L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD");
  స్థిరరాశి CHAR s2[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
  CHAR *exp_ఫలితం;

  exp_ఫలితం = simple_strstr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, s1, s2, exp_ఫలితం);
}

స్థిర శూన్య
check2 (శూన్య)
{
  స్థిరరాశి CHAR s1_దొంతర[] = L(", enable_static, \0, enable_shared, ");
  స్థిరరాశి size_t s1_char_లెక్క = 18;
  స్థిరరాశి size_t s1_byte_len = 18 * పరిమాణం (CHAR);
  స్థిరరాశి CHAR *s2_దొంతర = &(s1_దొంతర[s1_char_లెక్క]);
  స్థిరరాశి size_t s2_byte_len = 18 * పరిమాణం (CHAR);
  CHAR *exp_ఫలితం;
  స్థిరరాశి size_t పుట_కొలత_real = getpagesize ();

  /* Haystack at end of page.  The following page is protected.  */
  CHAR *s1_పుట_చివర = (శూన్య *) buf1 + పుట_కొలత - s1_byte_len;
  STRCPY (s1_పుట_చివర, s1_దొంతర);

  /* Haystack which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s1_పుట_cross = (శూన్య *) buf1 + పుట_కొలత_real - 8;
  STRCPY (s1_పుట_cross, s1_దొంతర);

  /* Needle at end of page.  The following page is protected.  */
  CHAR *s2_పుట_చివర = (శూన్య *) buf2 + పుట_కొలత - s2_byte_len;
  STRCPY (s2_పుట_చివర, s2_దొంతర);

  /* Needle which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s2_పుట_cross = (శూన్య *) buf2 + పుట_కొలత_real - 8;
  STRCPY (s2_పుట_cross, s2_దొంతర);

  exp_ఫలితం = simple_strstr (s1_దొంతర, s2_దొంతర);
  FOR_EACH_IMPL (impl, 0)
    {
      check_ఫలితం (impl, s1_దొంతర, s2_దొంతర, exp_ఫలితం);
      check_ఫలితం (impl, s1_దొంతర, s2_పుట_చివర, exp_ఫలితం);
      check_ఫలితం (impl, s1_దొంతర, s2_పుట_cross, exp_ఫలితం);

      check_ఫలితం (impl, s1_పుట_చివర, s2_దొంతర, exp_ఫలితం);
      check_ఫలితం (impl, s1_పుట_చివర, s2_పుట_చివర, exp_ఫలితం);
      check_ఫలితం (impl, s1_పుట_చివర, s2_పుట_cross, exp_ఫలితం);

      check_ఫలితం (impl, s1_పుట_cross, s2_దొంతర, exp_ఫలితం);
      check_ఫలితం (impl, s1_పుట_cross, s2_పుట_చివర, exp_ఫలితం);
      check_ఫలితం (impl, s1_పుట_cross, s2_పుట_cross, exp_ఫలితం);
    }
}

స్థిర శూన్య
check3 (శూన్య)
{
  /* Check that a long periodic needle does not cause false positives.  */
  {
    స్థిరరాశి CHAR ఆదానం[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_A7_20_EF_BF_BD");
    స్థిరరాశి CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, ఆదానం, need, ఖాళీ);
  }

  {
    స్థిరరాశి CHAR ఆదానం[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20"
			   "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    స్థిరరాశి CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, ఆదానం, need, (CHAR *) ఆదానం + 115);
  }
}


#నిర్వచించు N 1024

స్థిర శూన్య
pr23637 (శూన్య)
{
  CHAR *h = (CHAR*) buf1;
  CHAR *n = (CHAR*) buf2;

  కొరకు (పూర్ణాంకం i = 0; i < N; i++)
    {
      n[i] = 'x';
      h[i] = ' ';
      h[i + N] = 'x';
    }

  n[N] = '\0';
  h[N * 2] = '\0';

  /* Ensure we don't match at the first 'x'.  */
  h[0] = 'x';

  CHAR *exp_ఫలితం = simple_strstr (h, n);
  FOR_EACH_IMPL (impl, 0)
    check_ఫలితం (impl, h, n, exp_ఫలితం);
}

స్థిర శూన్య
pr23865 (శూన్య)
{
  /* Check that a very long haystack is handled quickly if the needle is
     short and occurs near the beginning.  */
  {
    size_t m = 1000000;
    స్థిరరాశి CHAR *needle =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    CHAR *haystack = xmalloc ((m + 1) * పరిమాణం (CHAR));
    MEMSET (haystack, L('A'), m);
    haystack[0] = L('B');
    haystack[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, haystack + 1);

    విడుదల (haystack);
  }

  /* Check that a very long needle is discarded quickly if the haystack is
     short.  */
  {
    size_t m = 1000000;
    స్థిరరాశి CHAR *haystack =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    CHAR *needle = xmalloc ((m + 1) * పరిమాణం (CHAR));
    MEMSET (needle, L'A', m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, ఖాళీ);

    విడుదల (needle);
  }

  /* Check that the asymptotic worst-case complexity is not quadratic.  */
  {
    size_t m = 1000000;
    CHAR *haystack = xmalloc ((2 * m + 2) * పరిమాణం (CHAR));
    CHAR *needle = xmalloc ((m + 2) * పరిమాణం (CHAR));

    MEMSET (haystack, L('A'), 2 * m);
    haystack[2 * m] = L('B');
    haystack[2 * m + 1] = L('\0');

    MEMSET (needle, L('A'), m);
    needle[m] = L('B');
    needle[m + 1] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, haystack + m);

    విడుదల (needle);
    విడుదల (haystack);
  }

  {
    /* Ensure that with a barely periodic "short" needle, STRSTR's
       search does not mistakenly skip just past the match point.  */
    స్థిరరాశి CHAR *haystack =
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
    స్థిరరాశి CHAR *needle =
      L("\n"
       "with_gnu_ld\n");

    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, (CHAR*) haystack + 114);
  }

  {
    /* Same bug, shorter trigger.  */
    స్థిరరాశి CHAR *haystack = L("..wi.d.");
    స్థిరరాశి CHAR *needle = L(".d.");
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, (CHAR*) haystack + 4);
  }

  /* Test case from Yves Bastide.
     <https://www.openwall.com/lists/musl/2014/04/18/2>  */
  {
    స్థిరరాశి CHAR *ఆదానం = L("playing play play play always");
    స్థిరరాశి CHAR *needle = L("play play play");
    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, ఆదానం, needle, (CHAR*) ఆదానం + 8);
  }

  /* Test long needles.  */
  {
    size_t m = 1024;
    CHAR *haystack = xmalloc ((2 * m + 1) * పరిమాణం (CHAR));
    CHAR *needle = xmalloc ((m + 1) * పరిమాణం (CHAR));
    haystack[0] = L('x');
    MEMSET (haystack + 1, L(' '), m - 1);
    MEMSET (haystack + m, L('x'), m);
    haystack[2 * m] = L('\0');
    MEMSET (needle, L('x'), m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_ఫలితం (impl, haystack, needle, haystack + m);

    విడుదల (needle);
    విడుదల (haystack);
  }
}

స్థిర పూర్ణాంకం
test_main (శూన్య)
{
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  pr23637 ();
  pr23865 ();

  రాయి ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    రాయి ("\t%s", impl->name);
  అక్షరం_రాయి ('\n');

  కొరకు (size_t klen = 2; klen < 32; ++klen)
    కొరకు (size_t hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, పుట_కొలత - 1, 16, 0);
  do_test (0, 0, పుట_కొలత - 1, 16, 1);

  తిరిగి ret;
}

#అన్తర్భావ <support/test-driver.c>
