/* Append a null-terminated string to another string, with length checking.
   Copyright (C) 2023-2026 Free Software Foundation, Inc.
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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

size_t
__strlcat (ਅੱਖਰ *__restrict dest, ਅਚਲ ਅੱਖਰ *__restrict src, size_t ਮਾਪ)
{
  size_t src_ਲੰਮਾਈ = ਲੜੀ_ਲੰਬਾਈ (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  ਜੇ (ਮਾਪ == 0)
    ਵਾਪਸ src_ਲੰਮਾਈ;

  size_t dest_ਲੰਮਾਈ = __strnlen (dest, ਮਾਪ);
  ਜੇ (dest_ਲੰਮਾਈ != ਮਾਪ)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      size_t ਮੰਜ਼ਿਲ_copy = ਮਾਪ - dest_ਲੰਮਾਈ - 1;
      /* But not more than what is available in the source string.  */
      ਜੇ (ਮੰਜ਼ਿਲ_copy > src_ਲੰਮਾਈ)
	ਮੰਜ਼ਿਲ_copy = src_ਲੰਮਾਈ;

      ਅੱਖਰ *ਨਿਸ਼ਾਨਾ = dest + dest_ਲੰਮਾਈ;
      ਸਮ੍ਰਿਤੀ_ਨਕਲ (ਨਿਸ਼ਾਨਾ, src, ਮੰਜ਼ਿਲ_copy);
      ਨਿਸ਼ਾਨਾ[ਮੰਜ਼ਿਲ_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (ਆਕਾਰ (uintptr_t) == ਆਕਾਰ (size_t),
		  "theoretical maximum object size covers address space");
  ਵਾਪਸ dest_ਲੰਮਾਈ + src_ਲੰਮਾਈ;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
