/* Fortify macros for strings.h functions.
   Copyright (C) 2017-2026 Free Software Foundation, Inc.
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

#నిర్వచితం_కాకపోతే __STRINGS_FORTIFIED
# define __STRINGS_FORTIFIED 1

__fortify_function శూన్య
__NTH (bcopy (స్థిరరాశి శూన్య *__src, శూన్య *__dest, size_t __len))
{
  (శూన్య) __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

__fortify_function శూన్య
__NTH (bzero (శూన్య *__dest, size_t __len))
{
  (శూన్య) __builtin___memset_chk (__dest, '\0', __len,
				 __glibc_objsize0 (__dest));
}

#అయితే_ముగింపు
