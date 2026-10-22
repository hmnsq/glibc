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


#অন্তর্ভাৱ <locale.h>
#অন্তর্ভাৱ <stdbool.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <support/check.h>
#অন্তর্ভাৱ <support/namespace.h>
#অন্তর্ভাৱ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

স্থির চঞ্চল bool fail_malloc;

শূন্য *
malloc (size_t size)
{
  যদি (fail_malloc)
    ঘূৰাই রিক্ত;

  স্থির শূন্য *(*original_malloc) (size_t);
  যদি (original_malloc == রিক্ত)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  ঘূৰাই original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

স্থির শূন্য
test_strerror (শূন্য *closure)
{
  fail_malloc = true;
  ধ্রুৱ ৱর্ণ *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

স্থির শূন্য
test_strerror_l (শূন্য *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ধ্রুৱ ৱর্ণ *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

স্থির পূর্ণাঙ্ক
do_test (শূন্য)
{
  support_isolate_in_subprocess (test_strerror, রিক্ত);
  support_isolate_in_subprocess (test_strerror_l, রিক্ত);

  ঘূৰাই 0;
}

#অন্তর্ভাৱ <support/test-driver.c>
