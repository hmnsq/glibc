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

#شامل <stdio.h>
#شامل <string.h>
#شامل <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

صحیح
test_cs_CZ (خالی)
{
  ثابت حرف t1[] = "config";
  ثابت حرف t2[] = "choose";
  اگر (setlocale (LC_ALL, "cs_CZ.UTF-8") == تہی)
    {
      perror ("setlocale");
      واپس 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  صحیح a = strcoll (t1, t2);
  صحیح b = strcoll (t2, t1);
  لکھو ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  لکھو ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  اگر (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      واپس 0;
    }
  ورنہ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      واپس 1;
    }
}

صحیح
test_da_DK (خالی)
{
  ثابت حرف t1[] = "AS";
  ثابت حرف t2[] = "AA";
  اگر (setlocale (LC_ALL, "da_DK.ISO-8859-1") == تہی)
    {
      perror ("setlocale");
      واپس 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  صحیح a = strcoll (t1, t2);
  صحیح b = strcoll (t2, t1);
  لکھو ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  لکھو ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  اگر (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      واپس 0;
    }
  ورنہ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      واپس 1;
    }
}

صحیح
do_test (خالی)
{
  صحیح err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  واپس err;
}

#شامل <support/test-driver.c>
