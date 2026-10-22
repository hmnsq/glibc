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

#include <stdio.h>
#include <string.h>
#include <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

整数
test_cs_CZ (void)
{
  const char t1[] = "config";
  const char t2[] = "choose";
  如果 (setlocale (LC_ALL, "cs_CZ.UTF-8") == NULL)
    {
      perror ("setlocale");
      返回 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  整数 a = strcoll (t1, t2);
  整数 b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  如果 (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      返回 0;
    }
  否则
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      返回 1;
    }
}

整数
test_da_DK (void)
{
  const char t1[] = "AS";
  const char t2[] = "AA";
  如果 (setlocale (LC_ALL, "da_DK.ISO-8859-1") == NULL)
    {
      perror ("setlocale");
      返回 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  整数 a = strcoll (t1, t2);
  整数 b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  如果 (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      返回 0;
    }
  否则
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      返回 1;
    }
}

整数
do_test (void)
{
  整数 err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  返回 err;
}

#include <support/test-driver.c>
