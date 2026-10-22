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


#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <stdbool.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <support/check.h>
#அந்தர்பாவ <support/namespace.h>
#அந்தர்பாவ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

நிலையான நிலையற்ற bool fail_malloc;

வெறுமை *
malloc (size_t size)
{
  எனில் (fail_malloc)
    திரும்பு வெற்று;

  நிலையான வெறுமை *(*original_malloc) (size_t);
  எனில் (original_malloc == வெற்று)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  திரும்பு original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

நிலையான வெறுமை
test_strerror (வெறுமை *closure)
{
  fail_malloc = true;
  மாறிலி எழுத்து *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

நிலையான வெறுமை
test_strerror_l (வெறுமை *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  மாறிலி எழுத்து *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

நிலையான முழு
do_test (வெறுமை)
{
  support_isolate_in_subprocess (test_strerror, வெற்று);
  support_isolate_in_subprocess (test_strerror_l, வெற்று);

  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
