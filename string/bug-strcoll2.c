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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

পূর্ণসংখ্যা
test_cs_CZ (শূন্য)
{
  ধ্রুবক অক্ষর t1[] = "config";
  ধ্রুবক অক্ষর t2[] = "choose";
  যদি (setlocale (LC_ALL, "cs_CZ.UTF-8") == ফাঁকা)
    {
      perror ("setlocale");
      ফেরত 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  পূর্ণসংখ্যা a = strcoll (t1, t2);
  পূর্ণসংখ্যা b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  যদি (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ফেরত 0;
    }
  অন্যথা
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ফেরত 1;
    }
}

পূর্ণসংখ্যা
test_da_DK (শূন্য)
{
  ধ্রুবক অক্ষর t1[] = "AS";
  ধ্রুবক অক্ষর t2[] = "AA";
  যদি (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ফাঁকা)
    {
      perror ("setlocale");
      ফেরত 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  পূর্ণসংখ্যা a = strcoll (t1, t2);
  পূর্ণসংখ্যা b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  যদি (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ফেরত 0;
    }
  অন্যথা
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ফেরত 1;
    }
}

পূর্ণসংখ্যা
do_test (শূন্য)
{
  পূর্ণসংখ্যা err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ফেরত err;
}

#অন্তর্ভাব <support/test-driver.c>
