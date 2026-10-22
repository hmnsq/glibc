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

#అన్తర్భావ <string.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <locale.h>
#అన్తర్భావ <array_length.h>

#అన్తర్భావ <support/support.h>
#అన్తర్భావ <support/check.h>

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strsignal (SIGINT),     "Interrupt");
  TEST_COMPARE_STRING (strsignal (-1),         "Unknown signal -1");
#నిర్వచితమైతే SIGRTMIN
  ఒకవేళ (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),   "Real-time signal 0");
#అయితే_ముగింపు
#నిర్వచితమైతే SIGRTMAX
  ఒకవేళ (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Unknown signal 65");
#అయితే_ముగింపు

  xsetlocale (LC_ALL, "pt_BR.UTF-8");

  TEST_COMPARE_STRING (strsignal (SIGINT),    "Interrup\xc3\xa7\xc3\xa3\x6f");
  TEST_COMPARE_STRING (strsignal (-1),        "Sinal desconhecido -1");
#నిర్వచితమైతే SIGRTMI
  ఒకవేళ (SIGRTMIN < SIGRTMAX)
    TEST_COMPARE_STRING (strsignal (SIGRTMIN),  "Sinal de tempo-real 0");
#అయితే_ముగింపు
#నిర్వచితమైతే SIGRTMAX
  ఒకవేళ (SIGRTMAX == 64)
    TEST_COMPARE_STRING (strsignal (SIGRTMAX+1), "Sinal desconhecido 65");
#అయితే_ముగింపు

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
