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


#అన్తర్భావ <locale.h>
#అన్తర్భావ <stdbool.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/namespace.h>
#అన్తర్భావ <support/xdlfcn.h>

/* Interposed malloc that can be used to inject allocation failures.  */

స్థిర అస్థిర bool fail_malloc;

శూన్య *
జ్ఞాపకం_ఇవ్వు (size_t కొలత)
{
  ఒకవేళ (fail_malloc)
    తిరిగి ఖాళీ;

  స్థిర శూన్య *(*original_malloc) (size_t);
  ఒకవేళ (original_malloc == ఖాళీ)
    original_malloc = xdlsym (RTLD_తదుపరి, "malloc");
  తిరిగి original_malloc (కొలత);
}

/* Callbacks for the actual tests.  Use fork to run both tests with a
   clean state.  */

స్థిర శూన్య
test_strerror (శూన్య *సంవృతం)
{
  fail_malloc = true;
  స్థిరరాశి అక్షరం *s = strerror (999);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
}

స్థిర శూన్య
test_strerror_l (శూన్య *సంవృతం)
{
  locale_t loc = newlocale (LC_ALL, "C", (locale_t) 0);
  TEST_VERIFY (loc != (locale_t) 0);
  fail_malloc = true;
  స్థిరరాశి అక్షరం *s = strerror_l (999, loc);
  fail_malloc = false;
  TEST_COMPARE_STRING (s, "Unknown error");
  freelocale (loc);
}

స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  support_isolate_లోపల_subprocess (test_strerror, ఖాళీ);
  support_isolate_లోపల_subprocess (test_strerror_l, ఖాళీ);

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>
