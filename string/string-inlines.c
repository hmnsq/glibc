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

#تعریف_کن __NO_STRING_INLINES
#ضمن <string.h>

#ضمن "shlib-compat.h"

#إذا SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

حرف *
__old_strtok_r_1c (حرف *__s, حرف __sep, حرف **__nextp)
{
  حرف *__result;
  إذا (__s == عدم)
    __s = *__nextp;
  طالما (*__s == __sep)
    ++__s;
  __result = عدم;
  إذا (*__s != '\0')
    {
      __result = __s++;
      طالما (*__s != '\0')
	إذا (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    اكسر;
	  }
    }
  *__nextp = __s;
  أرجع __result;
}
compat_نماد (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

حرف *
__old_strsep_1c (حرف **__s, حرف __reject)
{
  حرف *__retval = *__s;
  إذا (__retval != عدم && (*__s = strchr (__retval, __reject)) != عدم)
    *(*__s)++ = '\0';
  أرجع __retval;
}
compat_نماد (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

حرف *
__old_strsep_2c (حرف **__s, حرف __reject1, حرف __reject2)
{
  حرف *__retval = *__s;
  إذا (__retval != عدم)
    {
      حرف *__cp = __retval;
      طالما (1)
	{
	  إذا (*__cp == '\0')
	    {
	      __cp = عدم;
	      اكسر;
	    }
	  إذا (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      اكسر;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  أرجع __retval;
}
compat_نماد (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

حرف *
__old_strsep_3c (حرف **__s, حرف __reject1, حرف __reject2, حرف __reject3)
{
  حرف *__retval = *__s;
  إذا (__retval != عدم)
    {
      حرف *__cp = __retval;
      طالما (1)
	{
	  إذا (*__cp == '\0')
	    {
	      __cp = عدم;
	      اكسر;
	    }
	  إذا (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      اكسر;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  أرجع __retval;
}
compat_نماد (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#پایان_اگر

#إذا SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ثابت حرف *__s, صحيح __reject)
{
  size_t __result = 0;
  طالما (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ثابت حرف *__s, صحيح __reject1, صحيح __reject2)
{
  size_t __result = 0;
  طالما (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ثابت حرف *__s, صحيح __reject1, صحيح __reject2,
	      صحيح __reject3)
{
  size_t __result = 0;
  طالما (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ثابت حرف *__s, صحيح __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  طالما (__s[__result] == __accept)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ثابت حرف *__s, صحيح __accept1, صحيح __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  طالما (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ثابت حرف *__s, صحيح __accept1, صحيح __accept2,
		 صحيح __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  طالما (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  أرجع __result;
}
compat_نماد (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

حرف *
__old_strpbrk_c2 (ثابت حرف *__s, صحيح __accept1, صحيح __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  طالما (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  أرجع *__s == '\0' ? عدم : (حرف *) (size_t) __s;
}
compat_نماد (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

حرف *
__old_strpbrk_c3 (ثابت حرف *__s, صحيح __accept1, صحيح __accept2, صحيح __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  طالما (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  أرجع *__s == '\0' ? عدم : (حرف *) (size_t) __s;
}
compat_نماد (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# إذا defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# وإلا
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  تعريفنوع بنية { بیعلامت حرف __arr[N]; }				      \
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

# إذا _STRING_INLINE_unaligned
فراغ *
__old_mempcpy_small (فراغ *__dest1,
		     حرف __src0_1, حرف __src2_1, حرف __src4_1, حرف __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  اتحاد {
    __uint32_t __ui;
    __uint16_t __usi;
    بیعلامت حرف __uc;
    بیعلامت حرف __c;
  } *__u = __dest1;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__c = __src0_1;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((فراغ *) __u + 2);
      اكسر;
    حالة 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      اكسر;
    حالة 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((فراغ *) __u + 2);
      اكسر;
    حالة 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((فراغ *) __u + 4);
      اكسر;
    }
  أرجع (فراغ *) __u;
}

# وإلا

فراغ *
__old_mempcpy_small (فراغ *__dest, حرف __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اتحاد {
    حرف __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__c = __src1;
      اكسر;
    حالة 2:
      __extension__ __u->__sca2 = __src2;
      اكسر;
    حالة 3:
      __extension__ __u->__sca3 = __src3;
      اكسر;
    حالة 4:
      __extension__ __u->__sca4 = __src4;
      اكسر;
    حالة 5:
      __extension__ __u->__sca5 = __src5;
      اكسر;
    حالة 6:
      __extension__ __u->__sca6 = __src6;
      اكسر;
    حالة 7:
      __extension__ __u->__sca7 = __src7;
      اكسر;
    حالة 8:
      __extension__ __u->__sca8 = __src8;
      اكسر;
    }
  أرجع __extension__ ((فراغ *) __u + __srclen);
}
# endif
compat_نماد (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# إذا _STRING_INLINE_unaligned
حرف *
__old_strcpy_small (حرف *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  اتحاد {
    __uint32_t __ui;
    __uint16_t __usi;
    بیعلامت حرف __uc;
  } *__u = (فراغ *) __dest;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__uc = '\0';
      اكسر;
    حالة 2:
      __u->__usi = __src0_2;
      اكسر;
    حالة 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__uc = '\0';
      اكسر;
    حالة 4:
      __u->__ui = __src0_4;
      اكسر;
    حالة 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__uc = '\0';
      اكسر;
    حالة 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      اكسر;
    حالة 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__uc = '\0';
      اكسر;
    حالة 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__ui = __src4_4;
      اكسر;
    }
  أرجع __dest;
}

# وإلا

حرف *
__old_strcpy_small (حرف *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اتحاد {
    حرف __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (فراغ *) __dest;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__c = '\0';
      اكسر;
    حالة 2:
      __extension__ __u->__sca2 = __src2;
      اكسر;
    حالة 3:
      __extension__ __u->__sca3 = __src3;
      اكسر;
    حالة 4:
      __extension__ __u->__sca4 = __src4;
      اكسر;
    حالة 5:
      __extension__ __u->__sca5 = __src5;
      اكسر;
    حالة 6:
      __extension__ __u->__sca6 = __src6;
      اكسر;
    حالة 7:
      __extension__ __u->__sca7 = __src7;
      اكسر;
    حالة 8:
      __extension__ __u->__sca8 = __src8;
      اكسر;
  }
  أرجع __dest;
}
# endif
compat_نماد (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# إذا _STRING_INLINE_unaligned
حرف *
__old_stpcpy_small (حرف *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  اتحاد {
    بیعلامت صحيح __ui;
    بیعلامت کوتاه صحيح __usi;
    بیعلامت حرف __uc;
    حرف __c;
  } *__u = (فراغ *) __dest;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__uc = '\0';
      اكسر;
    حالة 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__uc = '\0';
      اكسر;
    حالة 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 3);
      اكسر;
    حالة 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__uc = '\0';
      اكسر;
    حالة 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((فراغ *) __u + 1);
      اكسر;
    حالة 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((فراغ *) __u + 2);
      __u->__uc = '\0';
      اكسر;
    حالة 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((فراغ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((فراغ *) __u + 3);
      اكسر;
    }
  أرجع &__u->__c;
}

# وإلا

حرف *
__old_stpcpy_small (حرف *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اتحاد {
    حرف __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (فراغ *) __dest;
  بدل ((بیعلامت صحيح) __srclen)
    {
    حالة 1:
      __u->__c = '\0';
      اكسر;
    حالة 2:
      __extension__ __u->__sca2 = __src2;
      اكسر;
    حالة 3:
      __extension__ __u->__sca3 = __src3;
      اكسر;
    حالة 4:
      __extension__ __u->__sca4 = __src4;
      اكسر;
    حالة 5:
      __extension__ __u->__sca5 = __src5;
      اكسر;
    حالة 6:
      __extension__ __u->__sca6 = __src6;
      اكسر;
    حالة 7:
      __extension__ __u->__sca7 = __src7;
      اكسر;
    حالة 8:
      __extension__ __u->__sca8 = __src8;
      اكسر;
  }
  أرجع __dest + __srclen - 1;
}
# endif
compat_نماد (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#پایان_اگر
