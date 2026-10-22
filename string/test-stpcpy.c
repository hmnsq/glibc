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

#تعریف_کړه STRCPY_پایله(dst, len) ((dst) + (len))
#تعریف_کړه TEST_MAIN
#که_نه_تعریف_شوی WIDE
# define TEST_NAME "stpcpy"
#وإلا
# define TEST_NAME "wcpcpy"
#د_که_پای /* !WIDE */
#ضمن "test-string.h"
#که_نه_تعریف_شوی WIDE
# define CHAR حرف
# define STPCPY stpcpy
#وإلا
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#د_که_پای /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#تعریف_لغوه STPCPY
#تعریف_لغوه weak_alias
#تعریف_کړه weak_alias(a, b)
#تعریف_لغوه libc_hidden_def
#تعریف_کړه libc_hidden_def(a)
#تعریف_لغوه libc_hidden_builtin_def
#تعریف_کړه libc_hidden_builtin_def(a)
#تعریف_لغوه attribute_hidden
#تعریف_کړه attribute_hidden
#که_نه_تعریف_شوی WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#وإلا
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#د_که_پای

#تعریف_لغوه CHAR
#ضمن "test-strcpy.c"
