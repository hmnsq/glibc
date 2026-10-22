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

#که_تعریف_شوی HAVE_CONFIG_H
# include "config.h"
#د_که_پای

#ضمن <stdio.h>
#ضمن <sys/types.h>

#إذا defined _LIBC || defined STDC_سرلیکونه
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *حافظه_ورکړه ();
#د_که_پای

#تعریف_لغوه __strndup
#تعریف_لغوه strndup

#که_نه_تعریف_شوی weak_alias
# define __strndup strndup
#د_که_پای

حرف *
__strndup (ثابت حرف *s, size_t n)
{
  size_t len = __strnlen (s, n);
  حرف *new = (حرف *) حافظه_ورکړه (len + 1);

  إذا (new == عدم)
    أرجع عدم;

  new[len] = '\0';
  أرجع (حرف *) حافظه_نقل (new, s, len);
}
#که_تعریف_شوی libc_hidden_def
libc_hidden_def (__strndup)
#د_که_پای
#که_تعریف_شوی weak_alias
weak_alias (__strndup, strndup)
#د_که_پای
