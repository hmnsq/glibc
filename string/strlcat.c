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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

माप_प्रकार
__strlcat (अक्षर *__restrict dest, स्थिरांक अक्षर *__restrict src, माप_प्रकार size)
{
  माप_प्रकार src_length = म_माप (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  जर (size == 0)
    परत src_length;

  माप_प्रकार dest_length = __strnlen (dest, size);
  जर (dest_length != size)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      माप_प्रकार to_copy = size - dest_length - 1;
      /* But not more than what is available in the source string.  */
      जर (to_copy > src_length)
	to_copy = src_length;

      अक्षर *target = dest + dest_length;
      स_नकल (target, src, to_copy);
      target[to_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (आकार (uintptr_t) == आकार (माप_प्रकार),
		  "theoretical maximum object size covers address space");
  परत dest_length + src_length;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
