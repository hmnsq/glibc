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

#ضمن <string.h>
#ضمن <libc-diag.h>

فراغ *vp;
ثابت فراغ *cvp;
صحيح *ip;
ثابت صحيح *cip;
حرف *cp;
ثابت حرف *ccp;
صحيح c;
size_t sz;

#define CHECK_TYPE(فرچ, TYPE)					\
  _Static_assert (_Generic (فرچ, TYPE: 1), "type check")

ساكن صحيح
do_test (فراغ)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), فراغ *);
  CHECK_TYPE (memchr (cvp, c, sz), ثابت فراغ *);
  CHECK_TYPE (memchr (ip, c, sz), فراغ *);
  CHECK_TYPE (memchr (cip, c, sz), ثابت فراغ *);
  CHECK_TYPE (memchr (cp, c, sz), فراغ *);
  CHECK_TYPE (memchr (ccp, c, sz), ثابت فراغ *);
  DIAG_تور_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), فراغ *);
  CHECK_TYPE (memchr ((فراغ *) 0, c, sz), فراغ *);
  DIAG_چرو_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), فراغ *);
  CHECK_TYPE (strchr (vp, c), حرف *);
  CHECK_TYPE (strchr (cvp, c), ثابت حرف *);
  CHECK_TYPE (strchr (cp, c), حرف *);
  CHECK_TYPE (strchr (ccp, c), ثابت حرف *);
  DIAG_تور_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), حرف *);
  CHECK_TYPE (strchr ((فراغ *) 0, c), حرف *);
  DIAG_چرو_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), حرف *);
  CHECK_TYPE (strpbrk (vp, vp), حرف *);
  CHECK_TYPE (strpbrk (vp, cvp), حرف *);
  CHECK_TYPE (strpbrk (cvp, vp), ثابت حرف *);
  CHECK_TYPE (strpbrk (cvp, cvp), ثابت حرف *);
  CHECK_TYPE (strpbrk (cp, cp), حرف *);
  CHECK_TYPE (strpbrk (cp, ccp), حرف *);
  CHECK_TYPE (strpbrk (ccp, cp), ثابت حرف *);
  CHECK_TYPE (strpbrk (ccp, ccp), ثابت حرف *);
  DIAG_تور_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), حرف *);
  CHECK_TYPE (strpbrk (0, ccp), حرف *);
  CHECK_TYPE (strpbrk ((فراغ *) 0, cp), حرف *);
  CHECK_TYPE (strpbrk ((فراغ *) 0, ccp), حرف *);
  DIAG_چرو_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), حرف *);
  CHECK_TYPE (strrchr (vp, c), حرف *);
  CHECK_TYPE (strrchr (cvp, c), ثابت حرف *);
  CHECK_TYPE (strrchr (cp, c), حرف *);
  CHECK_TYPE (strrchr (ccp, c), ثابت حرف *);
  DIAG_تور_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), حرف *);
  CHECK_TYPE (strrchr ((فراغ *) 0, c), حرف *);
  DIAG_چرو_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), حرف *);
  CHECK_TYPE (strstr (vp, vp), حرف *);
  CHECK_TYPE (strstr (vp, cvp), حرف *);
  CHECK_TYPE (strstr (cvp, vp), ثابت حرف *);
  CHECK_TYPE (strstr (cvp, cvp), ثابت حرف *);
  CHECK_TYPE (strstr (cp, cp), حرف *);
  CHECK_TYPE (strstr (cp, ccp), حرف *);
  CHECK_TYPE (strstr (ccp, cp), ثابت حرف *);
  CHECK_TYPE (strstr (ccp, ccp), ثابت حرف *);
  DIAG_تور_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), حرف *);
  CHECK_TYPE (strstr (0, ccp), حرف *);
  CHECK_TYPE (strstr ((فراغ *) 0, cp), حرف *);
  CHECK_TYPE (strstr ((فراغ *) 0, ccp), حرف *);
  DIAG_چرو_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), حرف *);
  أرجع 0;
}

#ضمن <support/test-driver.c>
