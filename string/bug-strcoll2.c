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

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

முழு
test_cs_CZ (வெறுமை)
{
  மாறிலி எழுத்து t1[] = "config";
  மாறிலி எழுத்து t2[] = "choose";
  எனில் (setlocale (LC_ALL, "cs_CZ.UTF-8") == வெற்று)
    {
      perror ("setlocale");
      திரும்பு 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  முழு a = strcoll (t1, t2);
  முழு b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  எனில் (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      திரும்பு 0;
    }
  இல்லையெனில்
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      திரும்பு 1;
    }
}

முழு
test_da_DK (வெறுமை)
{
  மாறிலி எழுத்து t1[] = "AS";
  மாறிலி எழுத்து t2[] = "AA";
  எனில் (setlocale (LC_ALL, "da_DK.ISO-8859-1") == வெற்று)
    {
      perror ("setlocale");
      திரும்பு 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  முழு a = strcoll (t1, t2);
  முழு b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  எனில் (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      திரும்பு 0;
    }
  இல்லையெனில்
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      திரும்பு 1;
    }
}

முழு
do_test (வெறுமை)
{
  முழு err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  திரும்பு err;
}

#அந்தர்பாவ <support/test-driver.c>
