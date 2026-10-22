/* Check that strerror, strerror_l do not return NULL on  failure (bug 30555).
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


#ଅନ୍ତର୍ଭାଵ <locale.h>
#ଅନ୍ତର୍ଭାଵ <stdbool.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <support/check.h>
#ଅନ୍ତର୍ଭାଵ <support/namespace.h>
#ଅନ୍ତର୍ଭାଵ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

ସ୍ଥିର ଅସ୍ଥିର bool fail_malloc;

ଶୂନ୍ୟ *
malloc (size_t size)
{
  ଯଦି (fail_malloc)
    ଫେରନ୍ତୁ ଖାଲି;

  ସ୍ଥିର ଶୂନ୍ୟ *(*original_malloc) (size_t);
  ଯଦି (original_malloc == ଖାଲି)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  ଫେରନ୍ତୁ original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ସ୍ଥିର ଶୂନ୍ୟ
test_strerror (ଶୂନ୍ୟ *closure)
{
  fail_malloc = true;
  ଅଚଳ ଅକ୍ଷର *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ସ୍ଥିର ଶୂନ୍ୟ
test_strerror_l (ଶୂନ୍ୟ *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ଅଚଳ ଅକ୍ଷର *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  support_isolate_in_subprocess (test_strerror, ଖାଲି);
  support_isolate_in_subprocess (test_strerror_l, ଖାଲି);

  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
