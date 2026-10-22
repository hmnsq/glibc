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

#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

صحيح
test_cs_CZ (فراغ)
{
  ثابت حرف t1[] = "config";
  ثابت حرف t2[] = "choose";
  إذا (setlocale (LC_ALL, "cs_CZ.UTF-8") == عدم)
    {
      perror ("setlocale");
      أرجع 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  صحيح a = strcoll (t1, t2);
  صحيح b = strcoll (t2, t1);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  إذا (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      أرجع 0;
    }
  وإلا
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      أرجع 1;
    }
}

صحيح
test_da_DK (فراغ)
{
  ثابت حرف t1[] = "AS";
  ثابت حرف t2[] = "AA";
  إذا (setlocale (LC_ALL, "da_DK.ISO-8859-1") == عدم)
    {
      perror ("setlocale");
      أرجع 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  صحيح a = strcoll (t1, t2);
  صحيح b = strcoll (t2, t1);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  چاپ_کن ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  إذا (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      أرجع 0;
    }
  وإلا
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      أرجع 1;
    }
}

صحيح
do_test (فراغ)
{
  صحيح err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  أرجع err;
}

#ضمن <support/test-driver.c>
