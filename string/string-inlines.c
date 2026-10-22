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
#अन्तर्भाव <string.h>

#अन्तर्भाव "shlib-compat.h"

#सचे SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

वर्ण *
__old_strtok_r_1c (वर्ण *__s, वर्ण __sep, वर्ण **__nextp)
{
  वर्ण *__result;
  सचे (__s == रिक्त)
    __s = *__nextp;
  याव (*__s == __sep)
    ++__s;
  __result = रिक्त;
  सचे (*__s != '\0')
    {
      __result = __s++;
      याव (*__s != '\0')
	सचे (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    भङ्ग;
	  }
    }
  *__nextp = __s;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

वर्ण *
__old_strsep_1c (वर्ण **__s, वर्ण __reject)
{
  वर्ण *__retval = *__s;
  सचे (__retval != रिक्त && (*__s = strchr (__retval, __reject)) != रिक्त)
    *(*__s)++ = '\0';
  पटिनिवत्त __retval;
}
compat_चिह्नम् (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

वर्ण *
__old_strsep_2c (वर्ण **__s, वर्ण __reject1, वर्ण __reject2)
{
  वर्ण *__retval = *__s;
  सचे (__retval != रिक्त)
    {
      वर्ण *__cp = __retval;
      याव (1)
	{
	  सचे (*__cp == '\0')
	    {
	      __cp = रिक्त;
	      भङ्ग;
	    }
	  सचे (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      भङ्ग;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  पटिनिवत्त __retval;
}
compat_चिह्नम् (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

वर्ण *
__old_strsep_3c (वर्ण **__s, वर्ण __reject1, वर्ण __reject2, वर्ण __reject3)
{
  वर्ण *__retval = *__s;
  सचे (__retval != रिक्त)
    {
      वर्ण *__cp = __retval;
      याव (1)
	{
	  सचे (*__cp == '\0')
	    {
	      __cp = रिक्त;
	      भङ्ग;
	    }
	  सचे (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      भङ्ग;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  पटिनिवत्त __retval;
}
compat_चिह्नम् (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#सचे SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (ध्रुव वर्ण *__s, पूर्णाङ्क __reject)
{
  size_t __result = 0;
  याव (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (ध्रुव वर्ण *__s, पूर्णाङ्क __reject1, पूर्णाङ्क __reject2)
{
  size_t __result = 0;
  याव (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (ध्रुव वर्ण *__s, पूर्णाङ्क __reject1, पूर्णाङ्क __reject2,
	      पूर्णाङ्क __reject3)
{
  size_t __result = 0;
  याव (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (ध्रुव वर्ण *__s, पूर्णाङ्क __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  याव (__s[__result] == __accept)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (ध्रुव वर्ण *__s, पूर्णाङ्क __accept1, पूर्णाङ्क __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  याव (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (ध्रुव वर्ण *__s, पूर्णाङ्क __accept1, पूर्णाङ्क __accept2,
		 पूर्णाङ्क __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  याव (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  पटिनिवत्त __result;
}
compat_चिह्नम् (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

वर्ण *
__old_strpbrk_c2 (ध्रुव वर्ण *__s, पूर्णाङ्क __accept1, पूर्णाङ्क __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  याव (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  पटिनिवत्त *__s == '\0' ? रिक्त : (वर्ण *) (size_t) __s;
}
compat_चिह्नम् (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

वर्ण *
__old_strpbrk_c3 (ध्रुव वर्ण *__s, पूर्णाङ्क __accept1, पूर्णाङ्क __accept2, पूर्णाङ्क __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  याव (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  पटिनिवत्त *__s == '\0' ? रिक्त : (वर्ण *) (size_t) __s;
}
compat_चिह्नम् (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# सचे defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# अञ्ञथा
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  प्रकारनिर्देश संरचना { unsigned वर्ण __arr[N]; }				      \
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

# सचे _STRING_INLINE_unaligned
शून्य *
__old_mempcpy_small (शून्य *__dest1,
		     वर्ण __src0_1, वर्ण __src2_1, वर्ण __src4_1, वर्ण __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  सङ्घ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned वर्ण __uc;
    unsigned वर्ण __c;
  } *__u = __dest1;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__c = __src0_1;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      भङ्ग;
    पक्ष 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      भङ्ग;
    पक्ष 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      भङ्ग;
    पक्ष 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((शून्य *) __u + 4);
      भङ्ग;
    }
  पटिनिवत्त (शून्य *) __u;
}

# अञ्ञथा

शून्य *
__old_mempcpy_small (शून्य *__dest, वर्ण __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  सङ्घ {
    वर्ण __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__c = __src1;
      भङ्ग;
    पक्ष 2:
      __extension__ __u->__sca2 = __src2;
      भङ्ग;
    पक्ष 3:
      __extension__ __u->__sca3 = __src3;
      भङ्ग;
    पक्ष 4:
      __extension__ __u->__sca4 = __src4;
      भङ्ग;
    पक्ष 5:
      __extension__ __u->__sca5 = __src5;
      भङ्ग;
    पक्ष 6:
      __extension__ __u->__sca6 = __src6;
      भङ्ग;
    पक्ष 7:
      __extension__ __u->__sca7 = __src7;
      भङ्ग;
    पक्ष 8:
      __extension__ __u->__sca8 = __src8;
      भङ्ग;
    }
  पटिनिवत्त __extension__ ((शून्य *) __u + __srclen);
}
# endif
compat_चिह्नम् (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# सचे _STRING_INLINE_unaligned
वर्ण *
__old_strcpy_small (वर्ण *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  सङ्घ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned वर्ण __uc;
  } *__u = (शून्य *) __dest;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 2:
      __u->__usi = __src0_2;
      भङ्ग;
    पक्ष 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 4:
      __u->__ui = __src0_4;
      भङ्ग;
    पक्ष 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      भङ्ग;
    पक्ष 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      भङ्ग;
    }
  पटिनिवत्त __dest;
}

# अञ्ञथा

वर्ण *
__old_strcpy_small (वर्ण *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  सङ्घ {
    वर्ण __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (शून्य *) __dest;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__c = '\0';
      भङ्ग;
    पक्ष 2:
      __extension__ __u->__sca2 = __src2;
      भङ्ग;
    पक्ष 3:
      __extension__ __u->__sca3 = __src3;
      भङ्ग;
    पक्ष 4:
      __extension__ __u->__sca4 = __src4;
      भङ्ग;
    पक्ष 5:
      __extension__ __u->__sca5 = __src5;
      भङ्ग;
    पक्ष 6:
      __extension__ __u->__sca6 = __src6;
      भङ्ग;
    पक्ष 7:
      __extension__ __u->__sca7 = __src7;
      भङ्ग;
    पक्ष 8:
      __extension__ __u->__sca8 = __src8;
      भङ्ग;
  }
  पटिनिवत्त __dest;
}
# endif
compat_चिह्नम् (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# सचे _STRING_INLINE_unaligned
वर्ण *
__old_stpcpy_small (वर्ण *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  सङ्घ {
    unsigned पूर्णाङ्क __ui;
    unsigned short पूर्णाङ्क __usi;
    unsigned वर्ण __uc;
    वर्ण __c;
  } *__u = (शून्य *) __dest;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 3);
      भङ्ग;
    पक्ष 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 1);
      भङ्ग;
    पक्ष 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      भङ्ग;
    पक्ष 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((शून्य *) __u + 3);
      भङ्ग;
    }
  पटिनिवत्त &__u->__c;
}

# अञ्ञथा

वर्ण *
__old_stpcpy_small (वर्ण *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  सङ्घ {
    वर्ण __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (शून्य *) __dest;
  विकल्प ((unsigned पूर्णाङ्क) __srclen)
    {
    पक्ष 1:
      __u->__c = '\0';
      भङ्ग;
    पक्ष 2:
      __extension__ __u->__sca2 = __src2;
      भङ्ग;
    पक्ष 3:
      __extension__ __u->__sca3 = __src3;
      भङ्ग;
    पक्ष 4:
      __extension__ __u->__sca4 = __src4;
      भङ्ग;
    पक्ष 5:
      __extension__ __u->__sca5 = __src5;
      भङ्ग;
    पक्ष 6:
      __extension__ __u->__sca6 = __src6;
      भङ्ग;
    पक्ष 7:
      __extension__ __u->__sca7 = __src7;
      भङ्ग;
    पक्ष 8:
      __extension__ __u->__sca8 = __src8;
      भङ्ग;
  }
  पटिनिवत्त __dest + __srclen - 1;
}
# endif
compat_चिह्नम् (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
