/* Copyright (C) 1994-2026 Free Software Foundation, Inc.
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

#समावेश <stdlib.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <support/check.h>

व्योम try (स्थिर अक्षर *name, दीर्घ दीर्घ पूर्णांक param, पूर्णांक मूल्य, पूर्णांक expected)
{
  अगर (मूल्य != expected)
    {
      म_लिखो ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, मूल्य);
      support_record_failure ();
    }
  अन्यथा
    म_लिखो ("%s(%#llx) as expected %d\n", name, param, मूल्य);
}

पूर्णांक
do_test (व्योम)
{
  पूर्णांक i;

#घोषणा TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  क्रम (i=0 ; i < 8 * माप (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  क्रम (i=0 ; i < 8 * माप (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, पूर्णांक);
  TEST (ffsl, दीर्घ पूर्णांक);
  TEST (ffsll, दीर्घ दीर्घ पूर्णांक);

  वापस 0;
}

#समावेश <support/test-driver.c>
