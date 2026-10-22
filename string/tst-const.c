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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

ಶೂನ್ಯ *vp;
ಧ್ರುವ ಶೂನ್ಯ *cvp;
ಪೂರ್ಣಾಙ್ಕ *ip;
ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *cip;
ವರ್ಣ *cp;
ಧ್ರುವ ವರ್ಣ *ccp;
ಪೂರ್ಣಾಙ್ಕ c;
size_t sz;

#define CHECK_TYPE(ಅಭಿವ್ಯಕ್ತಿ, TYPE)					\
  _Static_assert (_Generic (ಅಭಿವ್ಯಕ್ತಿ, TYPE: 1), "type check")

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cvp, c, sz), ಧ್ರುವ ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (ip, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cip, c, sz), ಧ್ರುವ ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (ccp, c, sz), ಧ್ರುವ ಶೂನ್ಯ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr ((ಶೂನ್ಯ *) 0, c, sz), ಶೂನ್ಯ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (strchr (vp, c), ವರ್ಣ *);
  CHECK_TYPE (strchr (cvp, c), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strchr (cp, c), ವರ್ಣ *);
  CHECK_TYPE (strchr (ccp, c), ಧ್ರುವ ವರ್ಣ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), ವರ್ಣ *);
  CHECK_TYPE (strchr ((ಶೂನ್ಯ *) 0, c), ವರ್ಣ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (vp, vp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (vp, cvp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (cvp, vp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strpbrk (cvp, cvp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strpbrk (cp, cp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (cp, ccp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (ccp, cp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strpbrk (ccp, ccp), ಧ್ರುವ ವರ್ಣ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk (0, ccp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk ((ಶೂನ್ಯ *) 0, cp), ವರ್ಣ *);
  CHECK_TYPE (strpbrk ((ಶೂನ್ಯ *) 0, ccp), ವರ್ಣ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), ವರ್ಣ *);
  CHECK_TYPE (strrchr (vp, c), ವರ್ಣ *);
  CHECK_TYPE (strrchr (cvp, c), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strrchr (cp, c), ವರ್ಣ *);
  CHECK_TYPE (strrchr (ccp, c), ಧ್ರುವ ವರ್ಣ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), ವರ್ಣ *);
  CHECK_TYPE (strrchr ((ಶೂನ್ಯ *) 0, c), ವರ್ಣ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), ವರ್ಣ *);
  CHECK_TYPE (strstr (vp, vp), ವರ್ಣ *);
  CHECK_TYPE (strstr (vp, cvp), ವರ್ಣ *);
  CHECK_TYPE (strstr (cvp, vp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strstr (cvp, cvp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strstr (cp, cp), ವರ್ಣ *);
  CHECK_TYPE (strstr (cp, ccp), ವರ್ಣ *);
  CHECK_TYPE (strstr (ccp, cp), ಧ್ರುವ ವರ್ಣ *);
  CHECK_TYPE (strstr (ccp, ccp), ಧ್ರುವ ವರ್ಣ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), ವರ್ಣ *);
  CHECK_TYPE (strstr (0, ccp), ವರ್ಣ *);
  CHECK_TYPE (strstr ((ಶೂನ್ಯ *) 0, cp), ವರ್ಣ *);
  CHECK_TYPE (strstr ((ಶೂನ್ಯ *) 0, ccp), ವರ್ಣ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), ವರ್ಣ *);
  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
