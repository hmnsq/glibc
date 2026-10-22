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
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "shlib-compat.h"

#જો SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

અક્ષર *
__old_strtok_r_1c (અક્ષર *__s, અક્ષર __sep, અક્ષર **__nextp)
{
  અક્ષર *__result;
  જો (__s == ખાલી)
    __s = *__nextp;
  જ્યારે (*__s == __sep)
    ++__s;
  __result = ખાલી;
  જો (*__s != '\0')
    {
      __result = __s++;
      જ્યારે (*__s != '\0')
	જો (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    તોડો;
	  }
    }
  *__nextp = __s;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

અક્ષર *
__old_strsep_1c (અક્ષર **__s, અક્ષર __reject)
{
  અક્ષર *__retval = *__s;
  જો (__retval != ખાલી && (*__s = strchr (__retval, __reject)) != ખાલી)
    *(*__s)++ = '\0';
  પાછા __retval;
}
compat_પ્રતીક (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

અક્ષર *
__old_strsep_2c (અક્ષર **__s, અક્ષર __reject1, અક્ષર __reject2)
{
  અક્ષર *__retval = *__s;
  જો (__retval != ખાલી)
    {
      અક્ષર *__cp = __retval;
      જ્યારે (1)
	{
	  જો (*__cp == '\0')
	    {
	      __cp = ખાલી;
	      તોડો;
	    }
	  જો (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      તોડો;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  પાછા __retval;
}
compat_પ્રતીક (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

અક્ષર *
__old_strsep_3c (અક્ષર **__s, અક્ષર __reject1, અક્ષર __reject2, અક્ષર __reject3)
{
  અક્ષર *__retval = *__s;
  જો (__retval != ખાલી)
    {
      અક્ષર *__cp = __retval;
      જ્યારે (1)
	{
	  જો (*__cp == '\0')
	    {
	      __cp = ખાલી;
	      તોડો;
	    }
	  જો (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      તોડો;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  પાછા __retval;
}
compat_પ્રતીક (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#જો SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (અચલ અક્ષર *__s, પૂર્ણાંક __reject)
{
  size_t __result = 0;
  જ્યારે (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (અચલ અક્ષર *__s, પૂર્ણાંક __reject1, પૂર્ણાંક __reject2)
{
  size_t __result = 0;
  જ્યારે (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (અચલ અક્ષર *__s, પૂર્ણાંક __reject1, પૂર્ણાંક __reject2,
	      પૂર્ણાંક __reject3)
{
  size_t __result = 0;
  જ્યારે (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (અચલ અક્ષર *__s, પૂર્ણાંક __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  જ્યારે (__s[__result] == __accept)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (અચલ અક્ષર *__s, પૂર્ણાંક __accept1, પૂર્ણાંક __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  જ્યારે (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (અચલ અક્ષર *__s, પૂર્ણાંક __accept1, પૂર્ણાંક __accept2,
		 પૂર્ણાંક __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  જ્યારે (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  પાછા __result;
}
compat_પ્રતીક (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

અક્ષર *
__old_strpbrk_c2 (અચલ અક્ષર *__s, પૂર્ણાંક __accept1, પૂર્ણાંક __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  જ્યારે (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  પાછા *__s == '\0' ? ખાલી : (અક્ષર *) (size_t) __s;
}
compat_પ્રતીક (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

અક્ષર *
__old_strpbrk_c3 (અચલ અક્ષર *__s, પૂર્ણાંક __accept1, પૂર્ણાંક __accept2, પૂર્ણાંક __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  જ્યારે (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  પાછા *__s == '\0' ? ખાલી : (અક્ષર *) (size_t) __s;
}
compat_પ્રતીક (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# જો defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# નહીંતર
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  પ્રકારવ્યાખ્યા સંરચના { unsigned અક્ષર __arr[N]; }				      \
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

# જો _STRING_INLINE_unaligned
શૂન્ય *
__old_mempcpy_small (શૂન્ય *__dest1,
		     અક્ષર __src0_1, અક્ષર __src2_1, અક્ષર __src4_1, અક્ષર __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  સંઘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned અક્ષર __uc;
    unsigned અક્ષર __c;
  } *__u = __dest1;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      તોડો;
    સ્થિતિ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      તોડો;
    સ્થિતિ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      તોડો;
    સ્થિતિ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      તોડો;
    }
  પાછા (શૂન્ય *) __u;
}

# નહીંતર

શૂન્ય *
__old_mempcpy_small (શૂન્ય *__dest, અક્ષર __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  સંઘ {
    અક્ષર __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__c = __src1;
      તોડો;
    સ્થિતિ 2:
      __extension__ __u->__sca2 = __src2;
      તોડો;
    સ્થિતિ 3:
      __extension__ __u->__sca3 = __src3;
      તોડો;
    સ્થિતિ 4:
      __extension__ __u->__sca4 = __src4;
      તોડો;
    સ્થિતિ 5:
      __extension__ __u->__sca5 = __src5;
      તોડો;
    સ્થિતિ 6:
      __extension__ __u->__sca6 = __src6;
      તોડો;
    સ્થિતિ 7:
      __extension__ __u->__sca7 = __src7;
      તોડો;
    સ્થિતિ 8:
      __extension__ __u->__sca8 = __src8;
      તોડો;
    }
  પાછા __extension__ ((શૂન્ય *) __u + __srclen);
}
# endif
compat_પ્રતીક (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# જો _STRING_INLINE_unaligned
અક્ષર *
__old_strcpy_small (અક્ષર *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  સંઘ {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned અક્ષર __uc;
  } *__u = (શૂન્ય *) __dest;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 2:
      __u->__usi = __src0_2;
      તોડો;
    સ્થિતિ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 4:
      __u->__ui = __src0_4;
      તોડો;
    સ્થિતિ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      તોડો;
    સ્થિતિ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__ui = __src4_4;
      તોડો;
    }
  પાછા __dest;
}

# નહીંતર

અક્ષર *
__old_strcpy_small (અક્ષર *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  સંઘ {
    અક્ષર __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (શૂન્ય *) __dest;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__c = '\0';
      તોડો;
    સ્થિતિ 2:
      __extension__ __u->__sca2 = __src2;
      તોડો;
    સ્થિતિ 3:
      __extension__ __u->__sca3 = __src3;
      તોડો;
    સ્થિતિ 4:
      __extension__ __u->__sca4 = __src4;
      તોડો;
    સ્થિતિ 5:
      __extension__ __u->__sca5 = __src5;
      તોડો;
    સ્થિતિ 6:
      __extension__ __u->__sca6 = __src6;
      તોડો;
    સ્થિતિ 7:
      __extension__ __u->__sca7 = __src7;
      તોડો;
    સ્થિતિ 8:
      __extension__ __u->__sca8 = __src8;
      તોડો;
  }
  પાછા __dest;
}
# endif
compat_પ્રતીક (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# જો _STRING_INLINE_unaligned
અક્ષર *
__old_stpcpy_small (અક્ષર *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  સંઘ {
    unsigned પૂર્ણાંક __ui;
    unsigned short પૂર્ણાંક __usi;
    unsigned અક્ષર __uc;
    અક્ષર __c;
  } *__u = (શૂન્ય *) __dest;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 3);
      તોડો;
    સ્થિતિ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((શૂન્ય *) __u + 1);
      તોડો;
    સ્થિતિ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((શૂન્ય *) __u + 2);
      __u->__uc = '\0';
      તોડો;
    સ્થિતિ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((શૂન્ય *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((શૂન્ય *) __u + 3);
      તોડો;
    }
  પાછા &__u->__c;
}

# નહીંતર

અક્ષર *
__old_stpcpy_small (અક્ષર *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  સંઘ {
    અક્ષર __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (શૂન્ય *) __dest;
  પસંદગી ((unsigned પૂર્ણાંક) __srclen)
    {
    સ્થિતિ 1:
      __u->__c = '\0';
      તોડો;
    સ્થિતિ 2:
      __extension__ __u->__sca2 = __src2;
      તોડો;
    સ્થિતિ 3:
      __extension__ __u->__sca3 = __src3;
      તોડો;
    સ્થિતિ 4:
      __extension__ __u->__sca4 = __src4;
      તોડો;
    સ્થિતિ 5:
      __extension__ __u->__sca5 = __src5;
      તોડો;
    સ્થિતિ 6:
      __extension__ __u->__sca6 = __src6;
      તોડો;
    સ્થિતિ 7:
      __extension__ __u->__sca7 = __src7;
      તોડો;
    સ્થિતિ 8:
      __extension__ __u->__sca8 = __src8;
      તોડો;
  }
  પાછા __dest + __srclen - 1;
}
# endif
compat_પ્રતીક (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
