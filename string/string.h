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
#ଅନ୍ତର୍ଭାଵ <bits/libc-header-start.h>

__BEGIN_DECLS

#ଯଦି __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#ଅନ୍ତର୍ଭାଵ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ଯଦି defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memcpy (ଶୂନ୍ୟ *__restrict __dest, ଅଚଳ ଶୂନ୍ୟ *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memmove (ଶୂନ୍ୟ *__dest, ଅଚଳ ଶୂନ୍ୟ *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#ଯଦି defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
ବାହ୍ୟ ଶୂନ୍ୟ *memccpy (ଶୂନ୍ୟ *__restrict __dest, ଅଚଳ ଶୂନ୍ୟ *__restrict __src,
		      ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memset (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n) __THROW __nonnull ((1));

#ଯଦି defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memset_explicit (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା memcmp (ଅଚଳ ଶୂନ୍ୟ *__s1, ଅଚଳ ଶୂନ୍ୟ *__s2, size_t __n)
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
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା __memcmpeq (ଅଚଳ ଶୂନ୍ୟ *__s1, ଅଚଳ ଶୂନ୍ୟ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଶୂନ୍ୟ *memchr (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ ଅଚଳ ଶୂନ୍ୟ *memchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ଶୂନ୍ୟ *
memchr (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n) __THROW
{
  ଫେରନ୍ତୁ __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ଅଚଳ ଶୂନ୍ୟ *
memchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n) __THROW
{
  ଫେରନ୍ତୁ __builtin_memchr (__s, __c, __n);
}
# endif
}
#ଅନ୍ୟଥା
ବାହ୍ୟ ଶୂନ୍ୟ *memchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# ଯଦି __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ଅଚଳ ଶୂନ୍ୟ *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++" ଶୂନ୍ୟ *rawmemchr (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ "C++" ଅଚଳ ଶୂନ୍ୟ *rawmemchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# ଅନ୍ୟଥା
ବାହ୍ୟ ଶୂନ୍ୟ *rawmemchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++" ଶୂନ୍ୟ *memrchr (ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
ବାହ୍ୟ "C++" ଅଚଳ ଶୂନ୍ୟ *memrchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# ଅନ୍ୟଥା
ବାହ୍ୟ ଶୂନ୍ୟ *memrchr (ଅଚଳ ଶୂନ୍ୟ *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *strcpy (ଅକ୍ଷର *__restrict __dest, ଅଚଳ ଅକ୍ଷର *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *strncpy (ଅକ୍ଷର *__restrict __dest,
		      ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *strcat (ଅକ୍ଷର *__restrict __dest, ଅଚଳ ଅକ୍ଷର *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *strncat (ଅକ୍ଷର *__restrict __dest, ଅଚଳ ଅକ୍ଷର *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strcmp (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strncmp (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strcoll (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
ବାହ୍ୟ size_t strxfrm (ଅକ୍ଷର *__restrict __dest,
		       ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strcoll_l (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
ବାହ୍ୟ size_t strxfrm_l (ଅକ୍ଷର *__dest, ଅଚଳ ଅକ୍ଷର *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#ଯଦି (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
ବାହ୍ୟ ଅକ୍ଷର *strdup (ଅଚଳ ଅକ୍ଷର *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#ଯଦି defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
ବାହ୍ୟ ଅକ୍ଷର *strndup (ଅଚଳ ଅକ୍ଷର *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#ଯଦି defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ଅଚଳ ଅକ୍ଷର *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      ଅକ୍ଷର *__new = (ଅକ୍ଷର *) __builtin_alloca (__len);			      \
      (ଅକ୍ଷର *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ଅଚଳ ଅକ୍ଷର *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      ଅକ୍ଷର *__new = (ଅକ୍ଷର *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (ଅକ୍ଷର *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *strchr (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
strchr (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_strchr (__s, __c);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
strchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_strchr (__s, __c);
}
# endif
}
#ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ଯଦି __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ଅଚଳ ଅକ୍ଷର *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *strrchr (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strrchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
strrchr (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_strrchr (__s, __c);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
strrchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_strrchr (__s, __c);
}
# endif
}
#ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strrchr (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ଯଦି __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ଅଚଳ ଅକ୍ଷର *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++" ଅକ୍ଷର *strchrnul (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ "C++" ଅଚଳ ଅକ୍ଷର *strchrnul (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strchrnul (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
ବାହ୍ୟ size_t strcspn (ଅଚଳ ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
ବାହ୍ୟ size_t strspn (ଅଚଳ ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *strpbrk (ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strpbrk (ଅଚଳ ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
strpbrk (ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept) __THROW
{
  ଫେରନ୍ତୁ __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
strpbrk (ଅଚଳ ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept) __THROW
{
  ଫେରନ୍ତୁ __builtin_strpbrk (__s, __accept);
}
# endif
}
#ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strpbrk (ଅଚଳ ଅକ୍ଷର *__s, ଅଚଳ ଅକ୍ଷର *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ଯଦି __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ଅଚଳ ଅକ୍ଷର *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *strstr (ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strstr (ଅଚଳ ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
strstr (ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle) __THROW
{
  ଫେରନ୍ତୁ __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
strstr (ଅଚଳ ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle) __THROW
{
  ଫେରନ୍ତୁ __builtin_strstr (__haystack, __needle);
}
# endif
}
#ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strstr (ଅଚଳ ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ଯଦି __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ଅଚଳ ଅକ୍ଷର *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
ବାହ୍ୟ ଅକ୍ଷର *strtok (ଅକ୍ଷର *__restrict __s, ଅଚଳ ଅକ୍ଷର *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
ବାହ୍ୟ ଅକ୍ଷର *__strtok_r (ଅକ୍ଷର *__restrict __s,
			 ଅଚଳ ଅକ୍ଷର *__restrict __delim,
			 ଅକ୍ଷର **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
ବାହ୍ୟ ଅକ୍ଷର *strtok_r (ଅକ୍ଷର *__restrict __s, ଅଚଳ ଅକ୍ଷର *__restrict __delim,
		       ଅକ୍ଷର **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++" ଅକ୍ଷର *strcasestr (ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
ବାହ୍ୟ "C++" ଅଚଳ ଅକ୍ଷର *strcasestr (ଅଚଳ ଅକ୍ଷର *__haystack,
				     ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *strcasestr (ଅଚଳ ଅକ୍ଷର *__haystack, ଅଚଳ ଅକ୍ଷର *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memmem (ଅଚଳ ଶୂନ୍ୟ *__haystack, size_t __haystacklen,
		     ଅଚଳ ଶୂନ୍ୟ *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
ବାହ୍ୟ ଶୂନ୍ୟ *__mempcpy (ଶୂନ୍ୟ *__restrict __dest,
			ଅଚଳ ଶୂନ୍ୟ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ବାହ୍ୟ ଶୂନ୍ୟ *mempcpy (ଶୂନ୍ୟ *__restrict __dest,
		      ଅଚଳ ଶୂନ୍ୟ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
ବାହ୍ୟ size_t strlen (ଅଚଳ ଅକ୍ଷର *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
ବାହ୍ୟ size_t strnlen (ଅଚଳ ଅକ୍ଷର *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
ବାହ୍ୟ ଅକ୍ଷର *strerror (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# ଯଦି defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା __REDIRECT_NTH (strerror_r,
			   (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __errnum, ଅକ୍ଷର *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  ଅନ୍ୟଥା
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା __xpg_strerror_r (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __errnum, ଅକ୍ଷର *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# ଅନ୍ୟଥା
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
ବାହ୍ୟ ଅକ୍ଷର *strerror_r (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __errnum, ଅକ୍ଷର *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strerrordesc_np (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __err) __THROW;
/* Return a string with the error name in ERR.  */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *strerrorname_np (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
ବାହ୍ୟ ଅକ୍ଷର *strerror_l (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
ବାହ୍ୟ ଶୂନ୍ୟ explicit_bzero (ଶୂନ୍ୟ *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
ବାହ୍ୟ ଅକ୍ଷର *strsep (ଅକ୍ଷର **__restrict __stringp,
		     ଅଚଳ ଅକ୍ଷର *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
ବାହ୍ୟ ଅକ୍ଷର *strsignal (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *sigabbrev_np (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *sigdescr_np (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *__stpcpy (ଅକ୍ଷର *__restrict __dest, ଅଚଳ ଅକ୍ଷର *__restrict __src)
     __THROW __nonnull ((1, 2));
ବାହ୍ୟ ଅକ୍ଷର *stpcpy (ଅକ୍ଷର *__restrict __dest, ଅଚଳ ଅକ୍ଷର *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
ବାହ୍ୟ ଅକ୍ଷର *__stpncpy (ଅକ୍ଷର *__restrict __dest,
			ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ବାହ୍ୟ ଅକ୍ଷର *stpncpy (ଅକ୍ଷର *__restrict __dest,
		      ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
ବାହ୍ୟ size_t strlcpy (ଅକ୍ଷର *__restrict __dest,
		       ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
ବାହ୍ୟ size_t strlcat (ଅକ୍ଷର *__restrict __dest,
		       ଅଚଳ ଅକ୍ଷର *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strverscmp (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
ବାହ୍ୟ ଅକ୍ଷର *strfry (ଅକ୍ଷର *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
ବାହ୍ୟ ଶୂନ୍ୟ *memfrob (ଶୂନ୍ୟ *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ବାହ୍ୟ "C++" ଅକ୍ଷର *basename (ଅକ୍ଷର *__filename)
     __THROW __asm ("basename") __nonnull ((1));
ବାହ୍ୟ "C++" ଅଚଳ ଅକ୍ଷର *basename (ଅଚଳ ଅକ୍ଷର *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *basename (ଅଚଳ ଅକ୍ଷର *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#ଯଦି __GNUC_PREREQ (3,4)
# ଯଦି __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
