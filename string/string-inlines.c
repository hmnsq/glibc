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
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "shlib-compat.h"

#எனில் SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

எழுத்து *
__old_strtok_r_1c (எழுத்து *__s, எழுத்து __sep, எழுத்து **__nextp)
{
  எழுத்து *__result;
  எனில் (__s == வெற்று)
    __s = *__nextp;
  போது (*__s == __sep)
    ++__s;
  __result = வெற்று;
  எனில் (*__s != '\0')
    {
      __result = __s++;
      போது (*__s != '\0')
	எனில் (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    நிறுத்து;
	  }
    }
  *__nextp = __s;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

எழுத்து *
__old_strsep_1c (எழுத்து **__s, எழுத்து __reject)
{
  எழுத்து *__retval = *__s;
  எனில் (__retval != வெற்று && (*__s = strchr (__retval, __reject)) != வெற்று)
    *(*__s)++ = '\0';
  திரும்பு __retval;
}
compat_குறியீடு (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

எழுத்து *
__old_strsep_2c (எழுத்து **__s, எழுத்து __reject1, எழுத்து __reject2)
{
  எழுத்து *__retval = *__s;
  எனில் (__retval != வெற்று)
    {
      எழுத்து *__cp = __retval;
      போது (1)
	{
	  எனில் (*__cp == '\0')
	    {
	      __cp = வெற்று;
	      நிறுத்து;
	    }
	  எனில் (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      நிறுத்து;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  திரும்பு __retval;
}
compat_குறியீடு (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

எழுத்து *
__old_strsep_3c (எழுத்து **__s, எழுத்து __reject1, எழுத்து __reject2, எழுத்து __reject3)
{
  எழுத்து *__retval = *__s;
  எனில் (__retval != வெற்று)
    {
      எழுத்து *__cp = __retval;
      போது (1)
	{
	  எனில் (*__cp == '\0')
	    {
	      __cp = வெற்று;
	      நிறுத்து;
	    }
	  எனில் (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      நிறுத்து;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  திரும்பு __retval;
}
compat_குறியீடு (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#எனில் SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (மாறிலி எழுத்து *__s, முழு __reject)
{
  size_t __result = 0;
  போது (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (மாறிலி எழுத்து *__s, முழு __reject1, முழு __reject2)
{
  size_t __result = 0;
  போது (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (மாறிலி எழுத்து *__s, முழு __reject1, முழு __reject2,
	      முழு __reject3)
{
  size_t __result = 0;
  போது (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (மாறிலி எழுத்து *__s, முழு __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  போது (__s[__result] == __accept)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (மாறிலி எழுத்து *__s, முழு __accept1, முழு __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  போது (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (மாறிலி எழுத்து *__s, முழு __accept1, முழு __accept2,
		 முழு __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  போது (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  திரும்பு __result;
}
compat_குறியீடு (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

எழுத்து *
__old_strpbrk_c2 (மாறிலி எழுத்து *__s, முழு __accept1, முழு __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  போது (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  திரும்பு *__s == '\0' ? வெற்று : (எழுத்து *) (size_t) __s;
}
compat_குறியீடு (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

எழுத்து *
__old_strpbrk_c3 (மாறிலி எழுத்து *__s, முழு __accept1, முழு __accept2, முழு __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  போது (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  திரும்பு *__s == '\0' ? வெற்று : (எழுத்து *) (size_t) __s;
}
compat_குறியீடு (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# எனில் defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# இல்லையெனில்
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  வகைவரை கட்டமைப்பு { unsigned எழுத்து __arr[N]; }				      \
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

# எனில் _STRING_INLINE_unaligned
வெறுமை *
__old_mempcpy_small (வெறுமை *__dest1,
		     எழுத்து __src0_1, எழுத்து __src2_1, எழுத்து __src4_1, எழுத்து __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  ஒன்றிப்பு {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned எழுத்து __uc;
    unsigned எழுத்து __c;
  } *__u = __dest1;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__c = __src0_1;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      நிறுத்து;
    நிலை 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      நிறுத்து;
    நிலை 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      நிறுத்து;
    நிலை 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      நிறுத்து;
    }
  திரும்பு (வெறுமை *) __u;
}

# இல்லையெனில்

வெறுமை *
__old_mempcpy_small (வெறுமை *__dest, எழுத்து __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ஒன்றிப்பு {
    எழுத்து __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__c = __src1;
      நிறுத்து;
    நிலை 2:
      __extension__ __u->__sca2 = __src2;
      நிறுத்து;
    நிலை 3:
      __extension__ __u->__sca3 = __src3;
      நிறுத்து;
    நிலை 4:
      __extension__ __u->__sca4 = __src4;
      நிறுத்து;
    நிலை 5:
      __extension__ __u->__sca5 = __src5;
      நிறுத்து;
    நிலை 6:
      __extension__ __u->__sca6 = __src6;
      நிறுத்து;
    நிலை 7:
      __extension__ __u->__sca7 = __src7;
      நிறுத்து;
    நிலை 8:
      __extension__ __u->__sca8 = __src8;
      நிறுத்து;
    }
  திரும்பு __extension__ ((வெறுமை *) __u + __srclen);
}
# endif
compat_குறியீடு (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# எனில் _STRING_INLINE_unaligned
எழுத்து *
__old_strcpy_small (எழுத்து *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ஒன்றிப்பு {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned எழுத்து __uc;
  } *__u = (வெறுமை *) __dest;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 2:
      __u->__usi = __src0_2;
      நிறுத்து;
    நிலை 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 4:
      __u->__ui = __src0_4;
      நிறுத்து;
    நிலை 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      நிறுத்து;
    நிலை 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__ui = __src4_4;
      நிறுத்து;
    }
  திரும்பு __dest;
}

# இல்லையெனில்

எழுத்து *
__old_strcpy_small (எழுத்து *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ஒன்றிப்பு {
    எழுத்து __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (வெறுமை *) __dest;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__c = '\0';
      நிறுத்து;
    நிலை 2:
      __extension__ __u->__sca2 = __src2;
      நிறுத்து;
    நிலை 3:
      __extension__ __u->__sca3 = __src3;
      நிறுத்து;
    நிலை 4:
      __extension__ __u->__sca4 = __src4;
      நிறுத்து;
    நிலை 5:
      __extension__ __u->__sca5 = __src5;
      நிறுத்து;
    நிலை 6:
      __extension__ __u->__sca6 = __src6;
      நிறுத்து;
    நிலை 7:
      __extension__ __u->__sca7 = __src7;
      நிறுத்து;
    நிலை 8:
      __extension__ __u->__sca8 = __src8;
      நிறுத்து;
  }
  திரும்பு __dest;
}
# endif
compat_குறியீடு (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# எனில் _STRING_INLINE_unaligned
எழுத்து *
__old_stpcpy_small (எழுத்து *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  ஒன்றிப்பு {
    unsigned முழு __ui;
    unsigned short முழு __usi;
    unsigned எழுத்து __uc;
    எழுத்து __c;
  } *__u = (வெறுமை *) __dest;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 3);
      நிறுத்து;
    நிலை 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((வெறுமை *) __u + 1);
      நிறுத்து;
    நிலை 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((வெறுமை *) __u + 2);
      __u->__uc = '\0';
      நிறுத்து;
    நிலை 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((வெறுமை *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((வெறுமை *) __u + 3);
      நிறுத்து;
    }
  திரும்பு &__u->__c;
}

# இல்லையெனில்

எழுத்து *
__old_stpcpy_small (எழுத்து *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  ஒன்றிப்பு {
    எழுத்து __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (வெறுமை *) __dest;
  தேர்வு ((unsigned முழு) __srclen)
    {
    நிலை 1:
      __u->__c = '\0';
      நிறுத்து;
    நிலை 2:
      __extension__ __u->__sca2 = __src2;
      நிறுத்து;
    நிலை 3:
      __extension__ __u->__sca3 = __src3;
      நிறுத்து;
    நிலை 4:
      __extension__ __u->__sca4 = __src4;
      நிறுத்து;
    நிலை 5:
      __extension__ __u->__sca5 = __src5;
      நிறுத்து;
    நிலை 6:
      __extension__ __u->__sca6 = __src6;
      நிறுத்து;
    நிலை 7:
      __extension__ __u->__sca7 = __src7;
      நிறுத்து;
    நிலை 8:
      __extension__ __u->__sca8 = __src8;
      நிறுத்து;
  }
  திரும்பு __dest + __srclen - 1;
}
# endif
compat_குறியீடு (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
