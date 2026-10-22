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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __NO_STRING_INLINES
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "shlib-compat.h"

#ਜੇ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

ਅੱਖਰ *
__old_strtok_r_1c (ਅੱਖਰ *__s, ਅੱਖਰ __sep, ਅੱਖਰ **__nextp)
{
  ਅੱਖਰ *__result;
  ਜੇ (__s == ਨਿਰਾ)
    __s = *__nextp;
  ਜਦੋਂ (*__s == __sep)
    ++__s;
  __result = ਨਿਰਾ;
  ਜੇ (*__s != '\0')
    {
      __result = __s++;
      ਜਦੋਂ (*__s != '\0')
	ਜੇ (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ਰੋਕੋ;
	  }
    }
  *__nextp = __s;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

ਅੱਖਰ *
__old_strsep_1c (ਅੱਖਰ **__s, ਅੱਖਰ __reject)
{
  ਅੱਖਰ *__retval = *__s;
  ਜੇ (__retval != ਨਿਰਾ && (*__s = strchr (__retval, __reject)) != ਨਿਰਾ)
    *(*__s)++ = '\0';
  ਵਾਪਸ __retval;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

ਅੱਖਰ *
__old_strsep_2c (ਅੱਖਰ **__s, ਅੱਖਰ __reject1, ਅੱਖਰ __reject2)
{
  ਅੱਖਰ *__retval = *__s;
  ਜੇ (__retval != ਨਿਰਾ)
    {
      ਅੱਖਰ *__cp = __retval;
      ਜਦੋਂ (1)
	{
	  ਜੇ (*__cp == '\0')
	    {
	      __cp = ਨਿਰਾ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ਰੋਕੋ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ਵਾਪਸ __retval;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

ਅੱਖਰ *
__old_strsep_3c (ਅੱਖਰ **__s, ਅੱਖਰ __reject1, ਅੱਖਰ __reject2, ਅੱਖਰ __reject3)
{
  ਅੱਖਰ *__retval = *__s;
  ਜੇ (__retval != ਨਿਰਾ)
    {
      ਅੱਖਰ *__cp = __retval;
      ਜਦੋਂ (1)
	{
	  ਜੇ (*__cp == '\0')
	    {
	      __cp = ਨਿਰਾ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ਰੋਕੋ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ਵਾਪਸ __retval;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#ਜੇ_ਅੰਤ

#ਜੇ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __reject)
{
  size_t __result = 0;
  ਜਦੋਂ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __reject1, ਪੂਰਨ __reject2)
{
  size_t __result = 0;
  ਜਦੋਂ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __reject1, ਪੂਰਨ __reject2,
	      ਪੂਰਨ __reject3)
{
  size_t __result = 0;
  ਜਦੋਂ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  ਜਦੋਂ (__s[__result] == __accept)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __accept1, ਪੂਰਨ __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ਜਦੋਂ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __accept1, ਪੂਰਨ __accept2,
		 ਪੂਰਨ __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ਜਦੋਂ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ਵਾਪਸ __result;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

ਅੱਖਰ *
__old_strpbrk_c2 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __accept1, ਪੂਰਨ __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ਜਦੋਂ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ਵਾਪਸ *__s == '\0' ? ਨਿਰਾ : (ਅੱਖਰ *) (size_t) __s;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

ਅੱਖਰ *
__old_strpbrk_c3 (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __accept1, ਪੂਰਨ __accept2, ਪੂਰਨ __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ਜਦੋਂ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ਵਾਪਸ *__s == '\0' ? ਨਿਰਾ : (ਅੱਖਰ *) (size_t) __s;
}
compat_ਚਿੰਨ੍ਹ (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# ਜੇ defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# ਨਹੀਂਤਾਂ
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ { ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ __arr[N]; }				      \
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

# ਜੇ _STRING_INLINE_unaligned
ਖਾਲੀ *
__old_mempcpy_small (ਖਾਲੀ *__dest1,
		     ਅੱਖਰ __src0_1, ਅੱਖਰ __src2_1, ਅੱਖਰ __src4_1, ਅੱਖਰ __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  ਸੰਘ {
    __uint32_t __ui;
    __uint16_t __usi;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ __uc;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ __c;
  } *__u = __dest1;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      ਰੋਕੋ;
    }
  ਵਾਪਸ (ਖਾਲੀ *) __u;
}

# ਨਹੀਂਤਾਂ

ਖਾਲੀ *
__old_mempcpy_small (ਖਾਲੀ *__dest, ਅੱਖਰ __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ਸੰਘ {
    ਅੱਖਰ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__c = __src1;
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __extension__ __u->__sca2 = __src2;
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __extension__ __u->__sca3 = __src3;
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __extension__ __u->__sca4 = __src4;
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __extension__ __u->__sca5 = __src5;
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __extension__ __u->__sca6 = __src6;
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __extension__ __u->__sca7 = __src7;
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __extension__ __u->__sca8 = __src8;
      ਰੋਕੋ;
    }
  ਵਾਪਸ __extension__ ((ਖਾਲੀ *) __u + __srclen);
}
# endif
compat_ਚਿੰਨ੍ਹ (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# ਜੇ _STRING_INLINE_unaligned
ਅੱਖਰ *
__old_strcpy_small (ਅੱਖਰ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ਸੰਘ {
    __uint32_t __ui;
    __uint16_t __usi;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ __uc;
  } *__u = (ਖਾਲੀ *) __dest;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __u->__usi = __src0_2;
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __u->__ui = __src0_4;
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__ui = __src4_4;
      ਰੋਕੋ;
    }
  ਵਾਪਸ __dest;
}

# ਨਹੀਂਤਾਂ

ਅੱਖਰ *
__old_strcpy_small (ਅੱਖਰ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ਸੰਘ {
    ਅੱਖਰ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ਖਾਲੀ *) __dest;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__c = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __extension__ __u->__sca2 = __src2;
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __extension__ __u->__sca3 = __src3;
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __extension__ __u->__sca4 = __src4;
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __extension__ __u->__sca5 = __src5;
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __extension__ __u->__sca6 = __src6;
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __extension__ __u->__sca7 = __src7;
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __extension__ __u->__sca8 = __src8;
      ਰੋਕੋ;
  }
  ਵਾਪਸ __dest;
}
# endif
compat_ਚਿੰਨ੍ਹ (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# ਜੇ _STRING_INLINE_unaligned
ਅੱਖਰ *
__old_stpcpy_small (ਅੱਖਰ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ਸੰਘ {
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ __ui;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਪੂਰਨ __usi;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ __uc;
    ਅੱਖਰ __c;
  } *__u = (ਖਾਲੀ *) __dest;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 3);
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 1);
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ਖਾਲੀ *) __u + 2);
      __u->__uc = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ਖਾਲੀ *) __u + 3);
      ਰੋਕੋ;
    }
  ਵਾਪਸ &__u->__c;
}

# ਨਹੀਂਤਾਂ

ਅੱਖਰ *
__old_stpcpy_small (ਅੱਖਰ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ਸੰਘ {
    ਅੱਖਰ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ਖਾਲੀ *) __dest;
  ਚੋਣ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) __srclen)
    {
    ਹਾਲਤ 1:
      __u->__c = '\0';
      ਰੋਕੋ;
    ਹਾਲਤ 2:
      __extension__ __u->__sca2 = __src2;
      ਰੋਕੋ;
    ਹਾਲਤ 3:
      __extension__ __u->__sca3 = __src3;
      ਰੋਕੋ;
    ਹਾਲਤ 4:
      __extension__ __u->__sca4 = __src4;
      ਰੋਕੋ;
    ਹਾਲਤ 5:
      __extension__ __u->__sca5 = __src5;
      ਰੋਕੋ;
    ਹਾਲਤ 6:
      __extension__ __u->__sca6 = __src6;
      ਰੋਕੋ;
    ਹਾਲਤ 7:
      __extension__ __u->__sca7 = __src7;
      ਰੋਕੋ;
    ਹਾਲਤ 8:
      __extension__ __u->__sca8 = __src8;
      ਰੋਕੋ;
  }
  ਵਾਪਸ __dest + __srclen - 1;
}
# endif
compat_ਚਿੰਨ੍ਹ (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#ਜੇ_ਅੰਤ
