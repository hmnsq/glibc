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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libc-diag.h>

শূন্য *vp;
ধ্রুবক শূন্য *cvp;
পূর্ণসংখ্যা *ip;
ধ্রুবক পূর্ণসংখ্যা *cip;
অক্ষর *cp;
ধ্রুবক অক্ষর *ccp;
পূর্ণসংখ্যা c;
size_t sz;

#define CHECK_TYPE(রাশিমালা, TYPE)					\
  _Static_assert (_Generic (রাশিমালা, TYPE: 1), "type check")

স্থির পূর্ণসংখ্যা
do_test (শূন্য)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), শূন্য *);
  CHECK_TYPE (memchr (cvp, c, sz), ধ্রুবক শূন্য *);
  CHECK_TYPE (memchr (ip, c, sz), শূন্য *);
  CHECK_TYPE (memchr (cip, c, sz), ধ্রুবক শূন্য *);
  CHECK_TYPE (memchr (cp, c, sz), শূন্য *);
  CHECK_TYPE (memchr (ccp, c, sz), ধ্রুবক শূন্য *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), শূন্য *);
  CHECK_TYPE (memchr ((শূন্য *) 0, c, sz), শূন্য *);
  DIAG_বের_করো_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), শূন্য *);
  CHECK_TYPE (strchr (vp, c), অক্ষর *);
  CHECK_TYPE (strchr (cvp, c), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strchr (cp, c), অক্ষর *);
  CHECK_TYPE (strchr (ccp, c), ধ্রুবক অক্ষর *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), অক্ষর *);
  CHECK_TYPE (strchr ((শূন্য *) 0, c), অক্ষর *);
  DIAG_বের_করো_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), অক্ষর *);
  CHECK_TYPE (strpbrk (vp, vp), অক্ষর *);
  CHECK_TYPE (strpbrk (vp, cvp), অক্ষর *);
  CHECK_TYPE (strpbrk (cvp, vp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strpbrk (cvp, cvp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strpbrk (cp, cp), অক্ষর *);
  CHECK_TYPE (strpbrk (cp, ccp), অক্ষর *);
  CHECK_TYPE (strpbrk (ccp, cp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strpbrk (ccp, ccp), ধ্রুবক অক্ষর *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), অক্ষর *);
  CHECK_TYPE (strpbrk (0, ccp), অক্ষর *);
  CHECK_TYPE (strpbrk ((শূন্য *) 0, cp), অক্ষর *);
  CHECK_TYPE (strpbrk ((শূন্য *) 0, ccp), অক্ষর *);
  DIAG_বের_করো_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), অক্ষর *);
  CHECK_TYPE (strrchr (vp, c), অক্ষর *);
  CHECK_TYPE (strrchr (cvp, c), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strrchr (cp, c), অক্ষর *);
  CHECK_TYPE (strrchr (ccp, c), ধ্রুবক অক্ষর *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), অক্ষর *);
  CHECK_TYPE (strrchr ((শূন্য *) 0, c), অক্ষর *);
  DIAG_বের_করো_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), অক্ষর *);
  CHECK_TYPE (strstr (vp, vp), অক্ষর *);
  CHECK_TYPE (strstr (vp, cvp), অক্ষর *);
  CHECK_TYPE (strstr (cvp, vp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strstr (cvp, cvp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strstr (cp, cp), অক্ষর *);
  CHECK_TYPE (strstr (cp, ccp), অক্ষর *);
  CHECK_TYPE (strstr (ccp, cp), ধ্রুবক অক্ষর *);
  CHECK_TYPE (strstr (ccp, ccp), ধ্রুবক অক্ষর *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), অক্ষর *);
  CHECK_TYPE (strstr (0, ccp), অক্ষর *);
  CHECK_TYPE (strstr ((শূন্য *) 0, cp), অক্ষর *);
  CHECK_TYPE (strstr ((শূন্য *) 0, ccp), অক্ষর *);
  DIAG_বের_করো_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), অক্ষর *);
  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
