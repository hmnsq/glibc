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

/*
 *	ISO C99 Standard: 7.21 String handling	<string.h>
 */

#अगर_अघोषित	_STRING_H
#घोषणा	_STRING_H	1

#घोषणा __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#समावेश <bits/libc-header-start.h>

__BEGIN_DECLS

#अगर __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#पूर्ण_अगर

/* Get size_t and NULL from <stddef.h>.  */
#घोषणा	__need_size_t
#घोषणा	__need_NULL
#समावेश <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#अगर defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#पूर्ण_अगर


/* Copy N bytes of SRC to DEST.  */
बाह्य व्योम *स_नकल (व्योम *__restrict __dest, स्थिर व्योम *__restrict __src,
		     माप_प्रकार __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
बाह्य व्योम *स_हटाओ (व्योम *__dest, स्थिर व्योम *__src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#अगर defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
बाह्य व्योम *memccpy (व्योम *__restrict __dest, स्थिर व्योम *__restrict __src,
		      पूर्णांक __c, माप_प्रकार __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#पूर्ण_अगर /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
बाह्य व्योम *स_रखो (व्योम *__s, पूर्णांक __c, माप_प्रकार __n) __THROW __nonnull ((1));

#अगर defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
बाह्य व्योम *memset_explicit (व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#पूर्ण_अगर

/* Compare N bytes of S1 and S2.  */
बाह्य पूर्णांक स_भेद (स्थिर व्योम *__s1, स्थिर व्योम *__s2, माप_प्रकार __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare N bytes of S1 and S2.  Return zero if S1 and S2 are equal.
   Return some non-zero value otherwise.

   Essentially __memcmpeq has the exact same semantics as memcmp
   except the return value is less constrained.  memcmp is always a
   correct implementation of __memcmpeq.  As well !!memcmp, -memcmp,
   or bcmp are correct implementations.

   __memcmpeq is meant to be used by compilers when memcmp return is
   only used for its boolean value.

   __memcmpeq is declared only for use by compilers.  Programs should
   continue to use memcmp.  */
बाह्य पूर्णांक __memcmpeq (स्थिर व्योम *__s1, स्थिर व्योम *__s2, माप_प्रकार __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#अगर_घोषित __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य व्योम *स_प्रथम (व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
बाह्य स्थिर व्योम *स_प्रथम (स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline व्योम *
स_प्रथम (व्योम *__s, पूर्णांक __c, माप_प्रकार __n) __THROW
{
  वापस __builtin_memchr (__s, __c, __n);
}

__extern_always_inline स्थिर व्योम *
स_प्रथम (स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n) __THROW
{
  वापस __builtin_memchr (__s, __c, __n);
}
# endif
}
#अन्यथा
बाह्य व्योम *स_प्रथम (स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __attribute_pure__ __nonnull ((1));
# अगर __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define स_प्रथम(S, C, N)					\
  __glibc_const_generic (S, स्थिर व्योम *, स_प्रथम (S, C, N))
# endif
#पूर्ण_अगर

#अगर_घोषित __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" व्योम *rawmemchr (व्योम *__s, पूर्णांक __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
बाह्य "C++" स्थिर व्योम *rawmemchr (स्थिर व्योम *__s, पूर्णांक __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# अन्यथा
बाह्य व्योम *rawmemchr (स्थिर व्योम *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" व्योम *memrchr (व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
बाह्य "C++" स्थिर व्योम *memrchr (स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# अन्यथा
बाह्य व्योम *memrchr (स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#पूर्ण_अगर


/* Copy SRC to DEST.  */
बाह्य अक्षर *म_नकल (अक्षर *__restrict __dest, स्थिर अक्षर *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
बाह्य अक्षर *म_नकलन (अक्षर *__restrict __dest,
		      स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
बाह्य अक्षर *म_जोड़ो (अक्षर *__restrict __dest, स्थिर अक्षर *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
बाह्य अक्षर *म_जोड़न (अक्षर *__restrict __dest, स्थिर अक्षर *__restrict __src,
		      माप_प्रकार __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
बाह्य पूर्णांक म_भेद (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
बाह्य पूर्णांक म_भेदन (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2, माप_प्रकार __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
बाह्य पूर्णांक strcoll (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
बाह्य माप_प्रकार strxfrm (अक्षर *__restrict __dest,
		       स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#अगर_घोषित __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
बाह्य पूर्णांक strcoll_l (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
बाह्य माप_प्रकार strxfrm_l (अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#पूर्ण_अगर

#अगर (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
बाह्य अक्षर *strdup (स्थिर अक्षर *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#पूर्ण_अगर

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#अगर defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
बाह्य अक्षर *strndup (स्थिर अक्षर *__string, माप_प्रकार __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#पूर्ण_अगर

#अगर defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      स्थिर अक्षर *__old = (s);						      \
      माप_प्रकार __len = म_माप (__old) + 1;				      \
      अक्षर *__new = (अक्षर *) __builtin_alloca (__len);			      \
      (अक्षर *) स_नकल (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      स्थिर अक्षर *__old = (s);						      \
      माप_प्रकार __len = strnlen (__old, (n));				      \
      अक्षर *__new = (अक्षर *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (अक्षर *) स_नकल (__new, __old, __len);				      \
    }))
#पूर्ण_अगर

/* Find the first occurrence of C in S.  */
#अगर_घोषित __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *म_अक्षर (अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
बाह्य स्थिर अक्षर *म_अक्षर (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline अक्षर *
म_अक्षर (अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_strchr (__s, __c);
}

__extern_always_inline स्थिर अक्षर *
म_अक्षर (स्थिर अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_strchr (__s, __c);
}
# endif
}
#अन्यथा
बाह्य अक्षर *म_अक्षर (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# अगर __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define म_अक्षर(S, C)						\
  __glibc_const_generic (S, स्थिर अक्षर *, म_अक्षर (S, C))
# endif
#पूर्ण_अगर
/* Find the last occurrence of C in S.  */
#अगर_घोषित __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *म_खोजप (अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
बाह्य स्थिर अक्षर *म_खोजप (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline अक्षर *
म_खोजप (अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_strrchr (__s, __c);
}

__extern_always_inline स्थिर अक्षर *
म_खोजप (स्थिर अक्षर *__s, पूर्णांक __c) __THROW
{
  वापस __builtin_strrchr (__s, __c);
}
# endif
}
#अन्यथा
बाह्य अक्षर *म_खोजप (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# अगर __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define म_खोजप(S, C)						\
  __glibc_const_generic (S, स्थिर अक्षर *, म_खोजप (S, C))
# endif
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" अक्षर *strchrnul (अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
बाह्य "C++" स्थिर अक्षर *strchrnul (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# अन्यथा
बाह्य अक्षर *strchrnul (स्थिर अक्षर *__s, पूर्णांक __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#पूर्ण_अगर

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
बाह्य माप_प्रकार म_खोज (स्थिर अक्षर *__s, स्थिर अक्षर *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
बाह्य माप_प्रकार म_अखोज (स्थिर अक्षर *__s, स्थिर अक्षर *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#अगर_घोषित __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *strpbrk (अक्षर *__s, स्थिर अक्षर *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
बाह्य स्थिर अक्षर *strpbrk (स्थिर अक्षर *__s, स्थिर अक्षर *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline अक्षर *
strpbrk (अक्षर *__s, स्थिर अक्षर *__accept) __THROW
{
  वापस __builtin_strpbrk (__s, __accept);
}

__extern_always_inline स्थिर अक्षर *
strpbrk (स्थिर अक्षर *__s, स्थिर अक्षर *__accept) __THROW
{
  वापस __builtin_strpbrk (__s, __accept);
}
# endif
}
#अन्यथा
बाह्य अक्षर *strpbrk (स्थिर अक्षर *__s, स्थिर अक्षर *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# अगर __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, स्थिर अक्षर *, strpbrk (S, ACCEPT))
# endif
#पूर्ण_अगर
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#अगर_घोषित __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य अक्षर *म_माला (अक्षर *__haystack, स्थिर अक्षर *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
बाह्य स्थिर अक्षर *म_माला (स्थिर अक्षर *__haystack, स्थिर अक्षर *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline अक्षर *
म_माला (अक्षर *__haystack, स्थिर अक्षर *__needle) __THROW
{
  वापस __builtin_strstr (__haystack, __needle);
}

__extern_always_inline स्थिर अक्षर *
म_माला (स्थिर अक्षर *__haystack, स्थिर अक्षर *__needle) __THROW
{
  वापस __builtin_strstr (__haystack, __needle);
}
# endif
}
#अन्यथा
बाह्य अक्षर *म_माला (स्थिर अक्षर *__haystack, स्थिर अक्षर *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# अगर __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define म_माला(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, स्थिर अक्षर *,	\
			 म_माला (HAYSTACK, NEEDLE))
# endif
#पूर्ण_अगर


/* Divide S into tokens separated by characters in DELIM.  */
बाह्य अक्षर *म_मोहर (अक्षर *__restrict __s, स्थिर अक्षर *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
बाह्य अक्षर *__strtok_r (अक्षर *__restrict __s,
			 स्थिर अक्षर *__restrict __delim,
			 अक्षर **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#अगर_घोषित __USE_POSIX
बाह्य अक्षर *strtok_r (अक्षर *__restrict __s, स्थिर अक्षर *__restrict __delim,
		       अक्षर **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" अक्षर *strcasestr (अक्षर *__haystack, स्थिर अक्षर *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
बाह्य "C++" स्थिर अक्षर *strcasestr (स्थिर अक्षर *__haystack,
				     स्थिर अक्षर *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# अन्यथा
बाह्य अक्षर *strcasestr (स्थिर अक्षर *__haystack, स्थिर अक्षर *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
बाह्य व्योम *memmem (स्थिर व्योम *__haystack, माप_प्रकार __haystacklen,
		     स्थिर व्योम *__needle, माप_प्रकार __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
बाह्य व्योम *__mempcpy (व्योम *__restrict __dest,
			स्थिर व्योम *__restrict __src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));
बाह्य व्योम *mempcpy (व्योम *__restrict __dest,
		      स्थिर व्योम *__restrict __src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));
#पूर्ण_अगर


/* Return the length of S.  */
बाह्य माप_प्रकार म_माप (स्थिर अक्षर *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#अगर_घोषित	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
बाह्य माप_प्रकार strnlen (स्थिर अक्षर *__string, माप_प्रकार __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#पूर्ण_अगर


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
बाह्य अक्षर *म_त्रुटि (पूर्णांक __errnum) __THROW;
#अगर_घोषित __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# अगर defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
बाह्य पूर्णांक __REDIRECT_NTH (strerror_r,
			   (पूर्णांक __errnum, अक्षर *__buf, माप_प्रकार __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  अन्यथा
बाह्य पूर्णांक __xpg_strerror_r (पूर्णांक __errnum, अक्षर *__buf, माप_प्रकार __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# अन्यथा
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
बाह्य अक्षर *strerror_r (पूर्णांक __errnum, अक्षर *__buf, माप_प्रकार __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
बाह्य स्थिर अक्षर *strerrordesc_np (पूर्णांक __err) __THROW;
/* Return a string with the error name in ERR.  */
बाह्य स्थिर अक्षर *strerrorname_np (पूर्णांक __err) __THROW;
# endif
#पूर्ण_अगर

#अगर_घोषित __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
बाह्य अक्षर *strerror_l (पूर्णांक __errnum, locale_t __l) __THROW;
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
बाह्य व्योम explicit_bzero (व्योम *__s, माप_प्रकार __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
बाह्य अक्षर *strsep (अक्षर **__restrict __stringp,
		     स्थिर अक्षर *__restrict __delim)
     __THROW __nonnull ((1, 2));
#पूर्ण_अगर

#अगर_घोषित	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
बाह्य अक्षर *strsignal (पूर्णांक __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
बाह्य स्थिर अक्षर *sigabbrev_np (पूर्णांक __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
बाह्य स्थिर अक्षर *sigdescr_np (पूर्णांक __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
बाह्य अक्षर *__stpcpy (अक्षर *__restrict __dest, स्थिर अक्षर *__restrict __src)
     __THROW __nonnull ((1, 2));
बाह्य अक्षर *stpcpy (अक्षर *__restrict __dest, स्थिर अक्षर *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
बाह्य अक्षर *__stpncpy (अक्षर *__restrict __dest,
			स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));
बाह्य अक्षर *stpncpy (अक्षर *__restrict __dest,
		      स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
     __THROW __nonnull ((1, 2));
#पूर्ण_अगर

#अगर_घोषित __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
बाह्य माप_प्रकार strlcpy (अक्षर *__restrict __dest,
		       स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
बाह्य माप_प्रकार strlcat (अक्षर *__restrict __dest,
		       स्थिर अक्षर *__restrict __src, माप_प्रकार __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#पूर्ण_अगर

#अगर_घोषित	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
बाह्य पूर्णांक strverscmp (स्थिर अक्षर *__s1, स्थिर अक्षर *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
बाह्य अक्षर *strfry (अक्षर *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
बाह्य व्योम *memfrob (व्योम *__s, माप_प्रकार __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" अक्षर *basename (अक्षर *__filename)
     __THROW __asm ("basename") __nonnull ((1));
बाह्य "C++" स्थिर अक्षर *basename (स्थिर अक्षर *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  अन्यथा
बाह्य अक्षर *basename (स्थिर अक्षर *__filename) __THROW __nonnull ((1));
#  endif
# endif
#पूर्ण_अगर

#अगर __GNUC_PREREQ (3,4)
# अगर __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#पूर्ण_अगर

__END_DECLS

#पूर्ण_अगर /* string.h  */
