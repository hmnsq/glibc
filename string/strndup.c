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

#جيڪڏهن_وصف_ٿيل HAVE_CONFIG_H
# include "config.h"
#جيڪڏهن_پورو

#ضمن <stdio.h>
#ضمن <sys/types.h>

#إذا defined _LIBC || defined STDC_سرا
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *يادگيري_ڏيو ();
#جيڪڏهن_پورو

#وصف_رد __strndup
#وصف_رد strndup

#جيڪڏهن_وصف_نه_ٿيل weak_alias
# define __strndup strndup
#جيڪڏهن_پورو

حرف *
__strndup (ثابت حرف *s, size_t n)
{
  size_t len = __strnlen (s, n);
  حرف *new = (حرف *) يادگيري_ڏيو (len + 1);

  إذا (new == عدم)
    أرجع عدم;

  new[len] = '\0';
  أرجع (حرف *) يادگيري_نقل (new, s, len);
}
#جيڪڏهن_وصف_ٿيل libc_hidden_def
libc_hidden_def (__strndup)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل weak_alias
weak_alias (__strndup, strndup)
#جيڪڏهن_پورو
