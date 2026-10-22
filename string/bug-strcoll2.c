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

ಪೂರ್ಣಾಂಕ
test_cs_CZ (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t1[] = "config";
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t2[] = "choose";
  ಆದರೆ (setlocale (LC_ALL, "cs_CZ.UTF-8") == ಖಾಲಿ)
    {
      perror ("setlocale");
      ಹಿಂತಿರುಗಿ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  ಪೂರ್ಣಾಂಕ a = strcoll (t1, t2);
  ಪೂರ್ಣಾಂಕ b = strcoll (t2, t1);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ಆದರೆ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ಹಿಂತಿರುಗಿ 0;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ಹಿಂತಿರುಗಿ 1;
    }
}

ಪೂರ್ಣಾಂಕ
test_da_DK (ಶೂನ್ಯ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t1[] = "AS";
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ t2[] = "AA";
  ಆದರೆ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ಖಾಲಿ)
    {
      perror ("setlocale");
      ಹಿಂತಿರುಗಿ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  ಪೂರ್ಣಾಂಕ a = strcoll (t1, t2);
  ಪೂರ್ಣಾಂಕ b = strcoll (t2, t1);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  ಬರೆ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ಆದರೆ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ಹಿಂತಿರುಗಿ 0;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ಹಿಂತಿರುಗಿ 1;
    }
}

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ಹಿಂತಿರುಗಿ err;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
