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

#అన్తర్భావ <string.h>

/* glibc-internal users use __memset_explicit_chk, and memset_explicit
   redirects to that.  */
#నిర్వచనం_రద్దు memset_explicit

/* Set LEN bytes of S to C.  The compiler will not delete a call to
   this function, even if S is dead after the call.  */
శూన్య *
memset_explicit (శూన్య *s, పూర్ణాంకం c, size_t len)
{
  memset (s, c, len);
  /* Compiler barrier.  */
  asm అస్థిర ("" ::: "memory");
  తిరిగి s;
}
