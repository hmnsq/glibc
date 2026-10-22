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

#నిర్వచితం_కాకపోతే _BITS_STRING_FORTIFIED_H
#నిర్వచించు _BITS_STRING_FORTIFIED_H 1

#నిర్వచితం_కాకపోతే _STRING_H
# error "Never use <bits/string_fortified.h> directly; include <string.h> instead."
#అయితే_ముగింపు

__fortify_function శూన్య *
__NTH (జ్ఞాపకం_నకలు (శూన్య *__restrict __dest, స్థిరరాశి శూన్య *__restrict __src,
	       size_t __len))
{
  తిరిగి __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function శూన్య *
__NTH (memmove (శూన్య *__dest, స్థిరరాశి శూన్య *__src, size_t __len))
{
  తిరిగి __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#నిర్వచితమైతే __USE_GNU
__fortify_function శూన్య *
__NTH (mempcpy (శూన్య *__restrict __dest, స్థిరరాశి శూన్య *__restrict __src,
		size_t __len))
{
  తిరిగి __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#అయితే_ముగింపు


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function శూన్య *
__NTH (memset (శూన్య *__dest, పూర్ణాంకం __ch, size_t __len))
{
  తిరిగి __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#ఒకవేళ defined __USE_MISC || __GLIBC_USE (ISOC23)
శూన్య *__memset_explicit_chk (శూన్య *__s, పూర్ణాంకం __c, size_t __n, size_t __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function శూన్య *
__NTH (memset_explicit (శూన్య *__dest, పూర్ణాంకం __ch, size_t __len))
{
  తిరిగి __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
# include <bits/strings_fortified.h>

శూన్య __explicit_bzero_chk (శూన్య *__dest, size_t __len, size_t __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function శూన్య
__NTH (explicit_bzero (శూన్య *__dest, size_t __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#అయితే_ముగింపు

__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (strcpy (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
	       స్థిరరాశి అక్షరం *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  తిరిగి __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#నిర్వచితమైతే __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (stpcpy (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
	       స్థిరరాశి అక్షరం *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  తిరిగి __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#అయితే_ముగింపు


__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (strncpy (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
		స్థిరరాశి అక్షరం *__restrict __src, size_t __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  తిరిగి __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#నిర్వచితమైతే __USE_XOPEN2K8
# ఒకవేళ __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (stpncpy (__fortify_clang_overload_arg (అక్షరం *, ,__dest),
		స్థిరరాశి అక్షరం *__src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  తిరిగి __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# లేకపోతే
బాహ్య అక్షరం *__stpncpy_chk (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n,
			    size_t __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
బాహ్య అక్షరం *__REDIRECT_NTH (__stpncpy_alias, (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src,
					       size_t __n), stpncpy);

__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (stpncpy (__fortify_clang_overload_arg (అక్షరం *, ,__dest),
		స్థిరరాశి అక్షరం *__src, size_t __n))
{
  ఒకవేళ (__bos (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    తిరిగి __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  తిరిగి __stpncpy_alias (__dest, __src, __n);
}
# endif
#అయితే_ముగింపు


__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (strcat (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
	       స్థిరరాశి అక్షరం *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  తిరిగి __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ అక్షరం *
__NTH (strncat (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
		స్థిరరాశి అక్షరం *__restrict __src, size_t __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  తిరిగి __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#నిర్వచితమైతే __USE_MISC
బాహ్య size_t __strlcpy_chk (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n,
			     size_t __destlen) __THROW;
బాహ్య size_t __REDIRECT_NTH (__strlcpy_alias,
			      (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcpy (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
		స్థిరరాశి అక్షరం *__restrict __src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ఒకవేళ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    తిరిగి __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  తిరిగి __strlcpy_alias (__dest, __src, __n);
}

బాహ్య size_t __strlcat_chk (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n,
			     size_t __destlen) __THROW;
బాహ్య size_t __REDIRECT_NTH (__strlcat_alias,
			      (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n),
			      strlcat);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcat (__fortify_clang_overload_arg (అక్షరం *, __restrict, __dest),
		స్థిరరాశి అక్షరం *__restrict __src, size_t __n))
{
  ఒకవేళ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    తిరిగి __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  తిరిగి __strlcat_alias (__dest, __src, __n);
}
#అయితే_ముగింపు /* __USE_MISC */

#అయితే_ముగింపు /* bits/string_fortified.h */
