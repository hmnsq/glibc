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

#अगर_अघोषित _BITS_STRING_FORTIFIED_H
#घोषणा _BITS_STRING_FORTIFIED_H 1

#अगर_अघोषित _STRING_H
# error "Never use <bits/string_fortified.h> directly; include <string.h> instead."
#पूर्ण_अगर

__fortify_function व्योम *
__NTH (स_नकल (व्योम *__restrict __dest, स्थिर व्योम *__restrict __src,
	       माप_प्रकार __len))
{
  वापस __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function व्योम *
__NTH (स_हटाओ (व्योम *__dest, स्थिर व्योम *__src, माप_प्रकार __len))
{
  वापस __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#अगर_घोषित __USE_GNU
__fortify_function व्योम *
__NTH (mempcpy (व्योम *__restrict __dest, स्थिर व्योम *__restrict __src,
		माप_प्रकार __len))
{
  वापस __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#पूर्ण_अगर


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function व्योम *
__NTH (स_रखो (व्योम *__dest, पूर्णांक __ch, माप_प्रकार __len))
{
  वापस __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#अगर defined __USE_MISC || __GLIBC_USE (ISOC23)
व्योम *__memset_explicit_chk (व्योम *__s, पूर्णांक __c, माप_प्रकार __n, माप_प्रकार __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function व्योम *
__NTH (memset_explicit (व्योम *__dest, पूर्णांक __ch, माप_प्रकार __len))
{
  वापस __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
# include <bits/strings_fortified.h>

व्योम __explicit_bzero_chk (व्योम *__dest, माप_प्रकार __len, माप_प्रकार __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function व्योम
__NTH (explicit_bzero (व्योम *__dest, माप_प्रकार __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#पूर्ण_अगर

__fortify_function __attribute_overloadable__ अक्षर *
__NTH (म_नकल (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
	       स्थिर अक्षर *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  वापस __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#अगर_घोषित __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ अक्षर *
__NTH (stpcpy (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
	       स्थिर अक्षर *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  वापस __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#पूर्ण_अगर


__fortify_function __attribute_overloadable__ अक्षर *
__NTH (म_नकलन (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
		स्थिर अक्षर *__restrict __src, माप_प्रकार __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  वापस __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#अगर_घोषित __USE_XOPEN2K8
# अगर __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ अक्षर *
__NTH (stpncpy (__fortify_clang_overload_arg (अक्षर *, ,__dest),
		स्थिर अक्षर *__src, माप_प्रकार __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  वापस __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# अन्यथा
बाह्य अक्षर *__stpncpy_chk (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n,
			    माप_प्रकार __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
बाह्य अक्षर *__REDIRECT_NTH (__stpncpy_alias, (अक्षर *__dest, स्थिर अक्षर *__src,
					       माप_प्रकार __n), stpncpy);

__fortify_function __attribute_overloadable__ अक्षर *
__NTH (stpncpy (__fortify_clang_overload_arg (अक्षर *, ,__dest),
		स्थिर अक्षर *__src, माप_प्रकार __n))
{
  अगर (__bos (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    वापस __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  वापस __stpncpy_alias (__dest, __src, __n);
}
# endif
#पूर्ण_अगर


__fortify_function __attribute_overloadable__ अक्षर *
__NTH (म_जोड़ो (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
	       स्थिर अक्षर *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  वापस __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ अक्षर *
__NTH (म_जोड़न (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
		स्थिर अक्षर *__restrict __src, माप_प्रकार __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  वापस __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#अगर_घोषित __USE_MISC
बाह्य माप_प्रकार __strlcpy_chk (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n,
			     माप_प्रकार __destlen) __THROW;
बाह्य माप_प्रकार __REDIRECT_NTH (__strlcpy_alias,
			      (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ माप_प्रकार
__NTH (strlcpy (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
		स्थिर अक्षर *__restrict __src, माप_प्रकार __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  अगर (__glibc_objsize (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    वापस __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  वापस __strlcpy_alias (__dest, __src, __n);
}

बाह्य माप_प्रकार __strlcat_chk (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n,
			     माप_प्रकार __destlen) __THROW;
बाह्य माप_प्रकार __REDIRECT_NTH (__strlcat_alias,
			      (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n),
			      strlcat);

__fortify_function __attribute_overloadable__ माप_प्रकार
__NTH (strlcat (__fortify_clang_overload_arg (अक्षर *, __restrict, __dest),
		स्थिर अक्षर *__restrict __src, माप_प्रकार __n))
{
  अगर (__glibc_objsize (__dest) != (माप_प्रकार) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    वापस __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  वापस __strlcat_alias (__dest, __src, __n);
}
#पूर्ण_अगर /* __USE_MISC */

#पूर्ण_अगर /* bits/string_fortified.h */
