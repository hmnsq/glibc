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

#شامل <string.h>
#شامل <libc-diag.h>

خالی *vp;
ثابت خالی *cvp;
صحیح *ip;
ثابت صحیح *cip;
حرف *cp;
ثابت حرف *ccp;
صحیح c;
size_t sz;

#تعریف_کرو CHECK_TYPE(اظہاریہ, TYPE)					\
  _Static_assert (_Generic (اظہاریہ, TYPE: 1), "type check")

ساکن صحیح
do_test (خالی)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), خالی *);
  CHECK_TYPE (memchr (cvp, c, sz), ثابت خالی *);
  CHECK_TYPE (memchr (ip, c, sz), خالی *);
  CHECK_TYPE (memchr (cip, c, sz), ثابت خالی *);
  CHECK_TYPE (memchr (cp, c, sz), خالی *);
  CHECK_TYPE (memchr (ccp, c, sz), ثابت خالی *);
  DIAG_ڈالو_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), خالی *);
  CHECK_TYPE (memchr ((خالی *) 0, c, sz), خالی *);
  DIAG_نکالو_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), خالی *);
  CHECK_TYPE (strchr (vp, c), حرف *);
  CHECK_TYPE (strchr (cvp, c), ثابت حرف *);
  CHECK_TYPE (strchr (cp, c), حرف *);
  CHECK_TYPE (strchr (ccp, c), ثابت حرف *);
  DIAG_ڈالو_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), حرف *);
  CHECK_TYPE (strchr ((خالی *) 0, c), حرف *);
  DIAG_نکالو_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), حرف *);
  CHECK_TYPE (strpbrk (vp, vp), حرف *);
  CHECK_TYPE (strpbrk (vp, cvp), حرف *);
  CHECK_TYPE (strpbrk (cvp, vp), ثابت حرف *);
  CHECK_TYPE (strpbrk (cvp, cvp), ثابت حرف *);
  CHECK_TYPE (strpbrk (cp, cp), حرف *);
  CHECK_TYPE (strpbrk (cp, ccp), حرف *);
  CHECK_TYPE (strpbrk (ccp, cp), ثابت حرف *);
  CHECK_TYPE (strpbrk (ccp, ccp), ثابت حرف *);
  DIAG_ڈالو_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), حرف *);
  CHECK_TYPE (strpbrk (0, ccp), حرف *);
  CHECK_TYPE (strpbrk ((خالی *) 0, cp), حرف *);
  CHECK_TYPE (strpbrk ((خالی *) 0, ccp), حرف *);
  DIAG_نکالو_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), حرف *);
  CHECK_TYPE (strrchr (vp, c), حرف *);
  CHECK_TYPE (strrchr (cvp, c), ثابت حرف *);
  CHECK_TYPE (strrchr (cp, c), حرف *);
  CHECK_TYPE (strrchr (ccp, c), ثابت حرف *);
  DIAG_ڈالو_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), حرف *);
  CHECK_TYPE (strrchr ((خالی *) 0, c), حرف *);
  DIAG_نکالو_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), حرف *);
  CHECK_TYPE (لڑی_تلاش (vp, vp), حرف *);
  CHECK_TYPE (لڑی_تلاش (vp, cvp), حرف *);
  CHECK_TYPE (لڑی_تلاش (cvp, vp), ثابت حرف *);
  CHECK_TYPE (لڑی_تلاش (cvp, cvp), ثابت حرف *);
  CHECK_TYPE (لڑی_تلاش (cp, cp), حرف *);
  CHECK_TYPE (لڑی_تلاش (cp, ccp), حرف *);
  CHECK_TYPE (لڑی_تلاش (ccp, cp), ثابت حرف *);
  CHECK_TYPE (لڑی_تلاش (ccp, ccp), ثابت حرف *);
  DIAG_ڈالو_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (لڑی_تلاش (0, cp), حرف *);
  CHECK_TYPE (لڑی_تلاش (0, ccp), حرف *);
  CHECK_TYPE (لڑی_تلاش ((خالی *) 0, cp), حرف *);
  CHECK_TYPE (لڑی_تلاش ((خالی *) 0, ccp), حرف *);
  DIAG_نکالو_NEEDS_COMMENT;
  CHECK_TYPE ((لڑی_تلاش) (ccp, ccp), حرف *);
  واپس 0;
}

#شامل <support/test-driver.c>
