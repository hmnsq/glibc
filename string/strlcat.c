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

#شامل <stdint.h>
#شامل <string.h>

size_t
__strlcat (حرف *__restrict dest, ثابت حرف *__restrict src, size_t سائز)
{
  size_t src_لمبائی = لڑی_لمبائی (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  اگر (سائز == 0)
    واپس src_لمبائی;

  size_t dest_لمبائی = __strnlen (dest, سائز);
  اگر (dest_لمبائی != سائز)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      size_t مقصد_copy = سائز - dest_لمبائی - 1;
      /* But not more than what is available in the source string.  */
      اگر (مقصد_copy > src_لمبائی)
	مقصد_copy = src_لمبائی;

      حرف *ہدف = dest + dest_لمبائی;
      حافظہ_نقل (ہدف, src, مقصد_copy);
      ہدف[مقصد_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (حجم (uintptr_t) == حجم (size_t),
		  "theoretical maximum object size covers address space");
  واپس dest_لمبائی + src_لمبائی;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
