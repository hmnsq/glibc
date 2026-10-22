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

#அந்தர்பாவ <argz.h>
#அந்தர்பாவ <string.h>

எழுத்து *
__argz_next (மாறிலி எழுத்து *argz, size_t argz_len, மாறிலி எழுத்து *entry)
{
  எனில் (entry)
    {
      எனில் (entry < argz + argz_len)
	entry = strchr (entry, '\0') + 1;

      திரும்பு entry >= argz + argz_len ? வெற்று : (எழுத்து *) entry;
    }
  இல்லையெனில்
    எனில் (argz_len > 0)
      திரும்பு (எழுத்து *) argz;
    இல்லையெனில்
      திரும்பு வெற்று;
}
libc_hidden_def (__argz_next)
static_weak_alias (__argz_next, argz_next)
libc_hidden_weak (argz_next)
