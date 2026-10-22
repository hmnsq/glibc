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

#اگر_تعریف_شدہ HAVE_CONFIG_H
#شامل <config.h>
#اگر_ختم

#اگر defined _LIBC || defined  STDC_سرخیاں
# include <stdlib.h>
# include <string.h>
#ورنہ
حرف *حافظہ_دو ();
حرف *حافظہ_نقل ();
#اگر_ختم

#تعریف_منسوخ __strdup
#تعریف_منسوخ strdup

#اگر_غیر_تعریف_شدہ weak_alias
# define __strdup strdup
#اگر_ختم

/* Duplicate S, returning an identical malloc'd string.  */
حرف *
__strdup (ثابت حرف *s)
{
  size_t len = لڑی_لمبائی (s) + 1;
  خالی *new = حافظہ_دو (len);

  اگر (new == تہی)
    واپس تہی;

  واپس (حرف *) حافظہ_نقل (new, s, len);
}
#اگر_تعریف_شدہ libc_hidden_def
libc_hidden_def (__strdup)
#اگر_ختم
#اگر_تعریف_شدہ weak_alias
weak_alias (__strdup, strdup)
#اگر_ختم
