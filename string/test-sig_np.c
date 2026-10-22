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

#अन्तर्भाव <string.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <array_length.h>

#अन्तर्भाव <support/support.h>
#अन्तर्भाव <support/check.h>

स्थिर ध्रुव संरचना test_t
{
  पूर्णाङ्क errno;
  ध्रुव वर्ण *abbrev;
  ध्रुव वर्ण *descr;
} tests[] =
{
#परिभाषय N_(name)                      name
#परिभाषय init_sig(sig, abbrev, desc)   { sig, abbrev, desc },
#अन्तर्भाव <siglist.h>
#अपरिभाषय init_sig
};

स्थिर पूर्णाङ्क
do_test (शून्य)
{
  प्रति (size_t i = 0; i < array_दीर्घता (tests); i++)
    {
      TEST_COMPARE_STRING (sigabbrev_np (tests[i].errno), tests[i].abbrev);
      TEST_COMPARE_STRING (sigdescr_np (tests[i].errno), tests[i].descr);
    }

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
