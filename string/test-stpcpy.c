/* Test stpcpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRCPY_ਨਤੀਜਾ(dst, len) ((dst) + (len))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_MAIN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define TEST_NAME "stpcpy"
#ਨਹੀਂਤਾਂ
# define TEST_NAME "wcpcpy"
#ਜੇ_ਅੰਤ /* !WIDE */
#ਅਨ੍ਤਰ੍ਭਾਵ "test-string.h"
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define CHAR ਅੱਖਰ
# define STPCPY stpcpy
#ਨਹੀਂਤਾਂ
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#ਜੇ_ਅੰਤ /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ STPCPY
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ weak_alias
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ weak_alias(a, b)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ libc_hidden_builtin_def
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ libc_hidden_builtin_def(a)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ attribute_hidden
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ attribute_hidden
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#ਨਹੀਂਤਾਂ
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHAR
#ਅਨ੍ਤਰ੍ਭਾਵ "test-strcpy.c"
