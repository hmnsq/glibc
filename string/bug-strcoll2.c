/* Bug 18589: sort-test.sh fails at random.
   Copyright (C) 2015-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

పూర్ణాంకం
test_cs_CZ (శూన్య)
{
  స్థిరరాశి అక్షరం t1[] = "config";
  స్థిరరాశి అక్షరం t2[] = "choose";
  ఒకవేళ (setlocale (LC_ALL, "cs_CZ.UTF-8") == ఖాళీ)
    {
      perror ("setlocale");
      తిరిగి 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  పూర్ణాంకం a = strcoll (t1, t2);
  పూర్ణాంకం b = strcoll (t2, t1);
  రాయి ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  రాయి ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ఒకవేళ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      తిరిగి 0;
    }
  లేకపోతే
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      తిరిగి 1;
    }
}

పూర్ణాంకం
test_da_DK (శూన్య)
{
  స్థిరరాశి అక్షరం t1[] = "AS";
  స్థిరరాశి అక్షరం t2[] = "AA";
  ఒకవేళ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ఖాళీ)
    {
      perror ("setlocale");
      తిరిగి 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  పూర్ణాంకం a = strcoll (t1, t2);
  పూర్ణాంకం b = strcoll (t2, t1);
  రాయి ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  రాయి ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ఒకవేళ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      తిరిగి 0;
    }
  లేకపోతే
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      తిరిగి 1;
    }
}

పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  తిరిగి err;
}

#అన్తర్భావ <support/test-driver.c>
