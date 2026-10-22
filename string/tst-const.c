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

#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <libc-diag.h>

শূন্য *vp;
ধ্রুৱ শূন্য *cvp;
পূর্ণাঙ্ক *ip;
ধ্রুৱ পূর্ণাঙ্ক *cip;
ৱর্ণ *cp;
ধ্রুৱ ৱর্ণ *ccp;
পূর্ণাঙ্ক c;
size_t sz;

#define CHECK_TYPE(ৰাশিমালা, TYPE)					\
  _Static_assert (_Generic (ৰাশিমালা, TYPE: 1), "type check")

স্থির পূর্ণাঙ্ক
do_test (শূন্য)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), শূন্য *);
  CHECK_TYPE (memchr (cvp, c, sz), ধ্রুৱ শূন্য *);
  CHECK_TYPE (memchr (ip, c, sz), শূন্য *);
  CHECK_TYPE (memchr (cip, c, sz), ধ্রুৱ শূন্য *);
  CHECK_TYPE (memchr (cp, c, sz), শূন্য *);
  CHECK_TYPE (memchr (ccp, c, sz), ধ্রুৱ শূন্য *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), শূন্য *);
  CHECK_TYPE (memchr ((শূন্য *) 0, c, sz), শূন্য *);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), শূন্য *);
  CHECK_TYPE (strchr (vp, c), ৱর্ণ *);
  CHECK_TYPE (strchr (cvp, c), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strchr (cp, c), ৱর্ণ *);
  CHECK_TYPE (strchr (ccp, c), ধ্রুৱ ৱর্ণ *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), ৱর্ণ *);
  CHECK_TYPE (strchr ((শূন্য *) 0, c), ৱর্ণ *);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), ৱর্ণ *);
  CHECK_TYPE (strpbrk (vp, vp), ৱর্ণ *);
  CHECK_TYPE (strpbrk (vp, cvp), ৱর্ণ *);
  CHECK_TYPE (strpbrk (cvp, vp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strpbrk (cvp, cvp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strpbrk (cp, cp), ৱর্ণ *);
  CHECK_TYPE (strpbrk (cp, ccp), ৱর্ণ *);
  CHECK_TYPE (strpbrk (ccp, cp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strpbrk (ccp, ccp), ধ্রুৱ ৱর্ণ *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), ৱর্ণ *);
  CHECK_TYPE (strpbrk (0, ccp), ৱর্ণ *);
  CHECK_TYPE (strpbrk ((শূন্য *) 0, cp), ৱর্ণ *);
  CHECK_TYPE (strpbrk ((শূন্য *) 0, ccp), ৱর্ণ *);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), ৱর্ণ *);
  CHECK_TYPE (strrchr (vp, c), ৱর্ণ *);
  CHECK_TYPE (strrchr (cvp, c), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strrchr (cp, c), ৱর্ণ *);
  CHECK_TYPE (strrchr (ccp, c), ধ্রুৱ ৱর্ণ *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), ৱর্ণ *);
  CHECK_TYPE (strrchr ((শূন্য *) 0, c), ৱর্ণ *);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), ৱর্ণ *);
  CHECK_TYPE (strstr (vp, vp), ৱর্ণ *);
  CHECK_TYPE (strstr (vp, cvp), ৱর্ণ *);
  CHECK_TYPE (strstr (cvp, vp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strstr (cvp, cvp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strstr (cp, cp), ৱর্ণ *);
  CHECK_TYPE (strstr (cp, ccp), ৱর্ণ *);
  CHECK_TYPE (strstr (ccp, cp), ধ্রুৱ ৱর্ণ *);
  CHECK_TYPE (strstr (ccp, ccp), ধ্রুৱ ৱর্ণ *);
  DIAG_ঠেলো_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), ৱর্ণ *);
  CHECK_TYPE (strstr (0, ccp), ৱর্ণ *);
  CHECK_TYPE (strstr ((শূন্য *) 0, cp), ৱর্ণ *);
  CHECK_TYPE (strstr ((শূন্য *) 0, ccp), ৱর্ণ *);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), ৱর্ণ *);
  ঘূৰাই 0;
}

#অন্তর্ভাৱ <support/test-driver.c>
