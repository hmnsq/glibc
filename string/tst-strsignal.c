/* Test for strsignal.

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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <locale.h>
#অন্তর্ভাব <array_length.h>

#অন্তর্ভাব <support/support.h>
#অন্তর্ভাব <support/check.h>

স্থির পূর্ণাঙ্ক
do_test (শূন্য)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strsignal (SIGINT),     "Interrupt");
  TEST_COMPARE_STRING (strsignal (-1),         "Unknown signal -1");
#ifdef SIGRTMIN
  যদি (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),   "Real-time signal 0");
#endif
#ifdef SIGRTMAX
  যদি (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Unknown signal 65");
#endif

  xsetlocale (LC_ALL, "pt_BR.UTF-8");

  TEST_COMPARE_STRING (strsignal (SIGINT),    "Interrup\xc3\xa7\xc3\xa3\x6f");
  TEST_COMPARE_STRING (strsignal (-1),        "Sinal desconhecido -1");
#ifdef SIGRTMI
  যদি (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),  "Sinal de tempo-real 0");
#endif
#ifdef SIGRTMAX
  যদি (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Sinal desconhecido 65");
#endif

  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>
