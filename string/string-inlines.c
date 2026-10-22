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
#include <string.h>

#include "shlib-compat.h"

#nếu SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

char *
__old_strtok_r_1c (char *__s, char __sep, char **__nextp)
{
  char *__result;
  nếu (__s == NULL)
    __s = *__nextp;
  trong_khi (*__s == __sep)
    ++__s;
  __result = NULL;
  nếu (*__s != '\0')
    {
      __result = __s++;
      trong_khi (*__s != '\0')
	nếu (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    break;
	  }
    }
  *__nextp = __s;
  trả_về __result;
}
compat_symbol (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

char *
__old_strsep_1c (char **__s, char __reject)
{
  char *__retval = *__s;
  nếu (__retval != NULL && (*__s = strchr (__retval, __reject)) != NULL)
    *(*__s)++ = '\0';
  trả_về __retval;
}
compat_symbol (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

char *
__old_strsep_2c (char **__s, char __reject1, char __reject2)
{
  char *__retval = *__s;
  nếu (__retval != NULL)
    {
      char *__cp = __retval;
      trong_khi (1)
	{
	  nếu (*__cp == '\0')
	    {
	      __cp = NULL;
	      break;
	    }
	  nếu (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      break;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  trả_về __retval;
}
compat_symbol (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

char *
__old_strsep_3c (char **__s, char __reject1, char __reject2, char __reject3)
{
  char *__retval = *__s;
  nếu (__retval != NULL)
    {
      char *__cp = __retval;
      trong_khi (1)
	{
	  nếu (*__cp == '\0')
	    {
	      __cp = NULL;
	      break;
	    }
	  nếu (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      break;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  trả_về __retval;
}
compat_symbol (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#nếu SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (const char *__s, số_nguyên __reject)
{
  size_t __result = 0;
  trong_khi (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (const char *__s, số_nguyên __reject1, số_nguyên __reject2)
{
  size_t __result = 0;
  trong_khi (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (const char *__s, số_nguyên __reject1, số_nguyên __reject2,
	      số_nguyên __reject3)
{
  size_t __result = 0;
  trong_khi (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (const char *__s, số_nguyên __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  trong_khi (__s[__result] == __accept)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (const char *__s, số_nguyên __accept1, số_nguyên __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  trong_khi (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (const char *__s, số_nguyên __accept1, số_nguyên __accept2,
		 số_nguyên __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  trong_khi (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  trả_về __result;
}
compat_symbol (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

char *
__old_strpbrk_c2 (const char *__s, số_nguyên __accept1, số_nguyên __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  trong_khi (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  trả_về *__s == '\0' ? NULL : (char *) (size_t) __s;
}
compat_symbol (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

char *
__old_strpbrk_c3 (const char *__s, số_nguyên __accept1, số_nguyên __accept2, số_nguyên __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  trong_khi (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  trả_về *__s == '\0' ? NULL : (char *) (size_t) __s;
}
compat_symbol (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# nếu defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# không_thì
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  typedef struct { unsigned char __arr[N]; }				      \
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

# nếu _STRING_INLINE_unaligned
void *
__old_mempcpy_small (void *__dest1,
		     char __src0_1, char __src2_1, char __src4_1, char __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  union {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned char __uc;
    unsigned char __c;
  } *__u = __dest1;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__c = __src0_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 4);
      break;
    }
  trả_về (void *) __u;
}

# không_thì

void *
__old_mempcpy_small (void *__dest, char __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__c = __src1;
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
    }
  trả_về __extension__ ((void *) __u + __srclen);
}
# endif
compat_symbol (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# nếu _STRING_INLINE_unaligned
char *
__old_strcpy_small (char *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  union {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned char __uc;
  } *__u = (void *) __dest;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__uc = '\0';
      break;
    case 2:
      __u->__usi = __src0_2;
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 4:
      __u->__ui = __src0_4;
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      break;
    }
  trả_về __dest;
}

# không_thì

char *
__old_strcpy_small (char *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__c = '\0';
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
  }
  trả_về __dest;
}
# endif
compat_symbol (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# nếu _STRING_INLINE_unaligned
char *
__old_stpcpy_small (char *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  union {
    unsigned số_nguyên __ui;
    unsigned short số_nguyên __usi;
    unsigned char __uc;
    char __c;
  } *__u = (void *) __dest;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__uc = '\0';
      break;
    case 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 3);
      break;
    case 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      break;
    case 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 1);
      break;
    case 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      break;
    case 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 3);
      break;
    }
  trả_về &__u->__c;
}

# không_thì

char *
__old_stpcpy_small (char *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  union {
    char __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned số_nguyên) __srclen)
    {
    case 1:
      __u->__c = '\0';
      break;
    case 2:
      __extension__ __u->__sca2 = __src2;
      break;
    case 3:
      __extension__ __u->__sca3 = __src3;
      break;
    case 4:
      __extension__ __u->__sca4 = __src4;
      break;
    case 5:
      __extension__ __u->__sca5 = __src5;
      break;
    case 6:
      __extension__ __u->__sca6 = __src6;
      break;
    case 7:
      __extension__ __u->__sca7 = __src7;
      break;
    case 8:
      __extension__ __u->__sca8 = __src8;
      break;
  }
  trả_về __dest + __srclen - 1;
}
# endif
compat_symbol (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
