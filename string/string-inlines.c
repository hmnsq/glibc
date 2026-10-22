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
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "shlib-compat.h"

#ଯଦି SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

ଅକ୍ଷର *
__old_strtok_r_1c (ଅକ୍ଷର *__s, ଅକ୍ଷର __sep, ଅକ୍ଷର **__nextp)
{
  ଅକ୍ଷର *__result;
  ଯଦି (__s == ଖାଲି)
    __s = *__nextp;
  ଯେତେବେଳେ (*__s == __sep)
    ++__s;
  __result = ଖାଲି;
  ଯଦି (*__s != '\0')
    {
      __result = __s++;
      ଯେତେବେଳେ (*__s != '\0')
	ଯଦି (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ଭାଙ୍ଗ;
	  }
    }
  *__nextp = __s;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

ଅକ୍ଷର *
__old_strsep_1c (ଅକ୍ଷର **__s, ଅକ୍ଷର __reject)
{
  ଅକ୍ଷର *__retval = *__s;
  ଯଦି (__retval != ଖାଲି && (*__s = strchr (__retval, __reject)) != ଖାଲି)
    *(*__s)++ = '\0';
  ଫେରନ୍ତୁ __retval;
}
compat_ପ୍ରତୀକ (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

ଅକ୍ଷର *
__old_strsep_2c (ଅକ୍ଷର **__s, ଅକ୍ଷର __reject1, ଅକ୍ଷର __reject2)
{
  ଅକ୍ଷର *__retval = *__s;
  ଯଦି (__retval != ଖାଲି)
    {
      ଅକ୍ଷର *__cp = __retval;
      ଯେତେବେଳେ (1)
	{
	  ଯଦି (*__cp == '\0')
	    {
	      __cp = ଖାଲି;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ଭାଙ୍ଗ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ଫେରନ୍ତୁ __retval;
}
compat_ପ୍ରତୀକ (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

ଅକ୍ଷର *
__old_strsep_3c (ଅକ୍ଷର **__s, ଅକ୍ଷର __reject1, ଅକ୍ଷର __reject2, ଅକ୍ଷର __reject3)
{
  ଅକ୍ଷର *__retval = *__s;
  ଯଦି (__retval != ଖାଲି)
    {
      ଅକ୍ଷର *__cp = __retval;
      ଯେତେବେଳେ (1)
	{
	  ଯଦି (*__cp == '\0')
	    {
	      __cp = ଖାଲି;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ଭାଙ୍ଗ;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ଫେରନ୍ତୁ __retval;
}
compat_ପ୍ରତୀକ (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#ଯଦି SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject)
{
  size_t __result = 0;
  ଯେତେବେଳେ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject2)
{
  size_t __result = 0;
  ଯେତେବେଳେ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject2,
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା __reject3)
{
  size_t __result = 0;
  ଯେତେବେଳେ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  ଯେତେବେଳେ (__s[__result] == __accept)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ଯେତେବେଳେ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept2,
		 ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ଯେତେବେଳେ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ଫେରନ୍ତୁ __result;
}
compat_ପ୍ରତୀକ (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

ଅକ୍ଷର *
__old_strpbrk_c2 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ଯେତେବେଳେ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ଫେରନ୍ତୁ *__s == '\0' ? ଖାଲି : (ଅକ୍ଷର *) (size_t) __s;
}
compat_ପ୍ରତୀକ (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

ଅକ୍ଷର *
__old_strpbrk_c3 (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ଯେତେବେଳେ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ଫେରନ୍ତୁ *__s == '\0' ? ଖାଲି : (ଅକ୍ଷର *) (size_t) __s;
}
compat_ପ୍ରତୀକ (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# ଯଦି defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# ଅନ୍ୟଥା
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା { unsigned ଅକ୍ଷର __arr[N]; }				      \
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

# ଯଦି _STRING_INLINE_unaligned
ଶୂନ୍ୟ *
__old_mempcpy_small (ଶୂନ୍ୟ *__dest1,
		     ଅକ୍ଷର __src0_1, ଅକ୍ଷର __src2_1, ଅକ୍ଷର __src4_1, ଅକ୍ଷର __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  ସଂଘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ଅକ୍ଷର __uc;
    unsigned ଅକ୍ଷର __c;
  } *__u = __dest1;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__c = __src0_1;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ (ଶୂନ୍ୟ *) __u;
}

# ଅନ୍ୟଥା

ଶୂନ୍ୟ *
__old_mempcpy_small (ଶୂନ୍ୟ *__dest, ଅକ୍ଷର __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ସଂଘ {
    ଅକ୍ଷର __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__c = __src1;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __extension__ __u->__sca2 = __src2;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __extension__ __u->__sca3 = __src3;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __extension__ __u->__sca4 = __src4;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __extension__ __u->__sca5 = __src5;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __extension__ __u->__sca6 = __src6;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __extension__ __u->__sca7 = __src7;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __extension__ __u->__sca8 = __src8;
      ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ __extension__ ((ଶୂନ୍ୟ *) __u + __srclen);
}
# endif
compat_ପ୍ରତୀକ (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# ଯଦି _STRING_INLINE_unaligned
ଅକ୍ଷର *
__old_strcpy_small (ଅକ୍ଷର *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ସଂଘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned ଅକ୍ଷର __uc;
  } *__u = (ଶୂନ୍ୟ *) __dest;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __u->__usi = __src0_2;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __u->__ui = __src0_4;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__ui = __src4_4;
      ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ __dest;
}

# ଅନ୍ୟଥା

ଅକ୍ଷର *
__old_strcpy_small (ଅକ୍ଷର *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ସଂଘ {
    ଅକ୍ଷର __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ଶୂନ୍ୟ *) __dest;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__c = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __extension__ __u->__sca2 = __src2;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __extension__ __u->__sca3 = __src3;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __extension__ __u->__sca4 = __src4;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __extension__ __u->__sca5 = __src5;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __extension__ __u->__sca6 = __src6;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __extension__ __u->__sca7 = __src7;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __extension__ __u->__sca8 = __src8;
      ଭାଙ୍ଗ;
  }
  ଫେରନ୍ତୁ __dest;
}
# endif
compat_ପ୍ରତୀକ (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# ଯଦି _STRING_INLINE_unaligned
ଅକ୍ଷର *
__old_stpcpy_small (ଅକ୍ଷର *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ସଂଘ {
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା __ui;
    unsigned short ପୂର୍ଣ୍ଣସଂଖ୍ୟା __usi;
    unsigned ଅକ୍ଷର __uc;
    ଅକ୍ଷର __c;
  } *__u = (ଶୂନ୍ୟ *) __dest;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 3);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 1);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 2);
      __u->__uc = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ଶୂନ୍ୟ *) __u + 3);
      ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ &__u->__c;
}

# ଅନ୍ୟଥା

ଅକ୍ଷର *
__old_stpcpy_small (ଅକ୍ଷର *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ସଂଘ {
    ଅକ୍ଷର __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ଶୂନ୍ୟ *) __dest;
  ବାଛ ((unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) __srclen)
    {
    ସ୍ଥିତି 1:
      __u->__c = '\0';
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 2:
      __extension__ __u->__sca2 = __src2;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 3:
      __extension__ __u->__sca3 = __src3;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 4:
      __extension__ __u->__sca4 = __src4;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 5:
      __extension__ __u->__sca5 = __src5;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 6:
      __extension__ __u->__sca6 = __src6;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 7:
      __extension__ __u->__sca7 = __src7;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି 8:
      __extension__ __u->__sca8 = __src8;
      ଭାଙ୍ଗ;
  }
  ଫେରନ୍ତୁ __dest + __srclen - 1;
}
# endif
compat_ପ୍ରତୀକ (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
