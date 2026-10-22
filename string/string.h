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
#অন্তর্ভাব <bits/libc-header-start.h>

__BEGIN_DECLS

#যদি __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#অন্তর্ভাব <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#যদি defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
বাহ্য শূন্য *memcpy (শূন্য *__restrict __dest, ধ্রুব শূন্য *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
বাহ্য শূন্য *memmove (শূন্য *__dest, ধ্রুব শূন্য *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#যদি defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
বাহ্য শূন্য *memccpy (শূন্য *__restrict __dest, ধ্রুব শূন্য *__restrict __src,
		      পূর্ণাঙ্ক __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
বাহ্য শূন্য *memset (শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n) __THROW __nonnull ((1));

#যদি defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
বাহ্য শূন্য *memset_explicit (শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
বাহ্য পূর্ণাঙ্ক memcmp (ধ্রুব শূন্য *__s1, ধ্রুব শূন্য *__s2, size_t __n)
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
বাহ্য পূর্ণাঙ্ক __memcmpeq (ধ্রুব শূন্য *__s1, ধ্রুব শূন্য *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++"
{
বাহ্য শূন্য *memchr (শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
বাহ্য ধ্রুব শূন্য *memchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline শূন্য *
memchr (শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n) __THROW
{
  প্রত্যাগম __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ধ্রুব শূন্য *
memchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n) __THROW
{
  প্রত্যাগম __builtin_memchr (__s, __c, __n);
}
# endif
}
#অন্যথা
বাহ্য শূন্য *memchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ধ্রুব শূন্য *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++" শূন্য *rawmemchr (শূন্য *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
বাহ্য "C++" ধ্রুব শূন্য *rawmemchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# অন্যথা
বাহ্য শূন্য *rawmemchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++" শূন্য *memrchr (শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
বাহ্য "C++" ধ্রুব শূন্য *memrchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# অন্যথা
বাহ্য শূন্য *memrchr (ধ্রুব শূন্য *__s, পূর্ণাঙ্ক __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
বাহ্য বর্ণ *strcpy (বর্ণ *__restrict __dest, ধ্রুব বর্ণ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
বাহ্য বর্ণ *strncpy (বর্ণ *__restrict __dest,
		      ধ্রুব বর্ণ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
বাহ্য বর্ণ *strcat (বর্ণ *__restrict __dest, ধ্রুব বর্ণ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
বাহ্য বর্ণ *strncat (বর্ণ *__restrict __dest, ধ্রুব বর্ণ *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
বাহ্য পূর্ণাঙ্ক strcmp (ধ্রুব বর্ণ *__s1, ধ্রুব বর্ণ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
বাহ্য পূর্ণাঙ্ক strncmp (ধ্রুব বর্ণ *__s1, ধ্রুব বর্ণ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
বাহ্য পূর্ণাঙ্ক strcoll (ধ্রুব বর্ণ *__s1, ধ্রুব বর্ণ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
বাহ্য size_t strxfrm (বর্ণ *__restrict __dest,
		       ধ্রুব বর্ণ *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
বাহ্য পূর্ণাঙ্ক strcoll_l (ধ্রুব বর্ণ *__s1, ধ্রুব বর্ণ *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
বাহ্য size_t strxfrm_l (বর্ণ *__dest, ধ্রুব বর্ণ *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#যদি (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
বাহ্য বর্ণ *strdup (ধ্রুব বর্ণ *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#যদি defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
বাহ্য বর্ণ *strndup (ধ্রুব বর্ণ *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#যদি defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ধ্রুব বর্ণ *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      বর্ণ *__new = (বর্ণ *) __builtin_alloca (__len);			      \
      (বর্ণ *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ধ্রুব বর্ণ *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      বর্ণ *__new = (বর্ণ *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (বর্ণ *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++"
{
বাহ্য বর্ণ *strchr (বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
বাহ্য ধ্রুব বর্ণ *strchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline বর্ণ *
strchr (বর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  প্রত্যাগম __builtin_strchr (__s, __c);
}

__extern_always_inline ধ্রুব বর্ণ *
strchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  প্রত্যাগম __builtin_strchr (__s, __c);
}
# endif
}
#অন্যথা
বাহ্য বর্ণ *strchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ধ্রুব বর্ণ *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++"
{
বাহ্য বর্ণ *strrchr (বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
বাহ্য ধ্রুব বর্ণ *strrchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline বর্ণ *
strrchr (বর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  প্রত্যাগম __builtin_strrchr (__s, __c);
}

__extern_always_inline ধ্রুব বর্ণ *
strrchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  প্রত্যাগম __builtin_strrchr (__s, __c);
}
# endif
}
#অন্যথা
বাহ্য বর্ণ *strrchr (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ধ্রুব বর্ণ *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++" বর্ণ *strchrnul (বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
বাহ্য "C++" ধ্রুব বর্ণ *strchrnul (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# অন্যথা
বাহ্য বর্ণ *strchrnul (ধ্রুব বর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
বাহ্য size_t strcspn (ধ্রুব বর্ণ *__s, ধ্রুব বর্ণ *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
বাহ্য size_t strspn (ধ্রুব বর্ণ *__s, ধ্রুব বর্ণ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++"
{
বাহ্য বর্ণ *strpbrk (বর্ণ *__s, ধ্রুব বর্ণ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
বাহ্য ধ্রুব বর্ণ *strpbrk (ধ্রুব বর্ণ *__s, ধ্রুব বর্ণ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline বর্ণ *
strpbrk (বর্ণ *__s, ধ্রুব বর্ণ *__accept) __THROW
{
  প্রত্যাগম __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ধ্রুব বর্ণ *
strpbrk (ধ্রুব বর্ণ *__s, ধ্রুব বর্ণ *__accept) __THROW
{
  প্রত্যাগম __builtin_strpbrk (__s, __accept);
}
# endif
}
#অন্যথা
বাহ্য বর্ণ *strpbrk (ধ্রুব বর্ণ *__s, ধ্রুব বর্ণ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ধ্রুব বর্ণ *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++"
{
বাহ্য বর্ণ *strstr (বর্ণ *__haystack, ধ্রুব বর্ণ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
বাহ্য ধ্রুব বর্ণ *strstr (ধ্রুব বর্ণ *__haystack, ধ্রুব বর্ণ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline বর্ণ *
strstr (বর্ণ *__haystack, ধ্রুব বর্ণ *__needle) __THROW
{
  প্রত্যাগম __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ধ্রুব বর্ণ *
strstr (ধ্রুব বর্ণ *__haystack, ধ্রুব বর্ণ *__needle) __THROW
{
  প্রত্যাগম __builtin_strstr (__haystack, __needle);
}
# endif
}
#অন্যথা
বাহ্য বর্ণ *strstr (ধ্রুব বর্ণ *__haystack, ধ্রুব বর্ণ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ধ্রুব বর্ণ *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
বাহ্য বর্ণ *strtok (বর্ণ *__restrict __s, ধ্রুব বর্ণ *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
বাহ্য বর্ণ *__strtok_r (বর্ণ *__restrict __s,
			 ধ্রুব বর্ণ *__restrict __delim,
			 বর্ণ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
বাহ্য বর্ণ *strtok_r (বর্ণ *__restrict __s, ধ্রুব বর্ণ *__restrict __delim,
		       বর্ণ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++" বর্ণ *strcasestr (বর্ণ *__haystack, ধ্রুব বর্ণ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
বাহ্য "C++" ধ্রুব বর্ণ *strcasestr (ধ্রুব বর্ণ *__haystack,
				     ধ্রুব বর্ণ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# অন্যথা
বাহ্য বর্ণ *strcasestr (ধ্রুব বর্ণ *__haystack, ধ্রুব বর্ণ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
বাহ্য শূন্য *memmem (ধ্রুব শূন্য *__haystack, size_t __haystacklen,
		     ধ্রুব শূন্য *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
বাহ্য শূন্য *__mempcpy (শূন্য *__restrict __dest,
			ধ্রুব শূন্য *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
বাহ্য শূন্য *mempcpy (শূন্য *__restrict __dest,
		      ধ্রুব শূন্য *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
বাহ্য size_t strlen (ধ্রুব বর্ণ *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
বাহ্য size_t strnlen (ধ্রুব বর্ণ *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
বাহ্য বর্ণ *strerror (পূর্ণাঙ্ক __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# যদি defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
বাহ্য পূর্ণাঙ্ক __REDIRECT_NTH (strerror_r,
			   (পূর্ণাঙ্ক __errnum, বর্ণ *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  অন্যথা
বাহ্য পূর্ণাঙ্ক __xpg_strerror_r (পূর্ণাঙ্ক __errnum, বর্ণ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# অন্যথা
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
বাহ্য বর্ণ *strerror_r (পূর্ণাঙ্ক __errnum, বর্ণ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
বাহ্য ধ্রুব বর্ণ *strerrordesc_np (পূর্ণাঙ্ক __err) __THROW;
/* Return a string with the error name in ERR.  */
বাহ্য ধ্রুব বর্ণ *strerrorname_np (পূর্ণাঙ্ক __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
বাহ্য বর্ণ *strerror_l (পূর্ণাঙ্ক __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
বাহ্য শূন্য explicit_bzero (শূন্য *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
বাহ্য বর্ণ *strsep (বর্ণ **__restrict __stringp,
		     ধ্রুব বর্ণ *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
বাহ্য বর্ণ *strsignal (পূর্ণাঙ্ক __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
বাহ্য ধ্রুব বর্ণ *sigabbrev_np (পূর্ণাঙ্ক __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
বাহ্য ধ্রুব বর্ণ *sigdescr_np (পূর্ণাঙ্ক __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
বাহ্য বর্ণ *__stpcpy (বর্ণ *__restrict __dest, ধ্রুব বর্ণ *__restrict __src)
     __THROW __nonnull ((1, 2));
বাহ্য বর্ণ *stpcpy (বর্ণ *__restrict __dest, ধ্রুব বর্ণ *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
বাহ্য বর্ণ *__stpncpy (বর্ণ *__restrict __dest,
			ধ্রুব বর্ণ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
বাহ্য বর্ণ *stpncpy (বর্ণ *__restrict __dest,
		      ধ্রুব বর্ণ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
বাহ্য size_t strlcpy (বর্ণ *__restrict __dest,
		       ধ্রুব বর্ণ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
বাহ্য size_t strlcat (বর্ণ *__restrict __dest,
		       ধ্রুব বর্ণ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
বাহ্য পূর্ণাঙ্ক strverscmp (ধ্রুব বর্ণ *__s1, ধ্রুব বর্ণ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
বাহ্য বর্ণ *strfry (বর্ণ *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
বাহ্য শূন্য *memfrob (শূন্য *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্য "C++" বর্ণ *basename (বর্ণ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
বাহ্য "C++" ধ্রুব বর্ণ *basename (ধ্রুব বর্ণ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  অন্যথা
বাহ্য বর্ণ *basename (ধ্রুব বর্ণ *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#যদি __GNUC_PREREQ (3,4)
# যদি __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
