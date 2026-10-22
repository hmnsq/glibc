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


#ಅನ್ತರ್ಭಾವ <locale.h>
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/namespace.h>
#ಅನ್ತರ್ಭಾವ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

ಸ್ಥಿರ ಚಞ್ಚಲ bool fail_malloc;

ಶೂನ್ಯ *
malloc (size_t size)
{
  ಯದಿ (fail_malloc)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  ಸ್ಥಿರ ಶೂನ್ಯ *(*original_malloc) (size_t);
  ಯದಿ (original_malloc == ರಿಕ್ತ)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  ಪ್ರತ್ಯಾಗಮ original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ಸ್ಥಿರ ಶೂನ್ಯ
test_strerror (ಶೂನ್ಯ *closure)
{
  fail_malloc = true;
  ಧ್ರುವ ವರ್ಣ *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ಸ್ಥಿರ ಶೂನ್ಯ
test_strerror_l (ಶೂನ್ಯ *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ಧ್ರುವ ವರ್ಣ *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  support_isolate_in_subprocess (test_strerror, ರಿಕ್ತ);
  support_isolate_in_subprocess (test_strerror_l, ರಿಕ್ತ);

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
