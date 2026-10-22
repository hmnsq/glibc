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

পূর্ণাঙ্ক
test_cs_CZ (শূন্য)
{
  ধ্রুব বর্ণ t1[] = "config";
  ধ্রুব বর্ণ t2[] = "choose";
  যদি (setlocale (LC_ALL, "cs_CZ.UTF-8") == রিক্ত)
    {
      perror ("setlocale");
      প্রত্যাগম 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  পূর্ণাঙ্ক a = strcoll (t1, t2);
  পূর্ণাঙ্ক b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  যদি (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      প্রত্যাগম 0;
    }
  অন্যথা
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      প্রত্যাগম 1;
    }
}

পূর্ণাঙ্ক
test_da_DK (শূন্য)
{
  ধ্রুব বর্ণ t1[] = "AS";
  ধ্রুব বর্ণ t2[] = "AA";
  যদি (setlocale (LC_ALL, "da_DK.ISO-8859-1") == রিক্ত)
    {
      perror ("setlocale");
      প্রত্যাগম 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  পূর্ণাঙ্ক a = strcoll (t1, t2);
  পূর্ণাঙ্ক b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  যদি (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      প্রত্যাগম 0;
    }
  অন্যথা
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      প্রত্যাগম 1;
    }
}

পূর্ণাঙ্ক
do_test (শূন্য)
{
  পূর্ণাঙ্ক err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  প্রত্যাগম err;
}

#অন্তর্ভাব <support/test-driver.c>
