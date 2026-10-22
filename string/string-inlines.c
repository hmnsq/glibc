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
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "shlib-compat.h"

#যদি SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

ৱর্ণ *
__old_strtok_r_1c (ৱর্ণ *__s, ৱর্ণ __sep, ৱর্ণ **__nextp)
{
  ৱর্ণ *__result;
  যদি (__s == রিক্ত)
    __s = *__nextp;
  যেতিয়ালৈ (*__s == __sep)
    ++__s;
  __result = রিক্ত;
  যদি (*__s != '\0')
    {
      __result = __s++;
      যেতিয়ালৈ (*__s != '\0')
	যদি (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ভঙ্গ;
	  }
    }
  *__nextp = __s;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

ৱর্ণ *
__old_strsep_1c (ৱর্ণ **__s, ৱর্ণ __reject)
{
  ৱর্ণ *__retval = *__s;
  যদি (__retval != রিক্ত && (*__s = strchr (__retval, __reject)) != রিক্ত)
    *(*__s)++ = '\0';
  ঘূৰাই __retval;
}
compat_প্ৰতীক (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

ৱর্ণ *
__old_strsep_2c (ৱর্ণ **__s, ৱর্ণ __reject1, ৱর্ণ __reject2)
{
  ৱর্ণ *__retval = *__s;
  যদি (__retval != রিক্ত)
    {
      ৱর্ণ *__cp = __retval;
      যেতিয়ালৈ (1)
	{
	  যদি (*__cp == '\0')
	    {
	      __cp = রিক্ত;
	      ভঙ্গ;
	    }
	  যদি (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ভঙ্গ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ঘূৰাই __retval;
}
compat_প্ৰতীক (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

ৱর্ণ *
__old_strsep_3c (ৱর্ণ **__s, ৱর্ণ __reject1, ৱর্ণ __reject2, ৱর্ণ __reject3)
{
  ৱর্ণ *__retval = *__s;
  যদি (__retval != রিক্ত)
    {
      ৱর্ণ *__cp = __retval;
      যেতিয়ালৈ (1)
	{
	  যদি (*__cp == '\0')
	    {
	      __cp = রিক্ত;
	      ভঙ্গ;
	    }
	  যদি (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ভঙ্গ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ঘূৰাই __retval;
}
compat_প্ৰতীক (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#যদি SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __reject)
{
  size_t __result = 0;
  যেতিয়ালৈ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __reject1, পূর্ণাঙ্ক __reject2)
{
  size_t __result = 0;
  যেতিয়ালৈ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __reject1, পূর্ণাঙ্ক __reject2,
	      পূর্ণাঙ্ক __reject3)
{
  size_t __result = 0;
  যেতিয়ালৈ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  যেতিয়ালৈ (__s[__result] == __accept)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __accept1, পূর্ণাঙ্ক __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  যেতিয়ালৈ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __accept1, পূর্ণাঙ্ক __accept2,
		 পূর্ণাঙ্ক __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  যেতিয়ালৈ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ঘূৰাই __result;
}
compat_প্ৰতীক (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

ৱর্ণ *
__old_strpbrk_c2 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __accept1, পূর্ণাঙ্ক __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  যেতিয়ালৈ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ঘূৰাই *__s == '\0' ? রিক্ত : (ৱর্ণ *) (size_t) __s;
}
compat_প্ৰতীক (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

ৱর্ণ *
__old_strpbrk_c3 (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __accept1, পূর্ণাঙ্ক __accept2, পূর্ণাঙ্ক __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  যেতিয়ালৈ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ঘূৰাই *__s == '\0' ? রিক্ত : (ৱর্ণ *) (size_t) __s;
}
compat_প্ৰতীক (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# যদি defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# অন্যথা
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  প্রকারনির্দেশ সংরচনা { unsigned ৱর্ণ __arr[N]; }				      \
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
		     ৱর্ণ __src0_1, ৱর্ণ __src2_1, ৱর্ণ __src4_1, ৱর্ণ __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  সঙ্ঘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ৱর্ণ __uc;
    unsigned ৱর্ণ __c;
  } *__u = __dest1;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      ভঙ্গ;
    পক্ষ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      ভঙ্গ;
    পক্ষ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      ভঙ্গ;
    পক্ষ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      ভঙ্গ;
    }
  ঘূৰাই (শূন্য *) __u;
}

# অন্যথা

শূন্য *
__old_mempcpy_small (শূন্য *__dest, ৱর্ণ __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সঙ্ঘ {
    ৱর্ণ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__c = __src1;
      ভঙ্গ;
    পক্ষ 2:
      __extension__ __u->__sca2 = __src2;
      ভঙ্গ;
    পক্ষ 3:
      __extension__ __u->__sca3 = __src3;
      ভঙ্গ;
    পক্ষ 4:
      __extension__ __u->__sca4 = __src4;
      ভঙ্গ;
    পক্ষ 5:
      __extension__ __u->__sca5 = __src5;
      ভঙ্গ;
    পক্ষ 6:
      __extension__ __u->__sca6 = __src6;
      ভঙ্গ;
    পক্ষ 7:
      __extension__ __u->__sca7 = __src7;
      ভঙ্গ;
    পক্ষ 8:
      __extension__ __u->__sca8 = __src8;
      ভঙ্গ;
    }
  ঘূৰাই __extension__ ((শূন্য *) __u + __srclen);
}
# endif
compat_প্ৰতীক (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# যদি _STRING_INLINE_unaligned
ৱর্ণ *
__old_strcpy_small (ৱর্ণ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  সঙ্ঘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ৱর্ণ __uc;
  } *__u = (শূন্য *) __dest;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 2:
      __u->__usi = __src0_2;
      ভঙ্গ;
    পক্ষ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 4:
      __u->__ui = __src0_4;
      ভঙ্গ;
    পক্ষ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      ভঙ্গ;
    পক্ষ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      ভঙ্গ;
    }
  ঘূৰাই __dest;
}

# অন্যথা

ৱর্ণ *
__old_strcpy_small (ৱর্ণ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সঙ্ঘ {
    ৱর্ণ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (শূন্য *) __dest;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__c = '\0';
      ভঙ্গ;
    পক্ষ 2:
      __extension__ __u->__sca2 = __src2;
      ভঙ্গ;
    পক্ষ 3:
      __extension__ __u->__sca3 = __src3;
      ভঙ্গ;
    পক্ষ 4:
      __extension__ __u->__sca4 = __src4;
      ভঙ্গ;
    পক্ষ 5:
      __extension__ __u->__sca5 = __src5;
      ভঙ্গ;
    পক্ষ 6:
      __extension__ __u->__sca6 = __src6;
      ভঙ্গ;
    পক্ষ 7:
      __extension__ __u->__sca7 = __src7;
      ভঙ্গ;
    পক্ষ 8:
      __extension__ __u->__sca8 = __src8;
      ভঙ্গ;
  }
  ঘূৰাই __dest;
}
# endif
compat_প্ৰতীক (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# যদি _STRING_INLINE_unaligned
ৱর্ণ *
__old_stpcpy_small (ৱর্ণ *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  সঙ্ঘ {
    unsigned পূর্ণাঙ্ক __ui;
    unsigned short পূর্ণাঙ্ক __usi;
    unsigned ৱর্ণ __uc;
    ৱর্ণ __c;
  } *__u = (শূন্য *) __dest;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 3);
      ভঙ্গ;
    পক্ষ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 1);
      ভঙ্গ;
    পক্ষ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((শূন্য *) __u + 2);
      __u->__uc = '\0';
      ভঙ্গ;
    পক্ষ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((শূন্য *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((শূন্য *) __u + 3);
      ভঙ্গ;
    }
  ঘূৰাই &__u->__c;
}

# অন্যথা

ৱর্ণ *
__old_stpcpy_small (ৱর্ণ *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  সঙ্ঘ {
    ৱর্ণ __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (শূন্য *) __dest;
  ৱিকল্প ((unsigned পূর্ণাঙ্ক) __srclen)
    {
    পক্ষ 1:
      __u->__c = '\0';
      ভঙ্গ;
    পক্ষ 2:
      __extension__ __u->__sca2 = __src2;
      ভঙ্গ;
    পক্ষ 3:
      __extension__ __u->__sca3 = __src3;
      ভঙ্গ;
    পক্ষ 4:
      __extension__ __u->__sca4 = __src4;
      ভঙ্গ;
    পক্ষ 5:
      __extension__ __u->__sca5 = __src5;
      ভঙ্গ;
    পক্ষ 6:
      __extension__ __u->__sca6 = __src6;
      ভঙ্গ;
    পক্ষ 7:
      __extension__ __u->__sca7 = __src7;
      ভঙ্গ;
    পক্ষ 8:
      __extension__ __u->__sca8 = __src8;
      ভঙ্গ;
  }
  ঘূৰাই __dest + __srclen - 1;
}
# endif
compat_প্ৰতীক (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
