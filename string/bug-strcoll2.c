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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <locale.h>

/* An incorrect strcoll optimization resulted in incorrect
   results from strcoll for cs_CZ and da_DK.  */

पूर्णांक
test_cs_CZ (शून्य)
{
  स्थिरांक अक्षर t1[] = "config";
  स्थिरांक अक्षर t2[] = "choose";
  जर (रखो_क्षेत्र (LC_ALL, "cs_CZ.UTF-8") == रिक्त)
    {
      लिखो_त्रुटि ("setlocale");
      परत 1;
    }
  /* In Czech the digraph ch sorts after c, therefore we expect
     config to sort before choose.  */
  पूर्णांक a = strcoll (t1, t2);
  पूर्णांक b = strcoll (t2, t1);
  म_लिखो ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  म_लिखो ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  जर (a < 0 && b > 0)
    {
      माला_दो ("PASS: config < choose");
      परत 0;
    }
  अन्यथा
    {
      माला_दो ("FAIL: Wrong sorting in cs_CZ.UTF-8.");
      परत 1;
    }
}

पूर्णांक
test_da_DK (शून्य)
{
  स्थिरांक अक्षर t1[] = "AS";
  स्थिरांक अक्षर t2[] = "AA";
  जर (रखो_क्षेत्र (LC_ALL, "da_DK.ISO-8859-1") == रिक्त)
    {
      लिखो_त्रुटि ("setlocale");
      परत 1;
    }
  /* AA should be treated as the last letter of the Danish alphabet,
     hence sorting after AS.  */
  पूर्णांक a = strcoll (t1, t2);
  पूर्णांक b = strcoll (t2, t1);
  म_लिखो ("strcoll (\"%s\", \"%s\") = %d\n", t1, t2, a);
  म_लिखो ("strcoll (\"%s\", \"%s\") = %d\n", t2, t1, b);
  जर (a < 0 && b > 0)
    {
      माला_दो ("PASS: AS < AA");
      परत 0;
    }
  अन्यथा
    {
      माला_दो ("FAIL: Wrong sorting in da_DK.ISO-8859-1");
      परत 1;
    }
}

पूर्णांक
do_test (शून्य)
{
  पूर्णांक err = 0;
  err |= test_cs_CZ ();
  err |= test_da_DK ();
  परत err;
}

#अन्तर्भाव <support/test-driver.c>
