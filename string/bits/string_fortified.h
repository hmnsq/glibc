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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _BITS_STRING_FORTIFIED_H
#ವ್ಯಾಖ್ಯಾನಿಸು _BITS_STRING_FORTIFIED_H 1

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _STRING_H
# error "Never use <bits/string_fortified.h> directly; include <string.h> instead."
#ಆದರೆ_ಅಂತ್ಯ

__fortify_function ಶೂನ್ಯ *
__NTH (ಸ್ಮರಣೆ_ನಕಲು (ಶೂನ್ಯ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src,
	       size_t __len))
{
  ಹಿಂತಿರುಗಿ __builtin___memcpy_chk (__dest, __src, __len,
				 __glibc_objsize0 (__dest));
}

__fortify_function ಶೂನ್ಯ *
__NTH (memmove (ಶೂನ್ಯ *__dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__src, size_t __len))
{
  ಹಿಂತಿರುಗಿ __builtin___memmove_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_GNU
__fortify_function ಶೂನ್ಯ *
__NTH (mempcpy (ಶೂನ್ಯ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src,
		size_t __len))
{
  ಹಿಂತಿರುಗಿ __builtin___mempcpy_chk (__dest, __src, __len,
				  __glibc_objsize0 (__dest));
}
#ಆದರೆ_ಅಂತ್ಯ


/* The first two tests here help to catch a somewhat common problem
   where the second and third parameter are transposed.  This is
   especially problematic if the intended fill value is zero.  In this
   case no work is done at all.  We detect these problems by referring
   non-existing functions.  */
__fortify_function ಶೂನ್ಯ *
__NTH (memset (ಶೂನ್ಯ *__dest, ಪೂರ್ಣಾಂಕ __ch, size_t __len))
{
  ಹಿಂತಿರುಗಿ __builtin___memset_chk (__dest, __ch, __len,
				 __glibc_objsize0 (__dest));
}

#ಆದರೆ defined __USE_MISC || __GLIBC_USE (ISOC23)
ಶೂನ್ಯ *__memset_explicit_chk (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n, size_t __destlen)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);

__fortify_function ಶೂನ್ಯ *
__NTH (memset_explicit (ಶೂನ್ಯ *__dest, ಪೂರ್ಣಾಂಕ __ch, size_t __len))
{
  ಹಿಂತಿರುಗಿ __memset_explicit_chk (__dest, __ch, __len,
				__glibc_objsize0 (__dest));
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
# include <bits/strings_fortified.h>

ಶೂನ್ಯ __explicit_bzero_chk (ಶೂನ್ಯ *__dest, size_t __len, size_t __destlen)
  __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 2);

__fortify_function ಶೂನ್ಯ
__NTH (explicit_bzero (ಶೂನ್ಯ *__dest, size_t __len))
{
  __explicit_bzero_chk (__dest, __len, __glibc_objsize0 (__dest));
}
#ಆದರೆ_ಅಂತ್ಯ

__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (strcpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
	       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಹಿಂತಿರುಗಿ __builtin___strcpy_chk (__dest, __src, __glibc_objsize (__dest));
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_XOPEN2K8
__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (stpcpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
	       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಹಿಂತಿರುಗಿ __builtin___stpcpy_chk (__dest, __src, __glibc_objsize (__dest));
}
#ಆದರೆ_ಅಂತ್ಯ


__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (strncpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __len))
     __fortify_clang_warn_if_dest_too_small (__dest, __len)
{
  ಹಿಂತಿರುಗಿ __builtin___strncpy_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_XOPEN2K8
# ಆದರೆ __GNUC_PREREQ (4, 7) || __glibc_clang_prereq (2, 6)
__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (stpncpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, ,__dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ಹಿಂತಿರುಗಿ __builtin___stpncpy_chk (__dest, __src, __n,
				  __glibc_objsize (__dest));
}
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *__stpncpy_chk (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n,
			    size_t __destlen) __THROW
  __fortified_attr_access (__write_only__, 1, 3)
  __attr_access ((__read_only__, 2));
ಬಾಹ್ಯ ಅಕ್ಷರ *__REDIRECT_NTH (__stpncpy_alias, (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src,
					       size_t __n), stpncpy);

__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (stpncpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, ,__dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n))
{
  ಆದರೆ (__bos (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n) || __n > __bos (__dest)))
    ಹಿಂತಿರುಗಿ __stpncpy_chk (__dest, __src, __n, __bos (__dest));
  ಹಿಂತಿರುಗಿ __stpncpy_alias (__dest, __src, __n);
}
# endif
#ಆದರೆ_ಅಂತ್ಯ


__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (strcat (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
	       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಹಿಂತಿರುಗಿ __builtin___strcat_chk (__dest, __src, __glibc_objsize (__dest));
}


__fortify_function __attribute_overloadable__ ಅಕ್ಷರ *
__NTH (strncat (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __len))
     __fortify_clang_warn_if_src_too_large (__dest, __src)
{
  ಹಿಂತಿರುಗಿ __builtin___strncat_chk (__dest, __src, __len,
				  __glibc_objsize (__dest));
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
ಬಾಹ್ಯ size_t __strlcpy_chk (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n,
			     size_t __destlen) __THROW;
ಬಾಹ್ಯ size_t __REDIRECT_NTH (__strlcpy_alias,
			      (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n),
			      strlcpy);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcpy (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n))
     __fortify_clang_warn_if_dest_too_small (__dest, __n)
{
  ಆದರೆ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ಹಿಂತಿರುಗಿ __strlcpy_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ಹಿಂತಿರುಗಿ __strlcpy_alias (__dest, __src, __n);
}

ಬಾಹ್ಯ size_t __strlcat_chk (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n,
			     size_t __destlen) __THROW;
ಬಾಹ್ಯ size_t __REDIRECT_NTH (__strlcat_alias,
			      (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n),
			      strlcat);

__fortify_function __attribute_overloadable__ size_t
__NTH (strlcat (__fortify_clang_overload_arg (ಅಕ್ಷರ *, __restrict, __dest),
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n))
{
  ಆದರೆ (__glibc_objsize (__dest) != (size_t) -1
      && (!__builtin_constant_p (__n > __glibc_objsize (__dest))
	  || __n > __glibc_objsize (__dest)))
    ಹಿಂತಿರುಗಿ __strlcat_chk (__dest, __src, __n, __glibc_objsize (__dest));
  ಹಿಂತಿರುಗಿ __strlcat_alias (__dest, __src, __n);
}
#ಆದರೆ_ಅಂತ್ಯ /* __USE_MISC */

#ಆದರೆ_ಅಂತ್ಯ /* bits/string_fortified.h */
