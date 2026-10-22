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

#تعریف_کن STRCPY_نتیجه(dst, len) ((dst) + (len))
#تعریف_کن TEST_MAIN
#اگر_تعریف_نشده WIDE
# define TEST_NAME "stpcpy"
#وإلا
# define TEST_NAME "wcpcpy"
#پایان_اگر /* !WIDE */
#ضمن "test-string.h"
#اگر_تعریف_نشده WIDE
# define CHAR حرف
# define STPCPY stpcpy
#وإلا
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#پایان_اگر /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#لغو_تعریف STPCPY
#لغو_تعریف weak_alias
#تعریف_کن weak_alias(a, b)
#لغو_تعریف libc_hidden_def
#تعریف_کن libc_hidden_def(a)
#لغو_تعریف libc_hidden_builtin_def
#تعریف_کن libc_hidden_builtin_def(a)
#لغو_تعریف attribute_hidden
#تعریف_کن attribute_hidden
#اگر_تعریف_نشده WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#وإلا
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#پایان_اگر

#لغو_تعریف CHAR
#ضمن "test-strcpy.c"
