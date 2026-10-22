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

#define __NO_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "shlib-compat.h"

#ಯದಿ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

ವರ್ಣ *
__old_strtok_r_1c (ವರ್ಣ *__s, ವರ್ಣ __sep, ವರ್ಣ **__nextp)
{
  ವರ್ಣ *__result;
  ಯದಿ (__s == ರಿಕ್ತ)
    __s = *__nextp;
  ಯಾವತ್ (*__s == __sep)
    ++__s;
  __result = ರಿಕ್ತ;
  ಯದಿ (*__s != '\0')
    {
      __result = __s++;
      ಯಾವತ್ (*__s != '\0')
	ಯದಿ (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ಭಙ್ಗ;
	  }
    }
  *__nextp = __s;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

ವರ್ಣ *
__old_strsep_1c (ವರ್ಣ **__s, ವರ್ಣ __reject)
{
  ವರ್ಣ *__retval = *__s;
  ಯದಿ (__retval != ರಿಕ್ತ && (*__s = strchr (__retval, __reject)) != ರಿಕ್ತ)
    *(*__s)++ = '\0';
  ಪ್ರತ್ಯಾಗಮ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

ವರ್ಣ *
__old_strsep_2c (ವರ್ಣ **__s, ವರ್ಣ __reject1, ವರ್ಣ __reject2)
{
  ವರ್ಣ *__retval = *__s;
  ಯದಿ (__retval != ರಿಕ್ತ)
    {
      ವರ್ಣ *__cp = __retval;
      ಯಾವತ್ (1)
	{
	  ಯದಿ (*__cp == '\0')
	    {
	      __cp = ರಿಕ್ತ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ಭಙ್ಗ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ಪ್ರತ್ಯಾಗಮ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

ವರ್ಣ *
__old_strsep_3c (ವರ್ಣ **__s, ವರ್ಣ __reject1, ವರ್ಣ __reject2, ವರ್ಣ __reject3)
{
  ವರ್ಣ *__retval = *__s;
  ಯದಿ (__retval != ರಿಕ್ತ)
    {
      ವರ್ಣ *__cp = __retval;
      ಯಾವತ್ (1)
	{
	  ಯದಿ (*__cp == '\0')
	    {
	      __cp = ರಿಕ್ತ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ಭಙ್ಗ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ಪ್ರತ್ಯಾಗಮ __retval;
}
compat_ಚಿಹ್ನೆ (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#ಯದಿ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __reject)
{
  size_t __result = 0;
  ಯಾವತ್ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __reject1, ಪೂರ್ಣಾಙ್ಕ __reject2)
{
  size_t __result = 0;
  ಯಾವತ್ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __reject1, ಪೂರ್ಣಾಙ್ಕ __reject2,
	      ಪೂರ್ಣಾಙ್ಕ __reject3)
{
  size_t __result = 0;
  ಯಾವತ್ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  ಯಾವತ್ (__s[__result] == __accept)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __accept1, ಪೂರ್ಣಾಙ್ಕ __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ಯಾವತ್ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __accept1, ಪೂರ್ಣಾಙ್ಕ __accept2,
		 ಪೂರ್ಣಾಙ್ಕ __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ಯಾವತ್ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ಪ್ರತ್ಯಾಗಮ __result;
}
compat_ಚಿಹ್ನೆ (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

ವರ್ಣ *
__old_strpbrk_c2 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __accept1, ಪೂರ್ಣಾಙ್ಕ __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ಯಾವತ್ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ಪ್ರತ್ಯಾಗಮ *__s == '\0' ? ರಿಕ್ತ : (ವರ್ಣ *) (size_t) __s;
}
compat_ಚಿಹ್ನೆ (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

ವರ್ಣ *
__old_strpbrk_c3 (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __accept1, ಪೂರ್ಣಾಙ್ಕ __accept2, ಪೂರ್ಣಾಙ್ಕ __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ಯಾವತ್ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ಪ್ರತ್ಯಾಗಮ *__s == '\0' ? ರಿಕ್ತ : (ವರ್ಣ *) (size_t) __s;
}
compat_ಚಿಹ್ನೆ (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# ಯದಿ defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# ಅನ್ಯಥಾ
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ { unsigned ವರ್ಣ __arr[N]; }				      \
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

# ಯದಿ _STRING_INLINE_unaligned
ಶೂನ್ಯ *
__old_mempcpy_small (ಶೂನ್ಯ *__dest1,
		     ವರ್ಣ __src0_1, ವರ್ಣ __src2_1, ವರ್ಣ __src4_1, ವರ್ಣ __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  ಸಙ್ಘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ವರ್ಣ __uc;
    unsigned ವರ್ಣ __c;
  } *__u = __dest1;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ (ಶೂನ್ಯ *) __u;
}

# ಅನ್ಯಥಾ

ಶೂನ್ಯ *
__old_mempcpy_small (ಶೂನ್ಯ *__dest, ವರ್ಣ __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಸಙ್ಘ {
    ವರ್ಣ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__c = __src1;
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __extension__ __u->__sca2 = __src2;
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __extension__ __u->__sca3 = __src3;
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __extension__ __u->__sca4 = __src4;
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __extension__ __u->__sca5 = __src5;
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __extension__ __u->__sca6 = __src6;
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __extension__ __u->__sca7 = __src7;
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __extension__ __u->__sca8 = __src8;
      ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ __extension__ ((ಶೂನ್ಯ *) __u + __srclen);
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# ಯದಿ _STRING_INLINE_unaligned
ವರ್ಣ *
__old_strcpy_small (ವರ್ಣ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ಸಙ್ಘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ವರ್ಣ __uc;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __u->__usi = __src0_2;
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __u->__ui = __src0_4;
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ __dest;
}

# ಅನ್ಯಥಾ

ವರ್ಣ *
__old_strcpy_small (ವರ್ಣ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಸಙ್ಘ {
    ವರ್ಣ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__c = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __extension__ __u->__sca2 = __src2;
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __extension__ __u->__sca3 = __src3;
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __extension__ __u->__sca4 = __src4;
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __extension__ __u->__sca5 = __src5;
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __extension__ __u->__sca6 = __src6;
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __extension__ __u->__sca7 = __src7;
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __extension__ __u->__sca8 = __src8;
      ಭಙ್ಗ;
  }
  ಪ್ರತ್ಯಾಗಮ __dest;
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# ಯದಿ _STRING_INLINE_unaligned
ವರ್ಣ *
__old_stpcpy_small (ವರ್ಣ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ಸಙ್ಘ {
    unsigned ಪೂರ್ಣಾಙ್ಕ __ui;
    unsigned short ಪೂರ್ಣಾಙ್ಕ __usi;
    unsigned ವರ್ಣ __uc;
    ವರ್ಣ __c;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 3);
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 1);
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 2);
      __u->__uc = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ಶೂನ್ಯ *) __u + 3);
      ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ &__u->__c;
}

# ಅನ್ಯಥಾ

ವರ್ಣ *
__old_stpcpy_small (ವರ್ಣ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ಸಙ್ಘ {
    ವರ್ಣ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ಶೂನ್ಯ *) __dest;
  ವಿಕಲ್ಪ ((unsigned ಪೂರ್ಣಾಙ್ಕ) __srclen)
    {
    ಪಕ್ಷ 1:
      __u->__c = '\0';
      ಭಙ್ಗ;
    ಪಕ್ಷ 2:
      __extension__ __u->__sca2 = __src2;
      ಭಙ್ಗ;
    ಪಕ್ಷ 3:
      __extension__ __u->__sca3 = __src3;
      ಭಙ್ಗ;
    ಪಕ್ಷ 4:
      __extension__ __u->__sca4 = __src4;
      ಭಙ್ಗ;
    ಪಕ್ಷ 5:
      __extension__ __u->__sca5 = __src5;
      ಭಙ್ಗ;
    ಪಕ್ಷ 6:
      __extension__ __u->__sca6 = __src6;
      ಭಙ್ಗ;
    ಪಕ್ಷ 7:
      __extension__ __u->__sca7 = __src7;
      ಭಙ್ಗ;
    ಪಕ್ಷ 8:
      __extension__ __u->__sca8 = __src8;
      ಭಙ್ಗ;
  }
  ಪ್ರತ್ಯಾಗಮ __dest + __srclen - 1;
}
# endif
compat_ಚಿಹ್ನೆ (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
