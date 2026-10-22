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

__fortify_function शून्य *
__NTH (स_नकल (शून्य *__restrict __dest, अचर शून्य *__restrict __src,
	       माप_प्रकार __len))
{
  फर्काऊ __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function शून्य *
__NTH (स_हटाओ (शून्य *__dest, अचर शून्य *__src, माप_प्रकार __len))
{
  फर्काऊ __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#ifdef __USE_GNU
__fortify_function शून्य *
__NTH (mempcpy (शून्य *__restrict __dest, अचर शून्य *__restrict __src,
		माप_प्रकार __len))
{
  फर्काऊ __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#endif


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function शून्य *
__NTH (स_रखो (शून्य *__dest, पूर्णाङ्क __ch, माप_प्रकार __len))
{
  फर्काऊ __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#यदि defined __USE_MISC || __GLIBC_USE (ISOC23)
शून्य *__memset_explicit_chk (शून्य *__s, पूर्णाङ्क __c, माप_प्रकार __n, माप_प्रकार __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function शून्य *
__NTH (memset_explicit (शून्य *__dest, पूर्णाङ्क __ch, माप_प्रकार __len))
{
  फर्काऊ __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#endif

#ifdef __USE_MISC
# include <bits/strings_fortified.h>

शून्य __explicit_bzero_chk (शून्य *__dest, माप_प्रकार __len, माप_प्रकार __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function शून्य
__NTH (explicit_bzero (शून्य *__dest, माप_प्रकार __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#endif

__fortify_function __attribute_overloadable__ वर्ण *
__NTH (म_नकल (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
	       अचर वर्ण *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  फर्काऊ __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ वर्ण *
__NTH (stpcpy (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
	       अचर वर्ण *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  फर्काऊ __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#endif


__fortify_function __attribute_overloadable__ वर्ण *
__NTH (म_नकलन (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
		अचर वर्ण *__restrict __src, माप_प्रकार __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  फर्काऊ __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_XOPEN2K8
# यदि __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ वर्ण *
__NTH (stpncpy (__fortify_clang_overload_arg (वर्ण *, ,__dest),
		अचर वर्ण *__src, माप_प्रकार __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  फर्काऊ __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# अन्यथा
बाह्य वर्ण *__stpncpy_chk (वर्ण *__dest, अचर वर्ण *__src, माप_प्रकार __n,
			    माप_प्रकार __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
बाह्य वर्ण *__REDIRECT_NTH (__stpncpy_alias, (वर्ण *__dest, अचर वर्ण *__src,
					       माप_प्रकार __n), stpncpy);

__fortify_function __attribute_overloadable__ वर्ण *
__NTH (stpncpy (__fortify_clang_overload_arg (वर्ण *, ,__dest),
		अचर वर्ण *__src, माप_प्रकार __n))
{
  यदि (__bos (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    फर्काऊ __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  फर्काऊ __stpncpy_alias (__dest, __src, __n);
}
# endif
#endif


__fortify_function __attribute_overloadable__ वर्ण *
__NTH (म_जोड़ो (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
	       अचर वर्ण *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  फर्काऊ __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ वर्ण *
__NTH (म_जोड़न (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
		अचर वर्ण *__restrict __src, माप_प्रकार __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  फर्काऊ __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ifdef __USE_MISC
बाह्य माप_प्रकार __strlcpy_chk (वर्ण *__dest, अचर वर्ण *__src, माप_प्रकार __n,
			     माप_प्रकार __destlen) __THROW;
बाह्य माप_प्रकार __REDIRECT_NTH (__strlcpy_alias,
			      (वर्ण *__dest, अचर वर्ण *__src, माप_प्रकार __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ माप_प्रकार
__NTH (strlcpy (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
		अचर वर्ण *__restrict __src, माप_प्रकार __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  यदि (__glibc_objsize (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    फर्काऊ __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  फर्काऊ __strlcpy_alias (__dest, __src, __n);
}

बाह्य माप_प्रकार __strlcat_chk (वर्ण *__dest, अचर वर्ण *__src, माप_प्रकार __n,
			     माप_प्रकार __destlen) __THROW;
बाह्य माप_प्रकार __REDIRECT_NTH (__strlcat_alias,
			      (वर्ण *__dest, अचर वर्ण *__src, माप_प्रकार __n),
			      strlcat);

__fortify_function __attribute_overloadable__ माप_प्रकार
__NTH (strlcat (__fortify_clang_overload_arg (वर्ण *, __restrict, __dest),
		अचर वर्ण *__restrict __src, माप_प्रकार __n))
{
  यदि (__glibc_objsize (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    फर्काऊ __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  फर्काऊ __strlcat_alias (__dest, __src, __n);
}
#endif /* __USE_MISC */

#endif /* bits/string_fortified.h */
