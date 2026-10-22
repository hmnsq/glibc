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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-diag.h>

ਖਾਲੀ *vp;
ਅਚਲ ਖਾਲੀ *cvp;
ਪੂਰਨ *ip;
ਅਚਲ ਪੂਰਨ *cip;
ਅੱਖਰ *cp;
ਅਚਲ ਅੱਖਰ *ccp;
ਪੂਰਨ c;
size_t sz;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_TYPE(ਵਿਅੰਜਕ, TYPE)					\
  _Static_assert (_Generic (ਵਿਅੰਜਕ, TYPE: 1), "type check")

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), ਖਾਲੀ *);
  CHECK_TYPE (memchr (cvp, c, sz), ਅਚਲ ਖਾਲੀ *);
  CHECK_TYPE (memchr (ip, c, sz), ਖਾਲੀ *);
  CHECK_TYPE (memchr (cip, c, sz), ਅਚਲ ਖਾਲੀ *);
  CHECK_TYPE (memchr (cp, c, sz), ਖਾਲੀ *);
  CHECK_TYPE (memchr (ccp, c, sz), ਅਚਲ ਖਾਲੀ *);
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), ਖਾਲੀ *);
  CHECK_TYPE (memchr ((ਖਾਲੀ *) 0, c, sz), ਖਾਲੀ *);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), ਖਾਲੀ *);
  CHECK_TYPE (strchr (vp, c), ਅੱਖਰ *);
  CHECK_TYPE (strchr (cvp, c), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (strchr (cp, c), ਅੱਖਰ *);
  CHECK_TYPE (strchr (ccp, c), ਅਚਲ ਅੱਖਰ *);
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), ਅੱਖਰ *);
  CHECK_TYPE (strchr ((ਖਾਲੀ *) 0, c), ਅੱਖਰ *);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (vp, vp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (vp, cvp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (cvp, vp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (cvp, cvp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (cp, cp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (cp, ccp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (ccp, cp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (ccp, ccp), ਅਚਲ ਅੱਖਰ *);
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk (0, ccp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk ((ਖਾਲੀ *) 0, cp), ਅੱਖਰ *);
  CHECK_TYPE (strpbrk ((ਖਾਲੀ *) 0, ccp), ਅੱਖਰ *);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), ਅੱਖਰ *);
  CHECK_TYPE (strrchr (vp, c), ਅੱਖਰ *);
  CHECK_TYPE (strrchr (cvp, c), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (strrchr (cp, c), ਅੱਖਰ *);
  CHECK_TYPE (strrchr (ccp, c), ਅਚਲ ਅੱਖਰ *);
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), ਅੱਖਰ *);
  CHECK_TYPE (strrchr ((ਖਾਲੀ *) 0, c), ਅੱਖਰ *);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (vp, vp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (vp, cvp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (cvp, vp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (cvp, cvp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (cp, cp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (cp, ccp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (ccp, cp), ਅਚਲ ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (ccp, ccp), ਅਚਲ ਅੱਖਰ *);
  DIAG_ਧੱਕੋ_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (0, cp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ (0, ccp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ ((ਖਾਲੀ *) 0, cp), ਅੱਖਰ *);
  CHECK_TYPE (ਲੜੀ_ਖੋਜ ((ਖਾਲੀ *) 0, ccp), ਅੱਖਰ *);
  DIAG_ਕੱਢੋ_NEEDS_COMMENT;
  CHECK_TYPE ((ਲੜੀ_ਖੋਜ) (ccp, ccp), ਅੱਖਰ *);
  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
