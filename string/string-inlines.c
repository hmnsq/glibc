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

#གལ་སྲིད SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

var_na *
__old_strtok_r_1c (var_na *__s, var_na __sep, var_na **__nextp)
{
  var_na *__result;
  གལ་སྲིད (__s == NULL)
    __s = *__nextp;
  སྐབས (*__s == __sep)
    ++__s;
  __result = NULL;
  གལ་སྲིད (*__s != '\0')
    {
      __result = __s++;
      སྐབས (*__s != '\0')
	གལ་སྲིད (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    bha_nga;
	  }
    }
  *__nextp = __s;
  ལོག __result;
}
compat_symbol (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

var_na *
__old_strsep_1c (var_na **__s, var_na __reject)
{
  var_na *__retval = *__s;
  གལ་སྲིད (__retval != NULL && (*__s = strchr (__retval, __reject)) != NULL)
    *(*__s)++ = '\0';
  ལོག __retval;
}
compat_symbol (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

var_na *
__old_strsep_2c (var_na **__s, var_na __reject1, var_na __reject2)
{
  var_na *__retval = *__s;
  གལ་སྲིད (__retval != NULL)
    {
      var_na *__cp = __retval;
      སྐབས (1)
	{
	  གལ་སྲིད (*__cp == '\0')
	    {
	      __cp = NULL;
	      bha_nga;
	    }
	  གལ་སྲིད (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      bha_nga;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ལོག __retval;
}
compat_symbol (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

var_na *
__old_strsep_3c (var_na **__s, var_na __reject1, var_na __reject2, var_na __reject3)
{
  var_na *__retval = *__s;
  གལ་སྲིད (__retval != NULL)
    {
      var_na *__cp = __retval;
      སྐབས (1)
	{
	  གལ་སྲིད (*__cp == '\0')
	    {
	      __cp = NULL;
	      bha_nga;
	    }
	  གལ་སྲིད (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      bha_nga;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  ལོག __retval;
}
compat_symbol (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#གལ་སྲིད SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

size_t
__old_strcspn_c1 (const var_na *__s, ཧྲིལ __reject)
{
  size_t __result = 0;
  སྐབས (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

size_t
__old_strcspn_c2 (const var_na *__s, ཧྲིལ __reject1, ཧྲིལ __reject2)
{
  size_t __result = 0;
  སྐབས (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

size_t
__old_strcspn_c3 (const var_na *__s, ཧྲིལ __reject1, ཧྲིལ __reject2,
	      ཧྲིལ __reject3)
{
  size_t __result = 0;
  སྐབས (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

size_t
__old_strspn_c1 (const var_na *__s, ཧྲིལ __accept)
{
  size_t __result = 0;
  /* Please note that __accept never can be '\0'.  */
  སྐབས (__s[__result] == __accept)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

size_t
__old_strspn_c2 (const var_na *__s, ཧྲིལ __accept1, ཧྲིལ __accept2)
{
  size_t __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  སྐབས (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

size_t
__old_strspn_c3 (const var_na *__s, ཧྲིལ __accept1, ཧྲིལ __accept2,
		 ཧྲིལ __accept3)
{
  size_t __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  སྐབས (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  ལོག __result;
}
compat_symbol (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

var_na *
__old_strpbrk_c2 (const var_na *__s, ཧྲིལ __accept1, ཧྲིལ __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  སྐབས (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  ལོག *__s == '\0' ? NULL : (var_na *) (size_t) __s;
}
compat_symbol (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

var_na *
__old_strpbrk_c3 (const var_na *__s, ཧྲིལ __accept1, ཧྲིལ __accept2, ཧྲིལ __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  སྐབས (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  ལོག *__s == '\0' ? NULL : (var_na *) (size_t) __s;
}
compat_symbol (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# གལ་སྲིད defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# དེ་མིན
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  typedef sa_nracanaa { unsigned var_na __arr[N]; }				      \
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

# གལ་སྲིད _STRING_INLINE_unaligned
void *
__old_mempcpy_small (void *__dest1,
		     var_na __src0_1, var_na __src2_1, var_na __src4_1, var_na __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     size_t __srclen)
{
  sa_ngha {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned var_na __uc;
    unsigned var_na __c;
  } *__u = __dest1;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__c = __src0_1;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      bha_nga;
    pak_sa 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      bha_nga;
    pak_sa 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      bha_nga;
    pak_sa 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 4);
      bha_nga;
    }
  ལོག (void *) __u;
}

# དེ་མིན

void *
__old_mempcpy_small (void *__dest, var_na __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  sa_ngha {
    var_na __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__c = __src1;
      bha_nga;
    pak_sa 2:
      __extension__ __u->__sca2 = __src2;
      bha_nga;
    pak_sa 3:
      __extension__ __u->__sca3 = __src3;
      bha_nga;
    pak_sa 4:
      __extension__ __u->__sca4 = __src4;
      bha_nga;
    pak_sa 5:
      __extension__ __u->__sca5 = __src5;
      bha_nga;
    pak_sa 6:
      __extension__ __u->__sca6 = __src6;
      bha_nga;
    pak_sa 7:
      __extension__ __u->__sca7 = __src7;
      bha_nga;
    pak_sa 8:
      __extension__ __u->__sca8 = __src8;
      bha_nga;
    }
  ལོག __extension__ ((void *) __u + __srclen);
}
# endif
compat_symbol (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# གལ་སྲིད _STRING_INLINE_unaligned
var_na *
__old_strcpy_small (var_na *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  sa_ngha {
    __uint32_t __ui;
    __uint16_t __usi;
    unsigned var_na __uc;
  } *__u = (void *) __dest;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__uc = '\0';
      bha_nga;
    pak_sa 2:
      __u->__usi = __src0_2;
      bha_nga;
    pak_sa 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 4:
      __u->__ui = __src0_4;
      bha_nga;
    pak_sa 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      bha_nga;
    pak_sa 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      bha_nga;
    }
  ལོག __dest;
}

# དེ་མིན

var_na *
__old_strcpy_small (var_na *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  sa_ngha {
    var_na __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__c = '\0';
      bha_nga;
    pak_sa 2:
      __extension__ __u->__sca2 = __src2;
      bha_nga;
    pak_sa 3:
      __extension__ __u->__sca3 = __src3;
      bha_nga;
    pak_sa 4:
      __extension__ __u->__sca4 = __src4;
      bha_nga;
    pak_sa 5:
      __extension__ __u->__sca5 = __src5;
      bha_nga;
    pak_sa 6:
      __extension__ __u->__sca6 = __src6;
      bha_nga;
    pak_sa 7:
      __extension__ __u->__sca7 = __src7;
      bha_nga;
    pak_sa 8:
      __extension__ __u->__sca8 = __src8;
      bha_nga;
  }
  ལོག __dest;
}
# endif
compat_symbol (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# གལ་སྲིད _STRING_INLINE_unaligned
var_na *
__old_stpcpy_small (var_na *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    size_t __srclen)
{
  sa_ngha {
    unsigned ཧྲིལ __ui;
    unsigned short ཧྲིལ __usi;
    unsigned var_na __uc;
    var_na __c;
  } *__u = (void *) __dest;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__uc = '\0';
      bha_nga;
    pak_sa 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 3);
      bha_nga;
    pak_sa 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 1);
      bha_nga;
    pak_sa 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((void *) __u + 2);
      __u->__uc = '\0';
      bha_nga;
    pak_sa 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((void *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((void *) __u + 3);
      bha_nga;
    }
  ལོག &__u->__c;
}

# དེ་མིན

var_na *
__old_stpcpy_small (var_na *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, size_t __srclen)
{
  sa_ngha {
    var_na __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (void *) __dest;
  switch ((unsigned ཧྲིལ) __srclen)
    {
    pak_sa 1:
      __u->__c = '\0';
      bha_nga;
    pak_sa 2:
      __extension__ __u->__sca2 = __src2;
      bha_nga;
    pak_sa 3:
      __extension__ __u->__sca3 = __src3;
      bha_nga;
    pak_sa 4:
      __extension__ __u->__sca4 = __src4;
      bha_nga;
    pak_sa 5:
      __extension__ __u->__sca5 = __src5;
      bha_nga;
    pak_sa 6:
      __extension__ __u->__sca6 = __src6;
      bha_nga;
    pak_sa 7:
      __extension__ __u->__sca7 = __src7;
      bha_nga;
    pak_sa 8:
      __extension__ __u->__sca8 = __src8;
      bha_nga;
  }
  ལོག __dest + __srclen - 1;
}
# endif
compat_symbol (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
