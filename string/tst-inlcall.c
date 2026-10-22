/* Tester for calling inline string functions.
   Copyright (C) 1998-2026 Free Software Foundation, Inc.
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

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर

/* Make sure we test the optimized inline functions.  */
#घोषणा __USE_STRING_INLINES	1

#समावेश <errno.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <strings.h>
#समावेश <fcntl.h>


पूर्णांक
do_test (व्योम)
{
  पूर्णांक status;
  पूर्णांक errors = 0;
  अक्षर buf1[1000];
  अक्षर *cp;
  अक्षर ch;

  cp = म_नकल (buf1, "hello world");
  अगर (म_भेद ("hello world", cp++) != 0)
    {
      माला_दो ("strcmp test 1 failed");
      ++errors;
    }

  cp = buf1;
  अगर (म_भेद (cp++, "hello world") != 0)
    {
      माला_दो ("strcmp test 2 failed");
      ++errors;
    }

  ch = 'h';
  अगर (म_अक्षर ("hello world", ch++) == शून्य)
    {
      माला_दो ("strchr test 1 failed");
      ++errors;
    }

  स्थिर अक्षर * स्थिर hw = "hello world";
  अगर (strpbrk (hw, "o") - hw != 4)
    {
      माला_दो ("strpbrk test 1 failed");
      ++errors;
    }

  अगर (errors == 0)
    {
      status = निकास_सफल;
      माला_दो ("No errors.");
    }
  अन्यथा
    {
      status = निकास_त्रुटि;
      म_लिखो ("%d errors.\n", errors);
    }
  वापस status;
}

#समावेश <support/test-driver.c>
