/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#شامل <argz.h>
#شامل <string.h>
#شامل <stdlib.h>

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ.  If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0.  */
error_t
__argz_insert (حرف **argz, size_t *argz_len, حرف *before, ثابت حرف *اندراج_2)
{
  اگر (! before)
    واپس __argz_add (argz, argz_len, اندراج_2);

  اگر (before < *argz || before >= *argz + *argz_len)
    واپس EINVAL;

  اگر (before > *argz)
    /* Make sure before is actually the beginning of an entry.  */
    جب (before[-1])
      before--;

  {
    size_t after_before = *argz_len - (before - *argz);
    size_t اندراج_len = لڑی_لمبائی  (اندراج_2) + 1;
    size_t new_argz_len = *argz_len + اندراج_len;
    حرف *new_argz = realloc (*argz, new_argz_len);

    اگر (new_argz)
      {
	before = new_argz + (before - *argz);
	memmove (before + اندراج_len, before, after_before);
	memmove (before, اندراج_2, اندراج_len);
	*argz = new_argz;
	*argz_len = new_argz_len;
	واپس 0;
      }
    ورنہ
      واپس ENOMEM;
  }
}
weak_alias (__argz_insert, argz_داخل_کرو)
