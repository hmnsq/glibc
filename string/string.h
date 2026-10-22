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
#અન્તર્ભાવ <bits/libc-header-start.h>

__BEGIN_DECLS

#જો __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#અન્તર્ભાવ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#જો defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
બાહ્ય શૂન્ય *memcpy (શૂન્ય *__restrict __dest, અચલ શૂન્ય *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
બાહ્ય શૂન્ય *memmove (શૂન્ય *__dest, અચલ શૂન્ય *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#જો defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
બાહ્ય શૂન્ય *memccpy (શૂન્ય *__restrict __dest, અચલ શૂન્ય *__restrict __src,
		      પૂર્ણાંક __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
બાહ્ય શૂન્ય *memset (શૂન્ય *__s, પૂર્ણાંક __c, size_t __n) __THROW __nonnull ((1));

#જો defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
બાહ્ય શૂન્ય *memset_explicit (શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
બાહ્ય પૂર્ણાંક memcmp (અચલ શૂન્ય *__s1, અચલ શૂન્ય *__s2, size_t __n)
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
બાહ્ય પૂર્ણાંક __memcmpeq (અચલ શૂન્ય *__s1, અચલ શૂન્ય *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++"
{
બાહ્ય શૂન્ય *memchr (શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
બાહ્ય અચલ શૂન્ય *memchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline શૂન્ય *
memchr (શૂન્ય *__s, પૂર્ણાંક __c, size_t __n) __THROW
{
  પાછા __builtin_memchr (__s, __c, __n);
}

__extern_always_inline અચલ શૂન્ય *
memchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c, size_t __n) __THROW
{
  પાછા __builtin_memchr (__s, __c, __n);
}
# endif
}
#નહીંતર
બાહ્ય શૂન્ય *memchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# જો __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, અચલ શૂન્ય *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++" શૂન્ય *rawmemchr (શૂન્ય *__s, પૂર્ણાંક __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
બાહ્ય "C++" અચલ શૂન્ય *rawmemchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# નહીંતર
બાહ્ય શૂન્ય *rawmemchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++" શૂન્ય *memrchr (શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
બાહ્ય "C++" અચલ શૂન્ય *memrchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# નહીંતર
બાહ્ય શૂન્ય *memrchr (અચલ શૂન્ય *__s, પૂર્ણાંક __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
બાહ્ય અક્ષર *strcpy (અક્ષર *__restrict __dest, અચલ અક્ષર *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
બાહ્ય અક્ષર *strncpy (અક્ષર *__restrict __dest,
		      અચલ અક્ષર *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
બાહ્ય અક્ષર *strcat (અક્ષર *__restrict __dest, અચલ અક્ષર *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
બાહ્ય અક્ષર *strncat (અક્ષર *__restrict __dest, અચલ અક્ષર *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
બાહ્ય પૂર્ણાંક strcmp (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
બાહ્ય પૂર્ણાંક strncmp (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
બાહ્ય પૂર્ણાંક strcoll (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
બાહ્ય size_t strxfrm (અક્ષર *__restrict __dest,
		       અચલ અક્ષર *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
બાહ્ય પૂર્ણાંક strcoll_l (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
બાહ્ય size_t strxfrm_l (અક્ષર *__dest, અચલ અક્ષર *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#જો (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
બાહ્ય અક્ષર *strdup (અચલ અક્ષર *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#જો defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
બાહ્ય અક્ષર *strndup (અચલ અક્ષર *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#જો defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      અચલ અક્ષર *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      અક્ષર *__new = (અક્ષર *) __builtin_alloca (__len);			      \
      (અક્ષર *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      અચલ અક્ષર *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      અક્ષર *__new = (અક્ષર *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (અક્ષર *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *strchr (અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
બાહ્ય અચલ અક્ષર *strchr (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline અક્ષર *
strchr (અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_strchr (__s, __c);
}

__extern_always_inline અચલ અક્ષર *
strchr (અચલ અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_strchr (__s, __c);
}
# endif
}
#નહીંતર
બાહ્ય અક્ષર *strchr (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# જો __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, અચલ અક્ષર *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *strrchr (અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
બાહ્ય અચલ અક્ષર *strrchr (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline અક્ષર *
strrchr (અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_strrchr (__s, __c);
}

__extern_always_inline અચલ અક્ષર *
strrchr (અચલ અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_strrchr (__s, __c);
}
# endif
}
#નહીંતર
બાહ્ય અક્ષર *strrchr (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# જો __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, અચલ અક્ષર *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++" અક્ષર *strchrnul (અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
બાહ્ય "C++" અચલ અક્ષર *strchrnul (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# નહીંતર
બાહ્ય અક્ષર *strchrnul (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
બાહ્ય size_t strcspn (અચલ અક્ષર *__s, અચલ અક્ષર *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
બાહ્ય size_t strspn (અચલ અક્ષર *__s, અચલ અક્ષર *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *strpbrk (અક્ષર *__s, અચલ અક્ષર *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
બાહ્ય અચલ અક્ષર *strpbrk (અચલ અક્ષર *__s, અચલ અક્ષર *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline અક્ષર *
strpbrk (અક્ષર *__s, અચલ અક્ષર *__accept) __THROW
{
  પાછા __builtin_strpbrk (__s, __accept);
}

__extern_always_inline અચલ અક્ષર *
strpbrk (અચલ અક્ષર *__s, અચલ અક્ષર *__accept) __THROW
{
  પાછા __builtin_strpbrk (__s, __accept);
}
# endif
}
#નહીંતર
બાહ્ય અક્ષર *strpbrk (અચલ અક્ષર *__s, અચલ અક્ષર *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# જો __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, અચલ અક્ષર *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *strstr (અક્ષર *__haystack, અચલ અક્ષર *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
બાહ્ય અચલ અક્ષર *strstr (અચલ અક્ષર *__haystack, અચલ અક્ષર *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline અક્ષર *
strstr (અક્ષર *__haystack, અચલ અક્ષર *__needle) __THROW
{
  પાછા __builtin_strstr (__haystack, __needle);
}

__extern_always_inline અચલ અક્ષર *
strstr (અચલ અક્ષર *__haystack, અચલ અક્ષર *__needle) __THROW
{
  પાછા __builtin_strstr (__haystack, __needle);
}
# endif
}
#નહીંતર
બાહ્ય અક્ષર *strstr (અચલ અક્ષર *__haystack, અચલ અક્ષર *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# જો __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, અચલ અક્ષર *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
બાહ્ય અક્ષર *strtok (અક્ષર *__restrict __s, અચલ અક્ષર *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
બાહ્ય અક્ષર *__strtok_r (અક્ષર *__restrict __s,
			 અચલ અક્ષર *__restrict __delim,
			 અક્ષર **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
બાહ્ય અક્ષર *strtok_r (અક્ષર *__restrict __s, અચલ અક્ષર *__restrict __delim,
		       અક્ષર **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++" અક્ષર *strcasestr (અક્ષર *__haystack, અચલ અક્ષર *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
બાહ્ય "C++" અચલ અક્ષર *strcasestr (અચલ અક્ષર *__haystack,
				     અચલ અક્ષર *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# નહીંતર
બાહ્ય અક્ષર *strcasestr (અચલ અક્ષર *__haystack, અચલ અક્ષર *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
બાહ્ય શૂન્ય *memmem (અચલ શૂન્ય *__haystack, size_t __haystacklen,
		     અચલ શૂન્ય *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
બાહ્ય શૂન્ય *__mempcpy (શૂન્ય *__restrict __dest,
			અચલ શૂન્ય *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
બાહ્ય શૂન્ય *mempcpy (શૂન્ય *__restrict __dest,
		      અચલ શૂન્ય *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
બાહ્ય size_t strlen (અચલ અક્ષર *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
બાહ્ય size_t strnlen (અચલ અક્ષર *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
બાહ્ય અક્ષર *strerror (પૂર્ણાંક __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# જો defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
બાહ્ય પૂર્ણાંક __REDIRECT_NTH (strerror_r,
			   (પૂર્ણાંક __errnum, અક્ષર *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  નહીંતર
બાહ્ય પૂર્ણાંક __xpg_strerror_r (પૂર્ણાંક __errnum, અક્ષર *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# નહીંતર
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
બાહ્ય અક્ષર *strerror_r (પૂર્ણાંક __errnum, અક્ષર *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
બાહ્ય અચલ અક્ષર *strerrordesc_np (પૂર્ણાંક __err) __THROW;
/* Return a string with the error name in ERR.  */
બાહ્ય અચલ અક્ષર *strerrorname_np (પૂર્ણાંક __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
બાહ્ય અક્ષર *strerror_l (પૂર્ણાંક __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
બાહ્ય શૂન્ય explicit_bzero (શૂન્ય *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
બાહ્ય અક્ષર *strsep (અક્ષર **__restrict __stringp,
		     અચલ અક્ષર *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
બાહ્ય અક્ષર *strsignal (પૂર્ણાંક __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
બાહ્ય અચલ અક્ષર *sigabbrev_np (પૂર્ણાંક __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
બાહ્ય અચલ અક્ષર *sigdescr_np (પૂર્ણાંક __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
બાહ્ય અક્ષર *__stpcpy (અક્ષર *__restrict __dest, અચલ અક્ષર *__restrict __src)
     __THROW __nonnull ((1, 2));
બાહ્ય અક્ષર *stpcpy (અક્ષર *__restrict __dest, અચલ અક્ષર *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
બાહ્ય અક્ષર *__stpncpy (અક્ષર *__restrict __dest,
			અચલ અક્ષર *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
બાહ્ય અક્ષર *stpncpy (અક્ષર *__restrict __dest,
		      અચલ અક્ષર *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
બાહ્ય size_t strlcpy (અક્ષર *__restrict __dest,
		       અચલ અક્ષર *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
બાહ્ય size_t strlcat (અક્ષર *__restrict __dest,
		       અચલ અક્ષર *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
બાહ્ય પૂર્ણાંક strverscmp (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
બાહ્ય અક્ષર *strfry (અક્ષર *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
બાહ્ય શૂન્ય *memfrob (શૂન્ય *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
બાહ્ય "C++" અક્ષર *basename (અક્ષર *__filename)
     __THROW __asm ("basename") __nonnull ((1));
બાહ્ય "C++" અચલ અક્ષર *basename (અચલ અક્ષર *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  નહીંતર
બાહ્ય અક્ષર *basename (અચલ અક્ષર *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#જો __GNUC_PREREQ (3,4)
# જો __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
