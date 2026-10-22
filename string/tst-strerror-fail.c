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


#ضمن <locale.h>
#ضمن <stdbool.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <support/check.h>
#ضمن <support/namespace.h>
#ضمن <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

ساكن متطاير bool fail_malloc;

فراغ *
malloc (size_t size)
{
  𐤀𐤌 (fail_malloc)
    أرجع عدم;

  ساكن فراغ *(*original_malloc) (size_t);
  𐤀𐤌 (original_malloc == عدم)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  أرجع original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

ساكن فراغ
test_strerror (فراغ *closure)
{
  fail_malloc = true;
  ثابت حرف *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

ساكن فراغ
test_strerror_l (فراغ *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  ثابت حرف *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

ساكن صحيح
do_test (فراغ)
{
  support_isolate_in_subprocess (test_strerror, عدم);
  support_isolate_in_subprocess (test_strerror_l, عدم);

  أرجع 0;
}

#ضمن <support/test-driver.c>
