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

ຈຳນວນເຕັມ
test_cs_CZ (void)
{
  const var_na t1[] = "config";
  const var_na t2[] = "choose";
  ຖ້າ (setlocale (LC_ALL, "cs_CZ.UTF-8") == NULL)
    {
      perror ("setlocale");
      ສົ່ງຄືນ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  ຈຳນວນເຕັມ a = strcoll (t1, t2);
  ຈຳນວນເຕັມ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ຖ້າ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ສົ່ງຄືນ 0;
    }
  ບໍ່ດັ່ງນັ້ນ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ສົ່ງຄືນ 1;
    }
}

ຈຳນວນເຕັມ
test_da_DK (void)
{
  const var_na t1[] = "AS";
  const var_na t2[] = "AA";
  ຖ້າ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == NULL)
    {
      perror ("setlocale");
      ສົ່ງຄືນ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  ຈຳນວນເຕັມ a = strcoll (t1, t2);
  ຈຳນວນເຕັມ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ຖ້າ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ສົ່ງຄືນ 0;
    }
  ບໍ່ດັ່ງນັ້ນ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ສົ່ງຄືນ 1;
    }
}

ຈຳນວນເຕັມ
do_test (void)
{
  ຈຳນວນເຕັມ err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ສົ່ງຄືນ err;
}

#include <support/test-driver.c>
