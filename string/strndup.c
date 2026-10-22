/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#اگر_تعریف_شده HAVE_CONFIG_H
# include "config.h"
#پایان_اگر

#ضمن <stdio.h>
#ضمن <sys/types.h>

#إذا defined _LIBC || defined STDC_سرآیندها
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *حافظه_بده ();
#پایان_اگر

#لغو_تعریف __strndup
#لغو_تعریف strndup

#اگر_تعریف_نشده weak_alias
# define __strndup strndup
#پایان_اگر

حرف *
__strndup (ثابت حرف *s, size_t n)
{
  size_t len = __strnlen (s, n);
  حرف *new = (حرف *) حافظه_بده (len + 1);

  إذا (new == عدم)
    أرجع عدم;

  new[len] = '\0';
  أرجع (حرف *) کپی_حافظه (new, s, len);
}
#اگر_تعریف_شده libc_hidden_def
libc_hidden_def (__strndup)
#پایان_اگر
#اگر_تعریف_شده weak_alias
weak_alias (__strndup, strndup)
#پایان_اگر
