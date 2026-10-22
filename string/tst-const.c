/* Test <string.h> const-generic macros.
   Copyright (C) 2025-2026 Free Software Foundation, Inc.
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
#अन्तर्भाव <libc-diag.h>

शून्य *vp;
स्थिरांक शून्य *cvp;
पूर्णांक *ip;
स्थिरांक पूर्णांक *cip;
अक्षर *cp;
स्थिरांक अक्षर *ccp;
पूर्णांक c;
माप_प्रकार sz;

#define CHECK_TYPE(अभिव्यक्ती, TYPE)					\
  _Static_assert (_Generic (अभिव्यक्ती, TYPE: 1), "type check")

स्थिर पूर्णांक
do_test (शून्य)
{
  /* This is a compilation test.  */
  CHECK_TYPE (स_प्रथम (vp, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (cvp, c, sz), स्थिरांक शून्य *);
  CHECK_TYPE (स_प्रथम (ip, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (cip, c, sz), स्थिरांक शून्य *);
  CHECK_TYPE (स_प्रथम (cp, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (ccp, c, sz), स्थिरांक शून्य *);
  DIAG_ढकला_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (स_प्रथम (0, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम ((शून्य *) 0, c, sz), शून्य *);
  DIAG_काढा_NEEDS_COMMENT;
  CHECK_TYPE ((स_प्रथम) (cvp, c, sz), शून्य *);
  CHECK_TYPE (म_अक्षर (vp, c), अक्षर *);
  CHECK_TYPE (म_अक्षर (cvp, c), स्थिरांक अक्षर *);
  CHECK_TYPE (म_अक्षर (cp, c), अक्षर *);
  CHECK_TYPE (म_अक्षर (ccp, c), स्थिरांक अक्षर *);
  DIAG_ढकला_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_अक्षर (0, c), अक्षर *);
  CHECK_TYPE (म_अक्षर ((शून्य *) 0, c), अक्षर *);
  DIAG_काढा_NEEDS_COMMENT;
  CHECK_TYPE ((म_अक्षर) (ccp, c), अक्षर *);
  CHECK_TYPE (strpbrk (vp, vp), अक्षर *);
  CHECK_TYPE (strpbrk (vp, cvp), अक्षर *);
  CHECK_TYPE (strpbrk (cvp, vp), स्थिरांक अक्षर *);
  CHECK_TYPE (strpbrk (cvp, cvp), स्थिरांक अक्षर *);
  CHECK_TYPE (strpbrk (cp, cp), अक्षर *);
  CHECK_TYPE (strpbrk (cp, ccp), अक्षर *);
  CHECK_TYPE (strpbrk (ccp, cp), स्थिरांक अक्षर *);
  CHECK_TYPE (strpbrk (ccp, ccp), स्थिरांक अक्षर *);
  DIAG_ढकला_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), अक्षर *);
  CHECK_TYPE (strpbrk (0, ccp), अक्षर *);
  CHECK_TYPE (strpbrk ((शून्य *) 0, cp), अक्षर *);
  CHECK_TYPE (strpbrk ((शून्य *) 0, ccp), अक्षर *);
  DIAG_काढा_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), अक्षर *);
  CHECK_TYPE (म_खोजप (vp, c), अक्षर *);
  CHECK_TYPE (म_खोजप (cvp, c), स्थिरांक अक्षर *);
  CHECK_TYPE (म_खोजप (cp, c), अक्षर *);
  CHECK_TYPE (म_खोजप (ccp, c), स्थिरांक अक्षर *);
  DIAG_ढकला_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_खोजप (0, c), अक्षर *);
  CHECK_TYPE (म_खोजप ((शून्य *) 0, c), अक्षर *);
  DIAG_काढा_NEEDS_COMMENT;
  CHECK_TYPE ((म_खोजप) (ccp, c), अक्षर *);
  CHECK_TYPE (म_माला (vp, vp), अक्षर *);
  CHECK_TYPE (म_माला (vp, cvp), अक्षर *);
  CHECK_TYPE (म_माला (cvp, vp), स्थिरांक अक्षर *);
  CHECK_TYPE (म_माला (cvp, cvp), स्थिरांक अक्षर *);
  CHECK_TYPE (म_माला (cp, cp), अक्षर *);
  CHECK_TYPE (म_माला (cp, ccp), अक्षर *);
  CHECK_TYPE (म_माला (ccp, cp), स्थिरांक अक्षर *);
  CHECK_TYPE (म_माला (ccp, ccp), स्थिरांक अक्षर *);
  DIAG_ढकला_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_माला (0, cp), अक्षर *);
  CHECK_TYPE (म_माला (0, ccp), अक्षर *);
  CHECK_TYPE (म_माला ((शून्य *) 0, cp), अक्षर *);
  CHECK_TYPE (म_माला ((शून्य *) 0, ccp), अक्षर *);
  DIAG_काढा_NEEDS_COMMENT;
  CHECK_TYPE ((म_माला) (ccp, ccp), अक्षर *);
  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
