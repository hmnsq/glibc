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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

size_t
__strlcat (ಅಕ್ಷರ *__restrict dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict src, size_t ಗಾತ್ರ_2)
{
  size_t src_ಉದ್ದಳತೆ = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  ಆದರೆ (ಗಾತ್ರ_2 == 0)
    ಹಿಂತಿರುಗಿ src_ಉದ್ದಳತೆ;

  size_t dest_ಉದ್ದಳತೆ = __strnlen (dest, ಗಾತ್ರ_2);
  ಆದರೆ (dest_ಉದ್ದಳತೆ != ಗಾತ್ರ_2)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      size_t ಗಮ್ಯ_copy = ಗಾತ್ರ_2 - dest_ಉದ್ದಳತೆ - 1;
      /* But not more than what is available in the source string.  */
      ಆದರೆ (ಗಮ್ಯ_copy > src_ಉದ್ದಳತೆ)
	ಗಮ್ಯ_copy = src_ಉದ್ದಳತೆ;

      ಅಕ್ಷರ *ಗುರಿ = dest + dest_ಉದ್ದಳತೆ;
      ಸ್ಮರಣೆ_ನಕಲು (ಗುರಿ, src, ಗಮ್ಯ_copy);
      ಗುರಿ[ಗಮ್ಯ_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (ಗಾತ್ರ (uintptr_t) == ಗಾತ್ರ (size_t),
		  "theoretical maximum object size covers address space");
  ಹಿಂತಿರುಗಿ dest_ಉದ್ದಳತೆ + src_ಉದ್ದಳತೆ;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
