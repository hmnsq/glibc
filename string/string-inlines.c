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

#నిర్వచించు __NO_STRING_INLINES
#అన్తర్భావ <string.h>

#అన్తర్భావ "shlib-compat.h"

#ఒకవేళ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

అక్షరం *
__old_strtok_r_1c (అక్షరం *__s, అక్షరం __sep, అక్షరం **__nextp)
{
  అక్షరం *__result;
  ఒకవేళ (__s == ఖాళీ)
    __s = *__nextp;
  అయితే (*__s == __sep)
    ++__s;
  __result = ఖాళీ;
  ఒకవేళ (*__s != '\0')
    {
      __result = __s++;
      అయితే (*__s != '\0')
	ఒకవేళ (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    ఆపు;
	  }
    }
  *__nextp = __s;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

అక్షరం *
__old_strsep_1c (అక్షరం **__s, అక్షరం __reject)
{
  అక్షరం *__retval = *__s;
  ఒకవేళ (__retval != ఖాళీ && (*__s = strchr (__retval, __reject)) != ఖాళీ)
    *(*__s)++ = '\0';
  తిరిగి __retval;
}
compat_చిహ్నం (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

అక్షరం *
__old_strsep_2c (అక్షరం **__s, అక్షరం __reject1, అక్షరం __reject2)
{
  అక్షరం *__retval = *__s;
  ఒకవేళ (__retval != ఖాళీ)
    {
      అక్షరం *__cp = __retval;
      అయితే (1)
	{
	  ఒకవేళ (*__cp == '\0')
	    {
	      __cp = ఖాళీ;
	      ఆపు;
	    }
	  ఒకవేళ (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      ఆపు;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  తిరిగి __retval;
}
compat_చిహ్నం (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

అక్షరం *
__old_strsep_3c (అక్షరం **__s, అక్షరం __reject1, అక్షరం __reject2, అక్షరం __reject3)
{
  అక్షరం *__retval = *__s;
  ఒకవేళ (__retval != ఖాళీ)
    {
      అక్షరం *__cp = __retval;
      అయితే (1)
	{
	  ఒకవేళ (*__cp == '\0')
	    {
	      __cp = ఖాళీ;
	      ఆపు;
	    }
	  ఒకవేళ (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      ఆపు;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  తిరిగి __retval;
}
compat_చిహ్నం (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#అయితే_ముగింపు

#ఒకవేళ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __reject)
{
  size_t __result = 0;
  అయితే (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __reject1, పూర్ణాంకం __reject2)
{
  size_t __result = 0;
  అయితే (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __reject1, పూర్ణాంకం __reject2,
	      పూర్ణాంకం __reject3)
{
  size_t __result = 0;
  అయితే (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  అయితే (__s[__result] == __accept)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __accept1, పూర్ణాంకం __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  అయితే (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __accept1, పూర్ణాంకం __accept2,
		 పూర్ణాంకం __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  అయితే (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  తిరిగి __result;
}
compat_చిహ్నం (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

అక్షరం *
__old_strpbrk_c2 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __accept1, పూర్ణాంకం __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  అయితే (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  తిరిగి *__s == '\0' ? ఖాళీ : (అక్షరం *) (size_t) __s;
}
compat_చిహ్నం (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

అక్షరం *
__old_strpbrk_c3 (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __accept1, పూర్ణాంకం __accept2, పూర్ణాంకం __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  అయితే (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  తిరిగి *__s == '\0' ? ఖాళీ : (అక్షరం *) (size_t) __s;
}
compat_చిహ్నం (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# ఒకవేళ defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# లేకపోతే
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  రకనిర్వచనం నిర్మాణం { గుర్తులేని అక్షరం __arr[N]; }				      \
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

# ఒకవేళ _STRING_INLINE_unaligned
శూన్య *
__old_mempcpy_small (శూన్య *__dest1,
		     అక్షరం __src0_1, అక్షరం __src2_1, అక్షరం __src4_1, అక్షరం __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  సంఘం {
    __uint32_t __ui;
    __uint16_t __usi;
    గుర్తులేని అక్షరం __uc;
    గుర్తులేని అక్షరం __c;
  } *__u = __dest1;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__c = __src0_1;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      ఆపు;
    స్థితి 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      ఆపు;
    స్థితి 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      ఆపు;
    స్థితి 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      ఆపు;
    }
  తిరిగి (శూన్య *) __u;
}

# లేకపోతే

శూన్య *
__old_mempcpy_small (శూన్య *__dest, అక్షరం __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  సంఘం {
    అక్షరం __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__c = __src1;
      ఆపు;
    స్థితి 2:
      __extension__ __u->__sca2 = __src2;
      ఆపు;
    స్థితి 3:
      __extension__ __u->__sca3 = __src3;
      ఆపు;
    స్థితి 4:
      __extension__ __u->__sca4 = __src4;
      ఆపు;
    స్థితి 5:
      __extension__ __u->__sca5 = __src5;
      ఆపు;
    స్థితి 6:
      __extension__ __u->__sca6 = __src6;
      ఆపు;
    స్థితి 7:
      __extension__ __u->__sca7 = __src7;
      ఆపు;
    స్థితి 8:
      __extension__ __u->__sca8 = __src8;
      ఆపు;
    }
  తిరిగి __extension__ ((శూన్య *) __u + __srclen);
}
# endif
compat_చిహ్నం (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# ఒకవేళ _STRING_INLINE_unaligned
అక్షరం *
__old_strcpy_small (అక్షరం *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  సంఘం {
    __uint32_t __ui;
    __uint16_t __usi;
    గుర్తులేని అక్షరం __uc;
  } *__u = (శూన్య *) __dest;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__uc = '\0';
      ఆపు;
    స్థితి 2:
      __u->__usi = __src0_2;
      ఆపు;
    స్థితి 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 4:
      __u->__ui = __src0_4;
      ఆపు;
    స్థితి 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      ఆపు;
    స్థితి 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__ui = __src4_4;
      ఆపు;
    }
  తిరిగి __dest;
}

# లేకపోతే

అక్షరం *
__old_strcpy_small (అక్షరం *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  సంఘం {
    అక్షరం __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (శూన్య *) __dest;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__c = '\0';
      ఆపు;
    స్థితి 2:
      __extension__ __u->__sca2 = __src2;
      ఆపు;
    స్థితి 3:
      __extension__ __u->__sca3 = __src3;
      ఆపు;
    స్థితి 4:
      __extension__ __u->__sca4 = __src4;
      ఆపు;
    స్థితి 5:
      __extension__ __u->__sca5 = __src5;
      ఆపు;
    స్థితి 6:
      __extension__ __u->__sca6 = __src6;
      ఆపు;
    స్థితి 7:
      __extension__ __u->__sca7 = __src7;
      ఆపు;
    స్థితి 8:
      __extension__ __u->__sca8 = __src8;
      ఆపు;
  }
  తిరిగి __dest;
}
# endif
compat_చిహ్నం (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# ఒకవేళ _STRING_INLINE_unaligned
అక్షరం *
__old_stpcpy_small (అక్షరం *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  సంఘం {
    గుర్తులేని పూర్ణాంకం __ui;
    గుర్తులేని పొట్టి పూర్ణాంకం __usi;
    గుర్తులేని అక్షరం __uc;
    అక్షరం __c;
  } *__u = (శూన్య *) __dest;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__uc = '\0';
      ఆపు;
    స్థితి 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 3);
      ఆపు;
    స్థితి 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((శూన్య *) __u + 1);
      ఆపు;
    స్థితి 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((శూన్య *) __u + 2);
      __u->__uc = '\0';
      ఆపు;
    స్థితి 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((శూన్య *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((శూన్య *) __u + 3);
      ఆపు;
    }
  తిరిగి &__u->__c;
}

# లేకపోతే

అక్షరం *
__old_stpcpy_small (అక్షరం *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  సంఘం {
    అక్షరం __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (శూన్య *) __dest;
  ఎంపిక ((గుర్తులేని పూర్ణాంకం) __srclen)
    {
    స్థితి 1:
      __u->__c = '\0';
      ఆపు;
    స్థితి 2:
      __extension__ __u->__sca2 = __src2;
      ఆపు;
    స్థితి 3:
      __extension__ __u->__sca3 = __src3;
      ఆపు;
    స్థితి 4:
      __extension__ __u->__sca4 = __src4;
      ఆపు;
    స్థితి 5:
      __extension__ __u->__sca5 = __src5;
      ఆపు;
    స్థితి 6:
      __extension__ __u->__sca6 = __src6;
      ఆపు;
    స్థితి 7:
      __extension__ __u->__sca7 = __src7;
      ఆపు;
    స్థితి 8:
      __extension__ __u->__sca8 = __src8;
      ఆపు;
  }
  తిరిగి __dest + __srclen - 1;
}
# endif
compat_చిహ్నం (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#అయితే_ముగింపు
