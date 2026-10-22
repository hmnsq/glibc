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

#ವ್ಯಾಖ್ಯಾನಿಸು STRCPY_ಫಲಿತಾಂಶ(dst, len) ((dst) + (len))
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define TEST_NAME "stpcpy"
#ಇಲ್ಲದಿದ್ದರೆ
# define TEST_NAME "wcpcpy"
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */
#ಅನ್ತರ್ಭಾವ "test-string.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define CHAR ಅಕ್ಷರ
# define STPCPY stpcpy
#ಇಲ್ಲದಿದ್ದರೆ
# include <wchar.h>
# define CHAR wchar_t
# define STPCPY wcpcpy
#ಆದರೆ_ಅಂತ್ಯ /* !WIDE */

IMPL (STPCPY, 1)

/* Also check the generic implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು STPCPY
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು weak_alias
#ವ್ಯಾಖ್ಯಾನಿಸು weak_alias(a, b)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು libc_hidden_builtin_def
#ವ್ಯಾಖ್ಯಾನಿಸು libc_hidden_builtin_def(a)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿಸು attribute_hidden
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ WIDE
# define STPCPY __stpcpy_default
# include "string/stpcpy.c"
IMPL (__stpcpy_default, 1)
#ಇಲ್ಲದಿದ್ದರೆ
# define __wcslen wcslen
# define __wmemcpy wmemcpy
# define WCPCPY __wcpcpy_default
# include "wcsmbs/wcpcpy.c"
IMPL (__wcpcpy_default, 1)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHAR
#ಅನ್ತರ್ಭಾವ "test-strcpy.c"
