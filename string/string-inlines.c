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

#जर SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_25)
/* These functions were removed from string.h in glibc 2.25.  */

अक्षर *
__old_strtok_r_1c (अक्षर *__s, अक्षर __sep, अक्षर **__nextp)
{
  अक्षर *__result;
  जर (__s == रिक्त)
    __s = *__nextp;
  पर्यंत (*__s == __sep)
    ++__s;
  __result = रिक्त;
  जर (*__s != '\0')
    {
      __result = __s++;
      पर्यंत (*__s != '\0')
	जर (*__s++ == __sep)
	  {
	    __s[-1] = '\0';
	    थांबा;
	  }
    }
  *__nextp = __s;
  परत __result;
}
compat_चिन्ह (libc, __old_strtok_r_1c, __strtok_r_1c, GLIBC_2_1_1);

अक्षर *
__old_strsep_1c (अक्षर **__s, अक्षर __reject)
{
  अक्षर *__retval = *__s;
  जर (__retval != रिक्त && (*__s = म_अक्षर (__retval, __reject)) != रिक्त)
    *(*__s)++ = '\0';
  परत __retval;
}
compat_चिन्ह (libc, __old_strsep_1c, __strsep_1c, GLIBC_2_1_1);

अक्षर *
__old_strsep_2c (अक्षर **__s, अक्षर __reject1, अक्षर __reject2)
{
  अक्षर *__retval = *__s;
  जर (__retval != रिक्त)
    {
      अक्षर *__cp = __retval;
      पर्यंत (1)
	{
	  जर (*__cp == '\0')
	    {
	      __cp = रिक्त;
	      थांबा;
	    }
	  जर (*__cp == __reject1 || *__cp == __reject2)
	    {
	      *__cp++ = '\0';
	      थांबा;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  परत __retval;
}
compat_चिन्ह (libc, __old_strsep_2c, __strsep_2c, GLIBC_2_1_1);

अक्षर *
__old_strsep_3c (अक्षर **__s, अक्षर __reject1, अक्षर __reject2, अक्षर __reject3)
{
  अक्षर *__retval = *__s;
  जर (__retval != रिक्त)
    {
      अक्षर *__cp = __retval;
      पर्यंत (1)
	{
	  जर (*__cp == '\0')
	    {
	      __cp = रिक्त;
	      थांबा;
	    }
	  जर (*__cp == __reject1 || *__cp == __reject2 || *__cp == __reject3)
	    {
	      *__cp++ = '\0';
	      थांबा;
	    }
	  ++__cp;
	}
      *__s = __cp;
    }
  परत __retval;
}
compat_चिन्ह (libc, __old_strsep_3c, __strsep_3c, GLIBC_2_1_1);
#endif

#जर SHLIB_COMPAT (libc, GLIBC_2_1_1, GLIBC_2_24)
/* These functions were removed from string.h in glibc 2.24.  */

माप_प्रकार
__old_strcspn_c1 (स्थिरांक अक्षर *__s, पूर्णांक __reject)
{
  माप_प्रकार __result = 0;
  पर्यंत (__s[__result] != '\0' && __s[__result] != __reject)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strcspn_c1, __strcspn_c1, GLIBC_2_1_1);

माप_प्रकार
__old_strcspn_c2 (स्थिरांक अक्षर *__s, पूर्णांक __reject1, पूर्णांक __reject2)
{
  माप_प्रकार __result = 0;
  पर्यंत (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strcspn_c2, __strcspn_c2, GLIBC_2_1_1);

माप_प्रकार
__old_strcspn_c3 (स्थिरांक अक्षर *__s, पूर्णांक __reject1, पूर्णांक __reject2,
	      पूर्णांक __reject3)
{
  माप_प्रकार __result = 0;
  पर्यंत (__s[__result] != '\0' && __s[__result] != __reject1
	 && __s[__result] != __reject2 && __s[__result] != __reject3)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strcspn_c3, __strcspn_c3, GLIBC_2_1_1);

माप_प्रकार
__old_strspn_c1 (स्थिरांक अक्षर *__s, पूर्णांक __accept)
{
  माप_प्रकार __result = 0;
  /* Please note that __accept never can be '\0'.  */
  पर्यंत (__s[__result] == __accept)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strspn_c1, __strspn_c1, GLIBC_2_1_1);

माप_प्रकार
__old_strspn_c2 (स्थिरांक अक्षर *__s, पूर्णांक __accept1, पूर्णांक __accept2)
{
  माप_प्रकार __result = 0;
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  पर्यंत (__s[__result] == __accept1 || __s[__result] == __accept2)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strspn_c2, __strspn_c2, GLIBC_2_1_1);

माप_प्रकार
__old_strspn_c3 (स्थिरांक अक्षर *__s, पूर्णांक __accept1, पूर्णांक __accept2,
		 पूर्णांक __accept3)
{
  माप_प्रकार __result = 0;
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  पर्यंत (__s[__result] == __accept1 || __s[__result] == __accept2
	 || __s[__result] == __accept3)
    ++__result;
  परत __result;
}
compat_चिन्ह (libc, __old_strspn_c3, __strspn_c3, GLIBC_2_1_1);

अक्षर *
__old_strpbrk_c2 (स्थिरांक अक्षर *__s, पूर्णांक __accept1, पूर्णांक __accept2)
{
  /* Please note that __accept1 and __accept2 never can be '\0'.  */
  पर्यंत (*__s != '\0' && *__s != __accept1 && *__s != __accept2)
    ++__s;
  परत *__s == '\0' ? रिक्त : (अक्षर *) (माप_प्रकार) __s;
}
compat_चिन्ह (libc, __old_strpbrk_c2, __strpbrk_c2, GLIBC_2_1_1);

अक्षर *
__old_strpbrk_c3 (स्थिरांक अक्षर *__s, पूर्णांक __accept1, पूर्णांक __accept2, पूर्णांक __accept3)
{
  /* Please note that __accept1 to __accept3 never can be '\0'.  */
  पर्यंत (*__s != '\0' && *__s != __accept1 && *__s != __accept2
	 && *__s != __accept3)
    ++__s;
  परत *__s == '\0' ? रिक्त : (अक्षर *) (माप_प्रकार) __s;
}
compat_चिन्ह (libc, __old_strpbrk_c3, __strpbrk_c3, GLIBC_2_1_1);

# जर defined __mc68020__ || defined __s390__ || defined __i386__
#  define _STRING_INLINE_unaligned 1
# अन्यथा
#  define _STRING_INLINE_unaligned 0
/* These are a few types we need for the optimizations if we cannot
   use unaligned memory accesses.  */
#  define __STRING2_COPY_TYPE(N) \
  प्रकारव्याख्या संरचना { अचिन्हित अक्षर __arr[N]; }				      \
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

# जर _STRING_INLINE_unaligned
शून्य *
__old_mempcpy_small (शून्य *__dest1,
		     अक्षर __src0_1, अक्षर __src2_1, अक्षर __src4_1, अक्षर __src6_1,
		     __uint16_t __src0_2, __uint16_t __src4_2,
		     __uint32_t __src0_4, __uint32_t __src4_4,
		     माप_प्रकार __srclen)
{
  संघ {
    __uint32_t __ui;
    __uint16_t __usi;
    अचिन्हित अक्षर __uc;
    अचिन्हित अक्षर __c;
  } *__u = __dest1;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__c = __src0_1;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      थांबा;
    स्थिती 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__c = __src2_1;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      थांबा;
    स्थिती 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__c = __src4_1;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      थांबा;
    स्थिती 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__c = __src6_1;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((शून्य *) __u + 4);
      थांबा;
    }
  परत (शून्य *) __u;
}

# अन्यथा

शून्य *
__old_mempcpy_small (शून्य *__dest, अक्षर __src1,
		     __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		     __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		     __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		     __STRING2_COPY_ARR8 __src8, माप_प्रकार __srclen)
{
  संघ {
    अक्षर __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = __dest;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__c = __src1;
      थांबा;
    स्थिती 2:
      __extension__ __u->__sca2 = __src2;
      थांबा;
    स्थिती 3:
      __extension__ __u->__sca3 = __src3;
      थांबा;
    स्थिती 4:
      __extension__ __u->__sca4 = __src4;
      थांबा;
    स्थिती 5:
      __extension__ __u->__sca5 = __src5;
      थांबा;
    स्थिती 6:
      __extension__ __u->__sca6 = __src6;
      थांबा;
    स्थिती 7:
      __extension__ __u->__sca7 = __src7;
      थांबा;
    स्थिती 8:
      __extension__ __u->__sca8 = __src8;
      थांबा;
    }
  परत __extension__ ((शून्य *) __u + __srclen);
}
# endif
compat_चिन्ह (libc, __old_mempcpy_small, __mempcpy_small, GLIBC_2_1_1);

# जर _STRING_INLINE_unaligned
अक्षर *
__old_strcpy_small (अक्षर *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    माप_प्रकार __srclen)
{
  संघ {
    __uint32_t __ui;
    __uint16_t __usi;
    अचिन्हित अक्षर __uc;
  } *__u = (शून्य *) __dest;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__uc = '\0';
      थांबा;
    स्थिती 2:
      __u->__usi = __src0_2;
      थांबा;
    स्थिती 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      थांबा;
    स्थिती 4:
      __u->__ui = __src0_4;
      थांबा;
    स्थिती 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__uc = '\0';
      थांबा;
    स्थिती 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      थांबा;
    स्थिती 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      थांबा;
    स्थिती 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      थांबा;
    }
  परत __dest;
}

# अन्यथा

अक्षर *
__old_strcpy_small (अक्षर *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, माप_प्रकार __srclen)
{
  संघ {
    अक्षर __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (शून्य *) __dest;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__c = '\0';
      थांबा;
    स्थिती 2:
      __extension__ __u->__sca2 = __src2;
      थांबा;
    स्थिती 3:
      __extension__ __u->__sca3 = __src3;
      थांबा;
    स्थिती 4:
      __extension__ __u->__sca4 = __src4;
      थांबा;
    स्थिती 5:
      __extension__ __u->__sca5 = __src5;
      थांबा;
    स्थिती 6:
      __extension__ __u->__sca6 = __src6;
      थांबा;
    स्थिती 7:
      __extension__ __u->__sca7 = __src7;
      थांबा;
    स्थिती 8:
      __extension__ __u->__sca8 = __src8;
      थांबा;
  }
  परत __dest;
}
# endif
compat_चिन्ह (libc, __old_strcpy_small, __strcpy_small, GLIBC_2_1_1);

# जर _STRING_INLINE_unaligned
अक्षर *
__old_stpcpy_small (अक्षर *__dest,
		    __uint16_t __src0_2, __uint16_t __src4_2,
		    __uint32_t __src0_4, __uint32_t __src4_4,
		    माप_प्रकार __srclen)
{
  संघ {
    अचिन्हित पूर्णांक __ui;
    अचिन्हित लघु पूर्णांक __usi;
    अचिन्हित अक्षर __uc;
    अक्षर __c;
  } *__u = (शून्य *) __dest;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__uc = '\0';
      थांबा;
    स्थिती 2:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 3:
      __u->__usi = __src0_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      थांबा;
    स्थिती 4:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 3);
      थांबा;
    स्थिती 5:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__uc = '\0';
      थांबा;
    स्थिती 6:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 1);
      थांबा;
    स्थिती 7:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__usi = __src4_2;
      __u = __extension__ ((शून्य *) __u + 2);
      __u->__uc = '\0';
      थांबा;
    स्थिती 8:
      __u->__ui = __src0_4;
      __u = __extension__ ((शून्य *) __u + 4);
      __u->__ui = __src4_4;
      __u = __extension__ ((शून्य *) __u + 3);
      थांबा;
    }
  परत &__u->__c;
}

# अन्यथा

अक्षर *
__old_stpcpy_small (अक्षर *__dest,
		    __STRING2_COPY_ARR2 __src2, __STRING2_COPY_ARR3 __src3,
		    __STRING2_COPY_ARR4 __src4, __STRING2_COPY_ARR5 __src5,
		    __STRING2_COPY_ARR6 __src6, __STRING2_COPY_ARR7 __src7,
		    __STRING2_COPY_ARR8 __src8, माप_प्रकार __srclen)
{
  संघ {
    अक्षर __c;
    __STRING2_COPY_ARR2 __sca2;
    __STRING2_COPY_ARR3 __sca3;
    __STRING2_COPY_ARR4 __sca4;
    __STRING2_COPY_ARR5 __sca5;
    __STRING2_COPY_ARR6 __sca6;
    __STRING2_COPY_ARR7 __sca7;
    __STRING2_COPY_ARR8 __sca8;
  } *__u = (शून्य *) __dest;
  निवड ((अचिन्हित पूर्णांक) __srclen)
    {
    स्थिती 1:
      __u->__c = '\0';
      थांबा;
    स्थिती 2:
      __extension__ __u->__sca2 = __src2;
      थांबा;
    स्थिती 3:
      __extension__ __u->__sca3 = __src3;
      थांबा;
    स्थिती 4:
      __extension__ __u->__sca4 = __src4;
      थांबा;
    स्थिती 5:
      __extension__ __u->__sca5 = __src5;
      थांबा;
    स्थिती 6:
      __extension__ __u->__sca6 = __src6;
      थांबा;
    स्थिती 7:
      __extension__ __u->__sca7 = __src7;
      थांबा;
    स्थिती 8:
      __extension__ __u->__sca8 = __src8;
      थांबा;
  }
  परत __dest + __srclen - 1;
}
# endif
compat_चिन्ह (libc, __old_stpcpy_small, __stpcpy_small, GLIBC_2_1_1);

#endif
