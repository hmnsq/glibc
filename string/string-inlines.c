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
#شامل <string.h>

#شامل "shlib-compat.h"

#اگر SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

نویسه *
__old_strtok_r_1c (نویسه *__s, نویسه __sep, نویسه **__nextp)
{
  نویسه *__result;
  اگر (__s == پوچ)
    __s = *__nextp;
  وقتی (*__s == __sep)
    ++__s;
  __result = پوچ;
  اگر (*__s != '\0')
    {
      __result = __s++;
      وقتی (*__s != '\0')
	اگر (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    بشکن;
	  }
    }
  *__nextp = __s;
  بازگشت __result;
}
compat_نماد (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

نویسه *
__old_strsep_1c (نویسه **__s, نویسه __reject)
{
  نویسه *__retval = *__s;
  اگر (__retval != پوچ && (*__s = strchr (__retval, __reject)) != پوچ)
    *(*__s)++ = '\0';
  بازگشت __retval;
}
compat_نماد (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

نویسه *
__old_strsep_2c (نویسه **__s, نویسه __reject1, نویسه __reject2)
{
  نویسه *__retval = *__s;
  اگر (__retval != پوچ)
    {
      نویسه *__cp = __retval;
      وقتی (1)
	{
	  اگر (*__cp == '\0')
	    {
	      __cp = پوچ;
	      بشکن;
	    }
	  اگر (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      بشکن;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  بازگشت __retval;
}
compat_نماد (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

نویسه *
__old_strsep_3c (نویسه **__s, نویسه __reject1, نویسه __reject2, نویسه __reject3)
{
  نویسه *__retval = *__s;
  اگر (__retval != پوچ)
    {
      نویسه *__cp = __retval;
      وقتی (1)
	{
	  اگر (*__cp == '\0')
	    {
	      __cp = پوچ;
	      بشکن;
	    }
	  اگر (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      بشکن;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  بازگشت __retval;
}
compat_نماد (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#اگر SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ثابت نویسه *__s, صحیح __reject)
{
  size_t __result = 0;
  وقتی (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ثابت نویسه *__s, صحیح __reject1, صحیح __reject2)
{
  size_t __result = 0;
  وقتی (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ثابت نویسه *__s, صحیح __reject1, صحیح __reject2,
	      صحیح __reject3)
{
  size_t __result = 0;
  وقتی (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ثابت نویسه *__s, صحیح __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  وقتی (__s[__result] == __accept)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ثابت نویسه *__s, صحیح __accept1, صحیح __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  وقتی (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ثابت نویسه *__s, صحیح __accept1, صحیح __accept2,
		 صحیح __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  وقتی (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  بازگشت __result;
}
compat_نماد (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

نویسه *
__old_strpbrk_c2 (ثابت نویسه *__s, صحیح __accept1, صحیح __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  وقتی (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  بازگشت *__s == '\0' ? پوچ : (نویسه *) (size_t) __s;
}
compat_نماد (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

نویسه *
__old_strpbrk_c3 (ثابت نویسه *__s, صحیح __accept1, صحیح __accept2, صحیح __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  وقتی (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  بازگشت *__s == '\0' ? پوچ : (نویسه *) (size_t) __s;
}
compat_نماد (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# اگر defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# وگرنه
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  تعریفنوع ساختار { unsigned نویسه __arr[N]; }				      \
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

# اگر _STRING_INLINE_unaligned
تهی *
__old_mempcpy_small (تهی *__dest1,
		     نویسه __src0_1, نویسه __src2_1, نویسه __src4_1, نویسه __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  اجتماع {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned نویسه __uc;
    unsigned نویسه __c;
  } *__u = __dest1;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__c = __src0_1;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((تهی *) __u + 2);
      بشکن;
    حالت 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      بشکن;
    حالت 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((تهی *) __u + 2);
      بشکن;
    حالت 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((تهی *) __u + 4);
      بشکن;
    }
  بازگشت (تهی *) __u;
}

# وگرنه

تهی *
__old_mempcpy_small (تهی *__dest, نویسه __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اجتماع {
    نویسه __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__c = __src1;
      بشکن;
    حالت 2:
      __extension__ __u->__sca2 = __src2;
      بشکن;
    حالت 3:
      __extension__ __u->__sca3 = __src3;
      بشکن;
    حالت 4:
      __extension__ __u->__sca4 = __src4;
      بشکن;
    حالت 5:
      __extension__ __u->__sca5 = __src5;
      بشکن;
    حالت 6:
      __extension__ __u->__sca6 = __src6;
      بشکن;
    حالت 7:
      __extension__ __u->__sca7 = __src7;
      بشکن;
    حالت 8:
      __extension__ __u->__sca8 = __src8;
      بشکن;
    }
  بازگشت __extension__ ((تهی *) __u + __srclen);
}
# endif
compat_نماد (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# اگر _STRING_INLINE_unaligned
نویسه *
__old_strcpy_small (نویسه *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  اجتماع {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned نویسه __uc;
  } *__u = (تهی *) __dest;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__uc = '\0';
      بشکن;
    حالت 2:
      __u->__usi = __src0_2;
      بشکن;
    حالت 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__uc = '\0';
      بشکن;
    حالت 4:
      __u->__ui = __src0_4;
      بشکن;
    حالت 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__uc = '\0';
      بشکن;
    حالت 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      بشکن;
    حالت 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__uc = '\0';
      بشکن;
    حالت 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__ui = __src4_4;
      بشکن;
    }
  بازگشت __dest;
}

# وگرنه

نویسه *
__old_strcpy_small (نویسه *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اجتماع {
    نویسه __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (تهی *) __dest;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__c = '\0';
      بشکن;
    حالت 2:
      __extension__ __u->__sca2 = __src2;
      بشکن;
    حالت 3:
      __extension__ __u->__sca3 = __src3;
      بشکن;
    حالت 4:
      __extension__ __u->__sca4 = __src4;
      بشکن;
    حالت 5:
      __extension__ __u->__sca5 = __src5;
      بشکن;
    حالت 6:
      __extension__ __u->__sca6 = __src6;
      بشکن;
    حالت 7:
      __extension__ __u->__sca7 = __src7;
      بشکن;
    حالت 8:
      __extension__ __u->__sca8 = __src8;
      بشکن;
  }
  بازگشت __dest;
}
# endif
compat_نماد (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# اگر _STRING_INLINE_unaligned
نویسه *
__old_stpcpy_small (نویسه *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  اجتماع {
    unsigned صحیح __ui;
    unsigned short صحیح __usi;
    unsigned نویسه __uc;
    نویسه __c;
  } *__u = (تهی *) __dest;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__uc = '\0';
      بشکن;
    حالت 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__uc = '\0';
      بشکن;
    حالت 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 3);
      بشکن;
    حالت 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__uc = '\0';
      بشکن;
    حالت 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((تهی *) __u + 1);
      بشکن;
    حالت 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((تهی *) __u + 2);
      __u->__uc = '\0';
      بشکن;
    حالت 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((تهی *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((تهی *) __u + 3);
      بشکن;
    }
  بازگشت &__u->__c;
}

# وگرنه

نویسه *
__old_stpcpy_small (نویسه *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  اجتماع {
    نویسه __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (تهی *) __dest;
  انتخاب ((unsigned صحیح) __srclen)
    {
    حالت 1:
      __u->__c = '\0';
      بشکن;
    حالت 2:
      __extension__ __u->__sca2 = __src2;
      بشکن;
    حالت 3:
      __extension__ __u->__sca3 = __src3;
      بشکن;
    حالت 4:
      __extension__ __u->__sca4 = __src4;
      بشکن;
    حالت 5:
      __extension__ __u->__sca5 = __src5;
      بشکن;
    حالت 6:
      __extension__ __u->__sca6 = __src6;
      بشکن;
    حالت 7:
      __extension__ __u->__sca7 = __src7;
      بشکن;
    حالت 8:
      __extension__ __u->__sca8 = __src8;
      بشکن;
  }
  بازگشت __dest + __srclen - 1;
}
# endif
compat_نماد (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
