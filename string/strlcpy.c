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

#समावेश <string.h>

माप_प्रकार
__strlcpy (अक्षर *__restrict dest, स्थिर अक्षर *__restrict src, माप_प्रकार आकार)
{
  माप_प्रकार src_लंबाई = म_माप (src);

  अगर (__glibc_unlikely (src_लंबाई >= आकार))
    {
      अगर (आकार > 0)
	{
	  /* Copy the leading portion of the string.  The last
	     character is subsequently overwritten with the NUL
	     terminator, but the destination size is usually a
	     multiple of a small power of two, so writing it twice
	     should be more efficient than copying an odd number of
	     bytes.  */
	  स_नकल (dest, src, आकार);
	  dest[आकार - 1] = '\0';
	}
    }
  अन्यथा
    /* Copy the string and its terminating NUL character.  */
    स_नकल (dest, src, src_लंबाई + 1);
  वापस src_लंबाई;
}
libc_hidden_def (__strlcpy)
weak_alias (__strlcpy, strlcpy)
