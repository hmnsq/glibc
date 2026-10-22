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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

size_t
__strlcat (అక్షరం *__restrict dest, స్థిరరాశి అక్షరం *__restrict src, size_t కొలత)
{
  size_t src_నిడివి = అక్షరశ్రేణి_పొడవు (src);

  /* Our implementation strlcat supports dest == NULL if size == 0
     (for consistency with snprintf and strlcpy), but strnlen does
     not, so we have to cover this case explicitly.  */
  ఒకవేళ (కొలత == 0)
    తిరిగి src_నిడివి;

  size_t dest_నిడివి = __strnlen (dest, కొలత);
  ఒకవేళ (dest_నిడివి != కొలత)
    {
      /* Copy at most the remaining number of characters in the
	 destination buffer.  Leave for the NUL terminator.  */
      size_t గమ్యం_copy = కొలత - dest_నిడివి - 1;
      /* But not more than what is available in the source string.  */
      ఒకవేళ (గమ్యం_copy > src_నిడివి)
	గమ్యం_copy = src_నిడివి;

      అక్షరం *లక్ష్యం = dest + dest_నిడివి;
      జ్ఞాపకం_నకలు (లక్ష్యం, src, గమ్యం_copy);
      లక్ష్యం[గమ్యం_copy] = '\0';
    }

  /* If the sum wraps around, we have more than SIZE_MAX + 2 bytes in
     the two input strings (including both null terminators).  If each
     byte in the address space can be assigned a unique size_t value
     (which the static_assert checks), then by the pigeonhole
     principle, the two input strings must overlap, which is
     undefined.  */
  _Static_assert (పరిమాణం (uintptr_t) == పరిమాణం (size_t),
		  "theoretical maximum object size covers address space");
  తిరిగి dest_నిడివి + src_నిడివి;
}
libc_hidden_def (__strlcat)
weak_alias (__strlcat, strlcat)
