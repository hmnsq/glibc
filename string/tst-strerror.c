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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <locale.h>
#અન્તર્ભાવ <array_length.h>

#અન્તર્ભાવ <support/support.h>
#અન્તર્ભાવ <support/check.h>

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strerror (EINVAL), "Invalid argument");
  TEST_COMPARE_STRING (strerror (-1),     "Unknown error -1");

  {
    અક્ષર buffer[32];
    TEST_COMPARE_STRING (strerror_r (EINVAL, buffer, 8),
			 "Invalid argument");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 8),
			 "Unknown");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 16),
			 "Unknown error -");
    TEST_COMPARE_STRING (strerror_r (-1, buffer, 32),
			 "Unknown error -1");
  }

  locale_t l = xnewlocale (LC_ALL_MASK, "pt_BR.UTF-8", ખાલી);

  TEST_COMPARE_STRING (strerror_l (EINVAL, l), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror_l (-1, l),     "Erro desconhecido -1");

  xuselocale (l);

  TEST_COMPARE_STRING (strerror (EINVAL), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror (-1),     "Erro desconhecido -1");

  {
    અક્ષર buffer[32];
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

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
