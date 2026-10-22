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


#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/namespace.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

ਸਥਿਰ ਅਸਥਿਰ bool fail_malloc;

ਖਾਲੀ *
ਸਮ੍ਰਿਤੀ_ਦਿਓ (size_t ਮਾਪ)
{
  ਜੇ (fail_malloc)
    ਵਾਪਸ ਨਿਰਾ;

  ਸਥਿਰ ਖਾਲੀ *(*original_malloc) (size_t);
  ਜੇ (original_malloc == ਨਿਰਾ)
    original_malloc = xdlsym (RTLD_ਅਗਲਾ, "malloc");
  ਵਾਪਸ original_malloc (ਮਾਪ);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ਸਥਿਰ ਖਾਲੀ
test_strerror (ਖਾਲੀ *ਘੇਰਾ)
{
  fail_malloc = true;
  ਅਚਲ ਅੱਖਰ *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ਸਥਿਰ ਖਾਲੀ
test_strerror_l (ਖਾਲੀ *ਘੇਰਾ)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ਅਚਲ ਅੱਖਰ *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  support_isolate_ਵਿੱਚ_subprocess (test_strerror, ਨਿਰਾ);
  support_isolate_ਵਿੱਚ_subprocess (test_strerror_l, ਨਿਰਾ);

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
