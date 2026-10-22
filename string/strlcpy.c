/* Copy a null-terminated string to a fixed-size buffer, with length checking.
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

#ಅನ್ತರ್ಭಾವ <string.h>

size_t
__strlcpy (ಅಕ್ಷರ *__restrict dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict src, size_t ಗಾತ್ರ_2)
{
  size_t src_ಉದ್ದಳತೆ = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (src);

  ಆದರೆ (__glibc_unlikely (src_ಉದ್ದಳತೆ >= ಗಾತ್ರ_2))
    {
      ಆದರೆ (ಗಾತ್ರ_2 > 0)
	{
	  /* Copy the leading portion of the string.  The last
	     character is subsequently overwritten with the NUL
	     terminator, but the destination size is usually a
	     multiple of a small power of two, so writing it twice
	     should be more efficient than copying an odd number of
	     bytes.  */
	  ಸ್ಮರಣೆ_ನಕಲು (dest, src, ಗಾತ್ರ_2);
	  dest[ಗಾತ್ರ_2 - 1] = '\0';
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    /* Copy the string and its terminating NUL character.  */
    ಸ್ಮರಣೆ_ನಕಲು (dest, src, src_ಉದ್ದಳತೆ + 1);
  ಹಿಂತಿರುಗಿ src_ಉದ್ದಳತೆ;
}
libc_hidden_def (__strlcpy)
weak_alias (__strlcpy, strlcpy)
