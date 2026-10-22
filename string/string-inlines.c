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
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "shlib-compat.h"

#যদি SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

অক্ষর *
__old_strtok_r_1c (অক্ষর *__s, অক্ষর __sep, অক্ষর **__nextp)
{
  অক্ষর *__result;
  যদি (__s == ফাঁকা)
    __s = *__nextp;
  যখন (*__s == __sep)
    ++__s;
  __result = ফাঁকা;
  যদি (*__s != '\0')
    {
      __result = __s++;
      যখন (*__s != '\0')
	যদি (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    বিরতি;
	  }
    }
  *__nextp = __s;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

অক্ষর *
__old_strsep_1c (অক্ষর **__s, অক্ষর __reject)
{
  অক্ষর *__retval = *__s;
  যদি (__retval != ফাঁকা && (*__s = strchr (__retval, __reject)) != ফাঁকা)
    *(*__s)++ = '\0';
  ফেরত __retval;
}
compat_প্রতীক (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

অক্ষর *
__old_strsep_2c (অক্ষর **__s, অক্ষর __reject1, অক্ষর __reject2)
{
  অক্ষর *__retval = *__s;
  যদি (__retval != ফাঁকা)
    {
      অক্ষর *__cp = __retval;
      যখন (1)
	{
	  যদি (*__cp == '\0')
	    {
	      __cp = ফাঁকা;
	      বিরতি;
	    }
	  যদি (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      বিরতি;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ফেরত __retval;
}
compat_প্রতীক (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

অক্ষর *
__old_strsep_3c (অক্ষর **__s, অক্ষর __reject1, অক্ষর __reject2, অক্ষর __reject3)
{
  অক্ষর *__retval = *__s;
  যদি (__retval != ফাঁকা)
    {
      অক্ষর *__cp = __retval;
      যখন (1)
	{
	  যদি (*__cp == '\0')
	    {
	      __cp = ফাঁকা;
	      বিরতি;
	    }
	  যদি (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      বিরতি;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ফেরত __retval;
}
compat_প্রতীক (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#যদি SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __reject)
{
  size_t __result = 0;
  যখন (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __reject1, পূর্ণসংখ্যা __reject2)
{
  size_t __result = 0;
  যখন (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __reject1, পূর্ণসংখ্যা __reject2,
	      পূর্ণসংখ্যা __reject3)
{
  size_t __result = 0;
  যখন (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  যখন (__s[__result] == __accept)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __accept1, পূর্ণসংখ্যা __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  যখন (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __accept1, পূর্ণসংখ্যা __accept2,
		 পূর্ণসংখ্যা __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  যখন (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ফেরত __result;
}
compat_প্রতীক (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

অক্ষর *
__old_strpbrk_c2 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __accept1, পূর্ণসংখ্যা __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  যখন (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ফেরত *__s == '\0' ? ফাঁকা : (অক্ষর *) (size_t) __s;
}
compat_প্রতীক (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

অক্ষর *
__old_strpbrk_c3 (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __accept1, পূর্ণসংখ্যা __accept2, পূর্ণসংখ্যা __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  যখন (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ফেরত *__s == '\0' ? ফাঁকা : (অক্ষর *) (size_t) __s;
}
compat_প্রতীক (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# যদি defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# অন্যথা
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  প্রকারলেখ কাঠামো { unsigned অক্ষর __arr[N]; }				      \
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

# যদি _STRING_INLINE_unaligned
শূন্য *
__old_mempcpy_small (শূন্য *__dest1,
		     অক্ষর __src0_1, অক্ষর __src2_1, অক্ষর __src4_1, অক্ষর __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  সংঘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned অক্ষর __uc;
    unsigned অক্ষর __c;
  } *__u = __dest1;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__c = __src0_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      বিরতি;
    ক্ষেত্র 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      বিরতি;
    ক্ষেত্র 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      বিরতি;
    ক্ষেত্র 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      বিরতি;
    }
  ফেরত (শূন্য *) __u;
}

# অন্যথা

শূন্য *
__old_mempcpy_small (শূন্য *__dest, অক্ষর __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সংঘ {
    অক্ষর __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__c = __src1;
      বিরতি;
    ক্ষেত্র 2:
      __extension__ __u->__sca2 = __src2;
      বিরতি;
    ক্ষেত্র 3:
      __extension__ __u->__sca3 = __src3;
      বিরতি;
    ক্ষেত্র 4:
      __extension__ __u->__sca4 = __src4;
      বিরতি;
    ক্ষেত্র 5:
      __extension__ __u->__sca5 = __src5;
      বিরতি;
    ক্ষেত্র 6:
      __extension__ __u->__sca6 = __src6;
      বিরতি;
    ক্ষেত্র 7:
      __extension__ __u->__sca7 = __src7;
      বিরতি;
    ক্ষেত্র 8:
      __extension__ __u->__sca8 = __src8;
      বিরতি;
    }
  ফেরত __extension__ ((শূন্য *) __u + __srclen);
}
# endif
compat_প্রতীক (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# যদি _STRING_INLINE_unaligned
অক্ষর *
__old_strcpy_small (অক্ষর *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  সংঘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned অক্ষর __uc;
  } *__u = (শূন্য *) __dest;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 2:
      __u->__usi = __src0_2;
      বিরতি;
    ক্ষেত্র 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 4:
      __u->__ui = __src0_4;
      বিরতি;
    ক্ষেত্র 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      বিরতি;
    ক্ষেত্র 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      বিরতি;
    }
  ফেরত __dest;
}

# অন্যথা

অক্ষর *
__old_strcpy_small (অক্ষর *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সংঘ {
    অক্ষর __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (শূন্য *) __dest;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__c = '\0';
      বিরতি;
    ক্ষেত্র 2:
      __extension__ __u->__sca2 = __src2;
      বিরতি;
    ক্ষেত্র 3:
      __extension__ __u->__sca3 = __src3;
      বিরতি;
    ক্ষেত্র 4:
      __extension__ __u->__sca4 = __src4;
      বিরতি;
    ক্ষেত্র 5:
      __extension__ __u->__sca5 = __src5;
      বিরতি;
    ক্ষেত্র 6:
      __extension__ __u->__sca6 = __src6;
      বিরতি;
    ক্ষেত্র 7:
      __extension__ __u->__sca7 = __src7;
      বিরতি;
    ক্ষেত্র 8:
      __extension__ __u->__sca8 = __src8;
      বিরতি;
  }
  ফেরত __dest;
}
# endif
compat_প্রতীক (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# যদি _STRING_INLINE_unaligned
অক্ষর *
__old_stpcpy_small (অক্ষর *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  সংঘ {
    unsigned পূর্ণসংখ্যা __ui;
    unsigned short পূর্ণসংখ্যা __usi;
    unsigned অক্ষর __uc;
    অক্ষর __c;
  } *__u = (শূন্য *) __dest;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 3);
      বিরতি;
    ক্ষেত্র 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 1);
      বিরতি;
    ক্ষেত্র 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      বিরতি;
    ক্ষেত্র 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((শূন্য *) __u + 3);
      বিরতি;
    }
  ফেরত &__u->__c;
}

# অন্যথা

অক্ষর *
__old_stpcpy_small (অক্ষর *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সংঘ {
    অক্ষর __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (শূন্য *) __dest;
  নির্বাচন ((unsigned পূর্ণসংখ্যা) __srclen)
    {
    ক্ষেত্র 1:
      __u->__c = '\0';
      বিরতি;
    ক্ষেত্র 2:
      __extension__ __u->__sca2 = __src2;
      বিরতি;
    ক্ষেত্র 3:
      __extension__ __u->__sca3 = __src3;
      বিরতি;
    ক্ষেত্র 4:
      __extension__ __u->__sca4 = __src4;
      বিরতি;
    ক্ষেত্র 5:
      __extension__ __u->__sca5 = __src5;
      বিরতি;
    ক্ষেত্র 6:
      __extension__ __u->__sca6 = __src6;
      বিরতি;
    ক্ষেত্র 7:
      __extension__ __u->__sca7 = __src7;
      বিরতি;
    ক্ষেত্র 8:
      __extension__ __u->__sca8 = __src8;
      বিরতি;
  }
  ফেরত __dest + __srclen - 1;
}
# endif
compat_প্রতীক (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
