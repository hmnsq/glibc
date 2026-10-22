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

تهی *vp;
ثابت تهی *cvp;
صحیح *ip;
ثابت صحیح *cip;
نویسه *cp;
ثابت نویسه *ccp;
صحیح c;
size_t sz;

#define CHECK_TYPE(عبارت, TYPE)					\
  _Static_assert (_Generic (عبارت, TYPE: 1), "type check")

ایستا صحیح
do_test (تهی)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), تهی *);
  CHECK_TYPE (memchr (cvp, c, sz), ثابت تهی *);
  CHECK_TYPE (memchr (ip, c, sz), تهی *);
  CHECK_TYPE (memchr (cip, c, sz), ثابت تهی *);
  CHECK_TYPE (memchr (cp, c, sz), تهی *);
  CHECK_TYPE (memchr (ccp, c, sz), ثابت تهی *);
  DIAG_افزودن_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), تهی *);
  CHECK_TYPE (memchr ((تهی *) 0, c, sz), تهی *);
  DIAG_برداشت_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), تهی *);
  CHECK_TYPE (strchr (vp, c), نویسه *);
  CHECK_TYPE (strchr (cvp, c), ثابت نویسه *);
  CHECK_TYPE (strchr (cp, c), نویسه *);
  CHECK_TYPE (strchr (ccp, c), ثابت نویسه *);
  DIAG_افزودن_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), نویسه *);
  CHECK_TYPE (strchr ((تهی *) 0, c), نویسه *);
  DIAG_برداشت_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), نویسه *);
  CHECK_TYPE (strpbrk (vp, vp), نویسه *);
  CHECK_TYPE (strpbrk (vp, cvp), نویسه *);
  CHECK_TYPE (strpbrk (cvp, vp), ثابت نویسه *);
  CHECK_TYPE (strpbrk (cvp, cvp), ثابت نویسه *);
  CHECK_TYPE (strpbrk (cp, cp), نویسه *);
  CHECK_TYPE (strpbrk (cp, ccp), نویسه *);
  CHECK_TYPE (strpbrk (ccp, cp), ثابت نویسه *);
  CHECK_TYPE (strpbrk (ccp, ccp), ثابت نویسه *);
  DIAG_افزودن_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), نویسه *);
  CHECK_TYPE (strpbrk (0, ccp), نویسه *);
  CHECK_TYPE (strpbrk ((تهی *) 0, cp), نویسه *);
  CHECK_TYPE (strpbrk ((تهی *) 0, ccp), نویسه *);
  DIAG_برداشت_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), نویسه *);
  CHECK_TYPE (strrchr (vp, c), نویسه *);
  CHECK_TYPE (strrchr (cvp, c), ثابت نویسه *);
  CHECK_TYPE (strrchr (cp, c), نویسه *);
  CHECK_TYPE (strrchr (ccp, c), ثابت نویسه *);
  DIAG_افزودن_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), نویسه *);
  CHECK_TYPE (strrchr ((تهی *) 0, c), نویسه *);
  DIAG_برداشت_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), نویسه *);
  CHECK_TYPE (strstr (vp, vp), نویسه *);
  CHECK_TYPE (strstr (vp, cvp), نویسه *);
  CHECK_TYPE (strstr (cvp, vp), ثابت نویسه *);
  CHECK_TYPE (strstr (cvp, cvp), ثابت نویسه *);
  CHECK_TYPE (strstr (cp, cp), نویسه *);
  CHECK_TYPE (strstr (cp, ccp), نویسه *);
  CHECK_TYPE (strstr (ccp, cp), ثابت نویسه *);
  CHECK_TYPE (strstr (ccp, ccp), ثابت نویسه *);
  DIAG_افزودن_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), نویسه *);
  CHECK_TYPE (strstr (0, ccp), نویسه *);
  CHECK_TYPE (strstr ((تهی *) 0, cp), نویسه *);
  CHECK_TYPE (strstr ((تهی *) 0, ccp), نویسه *);
  DIAG_برداشت_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), نویسه *);
  بازگشت 0;
}

#شامل <support/test-driver.c>
