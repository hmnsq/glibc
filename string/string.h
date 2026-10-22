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
#அந்தர்பாவ <bits/libc-header-start.h>

__BEGIN_DECLS

#எனில் __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#அந்தர்பாவ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#எனில் defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
வெளி வெறுமை *memcpy (வெறுமை *__restrict __dest, மாறிலி வெறுமை *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
வெளி வெறுமை *memmove (வெறுமை *__dest, மாறிலி வெறுமை *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#எனில் defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
வெளி வெறுமை *memccpy (வெறுமை *__restrict __dest, மாறிலி வெறுமை *__restrict __src,
		      முழு __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
வெளி வெறுமை *memset (வெறுமை *__s, முழு __c, size_t __n) __THROW __nonnull ((1));

#எனில் defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
வெளி வெறுமை *memset_explicit (வெறுமை *__s, முழு __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
வெளி முழு memcmp (மாறிலி வெறுமை *__s1, மாறிலி வெறுமை *__s2, size_t __n)
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
வெளி முழு __memcmpeq (மாறிலி வெறுமை *__s1, மாறிலி வெறுமை *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++"
{
வெளி வெறுமை *memchr (வெறுமை *__s, முழு __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
வெளி மாறிலி வெறுமை *memchr (மாறிலி வெறுமை *__s, முழு __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline வெறுமை *
memchr (வெறுமை *__s, முழு __c, size_t __n) __THROW
{
  திரும்பு __builtin_memchr (__s, __c, __n);
}

__extern_always_inline மாறிலி வெறுமை *
memchr (மாறிலி வெறுமை *__s, முழு __c, size_t __n) __THROW
{
  திரும்பு __builtin_memchr (__s, __c, __n);
}
# endif
}
#இல்லையெனில்
வெளி வெறுமை *memchr (மாறிலி வெறுமை *__s, முழு __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# எனில் __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, மாறிலி வெறுமை *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++" வெறுமை *rawmemchr (வெறுமை *__s, முழு __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
வெளி "C++" மாறிலி வெறுமை *rawmemchr (மாறிலி வெறுமை *__s, முழு __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# இல்லையெனில்
வெளி வெறுமை *rawmemchr (மாறிலி வெறுமை *__s, முழு __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++" வெறுமை *memrchr (வெறுமை *__s, முழு __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
வெளி "C++" மாறிலி வெறுமை *memrchr (மாறிலி வெறுமை *__s, முழு __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# இல்லையெனில்
வெளி வெறுமை *memrchr (மாறிலி வெறுமை *__s, முழு __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
வெளி எழுத்து *strcpy (எழுத்து *__restrict __dest, மாறிலி எழுத்து *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
வெளி எழுத்து *strncpy (எழுத்து *__restrict __dest,
		      மாறிலி எழுத்து *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
வெளி எழுத்து *strcat (எழுத்து *__restrict __dest, மாறிலி எழுத்து *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
வெளி எழுத்து *strncat (எழுத்து *__restrict __dest, மாறிலி எழுத்து *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
வெளி முழு strcmp (மாறிலி எழுத்து *__s1, மாறிலி எழுத்து *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
வெளி முழு strncmp (மாறிலி எழுத்து *__s1, மாறிலி எழுத்து *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
வெளி முழு strcoll (மாறிலி எழுத்து *__s1, மாறிலி எழுத்து *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
வெளி size_t strxfrm (எழுத்து *__restrict __dest,
		       மாறிலி எழுத்து *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
வெளி முழு strcoll_l (மாறிலி எழுத்து *__s1, மாறிலி எழுத்து *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
வெளி size_t strxfrm_l (எழுத்து *__dest, மாறிலி எழுத்து *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#எனில் (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
வெளி எழுத்து *strdup (மாறிலி எழுத்து *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#எனில் defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
வெளி எழுத்து *strndup (மாறிலி எழுத்து *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#எனில் defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      மாறிலி எழுத்து *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      எழுத்து *__new = (எழுத்து *) __builtin_alloca (__len);			      \
      (எழுத்து *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      மாறிலி எழுத்து *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      எழுத்து *__new = (எழுத்து *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (எழுத்து *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++"
{
வெளி எழுத்து *strchr (எழுத்து *__s, முழு __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
வெளி மாறிலி எழுத்து *strchr (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline எழுத்து *
strchr (எழுத்து *__s, முழு __c) __THROW
{
  திரும்பு __builtin_strchr (__s, __c);
}

__extern_always_inline மாறிலி எழுத்து *
strchr (மாறிலி எழுத்து *__s, முழு __c) __THROW
{
  திரும்பு __builtin_strchr (__s, __c);
}
# endif
}
#இல்லையெனில்
வெளி எழுத்து *strchr (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __attribute_pure__ __nonnull ((1));
# எனில் __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, மாறிலி எழுத்து *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++"
{
வெளி எழுத்து *strrchr (எழுத்து *__s, முழு __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
வெளி மாறிலி எழுத்து *strrchr (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline எழுத்து *
strrchr (எழுத்து *__s, முழு __c) __THROW
{
  திரும்பு __builtin_strrchr (__s, __c);
}

__extern_always_inline மாறிலி எழுத்து *
strrchr (மாறிலி எழுத்து *__s, முழு __c) __THROW
{
  திரும்பு __builtin_strrchr (__s, __c);
}
# endif
}
#இல்லையெனில்
வெளி எழுத்து *strrchr (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __attribute_pure__ __nonnull ((1));
# எனில் __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, மாறிலி எழுத்து *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++" எழுத்து *strchrnul (எழுத்து *__s, முழு __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
வெளி "C++" மாறிலி எழுத்து *strchrnul (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# இல்லையெனில்
வெளி எழுத்து *strchrnul (மாறிலி எழுத்து *__s, முழு __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
வெளி size_t strcspn (மாறிலி எழுத்து *__s, மாறிலி எழுத்து *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
வெளி size_t strspn (மாறிலி எழுத்து *__s, மாறிலி எழுத்து *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++"
{
வெளி எழுத்து *strpbrk (எழுத்து *__s, மாறிலி எழுத்து *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
வெளி மாறிலி எழுத்து *strpbrk (மாறிலி எழுத்து *__s, மாறிலி எழுத்து *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline எழுத்து *
strpbrk (எழுத்து *__s, மாறிலி எழுத்து *__accept) __THROW
{
  திரும்பு __builtin_strpbrk (__s, __accept);
}

__extern_always_inline மாறிலி எழுத்து *
strpbrk (மாறிலி எழுத்து *__s, மாறிலி எழுத்து *__accept) __THROW
{
  திரும்பு __builtin_strpbrk (__s, __accept);
}
# endif
}
#இல்லையெனில்
வெளி எழுத்து *strpbrk (மாறிலி எழுத்து *__s, மாறிலி எழுத்து *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# எனில் __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, மாறிலி எழுத்து *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++"
{
வெளி எழுத்து *strstr (எழுத்து *__haystack, மாறிலி எழுத்து *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
வெளி மாறிலி எழுத்து *strstr (மாறிலி எழுத்து *__haystack, மாறிலி எழுத்து *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline எழுத்து *
strstr (எழுத்து *__haystack, மாறிலி எழுத்து *__needle) __THROW
{
  திரும்பு __builtin_strstr (__haystack, __needle);
}

__extern_always_inline மாறிலி எழுத்து *
strstr (மாறிலி எழுத்து *__haystack, மாறிலி எழுத்து *__needle) __THROW
{
  திரும்பு __builtin_strstr (__haystack, __needle);
}
# endif
}
#இல்லையெனில்
வெளி எழுத்து *strstr (மாறிலி எழுத்து *__haystack, மாறிலி எழுத்து *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# எனில் __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, மாறிலி எழுத்து *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
வெளி எழுத்து *strtok (எழுத்து *__restrict __s, மாறிலி எழுத்து *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
வெளி எழுத்து *__strtok_r (எழுத்து *__restrict __s,
			 மாறிலி எழுத்து *__restrict __delim,
			 எழுத்து **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
வெளி எழுத்து *strtok_r (எழுத்து *__restrict __s, மாறிலி எழுத்து *__restrict __delim,
		       எழுத்து **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++" எழுத்து *strcasestr (எழுத்து *__haystack, மாறிலி எழுத்து *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
வெளி "C++" மாறிலி எழுத்து *strcasestr (மாறிலி எழுத்து *__haystack,
				     மாறிலி எழுத்து *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# இல்லையெனில்
வெளி எழுத்து *strcasestr (மாறிலி எழுத்து *__haystack, மாறிலி எழுத்து *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
வெளி வெறுமை *memmem (மாறிலி வெறுமை *__haystack, size_t __haystacklen,
		     மாறிலி வெறுமை *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
வெளி வெறுமை *__mempcpy (வெறுமை *__restrict __dest,
			மாறிலி வெறுமை *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
வெளி வெறுமை *mempcpy (வெறுமை *__restrict __dest,
		      மாறிலி வெறுமை *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
வெளி size_t strlen (மாறிலி எழுத்து *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
வெளி size_t strnlen (மாறிலி எழுத்து *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
வெளி எழுத்து *strerror (முழு __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# எனில் defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
வெளி முழு __REDIRECT_NTH (strerror_r,
			   (முழு __errnum, எழுத்து *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  இல்லையெனில்
வெளி முழு __xpg_strerror_r (முழு __errnum, எழுத்து *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# இல்லையெனில்
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
வெளி எழுத்து *strerror_r (முழு __errnum, எழுத்து *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
வெளி மாறிலி எழுத்து *strerrordesc_np (முழு __err) __THROW;
/* Return a string with the error name in ERR.  */
வெளி மாறிலி எழுத்து *strerrorname_np (முழு __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
வெளி எழுத்து *strerror_l (முழு __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
வெளி வெறுமை explicit_bzero (வெறுமை *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
வெளி எழுத்து *strsep (எழுத்து **__restrict __stringp,
		     மாறிலி எழுத்து *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
வெளி எழுத்து *strsignal (முழு __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
வெளி மாறிலி எழுத்து *sigabbrev_np (முழு __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
வெளி மாறிலி எழுத்து *sigdescr_np (முழு __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
வெளி எழுத்து *__stpcpy (எழுத்து *__restrict __dest, மாறிலி எழுத்து *__restrict __src)
     __THROW __nonnull ((1, 2));
வெளி எழுத்து *stpcpy (எழுத்து *__restrict __dest, மாறிலி எழுத்து *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
வெளி எழுத்து *__stpncpy (எழுத்து *__restrict __dest,
			மாறிலி எழுத்து *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
வெளி எழுத்து *stpncpy (எழுத்து *__restrict __dest,
		      மாறிலி எழுத்து *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
வெளி size_t strlcpy (எழுத்து *__restrict __dest,
		       மாறிலி எழுத்து *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
வெளி size_t strlcat (எழுத்து *__restrict __dest,
		       மாறிலி எழுத்து *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
வெளி முழு strverscmp (மாறிலி எழுத்து *__s1, மாறிலி எழுத்து *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
வெளி எழுத்து *strfry (எழுத்து *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
வெளி வெறுமை *memfrob (வெறுமை *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
வெளி "C++" எழுத்து *basename (எழுத்து *__filename)
     __THROW __asm ("basename") __nonnull ((1));
வெளி "C++" மாறிலி எழுத்து *basename (மாறிலி எழுத்து *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  இல்லையெனில்
வெளி எழுத்து *basename (மாறிலி எழுத்து *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#எனில் __GNUC_PREREQ (3,4)
# எனில் __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
