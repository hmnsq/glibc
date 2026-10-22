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

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_cs_CZ (ଶୂନ୍ୟ)
{
  ଅଚଳ ଅକ୍ଷର t1[] = "config";
  ଅଚଳ ଅକ୍ଷର t2[] = "choose";
  ଯଦି (setlocale (LC_ALL, "cs_CZ.UTF-8") == ଖାଲି)
    {
      perror ("setlocale");
      ଫେରନ୍ତୁ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = strcoll (t1, t2);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ଯଦି (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ଫେରନ୍ତୁ 0;
    }
  ଅନ୍ୟଥା
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ଫେରନ୍ତୁ 1;
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
test_da_DK (ଶୂନ୍ୟ)
{
  ଅଚଳ ଅକ୍ଷର t1[] = "AS";
  ଅଚଳ ଅକ୍ଷର t2[] = "AA";
  ଯଦି (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ଖାଲି)
    {
      perror ("setlocale");
      ଫେରନ୍ତୁ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = strcoll (t1, t2);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ଯଦି (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ଫେରନ୍ତୁ 0;
    }
  ଅନ୍ୟଥା
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ଫେରନ୍ତୁ 1;
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ଫେରନ୍ତୁ err;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
