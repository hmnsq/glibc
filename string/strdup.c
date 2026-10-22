/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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
#ضمن <config.h>
#جيڪڏهن_پورو

#إذا defined _LIBC || defined  STDC_سرا
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *يادگيري_ڏيو ();
حرف *يادگيري_نقل ();
#جيڪڏهن_پورو

#وصف_رد __strdup
#وصف_رد strdup

#جيڪڏهن_وصف_نه_ٿيل weak_alias
# define __strdup strdup
#جيڪڏهن_پورو

/* Duplicate S, returning an identical malloc'd string.  */
حرف *
__strdup (ثابت حرف *s)
{
  size_t len = لڙي_ڊيگهه (s) + 1;
  فراغ *new = يادگيري_ڏيو (len);

  إذا (new == عدم)
    أرجع عدم;

  أرجع (حرف *) يادگيري_نقل (new, s, len);
}
#جيڪڏهن_وصف_ٿيل libc_hidden_def
libc_hidden_def (__strdup)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل weak_alias
weak_alias (__strdup, strdup)
#جيڪڏهن_پورو
