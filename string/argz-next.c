/* Iterate through the elements of an argz block.
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

حرف *
__argz_next (ثابت حرف *argz, size_t argz_len, ثابت حرف *اندراج_2)
{
  اگر (اندراج_2)
    {
      اگر (اندراج_2 < argz + argz_len)
	اندراج_2 = strchr (اندراج_2, '\0') + 1;

      واپس اندراج_2 >= argz + argz_len ? تہی : (حرف *) اندراج_2;
    }
  ورنہ
    اگر (argz_len > 0)
      واپس (حرف *) argz;
    ورنہ
      واپس تہی;
}
libc_hidden_def (__argz_next)
static_weak_alias (__argz_next, argz_اگلا)
libc_hidden_weak (argz_اگلا)
