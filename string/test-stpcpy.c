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

#تعریف_کرو STRCPY_نتیجہ(dst, len) ((dst) + (len))
#تعریف_کرو TEST_MAIN
#اگر_غیر_تعریف_شدہ WIDE
# define TEST_NAME "stpcpy"
#ورنہ
# define TEST_NAME "wcpcpy"
#اگر_ختم /* !WIDE */
#شامل "test-string.h"
#اگر_غیر_تعریف_شدہ WIDE
# define CHAR حرف
# define STPCPY stpcpy
#ورنہ
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#اگر_ختم /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#تعریف_منسوخ STPCPY
#تعریف_منسوخ weak_alias
#تعریف_کرو weak_alias(a, b)
#تعریف_منسوخ libc_hidden_def
#تعریف_کرو libc_hidden_def(a)
#تعریف_منسوخ libc_hidden_builtin_def
#تعریف_کرو libc_hidden_builtin_def(a)
#تعریف_منسوخ attribute_hidden
#تعریف_کرو attribute_hidden
#اگر_غیر_تعریف_شدہ WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#ورنہ
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#اگر_ختم

#تعریف_منسوخ CHAR
#شامل "test-strcpy.c"
