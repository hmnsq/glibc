/* Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#अगर_अघोषित	_STRINGS_H
#घोषणा	_STRINGS_H	1

#समावेश <features.h>
#घोषणा __need_size_t
#समावेश <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#अगर defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#पूर्ण_अगर

__BEGIN_DECLS

#अगर defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
बाह्य पूर्णांक bcmp (स्थिर व्योम *__s1, स्थिर व्योम *__s2, माप_प्रकार __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
बाह्य व्योम bcopy (स्थिर व्योम *__src, व्योम *__dest, माप_प्रकार __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
बाह्य व्योम bzero (व्योम *__s, माप_प्रकार __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *सूचकांक (अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
बाह्य स्थिर अक्षर *सूचकांक (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  अगर defined __OPTIMIZE__
__extern_always_inline अक्षर *
सूचकांक (अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_index (__s, __c);
}

__extern_always_inline स्थिर अक्षर *
सूचकांक (स्थिर अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_index (__s, __c);
}
#  endif
}
# अन्यथा
बाह्य अक्षर *सूचकांक (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *rindex (अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
बाह्य स्थिर अक्षर *rindex (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  अगर defined __OPTIMIZE__
__extern_always_inline अक्षर *
rindex (अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_rindex (__s, __c);
}

__extern_always_inline स्थिर अक्षर *
rindex (स्थिर अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_rindex (__s, __c);
}
#  endif
}
# अन्यथा
बाह्य अक्षर *rindex (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#पूर्ण_अगर

#अगर defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
बाह्य पूर्णांक ffs (पूर्णांक __i) __THROW __attribute_const__;
#पूर्ण_अगर

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
बाह्य पूर्णांक ffsl (दीर्घ पूर्णांक __l) __THROW __attribute_const__;
__extension__ बाह्य पूर्णांक ffsll (दीर्घ दीर्घ पूर्णांक __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
बाह्य पूर्णांक strcasecmp (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
बाह्य पूर्णांक strncasecmp (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2, माप_प्रकार __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#अगर_घोषित	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
बाह्य पूर्णांक strcasecmp_l (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
बाह्य पूर्णांक strncasecmp_l (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2,
			  माप_प्रकार __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#पूर्ण_अगर

__END_DECLS

#अगर __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# अगर defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#पूर्ण_अगर

#पूर्ण_अगर	/* strings.h  */
