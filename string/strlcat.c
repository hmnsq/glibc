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

size_t
__strlcat (वर्ण *__restrict dest, ध्रुव वर्ण *__restrict src, size_t आकार)
{
  size_t src_दीर्घता = वाक्यदैर्घ्यम् (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  यदि (आकार == 0)
    प्रत्यागम src_दीर्घता;

  size_t dest_दीर्घता = __strnlen (dest, आकार);
  यदि (dest_दीर्घता != आकार)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      size_t गन्तव्यम्_copy = आकार - dest_दीर्घता - 1;
      /* But not more than what is available in the source string.  */
      यदि (गन्तव्यम्_copy > src_दीर्घता)
	गन्तव्यम्_copy = src_दीर्घता;

      वर्ण *target = dest + dest_दीर्घता;
      स्मृतिं_प्रतिलिख (target, src, गन्तव्यम्_copy);
      target[गन्तव्यम्_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (परिमाण (uintptr_t) == परिमाण (size_t),
		  "theoretical maximum object size covers address space");
  प्रत्यागम dest_दीर्घता + src_दीर्घता;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
