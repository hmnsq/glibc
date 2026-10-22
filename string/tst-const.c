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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <libc-diag.h>

ശൂന്യം *vp;
സ്ഥിരം ശൂന്യം *cvp;
പൂർണ്ണസംഖ്യ *ip;
സ്ഥിരം പൂർണ്ണസംഖ്യ *cip;
അക്ഷരം *cp;
സ്ഥിരം അക്ഷരം *ccp;
പൂർണ്ണസംഖ്യ c;
size_t sz;

#define CHECK_TYPE(വ്യഞ്ജകം, TYPE)					\
  _Static_assert (_Generic (വ്യഞ്ജകം, TYPE: 1), "type check")

സ്ഥിതം പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  /* This is a compilation test.  */
  CHECK_TYPE (memchr (vp, c, sz), ശൂന്യം *);
  CHECK_TYPE (memchr (cvp, c, sz), സ്ഥിരം ശൂന്യം *);
  CHECK_TYPE (memchr (ip, c, sz), ശൂന്യം *);
  CHECK_TYPE (memchr (cip, c, sz), സ്ഥിരം ശൂന്യം *);
  CHECK_TYPE (memchr (cp, c, sz), ശൂന്യം *);
  CHECK_TYPE (memchr (ccp, c, sz), സ്ഥിരം ശൂന്യം *);
  DIAG_തള്ളുക_NEEDS_COMMENT;
  /* This deliberately tests the type of the result with a null
     pointer constant argument.  */
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (memchr (0, c, sz), ശൂന്യം *);
  CHECK_TYPE (memchr ((ശൂന്യം *) 0, c, sz), ശൂന്യം *);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  CHECK_TYPE ((memchr) (cvp, c, sz), ശൂന്യം *);
  CHECK_TYPE (strchr (vp, c), അക്ഷരം *);
  CHECK_TYPE (strchr (cvp, c), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strchr (cp, c), അക്ഷരം *);
  CHECK_TYPE (strchr (ccp, c), സ്ഥിരം അക്ഷരം *);
  DIAG_തള്ളുക_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strchr (0, c), അക്ഷരം *);
  CHECK_TYPE (strchr ((ശൂന്യം *) 0, c), അക്ഷരം *);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  CHECK_TYPE ((strchr) (ccp, c), അക്ഷരം *);
  CHECK_TYPE (strpbrk (vp, vp), അക്ഷരം *);
  CHECK_TYPE (strpbrk (vp, cvp), അക്ഷരം *);
  CHECK_TYPE (strpbrk (cvp, vp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strpbrk (cvp, cvp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strpbrk (cp, cp), അക്ഷരം *);
  CHECK_TYPE (strpbrk (cp, ccp), അക്ഷരം *);
  CHECK_TYPE (strpbrk (ccp, cp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strpbrk (ccp, ccp), സ്ഥിരം അക്ഷരം *);
  DIAG_തള്ളുക_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strpbrk (0, cp), അക്ഷരം *);
  CHECK_TYPE (strpbrk (0, ccp), അക്ഷരം *);
  CHECK_TYPE (strpbrk ((ശൂന്യം *) 0, cp), അക്ഷരം *);
  CHECK_TYPE (strpbrk ((ശൂന്യം *) 0, ccp), അക്ഷരം *);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  CHECK_TYPE ((strpbrk) (ccp, ccp), അക്ഷരം *);
  CHECK_TYPE (strrchr (vp, c), അക്ഷരം *);
  CHECK_TYPE (strrchr (cvp, c), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strrchr (cp, c), അക്ഷരം *);
  CHECK_TYPE (strrchr (ccp, c), സ്ഥിരം അക്ഷരം *);
  DIAG_തള്ളുക_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strrchr (0, c), അക്ഷരം *);
  CHECK_TYPE (strrchr ((ശൂന്യം *) 0, c), അക്ഷരം *);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  CHECK_TYPE ((strrchr) (ccp, c), അക്ഷരം *);
  CHECK_TYPE (strstr (vp, vp), അക്ഷരം *);
  CHECK_TYPE (strstr (vp, cvp), അക്ഷരം *);
  CHECK_TYPE (strstr (cvp, vp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strstr (cvp, cvp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strstr (cp, cp), അക്ഷരം *);
  CHECK_TYPE (strstr (cp, ccp), അക്ഷരം *);
  CHECK_TYPE (strstr (ccp, cp), സ്ഥിരം അക്ഷരം *);
  CHECK_TYPE (strstr (ccp, ccp), സ്ഥിരം അക്ഷരം *);
  DIAG_തള്ളുക_NEEDS_COMMENT;
  DIAG_IGNORE_NEEDS_COMMENT (14, "-Wnonnull");
  CHECK_TYPE (strstr (0, cp), അക്ഷരം *);
  CHECK_TYPE (strstr (0, ccp), അക്ഷരം *);
  CHECK_TYPE (strstr ((ശൂന്യം *) 0, cp), അക്ഷരം *);
  CHECK_TYPE (strstr ((ശൂന്യം *) 0, ccp), അക്ഷരം *);
  DIAG_എടുക്കുക_NEEDS_COMMENT;
  CHECK_TYPE ((strstr) (ccp, ccp), അക്ഷരം *);
  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
