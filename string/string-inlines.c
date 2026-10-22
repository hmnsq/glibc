/* Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

/* This file contains compatibility definitions of functions that were
   formerly defined as "extern inline" in string.h; it's conceivable
   that old binaries contain references to them.  */

#ವ್ಯಾಖ್ಯಾನಿಸು __NO_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "shlib-compat.h"

#ಆದರೆ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

ಅಕ್ಷರ *
__old_strtok_r_1c (ಅಕ್ಷರ *__s, ಅಕ್ಷರ __sep, ಅಕ್ಷರ **__nextp)
{
  ಅಕ್ಷರ *__result;
  ಆದರೆ (__s == ಖಾಲಿ)
    __s = *__nextp;
  ಆಗ (*__s == __sep)
    ++__s;
  __result = ಖಾಲಿ;
  ಆದರೆ (*__s != '\0')
    {
      __result = __s++;
      ಆಗ (*__s != '\0')
	ಆದರೆ (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ನಿಲ್ಲಿಸು;
	  }
    }
  *__nextp = __s;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

ಅಕ್ಷರ *
__old_strsep_1c (ಅಕ್ಷರ **__s, ಅಕ್ಷರ __reject)
{
  ಅಕ್ಷರ *__retval = *__s;
  ಆದರೆ (__retval != ಖಾಲಿ && (*__s = strchr (__retval, __reject)) != ಖಾಲಿ)
    *(*__s)++ = '\0';
  ಹಿಂತಿರುಗಿ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

ಅಕ್ಷರ *
__old_strsep_2c (ಅಕ್ಷರ **__s, ಅಕ್ಷರ __reject1, ಅಕ್ಷರ __reject2)
{
  ಅಕ್ಷರ *__retval = *__s;
  ಆದರೆ (__retval != ಖಾಲಿ)
    {
      ಅಕ್ಷರ *__cp = __retval;
      ಆಗ (1)
	{
	  ಆದರೆ (*__cp == '\0')
	    {
	      __cp = ಖಾಲಿ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ನಿಲ್ಲಿಸು;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ಹಿಂತಿರುಗಿ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

ಅಕ್ಷರ *
__old_strsep_3c (ಅಕ್ಷರ **__s, ಅಕ್ಷರ __reject1, ಅಕ್ಷರ __reject2, ಅಕ್ಷರ __reject3)
{
  ಅಕ್ಷರ *__retval = *__s;
  ಆದರೆ (__retval != ಖಾಲಿ)
    {
      ಅಕ್ಷರ *__cp = __retval;
      ಆಗ (1)
	{
	  ಆದರೆ (*__cp == '\0')
	    {
	      __cp = ಖಾಲಿ;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ನಿಲ್ಲಿಸು;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ಹಿಂತಿರುಗಿ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __reject)
{
  size_t __result = 0;
  ಆಗ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __reject1, ಪೂರ್ಣಾಂಕ __reject2)
{
  size_t __result = 0;
  ಆಗ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __reject1, ಪೂರ್ಣಾಂಕ __reject2,
	      ಪೂರ್ಣಾಂಕ __reject3)
{
  size_t __result = 0;
  ಆಗ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  ಆಗ (__s[__result] == __accept)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __accept1, ಪೂರ್ಣಾಂಕ __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ಆಗ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __accept1, ಪೂರ್ಣಾಂಕ __accept2,
		 ಪೂರ್ಣಾಂಕ __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ಆಗ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ಹಿಂತಿರುಗಿ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

ಅಕ್ಷರ *
__old_strpbrk_c2 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __accept1, ಪೂರ್ಣಾಂಕ __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ಆಗ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ಹಿಂತಿರುಗಿ *__s == '\0' ? ಖಾಲಿ : (ಅಕ್ಷರ *) (size_t) __s;
}
compat_ಚಿಹ್ನೆ (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

ಅಕ್ಷರ *
__old_strpbrk_c3 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __accept1, ಪೂರ್ಣಾಂಕ __accept2, ಪೂರ್ಣಾಂಕ __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ಆಗ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ಹಿಂತಿರುಗಿ *__s == '\0' ? ಖಾಲಿ : (ಅಕ್ಷರ *) (size_t) __s;
}
compat_ಚಿಹ್ನೆ (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# ಆದರೆ defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# ಇಲ್ಲದಿದ್ದರೆ
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ { ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ __arr[N]; }				      \
    __attribute__ ((__packed__)) __STRING2_COPY_ARR##N
__STRING2_COPY_TYPE (2);
__STRING2_COPY_TYPE (3);
__STRING2_COPY_TYPE (4);
__STRING2_COPY_TYPE (5);
__STRING2_COPY_TYPE (6);
__STRING2_COPY_TYPE (7);
__STRING2_COPY_TYPE (8);
#  undef __STRING2_COPY_TYPE
# endif

# ಆದರೆ _STRING_INLINE_unaligned
ಶೂನ್ಯ *
__old_mempcpy_small (ಶೂನ್ಯ *__dest1,
		     ಅಕ್ಷರ __src0_1, ಅಕ್ಷರ __src2_1, ಅಕ್ಷರ __src4_1, ಅಕ್ಷರ __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    __uint32_t __ui;
    __uint16_t __usi;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ __uc;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ __c;
  } *__u = __dest1;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ (ಶೂನ್ಯ *) __u;
}

# ಇಲ್ಲದಿದ್ದರೆ

ಶೂನ್ಯ *
__old_mempcpy_small (ಶೂನ್ಯ *__dest, ಅಕ್ಷರ __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    ಅಕ್ಷರ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__c = __src1;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __extension__ __u->__sca2 = __src2;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __extension__ __u->__sca3 = __src3;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __extension__ __u->__sca4 = __src4;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __extension__ __u->__sca5 = __src5;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __extension__ __u->__sca6 = __src6;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __extension__ __u->__sca7 = __src7;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __extension__ __u->__sca8 = __src8;
      ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ __extension__ ((ಶೂನ್ಯ *) __u + __srclen);
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# ಆದರೆ _STRING_INLINE_unaligned
ಅಕ್ಷರ *
__old_strcpy_small (ಅಕ್ಷರ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    __uint32_t __ui;
    __uint16_t __usi;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ __uc;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __u->__usi = __src0_2;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __u->__ui = __src0_4;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ __dest;
}

# ಇಲ್ಲದಿದ್ದರೆ

ಅಕ್ಷರ *
__old_strcpy_small (ಅಕ್ಷರ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    ಅಕ್ಷರ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__c = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __extension__ __u->__sca2 = __src2;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __extension__ __u->__sca3 = __src3;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __extension__ __u->__sca4 = __src4;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __extension__ __u->__sca5 = __src5;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __extension__ __u->__sca6 = __src6;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __extension__ __u->__sca7 = __src7;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __extension__ __u->__sca8 = __src8;
      ನಿಲ್ಲಿಸು;
  }
  ಹಿಂತಿರುಗಿ __dest;
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# ಆದರೆ _STRING_INLINE_unaligned
ಅಕ್ಷರ *
__old_stpcpy_small (ಅಕ್ಷರ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ __ui;
    ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ಪೂರ್ಣಾಂಕ __usi;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ __uc;
    ಅಕ್ಷರ __c;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 3);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 3);
      ನಿಲ್ಲಿಸು;
    }
  ಹಿಂತಿರುಗಿ &__u->__c;
}

# ಇಲ್ಲದಿದ್ದರೆ

ಅಕ್ಷರ *
__old_stpcpy_small (ಅಕ್ಷರ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಒಕ್ಕೂಟ {
    ಅಕ್ಷರ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ಆಯ್ಕೆ ((ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) __srclen)
    {
    ಸ್ಥಿತಿ 1:
      __u->__c = '\0';
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
      __extension__ __u->__sca2 = __src2;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
      __extension__ __u->__sca3 = __src3;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
      __extension__ __u->__sca4 = __src4;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
      __extension__ __u->__sca5 = __src5;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
      __extension__ __u->__sca6 = __src6;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
      __extension__ __u->__sca7 = __src7;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
      __extension__ __u->__sca8 = __src8;
      ನಿಲ್ಲಿಸು;
  }
  ಹಿಂತಿರುಗಿ __dest + __srclen - 1;
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#ಆದರೆ_ಅಂತ್ಯ
