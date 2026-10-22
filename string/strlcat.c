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

#समावेश <stdint.h>
#समावेश <string.h>

माप_प्रकार
__strlcat (अक्षर *__restrict dest, स्थिर अक्षर *__restrict src, माप_प्रकार आकार)
{
  माप_प्रकार src_लंबाई = म_माप (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  अगर (आकार == 0)
    वापस src_लंबाई;

  माप_प्रकार dest_लंबाई = __strnlen (dest, आकार);
  अगर (dest_लंबाई != आकार)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      माप_प्रकार to_copy = आकार - dest_लंबाई - 1;
      /* But not more than what is available in the source string.  */
      अगर (to_copy > src_लंबाई)
	to_copy = src_लंबाई;

      अक्षर *target = dest + dest_लंबाई;
      स_नकल (target, src, to_copy);
      target[to_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (माप (uintptr_t) == माप (माप_प्रकार),
		  "theoretical maximum object size covers address space");
  वापस dest_लंबाई + src_लंबाई;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
