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

#அந்தர்பாவ <string.h>
#அந்தர்பாவ <libc-diag.h>

வெறுமை *vp;
மாறிலி வெறுமை *cvp;
முழு *ip;
மாறிலி முழு *cip;
எழுத்து *cp;
மாறிலி எழுத்து *ccp;
முழு c;
size_t sz;

#define CHECK_TYPE(கோவை, TYPE)					\
  _Static_assert (_Generic (கோவை, TYPE: 1), "type check")

நிலையான முழு
do_test (வெறுமை)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), வெறுமை *);
  CHECK_TYPE (memchr (cvp, c, sz), மாறிலி வெறுமை *);
  CHECK_TYPE (memchr (ip, c, sz), வெறுமை *);
  CHECK_TYPE (memchr (cip, c, sz), மாறிலி வெறுமை *);
  CHECK_TYPE (memchr (cp, c, sz), வெறுமை *);
  CHECK_TYPE (memchr (ccp, c, sz), மாறிலி வெறுமை *);
  DIAG_தள்ளு_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), வெறுமை *);
  CHECK_TYPE (memchr ((வெறுமை *) 0, c, sz), வெறுமை *);
  DIAG_எடு_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), வெறுமை *);
  CHECK_TYPE (strchr (vp, c), எழுத்து *);
  CHECK_TYPE (strchr (cvp, c), மாறிலி எழுத்து *);
  CHECK_TYPE (strchr (cp, c), எழுத்து *);
  CHECK_TYPE (strchr (ccp, c), மாறிலி எழுத்து *);
  DIAG_தள்ளு_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), எழுத்து *);
  CHECK_TYPE (strchr ((வெறுமை *) 0, c), எழுத்து *);
  DIAG_எடு_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), எழுத்து *);
  CHECK_TYPE (strpbrk (vp, vp), எழுத்து *);
  CHECK_TYPE (strpbrk (vp, cvp), எழுத்து *);
  CHECK_TYPE (strpbrk (cvp, vp), மாறிலி எழுத்து *);
  CHECK_TYPE (strpbrk (cvp, cvp), மாறிலி எழுத்து *);
  CHECK_TYPE (strpbrk (cp, cp), எழுத்து *);
  CHECK_TYPE (strpbrk (cp, ccp), எழுத்து *);
  CHECK_TYPE (strpbrk (ccp, cp), மாறிலி எழுத்து *);
  CHECK_TYPE (strpbrk (ccp, ccp), மாறிலி எழுத்து *);
  DIAG_தள்ளு_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), எழுத்து *);
  CHECK_TYPE (strpbrk (0, ccp), எழுத்து *);
  CHECK_TYPE (strpbrk ((வெறுமை *) 0, cp), எழுத்து *);
  CHECK_TYPE (strpbrk ((வெறுமை *) 0, ccp), எழுத்து *);
  DIAG_எடு_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), எழுத்து *);
  CHECK_TYPE (strrchr (vp, c), எழுத்து *);
  CHECK_TYPE (strrchr (cvp, c), மாறிலி எழுத்து *);
  CHECK_TYPE (strrchr (cp, c), எழுத்து *);
  CHECK_TYPE (strrchr (ccp, c), மாறிலி எழுத்து *);
  DIAG_தள்ளு_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), எழுத்து *);
  CHECK_TYPE (strrchr ((வெறுமை *) 0, c), எழுத்து *);
  DIAG_எடு_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), எழுத்து *);
  CHECK_TYPE (strstr (vp, vp), எழுத்து *);
  CHECK_TYPE (strstr (vp, cvp), எழுத்து *);
  CHECK_TYPE (strstr (cvp, vp), மாறிலி எழுத்து *);
  CHECK_TYPE (strstr (cvp, cvp), மாறிலி எழுத்து *);
  CHECK_TYPE (strstr (cp, cp), எழுத்து *);
  CHECK_TYPE (strstr (cp, ccp), எழுத்து *);
  CHECK_TYPE (strstr (ccp, cp), மாறிலி எழுத்து *);
  CHECK_TYPE (strstr (ccp, ccp), மாறிலி எழுத்து *);
  DIAG_தள்ளு_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), எழுத்து *);
  CHECK_TYPE (strstr (0, ccp), எழுத்து *);
  CHECK_TYPE (strstr ((வெறுமை *) 0, cp), எழுத்து *);
  CHECK_TYPE (strstr ((வெறுமை *) 0, ccp), எழுத்து *);
  DIAG_எடு_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), எழுத்து *);
  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
