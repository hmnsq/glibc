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


#അന്തര്ഭാവ <locale.h>
#അന്തര്ഭാവ <stdbool.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/check.h>
#അന്തര്ഭാവ <support/namespace.h>
#അന്തര്ഭാവ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

സ്ഥിതം അസ്ഥിര bool fail_malloc;

ശൂന്യം *
malloc (size_t size)
{
  എങ്കിൽ (fail_malloc)
    തിരികെ ശൂന്യ;

  സ്ഥിതം ശൂന്യം *(*original_malloc) (size_t);
  എങ്കിൽ (original_malloc == ശൂന്യ)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  തിരികെ original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

സ്ഥിതം ശൂന്യം
test_strerror (ശൂന്യം *closure)
{
  fail_malloc = true;
  സ്ഥിരം അക്ഷരം *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

സ്ഥിതം ശൂന്യം
test_strerror_l (ശൂന്യം *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  സ്ഥിരം അക്ഷരം *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  support_isolate_in_subprocess (test_strerror, ശൂന്യ);
  support_isolate_in_subprocess (test_strerror_l, ശൂന്യ);

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
