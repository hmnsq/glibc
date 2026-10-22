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
ध्रुव शून्य *cvp;
पूर्णाङ्क *ip;
ध्रुव पूर्णाङ्क *cip;
वर्ण *cp;
ध्रुव वर्ण *ccp;
पूर्णाङ्क c;
माप_प्रकार sz;

#define CHECK_TYPE(व्यंजक, TYPE)					\
  _Static_assert (_Generic (व्यंजक, TYPE: 1), "type check")

स्थिर पूर्णाङ्क
do_test (शून्य)
{
  /* This is a compilation test.  */
  CHECK_TYPE (स_प्रथम (vp, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (cvp, c, sz), ध्रुव शून्य *);
  CHECK_TYPE (स_प्रथम (ip, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (cip, c, sz), ध्रुव शून्य *);
  CHECK_TYPE (स_प्रथम (cp, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम (ccp, c, sz), ध्रुव शून्य *);
  DIAG_धकेलो_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (स_प्रथम (0, c, sz), शून्य *);
  CHECK_TYPE (स_प्रथम ((शून्य *) 0, c, sz), शून्य *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((स_प्रथम) (cvp, c, sz), शून्य *);
  CHECK_TYPE (म_अक्षर (vp, c), वर्ण *);
  CHECK_TYPE (म_अक्षर (cvp, c), ध्रुव वर्ण *);
  CHECK_TYPE (म_अक्षर (cp, c), वर्ण *);
  CHECK_TYPE (म_अक्षर (ccp, c), ध्रुव वर्ण *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_अक्षर (0, c), वर्ण *);
  CHECK_TYPE (म_अक्षर ((शून्य *) 0, c), वर्ण *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_अक्षर) (ccp, c), वर्ण *);
  CHECK_TYPE (strpbrk (vp, vp), वर्ण *);
  CHECK_TYPE (strpbrk (vp, cvp), वर्ण *);
  CHECK_TYPE (strpbrk (cvp, vp), ध्रुव वर्ण *);
  CHECK_TYPE (strpbrk (cvp, cvp), ध्रुव वर्ण *);
  CHECK_TYPE (strpbrk (cp, cp), वर्ण *);
  CHECK_TYPE (strpbrk (cp, ccp), वर्ण *);
  CHECK_TYPE (strpbrk (ccp, cp), ध्रुव वर्ण *);
  CHECK_TYPE (strpbrk (ccp, ccp), ध्रुव वर्ण *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), वर्ण *);
  CHECK_TYPE (strpbrk (0, ccp), वर्ण *);
  CHECK_TYPE (strpbrk ((शून्य *) 0, cp), वर्ण *);
  CHECK_TYPE (strpbrk ((शून्य *) 0, ccp), वर्ण *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), वर्ण *);
  CHECK_TYPE (म_खोजप (vp, c), वर्ण *);
  CHECK_TYPE (म_खोजप (cvp, c), ध्रुव वर्ण *);
  CHECK_TYPE (म_खोजप (cp, c), वर्ण *);
  CHECK_TYPE (म_खोजप (ccp, c), ध्रुव वर्ण *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_खोजप (0, c), वर्ण *);
  CHECK_TYPE (म_खोजप ((शून्य *) 0, c), वर्ण *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_खोजप) (ccp, c), वर्ण *);
  CHECK_TYPE (म_माला (vp, vp), वर्ण *);
  CHECK_TYPE (म_माला (vp, cvp), वर्ण *);
  CHECK_TYPE (म_माला (cvp, vp), ध्रुव वर्ण *);
  CHECK_TYPE (म_माला (cvp, cvp), ध्रुव वर्ण *);
  CHECK_TYPE (म_माला (cp, cp), वर्ण *);
  CHECK_TYPE (म_माला (cp, ccp), वर्ण *);
  CHECK_TYPE (म_माला (ccp, cp), ध्रुव वर्ण *);
  CHECK_TYPE (म_माला (ccp, ccp), ध्रुव वर्ण *);
  DIAG_धकेलो_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (म_माला (0, cp), वर्ण *);
  CHECK_TYPE (म_माला (0, ccp), वर्ण *);
  CHECK_TYPE (म_माला ((शून्य *) 0, cp), वर्ण *);
  CHECK_TYPE (म_माला ((शून्य *) 0, ccp), वर्ण *);
  DIAG_निकालो_NEEDS_COMMENT;
  CHECK_TYPE ((म_माला) (ccp, ccp), वर्ण *);
  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
