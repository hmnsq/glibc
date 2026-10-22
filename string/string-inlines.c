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
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "shlib-compat.h"

#എങ്കിൽ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

അക്ഷരം *
__old_strtok_r_1c (അക്ഷരം *__s, അക്ഷരം __sep, അക്ഷരം **__nextp)
{
  അക്ഷരം *__result;
  എങ്കിൽ (__s == ശൂന്യ)
    __s = *__nextp;
  ആകുമ്പോൾ (*__s == __sep)
    ++__s;
  __result = ശൂന്യ;
  എങ്കിൽ (*__s != '\0')
    {
      __result = __s++;
      ആകുമ്പോൾ (*__s != '\0')
	എങ്കിൽ (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    നിർത്തുക;
	  }
    }
  *__nextp = __s;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

അക്ഷരം *
__old_strsep_1c (അക്ഷരം **__s, അക്ഷരം __reject)
{
  അക്ഷരം *__retval = *__s;
  എങ്കിൽ (__retval != ശൂന്യ && (*__s = strchr (__retval, __reject)) != ശൂന്യ)
    *(*__s)++ = '\0';
  തിരികെ __retval;
}
compat_ചിഹ്നം (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

അക്ഷരം *
__old_strsep_2c (അക്ഷരം **__s, അക്ഷരം __reject1, അക്ഷരം __reject2)
{
  അക്ഷരം *__retval = *__s;
  എങ്കിൽ (__retval != ശൂന്യ)
    {
      അക്ഷരം *__cp = __retval;
      ആകുമ്പോൾ (1)
	{
	  എങ്കിൽ (*__cp == '\0')
	    {
	      __cp = ശൂന്യ;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      നിർത്തുക;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  തിരികെ __retval;
}
compat_ചിഹ്നം (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

അക്ഷരം *
__old_strsep_3c (അക്ഷരം **__s, അക്ഷരം __reject1, അക്ഷരം __reject2, അക്ഷരം __reject3)
{
  അക്ഷരം *__retval = *__s;
  എങ്കിൽ (__retval != ശൂന്യ)
    {
      അക്ഷരം *__cp = __retval;
      ആകുമ്പോൾ (1)
	{
	  എങ്കിൽ (*__cp == '\0')
	    {
	      __cp = ശൂന്യ;
	      നിർത്തുക;
	    }
	  എങ്കിൽ (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      നിർത്തുക;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  തിരികെ __retval;
}
compat_ചിഹ്നം (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#എങ്കിൽ SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __reject)
{
  size_t __result = 0;
  ആകുമ്പോൾ (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __reject1, പൂർണ്ണസംഖ്യ __reject2)
{
  size_t __result = 0;
  ആകുമ്പോൾ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __reject1, പൂർണ്ണസംഖ്യ __reject2,
	      പൂർണ്ണസംഖ്യ __reject3)
{
  size_t __result = 0;
  ആകുമ്പോൾ (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  ആകുമ്പോൾ (__s[__result] == __accept)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __accept1, പൂർണ്ണസംഖ്യ __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ആകുമ്പോൾ (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __accept1, പൂർണ്ണസംഖ്യ __accept2,
		 പൂർണ്ണസംഖ്യ __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ആകുമ്പോൾ (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  തിരികെ __result;
}
compat_ചിഹ്നം (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

അക്ഷരം *
__old_strpbrk_c2 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __accept1, പൂർണ്ണസംഖ്യ __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  ആകുമ്പോൾ (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  തിരികെ *__s == '\0' ? ശൂന്യ : (അക്ഷരം *) (size_t) __s;
}
compat_ചിഹ്നം (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

അക്ഷരം *
__old_strpbrk_c3 (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __accept1, പൂർണ്ണസംഖ്യ __accept2, പൂർണ്ണസംഖ്യ __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  ആകുമ്പോൾ (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  തിരികെ *__s == '\0' ? ശൂന്യ : (അക്ഷരം *) (size_t) __s;
}
compat_ചിഹ്നം (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# എങ്കിൽ defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# അല്ലെങ്കിൽ
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  തരനിർവചനം ഘടന { unsigned അക്ഷരം __arr[N]; }				      \
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

# എങ്കിൽ _STRING_INLINE_unaligned
ശൂന്യം *
__old_mempcpy_small (ശൂന്യം *__dest1,
		     അക്ഷരം __src0_1, അക്ഷരം __src2_1, അക്ഷരം __src4_1, അക്ഷരം __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  സംഘം {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned അക്ഷരം __uc;
    unsigned അക്ഷരം __c;
  } *__u = __dest1;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__c = __src0_1;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      നിർത്തുക;
    അവസ്ഥ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      നിർത്തുക;
    അവസ്ഥ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      നിർത്തുക;
    അവസ്ഥ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      നിർത്തുക;
    }
  തിരികെ (ശൂന്യം *) __u;
}

# അല്ലെങ്കിൽ

ശൂന്യം *
__old_mempcpy_small (ശൂന്യം *__dest, അക്ഷരം __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  സംഘം {
    അക്ഷരം __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__c = __src1;
      നിർത്തുക;
    അവസ്ഥ 2:
      __extension__ __u->__sca2 = __src2;
      നിർത്തുക;
    അവസ്ഥ 3:
      __extension__ __u->__sca3 = __src3;
      നിർത്തുക;
    അവസ്ഥ 4:
      __extension__ __u->__sca4 = __src4;
      നിർത്തുക;
    അവസ്ഥ 5:
      __extension__ __u->__sca5 = __src5;
      നിർത്തുക;
    അവസ്ഥ 6:
      __extension__ __u->__sca6 = __src6;
      നിർത്തുക;
    അവസ്ഥ 7:
      __extension__ __u->__sca7 = __src7;
      നിർത്തുക;
    അവസ്ഥ 8:
      __extension__ __u->__sca8 = __src8;
      നിർത്തുക;
    }
  തിരികെ __extension__ ((ശൂന്യം *) __u + __srclen);
}
# endif
compat_ചിഹ്നം (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# എങ്കിൽ _STRING_INLINE_unaligned
അക്ഷരം *
__old_strcpy_small (അക്ഷരം *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  സംഘം {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned അക്ഷരം __uc;
  } *__u = (ശൂന്യം *) __dest;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 2:
      __u->__usi = __src0_2;
      നിർത്തുക;
    അവസ്ഥ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 4:
      __u->__ui = __src0_4;
      നിർത്തുക;
    അവസ്ഥ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      നിർത്തുക;
    അവസ്ഥ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__ui = __src4_4;
      നിർത്തുക;
    }
  തിരികെ __dest;
}

# അല്ലെങ്കിൽ

അക്ഷരം *
__old_strcpy_small (അക്ഷരം *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  സംഘം {
    അക്ഷരം __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ശൂന്യം *) __dest;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__c = '\0';
      നിർത്തുക;
    അവസ്ഥ 2:
      __extension__ __u->__sca2 = __src2;
      നിർത്തുക;
    അവസ്ഥ 3:
      __extension__ __u->__sca3 = __src3;
      നിർത്തുക;
    അവസ്ഥ 4:
      __extension__ __u->__sca4 = __src4;
      നിർത്തുക;
    അവസ്ഥ 5:
      __extension__ __u->__sca5 = __src5;
      നിർത്തുക;
    അവസ്ഥ 6:
      __extension__ __u->__sca6 = __src6;
      നിർത്തുക;
    അവസ്ഥ 7:
      __extension__ __u->__sca7 = __src7;
      നിർത്തുക;
    അവസ്ഥ 8:
      __extension__ __u->__sca8 = __src8;
      നിർത്തുക;
  }
  തിരികെ __dest;
}
# endif
compat_ചിഹ്നം (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# എങ്കിൽ _STRING_INLINE_unaligned
അക്ഷരം *
__old_stpcpy_small (അക്ഷരം *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  സംഘം {
    unsigned പൂർണ്ണസംഖ്യ __ui;
    unsigned short പൂർണ്ണസംഖ്യ __usi;
    unsigned അക്ഷരം __uc;
    അക്ഷരം __c;
  } *__u = (ശൂന്യം *) __dest;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 3);
      നിർത്തുക;
    അവസ്ഥ 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ശൂന്യം *) __u + 1);
      നിർത്തുക;
    അവസ്ഥ 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((ശൂന്യം *) __u + 2);
      __u->__uc = '\0';
      നിർത്തുക;
    അവസ്ഥ 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((ശൂന്യം *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((ശൂന്യം *) __u + 3);
      നിർത്തുക;
    }
  തിരികെ &__u->__c;
}

# അല്ലെങ്കിൽ

അക്ഷരം *
__old_stpcpy_small (അക്ഷരം *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  സംഘം {
    അക്ഷരം __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (ശൂന്യം *) __dest;
  തിരഞ്ഞെടുപ്പ് ((unsigned പൂർണ്ണസംഖ്യ) __srclen)
    {
    അവസ്ഥ 1:
      __u->__c = '\0';
      നിർത്തുക;
    അവസ്ഥ 2:
      __extension__ __u->__sca2 = __src2;
      നിർത്തുക;
    അവസ്ഥ 3:
      __extension__ __u->__sca3 = __src3;
      നിർത്തുക;
    അവസ്ഥ 4:
      __extension__ __u->__sca4 = __src4;
      നിർത്തുക;
    അവസ്ഥ 5:
      __extension__ __u->__sca5 = __src5;
      നിർത്തുക;
    അവസ്ഥ 6:
      __extension__ __u->__sca6 = __src6;
      നിർത്തുക;
    അവസ്ഥ 7:
      __extension__ __u->__sca7 = __src7;
      നിർത്തുക;
    അവസ്ഥ 8:
      __extension__ __u->__sca8 = __src8;
      നിർത്തുക;
  }
  തിരികെ __dest + __srclen - 1;
}
# endif
compat_ചിഹ്നം (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
