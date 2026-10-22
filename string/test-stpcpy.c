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

#परिभाषय STRCPY_परिणाम(dst, len) ((dst) + (len))
#परिभाषय TEST_MAIN
#यदि_अपरिभाषितम् WIDE
# define TEST_NAME "stpcpy"
#अन्यथा
# define TEST_NAME "wcpcpy"
#यदि_अन्तः /* !WIDE */
#अन्तर्भाव "test-string.h"
#यदि_अपरिभाषितम् WIDE
# define CHAR वर्ण
# define STPCPY stpcpy
#अन्यथा
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#यदि_अन्तः /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#अपरिभाषय STPCPY
#अपरिभाषय weak_alias
#परिभाषय weak_alias(a, b)
#अपरिभाषय libc_hidden_def
#परिभाषय libc_hidden_def(a)
#अपरिभाषय libc_hidden_builtin_def
#परिभाषय libc_hidden_builtin_def(a)
#अपरिभाषय attribute_hidden
#परिभाषय attribute_hidden
#यदि_अपरिभाषितम् WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#अन्यथा
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#यदि_अन्तः

#अपरिभाषय CHAR
#अन्तर्भाव "test-strcpy.c"
