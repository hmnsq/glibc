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

ಸ್ಥಿರ ಅಸ್ಥಿರ bool fail_malloc;

ಶೂನ್ಯ *
ಸ್ಮರಣೆ_ಕೊಡು (size_t ಗಾತ್ರ_2)
{
  ಆದರೆ (fail_malloc)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಸ್ಥಿರ ಶೂನ್ಯ *(*original_malloc) (size_t);
  ಆದರೆ (original_malloc == ಖಾಲಿ)
    original_malloc = xdlsym (RTLD_ಮುಂದಿನ, "malloc");
  ಹಿಂತಿರುಗಿ original_malloc (ಗಾತ್ರ_2);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ಸ್ಥಿರ ಶೂನ್ಯ
test_strerror (ಶೂನ್ಯ *ಆವರಣ)
{
  fail_malloc = true;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ಸ್ಥಿರ ಶೂನ್ಯ
test_strerror_l (ಶೂನ್ಯ *ಆವರಣ)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  support_isolate_ಒಳ_subprocess (test_strerror, ಖಾಲಿ);
  support_isolate_ಒಳ_subprocess (test_strerror_l, ಖಾಲಿ);

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
