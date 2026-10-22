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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

પૂર્ણાંક
test_cs_CZ (શૂન્ય)
{
  અચલ અક્ષર t1[] = "config";
  અચલ અક્ષર t2[] = "choose";
  જો (setlocale (LC_ALL, "cs_CZ.UTF-8") == ખાલી)
    {
      perror ("setlocale");
      પાછા 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  પૂર્ણાંક a = strcoll (t1, t2);
  પૂર્ણાંક b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  જો (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      પાછા 0;
    }
  નહીંતર
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      પાછા 1;
    }
}

પૂર્ણાંક
test_da_DK (શૂન્ય)
{
  અચલ અક્ષર t1[] = "AS";
  અચલ અક્ષર t2[] = "AA";
  જો (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ખાલી)
    {
      perror ("setlocale");
      પાછા 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  પૂર્ણાંક a = strcoll (t1, t2);
  પૂર્ણાંક b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  જો (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      પાછા 0;
    }
  નહીંતર
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      પાછા 1;
    }
}

પૂર્ણાંક
do_test (શૂન્ય)
{
  પૂર્ણાંક err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  પાછા err;
}

#અન્તર્ભાવ <support/test-driver.c>
