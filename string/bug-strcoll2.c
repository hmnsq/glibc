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

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

പൂർണ്ണസംഖ്യ
test_cs_CZ (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം t1[] = "config";
  സ്ഥിരം അക്ഷരം t2[] = "choose";
  എങ്കിൽ (setlocale (LC_ALL, "cs_CZ.UTF-8") == ശൂന്യ)
    {
      perror ("setlocale");
      തിരികെ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  പൂർണ്ണസംഖ്യ a = strcoll (t1, t2);
  പൂർണ്ണസംഖ്യ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  എങ്കിൽ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      തിരികെ 0;
    }
  അല്ലെങ്കിൽ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      തിരികെ 1;
    }
}

പൂർണ്ണസംഖ്യ
test_da_DK (ശൂന്യം)
{
  സ്ഥിരം അക്ഷരം t1[] = "AS";
  സ്ഥിരം അക്ഷരം t2[] = "AA";
  എങ്കിൽ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ശൂന്യ)
    {
      perror ("setlocale");
      തിരികെ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  പൂർണ്ണസംഖ്യ a = strcoll (t1, t2);
  പൂർണ്ണസംഖ്യ b = strcoll (t2, t1);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  printf ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  എങ്കിൽ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      തിരികെ 0;
    }
  അല്ലെങ്കിൽ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      തിരികെ 1;
    }
}

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  തിരികെ err;
}

#അന്തര്ഭാവ <support/test-driver.c>
