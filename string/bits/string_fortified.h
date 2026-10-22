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

__fortify_function ଶୂନ୍ୟ *
__NTH (memcpy (ଶୂନ୍ୟ *__restrict __dest, ଅଚଳ ଶୂନ୍ୟ *__restrict __src,
	       size_t __len))
{
  ଫେରନ୍ତୁ __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function ଶୂନ୍ୟ *
__NTH (memmove (ଶୂନ୍ୟ *__dest, ଅଚଳ ଶୂନ୍ୟ *__src, size_t __len))
{
  ଫେରନ୍ତୁ __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#ifdef __USE_GNU
__fortify_function ଶୂନ୍ୟ *
__NTH (mempcpy (ଶୂନ୍ୟ *__restrict __dest, ଅଚଳ ଶୂନ୍ୟ *__restrict __src,
		size_t __len))
{
  ଫେରନ୍ତୁ __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#endif


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function ଶୂନ୍ୟ *
__NTH (memset (ଶୂନ୍ୟ *__dest, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __ch, size_t __len))
{
  ଫେରନ୍ତୁ __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#ଯଦି defined __USE_MISC || __GLIBC_USE (ISOC23)
ଶୂନ୍ୟ *__memset_explicit_chk (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n, size_t __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function ଶୂନ୍ୟ *
__NTH (memset_explicit (ଶୂନ୍ୟ *__dest, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __ch, size_t __len))
{
  ଫେରନ୍ତୁ __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#endif

#ifdef __USE_MISC
# include <bits/strings_fortified.h>

ଶୂନ୍ୟ __explicit_bzero_chk (ଶୂନ୍ୟ *__dest, size_t __len, size_t __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function ଶୂନ୍ୟ
__NTH (explicit_bzero (ଶୂନ୍ୟ *__dest, size_t __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#endif

__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (strcpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
	       ଅଚଳ ଅକ୍ଷର *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ଫେରନ୍ତୁ __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (stpcpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
	       ଅଚଳ ଅକ୍ଷର *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ଫେରନ୍ତୁ __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#endif


__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (strncpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
		ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  ଫେରନ୍ତୁ __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
# ଯଦି __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (stpncpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, ,__dest),
		ଅଚଳ ଅକ୍ଷର *__src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ଫେରନ୍ତୁ __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *__stpncpy_chk (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n,
			    size_t __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
ବାହ୍ୟ ଅକ୍ଷର *__REDIRECT_NTH (__stpncpy_alias, (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src,
					       size_t __n), stpncpy);

__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (stpncpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, ,__dest),
		ଅଚଳ ଅକ୍ଷର *__src, size_t __n))
{
  ଯଦି (__bos (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    ଫେରନ୍ତୁ __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  ଫେରନ୍ତୁ __stpncpy_alias (__dest, __src, __n);
}
# endif
#endif


__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (strcat (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
	       ଅଚଳ ଅକ୍ଷର *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ଫେରନ୍ତୁ __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ ଅକ୍ଷର *
__NTH (strncat (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
		ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ଫେରନ୍ତୁ __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_MISC
ବାହ୍ୟ size_t __strlcpy_chk (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n,
			     size_t __destlen) __THROW;
ବାହ୍ୟ size_t __REDIRECT_NTH (__strlcpy_alias,
			      (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcpy (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
		ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ଯଦି (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ଫେରନ୍ତୁ __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ଫେରନ୍ତୁ __strlcpy_alias (__dest, __src, __n);
}

ବାହ୍ୟ size_t __strlcat_chk (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n,
			     size_t __destlen) __THROW;
ବାହ୍ୟ size_t __REDIRECT_NTH (__strlcat_alias,
			      (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n),
			      strlcat);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcat (__fortify_clang_overload_arg (ଅକ୍ଷର *, __restrict, __dest),
		ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n))
{
  ଯଦି (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ଫେରନ୍ତୁ __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ଫେରନ୍ତୁ __strlcat_alias (__dest, __src, __n);
}
#endif /* __USE_MISC */

#endif /* bits/string_fortified.h */
