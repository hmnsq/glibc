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

#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "strstr"
# define TEST_FUNC म_माला
#अन्यथा
# define TEST_NAME "wcsstr"
# define TEST_FUNC wcsstr
#पूर्ण_अगर

#अगर_अघोषित WIDE
# define CHAR अक्षर
# define STRLEN म_माप
# define STRCPY म_नकल
# define MEMCPY स_नकल
# define MEMSET स_रखो
# define MEMPCPY mempcpy
# define L(s) s
#अन्यथा
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define STRLEN wcslen
# define STRCPY wcscpy
# define MEMCPY wmemcpy
# define MEMSET wmemset
# define MEMPCPY wmempcpy
# define L(s) L ## s
/* The test requires up to 8191 characters, so allocate at least 32Kb
   (considering 4kb page size).  */
# define BUF1PAGES 4
#पूर्ण_अगर

#समावेश "test-string.h"

#अगर_अघोषित WIDE
# define STRSTR c_strstr
# define libc_hidden_builtin_def(arg) /* nothing */
# define __strnlen strnlen
# include "strstr.c"
# define C_IMPL STRSTR
#अन्यथा
# undef weak_alias
# define weak_alias(a, b)
# define WCSSTR c_wcsstr
# define __wmemcmp wmemcmp
# define __wcsnlen wcsnlen
# define __wcslen wcslen
# include "wcsstr.c"
# define C_IMPL WCSSTR
#पूर्ण_अगर

/* Naive implementation to verify results.  */
अटल CHAR *
simple_strstr (स्थिर CHAR *s1, स्थिर CHAR *s2)
{
  ssize_t s1len = STRLEN (s1);
  ssize_t s2len = STRLEN (s2);

  अगर (s2len > s1len)
    वापस शून्य;

  क्रम (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
      माप_प्रकार j;
      क्रम (j = 0; j < s2len; ++j)
	अगर (s1[i + j] != s2[j])
	  अवरोध;
      अगर (j == s2len)
	वापस (CHAR *) s1 + i;
    }

  वापस शून्य;
}


प्रकार CHAR *(*proto_t) (स्थिर CHAR *, स्थिर CHAR *);

IMPL (C_IMPL, 1)
IMPL (TEST_FUNC, 1)

अटल पूर्णांक
check_परिणाम (impl_t *impl, स्थिर CHAR *s1, स्थिर CHAR *s2,
	      CHAR *exp_परिणाम)
{
  CHAR *परिणाम = CALL (impl, s1, s2);
  अगर (परिणाम != exp_परिणाम)
    {
      error (0, 0, "Wrong result in function %s %p %p", impl->name,
	     परिणाम, exp_परिणाम);
      ret = 1;
      वापस -1;
    }

  वापस 0;
}

अटल व्योम
do_one_test (impl_t *impl, स्थिर CHAR *s1, स्थिर CHAR *s2, CHAR *exp_परिणाम)
{
  अगर (check_परिणाम (impl, s1, s2, exp_परिणाम) < 0)
    वापस;
}


अटल व्योम
do_test (माप_प्रकार align1, माप_प्रकार align2, माप_प्रकार len1, माप_प्रकार len2,
	 पूर्णांक fail)
{
  align1 = align1 * माप (CHAR);
  align2 = align2 * माप (CHAR);

  CHAR *s1 = (CHAR *) (buf1 + align1);
  CHAR *s2 = (CHAR *) (buf2 + align2);

  अटल स्थिर CHAR d[] = L("1234567890abcdef");
  स्थिर माप_प्रकार dl = STRLEN (d);
  CHAR *ss2 = s2;
  क्रम (माप_प्रकार l = len2; l > 0; l = l > dl ? l - dl : 0)
    {
      माप_प्रकार t = l > dl ? dl : l;
      ss2 = MEMPCPY (ss2, d, t);
    }
  s2[len2] = '\0';

  अगर (fail)
    {
      CHAR *ss1 = s1;
      क्रम (माप_प्रकार l = len1; l > 0; l = l > dl ? l - dl : 0)
	{
	  माप_प्रकार t = l > dl ? dl : l;
	  MEMCPY (ss1, d, t);
	  ++ss1[len2 > 7 ? 7 : len2 - 1];
	  ss1 += t;
	}
    }
  अन्यथा
    {
      MEMSET (s1, '0', len1);
      MEMCPY (s1 + len1 - len2, s2, len2);
    }
  s1[len1] = '\0';

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, s1, s2, fail ? शून्य : s1 + len1 - len2);
}

अटल व्योम
check1 (व्योम)
{
  स्थिर CHAR s1[] =
    L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD_C3_A7_20_EF_BF_BD");
  स्थिर CHAR s2[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
  CHAR *exp_परिणाम;

  exp_परिणाम = simple_strstr (s1, s2);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, s1, s2, exp_परिणाम);
}

अटल व्योम
check2 (व्योम)
{
  स्थिर CHAR s1_ढेर[] = L(", enable_static, \0, enable_shared, ");
  स्थिर माप_प्रकार s1_char_गिनती = 18;
  स्थिर माप_प्रकार s1_byte_len = 18 * माप (CHAR);
  स्थिर CHAR *s2_ढेर = &(s1_ढेर[s1_char_गिनती]);
  स्थिर माप_प्रकार s2_byte_len = 18 * माप (CHAR);
  CHAR *exp_परिणाम;
  स्थिर माप_प्रकार page_आकार_real = getpagesize ();

  /* Haystack at end of page.  The following page is protected.  */
  CHAR *s1_page_end = (व्योम *) buf1 + page_आकार - s1_byte_len;
  STRCPY (s1_page_end, s1_ढेर);

  /* Haystack which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s1_page_cross = (व्योम *) buf1 + page_आकार_real - 8;
  STRCPY (s1_page_cross, s1_ढेर);

  /* Needle at end of page.  The following page is protected.  */
  CHAR *s2_page_end = (व्योम *) buf2 + page_आकार - s2_byte_len;
  STRCPY (s2_page_end, s2_ढेर);

  /* Needle which crosses a page boundary.
     Note: page_size is at least 2 * getpagesize.  See test_init.  */
  CHAR *s2_page_cross = (व्योम *) buf2 + page_आकार_real - 8;
  STRCPY (s2_page_cross, s2_ढेर);

  exp_परिणाम = simple_strstr (s1_ढेर, s2_ढेर);
  FOR_EACH_IMPL (impl, 0)
    {
      check_परिणाम (impl, s1_ढेर, s2_ढेर, exp_परिणाम);
      check_परिणाम (impl, s1_ढेर, s2_page_end, exp_परिणाम);
      check_परिणाम (impl, s1_ढेर, s2_page_cross, exp_परिणाम);

      check_परिणाम (impl, s1_page_end, s2_ढेर, exp_परिणाम);
      check_परिणाम (impl, s1_page_end, s2_page_end, exp_परिणाम);
      check_परिणाम (impl, s1_page_end, s2_page_cross, exp_परिणाम);

      check_परिणाम (impl, s1_page_cross, s2_ढेर, exp_परिणाम);
      check_परिणाम (impl, s1_page_cross, s2_page_end, exp_परिणाम);
      check_परिणाम (impl, s1_page_cross, s2_page_cross, exp_परिणाम);
    }
}

अटल व्योम
check3 (व्योम)
{
  /* Check that a long periodic needle does not cause false positives.  */
  {
    स्थिर CHAR निवेश[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
                            "_C3_A7_20_EF_BF_BD");
    स्थिर CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, निवेश, need, शून्य);
  }

  {
    स्थिर CHAR निवेश[] = L("F_BD_CE_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_88_20_EF_BF_BD_EF_BF_BD_EF_BF_BD"
			   "_C3_A7_20_EF_BF_BD_DA_B5_C2_A6_20"
			   "_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    स्थिर CHAR need[] = L("_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD_EF_BF_BD");
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, निवेश, need, (CHAR *) निवेश + 115);
  }
}


#घोषणा N 1024

अटल व्योम
pr23637 (व्योम)
{
  CHAR *h = (CHAR*) buf1;
  CHAR *n = (CHAR*) buf2;

  क्रम (पूर्णांक i = 0; i < N; i++)
    {
      n[i] = 'x';
      h[i] = ' ';
      h[i + N] = 'x';
    }

  n[N] = '\0';
  h[N * 2] = '\0';

  /* Ensure we don't match at the first 'x'.  */
  h[0] = 'x';

  CHAR *exp_परिणाम = simple_strstr (h, n);
  FOR_EACH_IMPL (impl, 0)
    check_परिणाम (impl, h, n, exp_परिणाम);
}

अटल व्योम
pr23865 (व्योम)
{
  /* Check that a very long haystack is handled quickly if the needle is
     short and occurs near the beginning.  */
  {
    माप_प्रकार m = 1000000;
    स्थिर CHAR *needle =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    CHAR *haystack = xmalloc ((m + 1) * माप (CHAR));
    MEMSET (haystack, L('A'), m);
    haystack[0] = L('B');
    haystack[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, haystack + 1);

    मुक्त (haystack);
  }

  /* Check that a very long needle is discarded quickly if the haystack is
     short.  */
  {
    माप_प्रकार m = 1000000;
    स्थिर CHAR *haystack =
      L("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
	"ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB");
    CHAR *needle = xmalloc ((m + 1) * माप (CHAR));
    MEMSET (needle, L'A', m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, शून्य);

    मुक्त (needle);
  }

  /* Check that the asymptotic worst-case complexity is not quadratic.  */
  {
    माप_प्रकार m = 1000000;
    CHAR *haystack = xmalloc ((2 * m + 2) * माप (CHAR));
    CHAR *needle = xmalloc ((m + 2) * माप (CHAR));

    MEMSET (haystack, L('A'), 2 * m);
    haystack[2 * m] = L('B');
    haystack[2 * m + 1] = L('\0');

    MEMSET (needle, L('A'), m);
    needle[m] = L('B');
    needle[m + 1] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, haystack + m);

    मुक्त (needle);
    मुक्त (haystack);
  }

  {
    /* Ensure that with a barely periodic "short" needle, STRSTR's
       search does not mistakenly skip just past the match point.  */
    स्थिर CHAR *haystack =
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
    स्थिर CHAR *needle =
      L("\n"
       "with_gnu_ld\n");

    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, (CHAR*) haystack + 114);
  }

  {
    /* Same bug, shorter trigger.  */
    स्थिर CHAR *haystack = L("..wi.d.");
    स्थिर CHAR *needle = L(".d.");
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, (CHAR*) haystack + 4);
  }

  /* Test case from Yves Bastide.
     <https://www.openwall.com/lists/musl/2014/04/18/2>  */
  {
    स्थिर CHAR *निवेश = L("playing play play play always");
    स्थिर CHAR *needle = L("play play play");
    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, निवेश, needle, (CHAR*) निवेश + 8);
  }

  /* Test long needles.  */
  {
    माप_प्रकार m = 1024;
    CHAR *haystack = xmalloc ((2 * m + 1) * माप (CHAR));
    CHAR *needle = xmalloc ((m + 1) * माप (CHAR));
    haystack[0] = L('x');
    MEMSET (haystack + 1, L(' '), m - 1);
    MEMSET (haystack + m, L('x'), m);
    haystack[2 * m] = L('\0');
    MEMSET (needle, L('x'), m);
    needle[m] = L('\0');

    FOR_EACH_IMPL (impl, 0)
      check_परिणाम (impl, haystack, needle, haystack + m);

    मुक्त (needle);
    मुक्त (haystack);
  }
}

अटल पूर्णांक
test_main (व्योम)
{
  test_init ();

  check1 ();
  check2 ();
  check3 ();
  pr23637 ();
  pr23865 ();

  म_लिखो ("%23s", "");
  FOR_EACH_IMPL (impl, 0)
    म_लिखो ("\t%s", impl->name);
  अक्षर_दो ('\n');

  क्रम (माप_प्रकार klen = 2; klen < 32; ++klen)
    क्रम (माप_प्रकार hlen = 2 * klen; hlen < 16 * klen; hlen += klen)
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

  do_test (0, 0, page_आकार - 1, 16, 0);
  do_test (0, 0, page_आकार - 1, 16, 1);

  वापस ret;
}

#समावेश <support/test-driver.c>
