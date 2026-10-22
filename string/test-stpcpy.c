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

#నిర్వచించు STRCPY_ఫలితం(dst, len) ((dst) + (len))
#నిర్వచించు TEST_MAIN
#నిర్వచితం_కాకపోతే WIDE
# define TEST_NAME "stpcpy"
#లేకపోతే
# define TEST_NAME "wcpcpy"
#అయితే_ముగింపు /* !WIDE */
#అన్తర్భావ "test-string.h"
#నిర్వచితం_కాకపోతే WIDE
# define CHAR అక్షరం
# define STPCPY stpcpy
#లేకపోతే
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#అయితే_ముగింపు /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#నిర్వచనం_రద్దు STPCPY
#నిర్వచనం_రద్దు weak_alias
#నిర్వచించు weak_alias(a, b)
#నిర్వచనం_రద్దు libc_hidden_def
#నిర్వచించు libc_hidden_def(a)
#నిర్వచనం_రద్దు libc_hidden_builtin_def
#నిర్వచించు libc_hidden_builtin_def(a)
#నిర్వచనం_రద్దు attribute_hidden
#నిర్వచించు attribute_hidden
#నిర్వచితం_కాకపోతే WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#లేకపోతే
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#అయితే_ముగింపు

#నిర్వచనం_రద్దు CHAR
#అన్తర్భావ "test-strcpy.c"
