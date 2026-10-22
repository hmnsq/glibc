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

#اگر_تعریف_شده HAVE_CONFIG_H
#ضمن <config.h>
#پایان_اگر

#إذا defined _LIBC || defined  STDC_سرآیندها
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *حافظه_بده ();
حرف *کپی_حافظه ();
#پایان_اگر

#لغو_تعریف __strdup
#لغو_تعریف strdup

#اگر_تعریف_نشده weak_alias
# define __strdup strdup
#پایان_اگر

/* Duplicate S, returning an identical malloc'd string.  */
حرف *
__strdup (ثابت حرف *s)
{
  size_t len = طول_رشته (s) + 1;
  فراغ *new = حافظه_بده (len);

  إذا (new == عدم)
    أرجع عدم;

  أرجع (حرف *) کپی_حافظه (new, s, len);
}
#اگر_تعریف_شده libc_hidden_def
libc_hidden_def (__strdup)
#پایان_اگر
#اگر_تعریف_شده weak_alias
weak_alias (__strdup, strdup)
#پایان_اگر
