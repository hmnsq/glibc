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

#وصف_ڪريو STRCPY_نتيجو(dst, len) ((dst) + (len))
#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define TEST_NAME "stpcpy"
#وإلا
# define TEST_NAME "wcpcpy"
#جيڪڏهن_پورو /* !WIDE */
#ضمن "test-string.h"
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define CHAR حرف
# define STPCPY stpcpy
#وإلا
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#جيڪڏهن_پورو /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#وصف_رد STPCPY
#وصف_رد weak_alias
#وصف_ڪريو weak_alias(a, b)
#وصف_رد libc_hidden_def
#وصف_ڪريو libc_hidden_def(a)
#وصف_رد libc_hidden_builtin_def
#وصف_ڪريو libc_hidden_builtin_def(a)
#وصف_رد attribute_hidden
#وصف_ڪريو attribute_hidden
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#وإلا
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#جيڪڏهن_پورو

#وصف_رد CHAR
#ضمن "test-strcpy.c"
