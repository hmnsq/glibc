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

#घोषणा STRCPY_परिणाम(dst, len) ((dst) + (len))
#घोषणा TEST_MAIN
#अगर_अघोषित WIDE
# define TEST_NAME "stpcpy"
#अन्यथा
# define TEST_NAME "wcpcpy"
#पूर्ण_अगर /* !WIDE */
#समावेश "test-string.h"
#अगर_अघोषित WIDE
# define CHAR अक्षर
# define STPCPY stpcpy
#अन्यथा
# include <wchar.h>
# define CHAR ब_अक्षर_प्रकार
# define STPCPY wcpcpy
#पूर्ण_अगर /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#अघोषित STPCPY
#अघोषित weak_alias
#घोषणा weak_alias(a, b)
#अघोषित libc_hidden_def
#घोषणा libc_hidden_def(a)
#अघोषित libc_hidden_builtin_def
#घोषणा libc_hidden_builtin_def(a)
#अघोषित attribute_hidden
#घोषणा attribute_hidden
#अगर_अघोषित WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#अन्यथा
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#पूर्ण_अगर

#अघोषित CHAR
#समावेश "test-strcpy.c"
