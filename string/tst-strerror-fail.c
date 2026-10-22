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


#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <stdbool.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <support/check.h>
#અન્તર્ભાવ <support/namespace.h>
#અન્તર્ભાવ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

સ્થિર અસ્થિર bool fail_malloc;

શૂન્ય *
malloc (size_t size)
{
  જો (fail_malloc)
    પાછા ખાલી;

  સ્થિર શૂન્ય *(*original_malloc) (size_t);
  જો (original_malloc == ખાલી)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  પાછા original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

સ્થિર શૂન્ય
test_strerror (શૂન્ય *closure)
{
  fail_malloc = true;
  અચલ અક્ષર *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

સ્થિર શૂન્ય
test_strerror_l (શૂન્ય *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  અચલ અક્ષર *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  support_isolate_in_subprocess (test_strerror, ખાલી);
  support_isolate_in_subprocess (test_strerror_l, ખાલી);

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
