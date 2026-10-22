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

#समावेश <string.h>
#समावेश <libc-diag.h>

व्योम *vp;
स्थिर व्योम *cvp;
पूर्णांक *ip;
स्थिर पूर्णांक *cip;
अक्षर *cp;
स्थिर अक्षर *ccp;
पूर्णांक c;
माप_प्रकार sz;

#घोषणा CHECK_TYPE(व्यंजक, TYPE)					\
  _Static_assert (_Generic (व्यंजक, TYPE: 1), "type check")

अटल पूर्णांक
do_test (व्योम)
{
  /* This is a compilation test.  */
  CHECK_TYPE (स_प्रथम (vp, c, sz), व्योम *);
  CHECK_TYPE (स_प्रथम (cvp, c, sz), स्थिर व्योम *);
  CHECK_TYPE (स_प्रथम (ip, c, sz), व्योम *);
  CHECK_TYPE (स_प्रथम (cip, c, sz), स्थिर व्योम *);
  CHECK_TYPE (स_प्रथम (cp, c, sz), व्योम *);
  CHECK_TYPE (स_प्रथम (ccp, c, sz), स्थिर व्योम *);
  DIAG_धकेलो_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (स_प्रथम (0, c, sz), व्योम *);
  CHECK_TYPE (स_प्रथम ((व्योम *) 0, c, sz), व्योम *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((स_प्रथम) (cvp, c, sz), व्योम *);
  CHECK_TYPE (म_अक्षर (vp, c), अक्षर *);
  CHECK_TYPE (म_अक्षर (cvp, c), स्थिर अक्षर *);
  CHECK_TYPE (म_अक्षर (cp, c), अक्षर *);
  CHECK_TYPE (म_अक्षर (ccp, c), स्थिर अक्षर *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_अक्षर (0, c), अक्षर *);
  CHECK_TYPE (म_अक्षर ((व्योम *) 0, c), अक्षर *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_अक्षर) (ccp, c), अक्षर *);
  CHECK_TYPE (strpbrk (vp, vp), अक्षर *);
  CHECK_TYPE (strpbrk (vp, cvp), अक्षर *);
  CHECK_TYPE (strpbrk (cvp, vp), स्थिर अक्षर *);
  CHECK_TYPE (strpbrk (cvp, cvp), स्थिर अक्षर *);
  CHECK_TYPE (strpbrk (cp, cp), अक्षर *);
  CHECK_TYPE (strpbrk (cp, ccp), अक्षर *);
  CHECK_TYPE (strpbrk (ccp, cp), स्थिर अक्षर *);
  CHECK_TYPE (strpbrk (ccp, ccp), स्थिर अक्षर *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), अक्षर *);
  CHECK_TYPE (strpbrk (0, ccp), अक्षर *);
  CHECK_TYPE (strpbrk ((व्योम *) 0, cp), अक्षर *);
  CHECK_TYPE (strpbrk ((व्योम *) 0, ccp), अक्षर *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), अक्षर *);
  CHECK_TYPE (म_खोजप (vp, c), अक्षर *);
  CHECK_TYPE (म_खोजप (cvp, c), स्थिर अक्षर *);
  CHECK_TYPE (म_खोजप (cp, c), अक्षर *);
  CHECK_TYPE (म_खोजप (ccp, c), स्थिर अक्षर *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_खोजप (0, c), अक्षर *);
  CHECK_TYPE (म_खोजप ((व्योम *) 0, c), अक्षर *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_खोजप) (ccp, c), अक्षर *);
  CHECK_TYPE (म_माला (vp, vp), अक्षर *);
  CHECK_TYPE (म_माला (vp, cvp), अक्षर *);
  CHECK_TYPE (म_माला (cvp, vp), स्थिर अक्षर *);
  CHECK_TYPE (म_माला (cvp, cvp), स्थिर अक्षर *);
  CHECK_TYPE (म_माला (cp, cp), अक्षर *);
  CHECK_TYPE (म_माला (cp, ccp), अक्षर *);
  CHECK_TYPE (म_माला (ccp, cp), स्थिर अक्षर *);
  CHECK_TYPE (म_माला (ccp, ccp), स्थिर अक्षर *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_माला (0, cp), अक्षर *);
  CHECK_TYPE (म_माला (0, ccp), अक्षर *);
  CHECK_TYPE (म_माला ((व्योम *) 0, cp), अक्षर *);
  CHECK_TYPE (म_माला ((व्योम *) 0, ccp), अक्षर *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_माला) (ccp, ccp), अक्षर *);
  वापस 0;
}

#समावेश <support/test-driver.c>
