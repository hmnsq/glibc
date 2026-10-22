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

#include <string.h>
#include <libc-diag.h>

void *vp;
const void *cvp;
puur_naa_nka *ip;
const puur_naa_nka *cip;
var_na *cp;
const var_na *ccp;
puur_naa_nka c;
size_t sz;

#define CHECK_TYPE(EXPR, TYPE)					\
  _Static_assert (_Generic (EXPR, TYPE: 1), "type check")

static puur_naa_nka
do_test (void)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), void *);
  CHECK_TYPE (memchr (cvp, c, sz), const void *);
  CHECK_TYPE (memchr (ip, c, sz), void *);
  CHECK_TYPE (memchr (cip, c, sz), const void *);
  CHECK_TYPE (memchr (cp, c, sz), void *);
  CHECK_TYPE (memchr (ccp, c, sz), const void *);
  DIAG_PUSH_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), void *);
  CHECK_TYPE (memchr ((void *) 0, c, sz), void *);
  DIAG_POP_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), void *);
  CHECK_TYPE (strchr (vp, c), var_na *);
  CHECK_TYPE (strchr (cvp, c), const var_na *);
  CHECK_TYPE (strchr (cp, c), var_na *);
  CHECK_TYPE (strchr (ccp, c), const var_na *);
  DIAG_PUSH_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), var_na *);
  CHECK_TYPE (strchr ((void *) 0, c), var_na *);
  DIAG_POP_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), var_na *);
  CHECK_TYPE (strpbrk (vp, vp), var_na *);
  CHECK_TYPE (strpbrk (vp, cvp), var_na *);
  CHECK_TYPE (strpbrk (cvp, vp), const var_na *);
  CHECK_TYPE (strpbrk (cvp, cvp), const var_na *);
  CHECK_TYPE (strpbrk (cp, cp), var_na *);
  CHECK_TYPE (strpbrk (cp, ccp), var_na *);
  CHECK_TYPE (strpbrk (ccp, cp), const var_na *);
  CHECK_TYPE (strpbrk (ccp, ccp), const var_na *);
  DIAG_PUSH_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), var_na *);
  CHECK_TYPE (strpbrk (0, ccp), var_na *);
  CHECK_TYPE (strpbrk ((void *) 0, cp), var_na *);
  CHECK_TYPE (strpbrk ((void *) 0, ccp), var_na *);
  DIAG_POP_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), var_na *);
  CHECK_TYPE (strrchr (vp, c), var_na *);
  CHECK_TYPE (strrchr (cvp, c), const var_na *);
  CHECK_TYPE (strrchr (cp, c), var_na *);
  CHECK_TYPE (strrchr (ccp, c), const var_na *);
  DIAG_PUSH_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), var_na *);
  CHECK_TYPE (strrchr ((void *) 0, c), var_na *);
  DIAG_POP_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), var_na *);
  CHECK_TYPE (strstr (vp, vp), var_na *);
  CHECK_TYPE (strstr (vp, cvp), var_na *);
  CHECK_TYPE (strstr (cvp, vp), const var_na *);
  CHECK_TYPE (strstr (cvp, cvp), const var_na *);
  CHECK_TYPE (strstr (cp, cp), var_na *);
  CHECK_TYPE (strstr (cp, ccp), var_na *);
  CHECK_TYPE (strstr (ccp, cp), const var_na *);
  CHECK_TYPE (strstr (ccp, ccp), const var_na *);
  DIAG_PUSH_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), var_na *);
  CHECK_TYPE (strstr (0, ccp), var_na *);
  CHECK_TYPE (strstr ((void *) 0, cp), var_na *);
  CHECK_TYPE (strstr ((void *) 0, ccp), var_na *);
  DIAG_POP_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), var_na *);
  ᱨᱩᱣᱟᱹᱲ 0;
}

#include <support/test-driver.c>
