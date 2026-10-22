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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

ಪೂರ್ಣಾಙ್ಕ
test_cs_CZ (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ t1[] = "config";
  ಧ್ರುವ ವರ್ಣ t2[] = "choose";
  ಯದಿ (setlocale (LC_ALL, "cs_CZ.UTF-8") == ರಿಕ್ತ)
    {
      perror ("setlocale");
      ಪ್ರತ್ಯಾಗಮ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  ಪೂರ್ಣಾಙ್ಕ a = strcoll (t1, t2);
  ಪೂರ್ಣಾಙ್ಕ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ಯದಿ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  ಅನ್ಯಥಾ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ಪ್ರತ್ಯಾಗಮ 1;
    }
}

ಪೂರ್ಣಾಙ್ಕ
test_da_DK (ಶೂನ್ಯ)
{
  ಧ್ರುವ ವರ್ಣ t1[] = "AS";
  ಧ್ರುವ ವರ್ಣ t2[] = "AA";
  ಯದಿ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ರಿಕ್ತ)
    {
      perror ("setlocale");
      ಪ್ರತ್ಯಾಗಮ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  ಪೂರ್ಣಾಙ್ಕ a = strcoll (t1, t2);
  ಪೂರ್ಣಾಙ್ಕ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ಯದಿ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  ಅನ್ಯಥಾ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ಪ್ರತ್ಯಾಗಮ 1;
    }
}

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ಪ್ರತ್ಯಾಗಮ err;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
