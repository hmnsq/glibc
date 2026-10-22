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

#ifndef	_STRING_H
#define	_STRING_H	1

#define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#അന്തര്ഭാവ <bits/libc-header-start.h>

__BEGIN_DECLS

#എങ്കിൽ __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#അന്തര്ഭാവ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#എങ്കിൽ defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
ബാഹ്യ ശൂന്യം *memcpy (ശൂന്യം *__restrict __dest, സ്ഥിരം ശൂന്യം *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
ബാഹ്യ ശൂന്യം *memmove (ശൂന്യം *__dest, സ്ഥിരം ശൂന്യം *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#എങ്കിൽ defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
ബാഹ്യ ശൂന്യം *memccpy (ശൂന്യം *__restrict __dest, സ്ഥിരം ശൂന്യം *__restrict __src,
		      പൂർണ്ണസംഖ്യ __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
ബാഹ്യ ശൂന്യം *memset (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n) __THROW __nonnull ((1));

#എങ്കിൽ defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
ബാഹ്യ ശൂന്യം *memset_explicit (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ memcmp (സ്ഥിരം ശൂന്യം *__s1, സ്ഥിരം ശൂന്യം *__s2, size_t __n)
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
ബാഹ്യ പൂർണ്ണസംഖ്യ __memcmpeq (സ്ഥിരം ശൂന്യം *__s1, സ്ഥിരം ശൂന്യം *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ ശൂന്യം *memchr (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
ബാഹ്യ സ്ഥിരം ശൂന്യം *memchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ശൂന്യം *
memchr (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n) __THROW
{
  തിരികെ __builtin_memchr (__s, __c, __n);
}

__extern_always_inline സ്ഥിരം ശൂന്യം *
memchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n) __THROW
{
  തിരികെ __builtin_memchr (__s, __c, __n);
}
# endif
}
#അല്ലെങ്കിൽ
ബാഹ്യ ശൂന്യം *memchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# എങ്കിൽ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, സ്ഥിരം ശൂന്യം *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++" ശൂന്യം *rawmemchr (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
ബാഹ്യ "C++" സ്ഥിരം ശൂന്യം *rawmemchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# അല്ലെങ്കിൽ
ബാഹ്യ ശൂന്യം *rawmemchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++" ശൂന്യം *memrchr (ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
ബാഹ്യ "C++" സ്ഥിരം ശൂന്യം *memrchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# അല്ലെങ്കിൽ
ബാഹ്യ ശൂന്യം *memrchr (സ്ഥിരം ശൂന്യം *__s, പൂർണ്ണസംഖ്യ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
ബാഹ്യ അക്ഷരം *strcpy (അക്ഷരം *__restrict __dest, സ്ഥിരം അക്ഷരം *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
ബാഹ്യ അക്ഷരം *strncpy (അക്ഷരം *__restrict __dest,
		      സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
ബാഹ്യ അക്ഷരം *strcat (അക്ഷരം *__restrict __dest, സ്ഥിരം അക്ഷരം *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
ബാഹ്യ അക്ഷരം *strncat (അക്ഷരം *__restrict __dest, സ്ഥിരം അക്ഷരം *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strcmp (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strncmp (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strcoll (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
ബാഹ്യ size_t strxfrm (അക്ഷരം *__restrict __dest,
		       സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strcoll_l (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
ബാഹ്യ size_t strxfrm_l (അക്ഷരം *__dest, സ്ഥിരം അക്ഷരം *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#എങ്കിൽ (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
ബാഹ്യ അക്ഷരം *strdup (സ്ഥിരം അക്ഷരം *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#എങ്കിൽ defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
ബാഹ്യ അക്ഷരം *strndup (സ്ഥിരം അക്ഷരം *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#എങ്കിൽ defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      സ്ഥിരം അക്ഷരം *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      അക്ഷരം *__new = (അക്ഷരം *) __builtin_alloca (__len);			      \
      (അക്ഷരം *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      സ്ഥിരം അക്ഷരം *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      അക്ഷരം *__new = (അക്ഷരം *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (അക്ഷരം *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *strchr (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
ബാഹ്യ സ്ഥിരം അക്ഷരം *strchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline അക്ഷരം *
strchr (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_strchr (__s, __c);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
strchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_strchr (__s, __c);
}
# endif
}
#അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# എങ്കിൽ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, സ്ഥിരം അക്ഷരം *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *strrchr (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
ബാഹ്യ സ്ഥിരം അക്ഷരം *strrchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline അക്ഷരം *
strrchr (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_strrchr (__s, __c);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
strrchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_strrchr (__s, __c);
}
# endif
}
#അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strrchr (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# എങ്കിൽ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, സ്ഥിരം അക്ഷരം *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++" അക്ഷരം *strchrnul (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
ബാഹ്യ "C++" സ്ഥിരം അക്ഷരം *strchrnul (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strchrnul (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
ബാഹ്യ size_t strcspn (സ്ഥിരം അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
ബാഹ്യ size_t strspn (സ്ഥിരം അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *strpbrk (അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
ബാഹ്യ സ്ഥിരം അക്ഷരം *strpbrk (സ്ഥിരം അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline അക്ഷരം *
strpbrk (അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept) __THROW
{
  തിരികെ __builtin_strpbrk (__s, __accept);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
strpbrk (സ്ഥിരം അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept) __THROW
{
  തിരികെ __builtin_strpbrk (__s, __accept);
}
# endif
}
#അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strpbrk (സ്ഥിരം അക്ഷരം *__s, സ്ഥിരം അക്ഷരം *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# എങ്കിൽ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, സ്ഥിരം അക്ഷരം *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *strstr (അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
ബാഹ്യ സ്ഥിരം അക്ഷരം *strstr (സ്ഥിരം അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline അക്ഷരം *
strstr (അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle) __THROW
{
  തിരികെ __builtin_strstr (__haystack, __needle);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
strstr (സ്ഥിരം അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle) __THROW
{
  തിരികെ __builtin_strstr (__haystack, __needle);
}
# endif
}
#അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strstr (സ്ഥിരം അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# എങ്കിൽ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, സ്ഥിരം അക്ഷരം *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
ബാഹ്യ അക്ഷരം *strtok (അക്ഷരം *__restrict __s, സ്ഥിരം അക്ഷരം *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
ബാഹ്യ അക്ഷരം *__strtok_r (അക്ഷരം *__restrict __s,
			 സ്ഥിരം അക്ഷരം *__restrict __delim,
			 അക്ഷരം **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
ബാഹ്യ അക്ഷരം *strtok_r (അക്ഷരം *__restrict __s, സ്ഥിരം അക്ഷരം *__restrict __delim,
		       അക്ഷരം **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++" അക്ഷരം *strcasestr (അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
ബാഹ്യ "C++" സ്ഥിരം അക്ഷരം *strcasestr (സ്ഥിരം അക്ഷരം *__haystack,
				     സ്ഥിരം അക്ഷരം *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *strcasestr (സ്ഥിരം അക്ഷരം *__haystack, സ്ഥിരം അക്ഷരം *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
ബാഹ്യ ശൂന്യം *memmem (സ്ഥിരം ശൂന്യം *__haystack, size_t __haystacklen,
		     സ്ഥിരം ശൂന്യം *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
ബാഹ്യ ശൂന്യം *__mempcpy (ശൂന്യം *__restrict __dest,
			സ്ഥിരം ശൂന്യം *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ബാഹ്യ ശൂന്യം *mempcpy (ശൂന്യം *__restrict __dest,
		      സ്ഥിരം ശൂന്യം *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
ബാഹ്യ size_t strlen (സ്ഥിരം അക്ഷരം *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
ബാഹ്യ size_t strnlen (സ്ഥിരം അക്ഷരം *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
ബാഹ്യ അക്ഷരം *strerror (പൂർണ്ണസംഖ്യ __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# എങ്കിൽ defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
ബാഹ്യ പൂർണ്ണസംഖ്യ __REDIRECT_NTH (strerror_r,
			   (പൂർണ്ണസംഖ്യ __errnum, അക്ഷരം *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  അല്ലെങ്കിൽ
ബാഹ്യ പൂർണ്ണസംഖ്യ __xpg_strerror_r (പൂർണ്ണസംഖ്യ __errnum, അക്ഷരം *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# അല്ലെങ്കിൽ
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
ബാഹ്യ അക്ഷരം *strerror_r (പൂർണ്ണസംഖ്യ __errnum, അക്ഷരം *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
ബാഹ്യ സ്ഥിരം അക്ഷരം *strerrordesc_np (പൂർണ്ണസംഖ്യ __err) __THROW;
/* Return a string with the error name in ERR.  */
ബാഹ്യ സ്ഥിരം അക്ഷരം *strerrorname_np (പൂർണ്ണസംഖ്യ __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
ബാഹ്യ അക്ഷരം *strerror_l (പൂർണ്ണസംഖ്യ __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
ബാഹ്യ ശൂന്യം explicit_bzero (ശൂന്യം *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
ബാഹ്യ അക്ഷരം *strsep (അക്ഷരം **__restrict __stringp,
		     സ്ഥിരം അക്ഷരം *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
ബാഹ്യ അക്ഷരം *strsignal (പൂർണ്ണസംഖ്യ __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
ബാഹ്യ സ്ഥിരം അക്ഷരം *sigabbrev_np (പൂർണ്ണസംഖ്യ __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
ബാഹ്യ സ്ഥിരം അക്ഷരം *sigdescr_np (പൂർണ്ണസംഖ്യ __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ബാഹ്യ അക്ഷരം *__stpcpy (അക്ഷരം *__restrict __dest, സ്ഥിരം അക്ഷരം *__restrict __src)
     __THROW __nonnull ((1, 2));
ബാഹ്യ അക്ഷരം *stpcpy (അക്ഷരം *__restrict __dest, സ്ഥിരം അക്ഷരം *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
ബാഹ്യ അക്ഷരം *__stpncpy (അക്ഷരം *__restrict __dest,
			സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ബാഹ്യ അക്ഷരം *stpncpy (അക്ഷരം *__restrict __dest,
		      സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
ബാഹ്യ size_t strlcpy (അക്ഷരം *__restrict __dest,
		       സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
ബാഹ്യ size_t strlcat (അക്ഷരം *__restrict __dest,
		       സ്ഥിരം അക്ഷരം *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strverscmp (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
ബാഹ്യ അക്ഷരം *strfry (അക്ഷരം *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
ബാഹ്യ ശൂന്യം *memfrob (ശൂന്യം *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ബാഹ്യ "C++" അക്ഷരം *basename (അക്ഷരം *__filename)
     __THROW __asm ("basename") __nonnull ((1));
ബാഹ്യ "C++" സ്ഥിരം അക്ഷരം *basename (സ്ഥിരം അക്ഷരം *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *basename (സ്ഥിരം അക്ഷരം *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#എങ്കിൽ __GNUC_PREREQ (3,4)
# എങ്കിൽ __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
