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
বাহ্যিক শূন্য *memcpy (শূন্য *__restrict __dest, ধ্রুবক শূন্য *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
বাহ্যিক শূন্য *memmove (শূন্য *__dest, ধ্রুবক শূন্য *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#যদি defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
বাহ্যিক শূন্য *memccpy (শূন্য *__restrict __dest, ধ্রুবক শূন্য *__restrict __src,
		      পূর্ণসংখ্যা __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
বাহ্যিক শূন্য *memset (শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n) __THROW __nonnull ((1));

#যদি defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
বাহ্যিক শূন্য *memset_explicit (শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
বাহ্যিক পূর্ণসংখ্যা memcmp (ধ্রুবক শূন্য *__s1, ধ্রুবক শূন্য *__s2, size_t __n)
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
বাহ্যিক পূর্ণসংখ্যা __memcmpeq (ধ্রুবক শূন্য *__s1, ধ্রুবক শূন্য *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++"
{
বাহ্যিক শূন্য *memchr (শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
বাহ্যিক ধ্রুবক শূন্য *memchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline শূন্য *
memchr (শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n) __THROW
{
  ফেরত __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ধ্রুবক শূন্য *
memchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n) __THROW
{
  ফেরত __builtin_memchr (__s, __c, __n);
}
# endif
}
#অন্যথা
বাহ্যিক শূন্য *memchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ধ্রুবক শূন্য *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++" শূন্য *rawmemchr (শূন্য *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
বাহ্যিক "C++" ধ্রুবক শূন্য *rawmemchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# অন্যথা
বাহ্যিক শূন্য *rawmemchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++" শূন্য *memrchr (শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
বাহ্যিক "C++" ধ্রুবক শূন্য *memrchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# অন্যথা
বাহ্যিক শূন্য *memrchr (ধ্রুবক শূন্য *__s, পূর্ণসংখ্যা __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
বাহ্যিক অক্ষর *strcpy (অক্ষর *__restrict __dest, ধ্রুবক অক্ষর *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
বাহ্যিক অক্ষর *strncpy (অক্ষর *__restrict __dest,
		      ধ্রুবক অক্ষর *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
বাহ্যিক অক্ষর *strcat (অক্ষর *__restrict __dest, ধ্রুবক অক্ষর *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
বাহ্যিক অক্ষর *strncat (অক্ষর *__restrict __dest, ধ্রুবক অক্ষর *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
বাহ্যিক পূর্ণসংখ্যা strcmp (ধ্রুবক অক্ষর *__s1, ধ্রুবক অক্ষর *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
বাহ্যিক পূর্ণসংখ্যা strncmp (ধ্রুবক অক্ষর *__s1, ধ্রুবক অক্ষর *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
বাহ্যিক পূর্ণসংখ্যা strcoll (ধ্রুবক অক্ষর *__s1, ধ্রুবক অক্ষর *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
বাহ্যিক size_t strxfrm (অক্ষর *__restrict __dest,
		       ধ্রুবক অক্ষর *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
বাহ্যিক পূর্ণসংখ্যা strcoll_l (ধ্রুবক অক্ষর *__s1, ধ্রুবক অক্ষর *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
বাহ্যিক size_t strxfrm_l (অক্ষর *__dest, ধ্রুবক অক্ষর *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#যদি (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
বাহ্যিক অক্ষর *strdup (ধ্রুবক অক্ষর *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#যদি defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
বাহ্যিক অক্ষর *strndup (ধ্রুবক অক্ষর *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#যদি defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ধ্রুবক অক্ষর *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      অক্ষর *__new = (অক্ষর *) __builtin_alloca (__len);			      \
      (অক্ষর *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ধ্রুবক অক্ষর *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      অক্ষর *__new = (অক্ষর *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (অক্ষর *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++"
{
বাহ্যিক অক্ষর *strchr (অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
বাহ্যিক ধ্রুবক অক্ষর *strchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline অক্ষর *
strchr (অক্ষর *__s, পূর্ণসংখ্যা __c) __THROW
{
  ফেরত __builtin_strchr (__s, __c);
}

__extern_always_inline ধ্রুবক অক্ষর *
strchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c) __THROW
{
  ফেরত __builtin_strchr (__s, __c);
}
# endif
}
#অন্যথা
বাহ্যিক অক্ষর *strchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ধ্রুবক অক্ষর *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++"
{
বাহ্যিক অক্ষর *strrchr (অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
বাহ্যিক ধ্রুবক অক্ষর *strrchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline অক্ষর *
strrchr (অক্ষর *__s, পূর্ণসংখ্যা __c) __THROW
{
  ফেরত __builtin_strrchr (__s, __c);
}

__extern_always_inline ধ্রুবক অক্ষর *
strrchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c) __THROW
{
  ফেরত __builtin_strrchr (__s, __c);
}
# endif
}
#অন্যথা
বাহ্যিক অক্ষর *strrchr (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __attribute_pure__ __nonnull ((1));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ধ্রুবক অক্ষর *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++" অক্ষর *strchrnul (অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
বাহ্যিক "C++" ধ্রুবক অক্ষর *strchrnul (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# অন্যথা
বাহ্যিক অক্ষর *strchrnul (ধ্রুবক অক্ষর *__s, পূর্ণসংখ্যা __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
বাহ্যিক size_t strcspn (ধ্রুবক অক্ষর *__s, ধ্রুবক অক্ষর *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
বাহ্যিক size_t strspn (ধ্রুবক অক্ষর *__s, ধ্রুবক অক্ষর *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++"
{
বাহ্যিক অক্ষর *strpbrk (অক্ষর *__s, ধ্রুবক অক্ষর *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
বাহ্যিক ধ্রুবক অক্ষর *strpbrk (ধ্রুবক অক্ষর *__s, ধ্রুবক অক্ষর *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline অক্ষর *
strpbrk (অক্ষর *__s, ধ্রুবক অক্ষর *__accept) __THROW
{
  ফেরত __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ধ্রুবক অক্ষর *
strpbrk (ধ্রুবক অক্ষর *__s, ধ্রুবক অক্ষর *__accept) __THROW
{
  ফেরত __builtin_strpbrk (__s, __accept);
}
# endif
}
#অন্যথা
বাহ্যিক অক্ষর *strpbrk (ধ্রুবক অক্ষর *__s, ধ্রুবক অক্ষর *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ধ্রুবক অক্ষর *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++"
{
বাহ্যিক অক্ষর *strstr (অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
বাহ্যিক ধ্রুবক অক্ষর *strstr (ধ্রুবক অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline অক্ষর *
strstr (অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle) __THROW
{
  ফেরত __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ধ্রুবক অক্ষর *
strstr (ধ্রুবক অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle) __THROW
{
  ফেরত __builtin_strstr (__haystack, __needle);
}
# endif
}
#অন্যথা
বাহ্যিক অক্ষর *strstr (ধ্রুবক অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# যদি __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ধ্রুবক অক্ষর *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
বাহ্যিক অক্ষর *strtok (অক্ষর *__restrict __s, ধ্রুবক অক্ষর *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
বাহ্যিক অক্ষর *__strtok_r (অক্ষর *__restrict __s,
			 ধ্রুবক অক্ষর *__restrict __delim,
			 অক্ষর **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
বাহ্যিক অক্ষর *strtok_r (অক্ষর *__restrict __s, ধ্রুবক অক্ষর *__restrict __delim,
		       অক্ষর **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++" অক্ষর *strcasestr (অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
বাহ্যিক "C++" ধ্রুবক অক্ষর *strcasestr (ধ্রুবক অক্ষর *__haystack,
				     ধ্রুবক অক্ষর *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# অন্যথা
বাহ্যিক অক্ষর *strcasestr (ধ্রুবক অক্ষর *__haystack, ধ্রুবক অক্ষর *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
বাহ্যিক শূন্য *memmem (ধ্রুবক শূন্য *__haystack, size_t __haystacklen,
		     ধ্রুবক শূন্য *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
বাহ্যিক শূন্য *__mempcpy (শূন্য *__restrict __dest,
			ধ্রুবক শূন্য *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
বাহ্যিক শূন্য *mempcpy (শূন্য *__restrict __dest,
		      ধ্রুবক শূন্য *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
বাহ্যিক size_t strlen (ধ্রুবক অক্ষর *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
বাহ্যিক size_t strnlen (ধ্রুবক অক্ষর *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
বাহ্যিক অক্ষর *strerror (পূর্ণসংখ্যা __errnum) __THROW;
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
বাহ্যিক পূর্ণসংখ্যা __REDIRECT_NTH (strerror_r,
			   (পূর্ণসংখ্যা __errnum, অক্ষর *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  অন্যথা
বাহ্যিক পূর্ণসংখ্যা __xpg_strerror_r (পূর্ণসংখ্যা __errnum, অক্ষর *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# অন্যথা
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
বাহ্যিক অক্ষর *strerror_r (পূর্ণসংখ্যা __errnum, অক্ষর *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
বাহ্যিক ধ্রুবক অক্ষর *strerrordesc_np (পূর্ণসংখ্যা __err) __THROW;
/* Return a string with the error name in ERR.  */
বাহ্যিক ধ্রুবক অক্ষর *strerrorname_np (পূর্ণসংখ্যা __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
বাহ্যিক অক্ষর *strerror_l (পূর্ণসংখ্যা __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
বাহ্যিক শূন্য explicit_bzero (শূন্য *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
বাহ্যিক অক্ষর *strsep (অক্ষর **__restrict __stringp,
		     ধ্রুবক অক্ষর *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
বাহ্যিক অক্ষর *strsignal (পূর্ণসংখ্যা __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
বাহ্যিক ধ্রুবক অক্ষর *sigabbrev_np (পূর্ণসংখ্যা __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
বাহ্যিক ধ্রুবক অক্ষর *sigdescr_np (পূর্ণসংখ্যা __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
বাহ্যিক অক্ষর *__stpcpy (অক্ষর *__restrict __dest, ধ্রুবক অক্ষর *__restrict __src)
     __THROW __nonnull ((1, 2));
বাহ্যিক অক্ষর *stpcpy (অক্ষর *__restrict __dest, ধ্রুবক অক্ষর *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
বাহ্যিক অক্ষর *__stpncpy (অক্ষর *__restrict __dest,
			ধ্রুবক অক্ষর *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
বাহ্যিক অক্ষর *stpncpy (অক্ষর *__restrict __dest,
		      ধ্রুবক অক্ষর *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
বাহ্যিক size_t strlcpy (অক্ষর *__restrict __dest,
		       ধ্রুবক অক্ষর *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
বাহ্যিক size_t strlcat (অক্ষর *__restrict __dest,
		       ধ্রুবক অক্ষর *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
বাহ্যিক পূর্ণসংখ্যা strverscmp (ধ্রুবক অক্ষর *__s1, ধ্রুবক অক্ষর *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
বাহ্যিক অক্ষর *strfry (অক্ষর *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
বাহ্যিক শূন্য *memfrob (শূন্য *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
বাহ্যিক "C++" অক্ষর *basename (অক্ষর *__filename)
     __THROW __asm ("basename") __nonnull ((1));
বাহ্যিক "C++" ধ্রুবক অক্ষর *basename (ধ্রুবক অক্ষর *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  অন্যথা
বাহ্যিক অক্ষর *basename (ধ্রুবক অক্ষর *__filename) __THROW __nonnull ((1));
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
