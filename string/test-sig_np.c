/* Test and sigabbrev_np and sigdescr_np.
   Copyright (C) 2020-2026 Free Software Foundation, Inc.
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

#समावेश <string.h>
#समावेश <signal.h>
#समावेश <array_length.h>

#समावेश <support/support.h>
#समावेश <support/check.h>

अटल स्थिर काष्ठा test_t
{
  पूर्णांक त्रुटि_सं;
  स्थिर अक्षर *abbrev;
  स्थिर अक्षर *descr;
} tests[] =
{
#घोषणा N_(name)                      name
#घोषणा init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#समावेश <siglist.h>
#अघोषित init_sig
};

अटल पूर्णांक
do_test (व्योम)
{
  क्रम (माप_प्रकार i = 0; i < array_लंबाई (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].त्रुटि_सं), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].त्रुटि_सं), tests[i].descr);
    }

  वापस 0;
}

#समावेश <support/test-driver.c>
