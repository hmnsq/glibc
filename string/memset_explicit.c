/* Erasure of sensitive data, generic implementation.
   Copyright (C) 2016-2026 Free Software Foundation, Inc.
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

/* An assembler implementation of memset_explicit can be created as an
   assembler alias of an optimized memset implementation.
   Architecture-specific implementations also need to define
   __memset_explicit_chk.  */

#ଅନ୍ତର୍ଭାଵ <string.h>

/* glibc-internal users use __memset_explicit_chk, and memset_explicit
   redirects to that.  */
#undef memset_explicit

/* Set LEN bytes of S to C.  The compiler will not delete a call to
   this function, even if S is dead after the call.  */
ଶୂନ୍ୟ *
memset_explicit (ଶୂନ୍ୟ *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, size_t len)
{
  memset (s, c, len);
  /* Compiler barrier.  */
  asm ଅସ୍ଥିର ("" ::: "memory");
  ଫେରନ୍ତୁ s;
}
