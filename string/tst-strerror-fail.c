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


#شامل <locale.h>
#شامل <stdbool.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <support/check.h>
#شامل <support/namespace.h>
#شامل <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

ساکن متلون bool fail_malloc;

خالی *
حافظہ_دو (size_t سائز)
{
  اگر (fail_malloc)
    واپس تہی;

  ساکن خالی *(*original_malloc) (size_t);
  اگر (original_malloc == تہی)
    original_malloc = xdlsym (RTLD_اگلا, "malloc");
  واپس original_malloc (سائز);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ساکن خالی
test_strerror (خالی *احاطہ)
{
  fail_malloc = true;
  ثابت حرف *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ساکن خالی
test_strerror_l (خالی *احاطہ)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ثابت حرف *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ساکن صحیح
do_test (خالی)
{
  support_isolate_اندر_subprocess (test_strerror, تہی);
  support_isolate_اندر_subprocess (test_strerror_l, تہی);

  واپس 0;
}

#شامل <support/test-driver.c>
