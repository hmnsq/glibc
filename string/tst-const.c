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
ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *cvp;
ಪೂರ್ಣಾಂಕ *ip;
ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *cip;
ಅಕ್ಷರ *cp;
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ccp;
ಪೂರ್ಣಾಂಕ c;
size_t sz;

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_TYPE(ಅಭಿವ್ಯಕ್ತಿ, TYPE)					\
  _Static_assert (_Generic (ಅಭಿವ್ಯಕ್ತಿ, TYPE: 1), "type check")

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cvp, c, sz), ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (ip, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cip, c, sz), ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (cp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr (ccp, c, sz), ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (memchr ((ಶೂನ್ಯ *) 0, c, sz), ಶೂನ್ಯ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), ಶೂನ್ಯ *);
  CHECK_TYPE (strchr (vp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strchr (cvp, c), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (strchr (cp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strchr (ccp, c), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strchr ((ಶೂನ್ಯ *) 0, c), ಅಕ್ಷರ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (vp, vp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (vp, cvp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (cvp, vp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (cvp, cvp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (cp, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (cp, ccp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (ccp, cp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (ccp, ccp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk (0, ccp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk ((ಶೂನ್ಯ *) 0, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (strpbrk ((ಶೂನ್ಯ *) 0, ccp), ಅಕ್ಷರ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), ಅಕ್ಷರ *);
  CHECK_TYPE (strrchr (vp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strrchr (cvp, c), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (strrchr (cp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strrchr (ccp, c), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), ಅಕ್ಷರ *);
  CHECK_TYPE (strrchr ((ಶೂನ್ಯ *) 0, c), ಅಕ್ಷರ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (vp, vp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (vp, cvp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (cvp, vp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (cvp, cvp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (cp, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (cp, ccp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ccp, cp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ccp, ccp), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (0, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (0, ccp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು ((ಶೂನ್ಯ *) 0, cp), ಅಕ್ಷರ *);
  CHECK_TYPE (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು ((ಶೂನ್ಯ *) 0, ccp), ಅಕ್ಷರ *);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  CHECK_TYPE ((ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು) (ccp, ccp), ಅಕ್ಷರ *);
  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
