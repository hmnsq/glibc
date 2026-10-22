/* Copyright (C) 2004-2026 Free Software Foundation, Inc.
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

#ifndef _BITS_STRING_FORTIFIED_H
#define _BITS_STRING_FORTIFIED_H 1

#ifndef _STRING_H
# error "Never use <bits/string_fortified.h> directly; include <string.h> instead."
#endif

__fortify_function ಶೂನ್ಯ *
__NTH (memcpy (ಶೂನ್ಯ *__restrict __dest, ಧ್ರುವ ಶೂನ್ಯ *__restrict __src,
	       size_t __len))
{
  ಪ್ರತ್ಯಾಗಮ __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function ಶೂನ್ಯ *
__NTH (memmove (ಶೂನ್ಯ *__dest, ಧ್ರುವ ಶೂನ್ಯ *__src, size_t __len))
{
  ಪ್ರತ್ಯಾಗಮ __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#ifdef __USE_GNU
__fortify_function ಶೂನ್ಯ *
__NTH (mempcpy (ಶೂನ್ಯ *__restrict __dest, ಧ್ರುವ ಶೂನ್ಯ *__restrict __src,
		size_t __len))
{
  ಪ್ರತ್ಯಾಗಮ __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#endif


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function ಶೂನ್ಯ *
__NTH (memset (ಶೂನ್ಯ *__dest, ಪೂರ್ಣಾಙ್ಕ __ch, size_t __len))
{
  ಪ್ರತ್ಯಾಗಮ __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#ಯದಿ defined __USE_MISC || __GLIBC_USE (ISOC23)
ಶೂನ್ಯ *__memset_explicit_chk (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಙ್ಕ __c, size_t __n, size_t __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function ಶೂನ್ಯ *
__NTH (memset_explicit (ಶೂನ್ಯ *__dest, ಪೂರ್ಣಾಙ್ಕ __ch, size_t __len))
{
  ಪ್ರತ್ಯಾಗಮ __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#endif

#ifdef __USE_MISC
# include <bits/strings_fortified.h>

ಶೂನ್ಯ __explicit_bzero_chk (ಶೂನ್ಯ *__dest, size_t __len, size_t __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function ಶೂನ್ಯ
__NTH (explicit_bzero (ಶೂನ್ಯ *__dest, size_t __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#endif

__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (strcpy (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
	       ಧ್ರುವ ವರ್ಣ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (stpcpy (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
	       ಧ್ರುವ ವರ್ಣ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#endif


__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (strncpy (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
		ಧ್ರುವ ವರ್ಣ *__restrict __src, size_t __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
# ಯದಿ __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (stpncpy (__fortify_clang_overload_arg (ವರ್ಣ *, ,__dest),
		ಧ್ರುವ ವರ್ಣ *__src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# ಅನ್ಯಥಾ
ಬಾಹ್ಯ ವರ್ಣ *__stpncpy_chk (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src, size_t __n,
			    size_t __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
ಬಾಹ್ಯ ವರ್ಣ *__REDIRECT_NTH (__stpncpy_alias, (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src,
					       size_t __n), stpncpy);

__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (stpncpy (__fortify_clang_overload_arg (ವರ್ಣ *, ,__dest),
		ಧ್ರುವ ವರ್ಣ *__src, size_t __n))
{
  ಯದಿ (__bos (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    ಪ್ರತ್ಯಾಗಮ __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  ಪ್ರತ್ಯಾಗಮ __stpncpy_alias (__dest, __src, __n);
}
# endif
#endif


__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (strcat (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
	       ಧ್ರುವ ವರ್ಣ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ ವರ್ಣ *
__NTH (strncat (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
		ಧ್ರುವ ವರ್ಣ *__restrict __src, size_t __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಪ್ರತ್ಯಾಗಮ __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_MISC
ಬಾಹ್ಯ size_t __strlcpy_chk (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src, size_t __n,
			     size_t __destlen) __THROW;
ಬಾಹ್ಯ size_t __REDIRECT_NTH (__strlcpy_alias,
			      (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src, size_t __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcpy (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
		ಧ್ರುವ ವರ್ಣ *__restrict __src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ಯದಿ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ಪ್ರತ್ಯಾಗಮ __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ಪ್ರತ್ಯಾಗಮ __strlcpy_alias (__dest, __src, __n);
}

ಬಾಹ್ಯ size_t __strlcat_chk (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src, size_t __n,
			     size_t __destlen) __THROW;
ಬಾಹ್ಯ size_t __REDIRECT_NTH (__strlcat_alias,
			      (ವರ್ಣ *__dest, ಧ್ರುವ ವರ್ಣ *__src, size_t __n),
			      strlcat);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcat (__fortify_clang_overload_arg (ವರ್ಣ *, __restrict, __dest),
		ಧ್ರುವ ವರ್ಣ *__restrict __src, size_t __n))
{
  ಯದಿ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ಪ್ರತ್ಯಾಗಮ __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ಪ್ರತ್ಯಾಗಮ __strlcat_alias (__dest, __src, __n);
}
#endif /* __USE_MISC */

#endif /* bits/string_fortified.h */
