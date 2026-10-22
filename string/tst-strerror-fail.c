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


#अन्तर्भाव <locale.h>
#अन्तर्भाव <stdbool.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/namespace.h>
#अन्तर्भाव <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

स्थिर अस्थिर bool fail_malloc;

शून्य *
दो_स्मृति (माप_प्रकार size)
{
  जर (fail_malloc)
    परत रिक्त;

  स्थिर शून्य *(*original_malloc) (माप_प्रकार);
  जर (original_malloc == रिक्त)
    original_malloc = xdlsym (RTLD_NEXT, "malloc");
  परत original_malloc (size);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

स्थिर शून्य
test_strerror (शून्य *closure)
{
  fail_malloc = true;
  स्थिरांक अक्षर *s = म_त्रुटि (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

स्थिर शून्य
test_strerror_l (शून्य *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  स्थिरांक अक्षर *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

स्थिर पूर्णांक
do_test (शून्य)
{
  support_isolate_in_subprocess (test_strerror, रिक्त);
  support_isolate_in_subprocess (test_strerror_l, रिक्त);

  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
