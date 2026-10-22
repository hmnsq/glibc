/* Test for strerror, strerror_r, and strerror_l.

   Copyright (C) 2020-2026 Free Software Foundation, Inc.
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

#அந்தர்பாவ <string.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <locale.h>
#அந்தர்பாவ <array_length.h>

#அந்தர்பாவ <support/support.h>
#அந்தர்பாவ <support/check.h>

நிலையான முழு
do_test (வெறுமை)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strerror (EINVAL), "Invalid argument");
  TEST_COMPARE_STRING (strerror (-1),     "Unknown error -1");

  {
    எழுத்து buffer[32];
    TEST_COMPARE_STRING (strerror_r (EINVAL, buffer, 8),
			 "Invalid argument");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 8),
			 "Unknown");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 16),
			 "Unknown error -");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 32),
			 "Unknown error -1");
  }

  locale_t l = xnewlocale (LC_ALL_MASK, "pt_BR.UTF-8", வெற்று);

  TEST_COMPARE_STRING (strerror_l (EINVAL, l), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror_l (-1, l),     "Erro desconhecido -1");

  xuselocale (l);

  TEST_COMPARE_STRING (strerror (EINVAL), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror (-1),     "Erro desconhecido -1");

  {
    எழுத்து buffer[32];
    TEST_COMPARE_STRING (strerror_r (EINVAL, buffer, 8),
			 "Argumento inv\303\241lido");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 8),
			 "Erro de");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 16),
			 "Erro desconheci");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 32),
			 "Erro desconhecido -1");
  }

  freelocale (l);

  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
