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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

ਪੂਰਨ
test_cs_CZ (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ t1[] = "config";
  ਅਚਲ ਅੱਖਰ t2[] = "choose";
  ਜੇ (setlocale (LC_ALL, "cs_CZ.UTF-8") == ਨਿਰਾ)
    {
      perror ("setlocale");
      ਵਾਪਸ 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  ਪੂਰਨ a = strcoll (t1, t2);
  ਪੂਰਨ b = strcoll (t2, t1);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ਜੇ (a < 0 && b > 0)
    {
      puts ("PASS: config < choose");
      ਵਾਪਸ 0;
    }
  ਨਹੀਂਤਾਂ
    {
      puts ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      ਵਾਪਸ 1;
    }
}

ਪੂਰਨ
test_da_DK (ਖਾਲੀ)
{
  ਅਚਲ ਅੱਖਰ t1[] = "AS";
  ਅਚਲ ਅੱਖਰ t2[] = "AA";
  ਜੇ (setlocale (LC_ALL, "da_DK.ISO-8859-1") == ਨਿਰਾ)
    {
      perror ("setlocale");
      ਵਾਪਸ 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  ਪੂਰਨ a = strcoll (t1, t2);
  ਪੂਰਨ b = strcoll (t2, t1);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  ਲਿਖੋ ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  ਜੇ (a < 0 && b > 0)
    {
      puts ("PASS: AS < AA");
      ਵਾਪਸ 0;
    }
  ਨਹੀਂਤਾਂ
    {
      puts ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      ਵਾਪਸ 1;
    }
}

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  ਵਾਪਸ err;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
