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

#جے_بنا_تعریف _BITS_STRING_FORTIFIED_H
#تعریف_کرو _BITS_STRING_FORTIFIED_H 1

#جے_بنا_تعریف _STRING_H
# error "Never use <bits/string_fortified.h> directly; include <string.h> instead."
#جے_انت

__fortify_function فراغ *
__NTH (حافظہ_نقل (فراغ *__restrict __dest, ثابت فراغ *__restrict __src,
	       size_t __len))
{
  أرجع __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function فراغ *
__NTH (memmove (فراغ *__dest, ثابت فراغ *__src, size_t __len))
{
  أرجع __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#جے_تعریف_شدہ __USE_GNU
__fortify_function فراغ *
__NTH (mempcpy (فراغ *__restrict __dest, ثابت فراغ *__restrict __src,
		size_t __len))
{
  أرجع __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#جے_انت


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function فراغ *
__NTH (memset (فراغ *__dest, صحيح __ch, size_t __len))
{
  أرجع __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#إذا defined __USE_MISC || __GLIBC_USE (ISOC23)
فراغ *__memset_explicit_chk (فراغ *__s, صحيح __c, size_t __n, size_t __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function فراغ *
__NTH (memset_explicit (فراغ *__dest, صحيح __ch, size_t __len))
{
  أرجع __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#جے_انت

#جے_تعریف_شدہ __USE_MISC
# include <bits/strings_fortified.h>

فراغ __explicit_bzero_chk (فراغ *__dest, size_t __len, size_t __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function فراغ
__NTH (explicit_bzero (فراغ *__dest, size_t __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#جے_انت

__fortify_function __attribute_overloadable__ حرف *
__NTH (strcpy (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
	       ثابت حرف *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  أرجع __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#جے_تعریف_شدہ __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ حرف *
__NTH (stpcpy (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
	       ثابت حرف *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  أرجع __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#جے_انت


__fortify_function __attribute_overloadable__ حرف *
__NTH (strncpy (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
		ثابت حرف *__restrict __src, size_t __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  أرجع __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#جے_تعریف_شدہ __USE_XOPEN2K8
# إذا __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ حرف *
__NTH (stpncpy (__fortify_clang_overload_arg (حرف *, ,__dest),
		ثابت حرف *__src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  أرجع __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# وإلا
خارجي حرف *__stpncpy_chk (حرف *__dest, ثابت حرف *__src, size_t __n,
			    size_t __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
خارجي حرف *__REDIRECT_NTH (__stpncpy_alias, (حرف *__dest, ثابت حرف *__src,
					       size_t __n), stpncpy);

__fortify_function __attribute_overloadable__ حرف *
__NTH (stpncpy (__fortify_clang_overload_arg (حرف *, ,__dest),
		ثابت حرف *__src, size_t __n))
{
  إذا (__bos (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    أرجع __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  أرجع __stpncpy_alias (__dest, __src, __n);
}
# endif
#جے_انت


__fortify_function __attribute_overloadable__ حرف *
__NTH (strcat (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
	       ثابت حرف *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  أرجع __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ حرف *
__NTH (strncat (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
		ثابت حرف *__restrict __src, size_t __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  أرجع __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#جے_تعریف_شدہ __USE_MISC
خارجي size_t __strlcpy_chk (حرف *__dest, ثابت حرف *__src, size_t __n,
			     size_t __destlen) __THROW;
خارجي size_t __REDIRECT_NTH (__strlcpy_alias,
			      (حرف *__dest, ثابت حرف *__src, size_t __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcpy (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
		ثابت حرف *__restrict __src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  إذا (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    أرجع __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  أرجع __strlcpy_alias (__dest, __src, __n);
}

خارجي size_t __strlcat_chk (حرف *__dest, ثابت حرف *__src, size_t __n,
			     size_t __destlen) __THROW;
خارجي size_t __REDIRECT_NTH (__strlcat_alias,
			      (حرف *__dest, ثابت حرف *__src, size_t __n),
			      strlcat);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcat (__fortify_clang_overload_arg (حرف *, __restrict, __dest),
		ثابت حرف *__restrict __src, size_t __n))
{
  إذا (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    أرجع __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  أرجع __strlcat_alias (__dest, __src, __n);
}
#جے_انت /* __USE_MISC */

#جے_انت /* bits/string_fortified.h */
