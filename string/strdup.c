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

#که_تعریف_شوی HAVE_CONFIG_H
#ضمن <config.h>
#د_که_پای

#إذا defined _LIBC || defined  STDC_سرلیکونه
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *حافظه_ورکړه ();
حرف *حافظه_نقل ();
#د_که_پای

#تعریف_لغوه __strdup
#تعریف_لغوه strdup

#که_نه_تعریف_شوی weak_alias
# define __strdup strdup
#د_که_پای

/* Duplicate S, returning an identical malloc'd string.  */
حرف *
__strdup (ثابت حرف *s)
{
  size_t len = مزي_اوږدوالی (s) + 1;
  فراغ *new = حافظه_ورکړه (len);

  إذا (new == عدم)
    أرجع عدم;

  أرجع (حرف *) حافظه_نقل (new, s, len);
}
#که_تعریف_شوی libc_hidden_def
libc_hidden_def (__strdup)
#د_که_پای
#که_تعریف_شوی weak_alias
weak_alias (__strdup, strdup)
#د_که_پای
