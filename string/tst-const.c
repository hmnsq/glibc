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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>

ଶୂନ୍ୟ *vp;
ଅଚଳ ଶୂନ୍ୟ *cvp;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ip;
ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *cip;
ଅକ୍ଷର *cp;
ଅଚଳ ଅକ୍ଷର *ccp;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା c;
size_t sz;

#define CHECK_TYPE(ପଦସମଷ୍ଟି, TYPE)					\
  _Static_assert (_Generic (ପଦସମଷ୍ଟି, TYPE: 1), "type check")

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr (cvp, c, sz), ଅଚଳ ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr (ip, c, sz), ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr (cip, c, sz), ଅଚଳ ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr (cp, c, sz), ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr (ccp, c, sz), ଅଚଳ ଶୂନ୍ୟ *);
  DIAG_ଠେଲ_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), ଶୂନ୍ୟ *);
  CHECK_TYPE (memchr ((ଶୂନ୍ୟ *) 0, c, sz), ଶୂନ୍ୟ *);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), ଶୂନ୍ୟ *);
  CHECK_TYPE (strchr (vp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strchr (cvp, c), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strchr (cp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strchr (ccp, c), ଅଚଳ ଅକ୍ଷର *);
  DIAG_ଠେଲ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), ଅକ୍ଷର *);
  CHECK_TYPE (strchr ((ଶୂନ୍ୟ *) 0, c), ଅକ୍ଷର *);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (vp, vp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (vp, cvp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (cvp, vp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (cvp, cvp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (cp, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (cp, ccp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (ccp, cp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (ccp, ccp), ଅଚଳ ଅକ୍ଷର *);
  DIAG_ଠେଲ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk (0, ccp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk ((ଶୂନ୍ୟ *) 0, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strpbrk ((ଶୂନ୍ୟ *) 0, ccp), ଅକ୍ଷର *);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), ଅକ୍ଷର *);
  CHECK_TYPE (strrchr (vp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strrchr (cvp, c), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strrchr (cp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strrchr (ccp, c), ଅଚଳ ଅକ୍ଷର *);
  DIAG_ଠେଲ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), ଅକ୍ଷର *);
  CHECK_TYPE (strrchr ((ଶୂନ୍ୟ *) 0, c), ଅକ୍ଷର *);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (vp, vp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (vp, cvp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (cvp, vp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strstr (cvp, cvp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strstr (cp, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (cp, ccp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (ccp, cp), ଅଚଳ ଅକ୍ଷର *);
  CHECK_TYPE (strstr (ccp, ccp), ଅଚଳ ଅକ୍ଷର *);
  DIAG_ଠେଲ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr (0, ccp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr ((ଶୂନ୍ୟ *) 0, cp), ଅକ୍ଷର *);
  CHECK_TYPE (strstr ((ଶୂନ୍ୟ *) 0, ccp), ଅକ୍ଷର *);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), ଅକ୍ଷର *);
  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
