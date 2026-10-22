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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <libc-diag.h>

શૂન્ય *vp;
અચલ શૂન્ય *cvp;
પૂર્ણાંક *ip;
અચલ પૂર્ણાંક *cip;
અક્ષર *cp;
અચલ અક્ષર *ccp;
પૂર્ણાંક c;
size_t sz;

#define CHECK_TYPE(પદાવલિ, TYPE)					\
  _Static_assert (_Generic (પદાવલિ, TYPE: 1), "type check")

સ્થિર પૂર્ણાંક
do_test (શૂન્ય)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), શૂન્ય *);
  CHECK_TYPE (memchr (cvp, c, sz), અચલ શૂન્ય *);
  CHECK_TYPE (memchr (ip, c, sz), શૂન્ય *);
  CHECK_TYPE (memchr (cip, c, sz), અચલ શૂન્ય *);
  CHECK_TYPE (memchr (cp, c, sz), શૂન્ય *);
  CHECK_TYPE (memchr (ccp, c, sz), અચલ શૂન્ય *);
  DIAG_ધકેલો_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), શૂન્ય *);
  CHECK_TYPE (memchr ((શૂન્ય *) 0, c, sz), શૂન્ય *);
  DIAG_કાઢો_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), શૂન્ય *);
  CHECK_TYPE (strchr (vp, c), અક્ષર *);
  CHECK_TYPE (strchr (cvp, c), અચલ અક્ષર *);
  CHECK_TYPE (strchr (cp, c), અક્ષર *);
  CHECK_TYPE (strchr (ccp, c), અચલ અક્ષર *);
  DIAG_ધકેલો_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), અક્ષર *);
  CHECK_TYPE (strchr ((શૂન્ય *) 0, c), અક્ષર *);
  DIAG_કાઢો_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), અક્ષર *);
  CHECK_TYPE (strpbrk (vp, vp), અક્ષર *);
  CHECK_TYPE (strpbrk (vp, cvp), અક્ષર *);
  CHECK_TYPE (strpbrk (cvp, vp), અચલ અક્ષર *);
  CHECK_TYPE (strpbrk (cvp, cvp), અચલ અક્ષર *);
  CHECK_TYPE (strpbrk (cp, cp), અક્ષર *);
  CHECK_TYPE (strpbrk (cp, ccp), અક્ષર *);
  CHECK_TYPE (strpbrk (ccp, cp), અચલ અક્ષર *);
  CHECK_TYPE (strpbrk (ccp, ccp), અચલ અક્ષર *);
  DIAG_ધકેલો_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), અક્ષર *);
  CHECK_TYPE (strpbrk (0, ccp), અક્ષર *);
  CHECK_TYPE (strpbrk ((શૂન્ય *) 0, cp), અક્ષર *);
  CHECK_TYPE (strpbrk ((શૂન્ય *) 0, ccp), અક્ષર *);
  DIAG_કાઢો_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), અક્ષર *);
  CHECK_TYPE (strrchr (vp, c), અક્ષર *);
  CHECK_TYPE (strrchr (cvp, c), અચલ અક્ષર *);
  CHECK_TYPE (strrchr (cp, c), અક્ષર *);
  CHECK_TYPE (strrchr (ccp, c), અચલ અક્ષર *);
  DIAG_ધકેલો_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), અક્ષર *);
  CHECK_TYPE (strrchr ((શૂન્ય *) 0, c), અક્ષર *);
  DIAG_કાઢો_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), અક્ષર *);
  CHECK_TYPE (strstr (vp, vp), અક્ષર *);
  CHECK_TYPE (strstr (vp, cvp), અક્ષર *);
  CHECK_TYPE (strstr (cvp, vp), અચલ અક્ષર *);
  CHECK_TYPE (strstr (cvp, cvp), અચલ અક્ષર *);
  CHECK_TYPE (strstr (cp, cp), અક્ષર *);
  CHECK_TYPE (strstr (cp, ccp), અક્ષર *);
  CHECK_TYPE (strstr (ccp, cp), અચલ અક્ષર *);
  CHECK_TYPE (strstr (ccp, ccp), અચલ અક્ષર *);
  DIAG_ધકેલો_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), અક્ષર *);
  CHECK_TYPE (strstr (0, ccp), અક્ષર *);
  CHECK_TYPE (strstr ((શૂન્ય *) 0, cp), અક્ષર *);
  CHECK_TYPE (strstr ((શૂન્ય *) 0, ccp), અક્ષર *);
  DIAG_કાઢો_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), અક્ષર *);
  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
