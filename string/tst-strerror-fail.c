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


#समावेश <locale.h>
#समावेश <stdbool.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <support/check.h>
#समावेश <support/namespace.h>
#समावेश <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

अटल अस्थिर bool fail_malloc;

व्योम *
दो_स्मृति (माप_प्रकार आकार)
{
  अगर (fail_malloc)
    वापस शून्य;

  अटल व्योम *(*original_malloc) (माप_प्रकार);
  अगर (original_malloc == शून्य)
    original_malloc = xdlsym (RTLD_अग्र, "malloc");
  वापस original_malloc (आकार);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

अटल व्योम
test_strerror (व्योम *closure)
{
  fail_malloc = true;
  स्थिर अक्षर *s = म_त्रुटि (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

अटल व्योम
test_strerror_l (व्योम *closure)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  स्थिर अक्षर *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

अटल पूर्णांक
do_test (व्योम)
{
  support_isolate_in_subprocess (test_strerror, शून्य);
  support_isolate_in_subprocess (test_strerror_l, शून्य);

  वापस 0;
}

#समावेश <support/test-driver.c>
