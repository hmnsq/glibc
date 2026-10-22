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

#جے_تعریف_شدہ HAVE_CONFIG_H
#ضمن <config.h>
#جے_انت

#إذا defined _LIBC || defined  STDC_سرخیاں
# include <stdlib.h>
# include <string.h>
#وإلا
حرف *حافظہ_دیو ();
حرف *حافظہ_نقل ();
#جے_انت

#تعریف_رد __strdup
#تعریف_رد strdup

#جے_بنا_تعریف weak_alias
# define __strdup strdup
#جے_انت

/* Duplicate S, returning an identical malloc'd string.  */
حرف *
__strdup (ثابت حرف *s)
{
  size_t len = لڑی_لمبائی (s) + 1;
  فراغ *new = حافظہ_دیو (len);

  إذا (new == عدم)
    أرجع عدم;

  أرجع (حرف *) حافظہ_نقل (new, s, len);
}
#جے_تعریف_شدہ libc_hidden_def
libc_hidden_def (__strdup)
#جے_انت
#جے_تعریف_شدہ weak_alias
weak_alias (__strdup, strdup)
#جے_انت
