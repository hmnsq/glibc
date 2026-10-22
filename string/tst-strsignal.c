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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <support/support.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strsignal (SIGINT),     "Interrupt");
  TEST_COMPARE_STRING (strsignal (-1),         "Unknown signal -1");
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SIGRTMIN
  ਜੇ (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),   "Real-time signal 0");
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SIGRTMAX
  ਜੇ (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Unknown signal 65");
#ਜੇ_ਅੰਤ

  xsetlocale (LC_ALL, "pt_BR.UTF-8");

  TEST_COMPARE_STRING (strsignal (SIGINT),    "Interrup\xc3\xa7\xc3\xa3\x6f");
  TEST_COMPARE_STRING (strsignal (-1),        "Sinal desconhecido -1");
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SIGRTMI
  ਜੇ (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),  "Sinal de tempo-real 0");
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SIGRTMAX
  ਜੇ (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Sinal desconhecido 65");
#ਜੇ_ਅੰਤ

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
