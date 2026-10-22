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
#अन्तर्भाव <bits/libc-header-start.h>

__BEGIN_DECLS

#यदि __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#अन्तर्भाव <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#यदि defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
बाह्य शून्य *memcpy (शून्य *__restrict __dest, ध्रुव शून्य *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
बाह्य शून्य *memmove (शून्य *__dest, ध्रुव शून्य *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#यदि defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
बाह्य शून्य *memccpy (शून्य *__restrict __dest, ध्रुव शून्य *__restrict __src,
		      पूर्णाङ्क __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
बाह्य शून्य *memset (शून्य *__s, पूर्णाङ्क __c, size_t __n) __THROW __nonnull ((1));

#यदि defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
बाह्य शून्य *memset_explicit (शून्य *__s, पूर्णाङ्क __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
बाह्य पूर्णाङ्क memcmp (ध्रुव शून्य *__s1, ध्रुव शून्य *__s2, size_t __n)
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
बाह्य पूर्णाङ्क __memcmpeq (ध्रुव शून्य *__s1, ध्रुव शून्य *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य शून्य *memchr (शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
बाह्य ध्रुव शून्य *memchr (ध्रुव शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline शून्य *
memchr (शून्य *__s, पूर्णाङ्क __c, size_t __n) __THROW
{
  प्रत्यागम __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ध्रुव शून्य *
memchr (ध्रुव शून्य *__s, पूर्णाङ्क __c, size_t __n) __THROW
{
  प्रत्यागम __builtin_memchr (__s, __c, __n);
}
# endif
}
#अन्यथा
बाह्य शून्य *memchr (ध्रुव शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# यदि __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ध्रुव शून्य *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" शून्य *rawmemchr (शून्य *__s, पूर्णाङ्क __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
बाह्य "C++" ध्रुव शून्य *rawmemchr (ध्रुव शून्य *__s, पूर्णाङ्क __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# अन्यथा
बाह्य शून्य *rawmemchr (ध्रुव शून्य *__s, पूर्णाङ्क __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" शून्य *memrchr (शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
बाह्य "C++" ध्रुव शून्य *memrchr (ध्रुव शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# अन्यथा
बाह्य शून्य *memrchr (ध्रुव शून्य *__s, पूर्णाङ्क __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
बाह्य वर्ण *strcpy (वर्ण *__restrict __dest, ध्रुव वर्ण *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
बाह्य वर्ण *strncpy (वर्ण *__restrict __dest,
		      ध्रुव वर्ण *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
बाह्य वर्ण *strcat (वर्ण *__restrict __dest, ध्रुव वर्ण *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
बाह्य वर्ण *strncat (वर्ण *__restrict __dest, ध्रुव वर्ण *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
बाह्य पूर्णाङ्क strcmp (ध्रुव वर्ण *__s1, ध्रुव वर्ण *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
बाह्य पूर्णाङ्क strncmp (ध्रुव वर्ण *__s1, ध्रुव वर्ण *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
बाह्य पूर्णाङ्क strcoll (ध्रुव वर्ण *__s1, ध्रुव वर्ण *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
बाह्य size_t strxfrm (वर्ण *__restrict __dest,
		       ध्रुव वर्ण *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
बाह्य पूर्णाङ्क strcoll_l (ध्रुव वर्ण *__s1, ध्रुव वर्ण *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
बाह्य size_t strxfrm_l (वर्ण *__dest, ध्रुव वर्ण *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#यदि (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
बाह्य वर्ण *strdup (ध्रुव वर्ण *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#यदि defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
बाह्य वर्ण *strndup (ध्रुव वर्ण *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#यदि defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ध्रुव वर्ण *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      वर्ण *__new = (वर्ण *) __builtin_alloca (__len);			      \
      (वर्ण *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ध्रुव वर्ण *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      वर्ण *__new = (वर्ण *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (वर्ण *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य वर्ण *strchr (वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
बाह्य ध्रुव वर्ण *strchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline वर्ण *
strchr (वर्ण *__s, पूर्णाङ्क __c) __THROW
{
  प्रत्यागम __builtin_strchr (__s, __c);
}

__extern_always_inline ध्रुव वर्ण *
strchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c) __THROW
{
  प्रत्यागम __builtin_strchr (__s, __c);
}
# endif
}
#अन्यथा
बाह्य वर्ण *strchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __attribute_pure__ __nonnull ((1));
# यदि __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ध्रुव वर्ण *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य वर्ण *strrchr (वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
बाह्य ध्रुव वर्ण *strrchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline वर्ण *
strrchr (वर्ण *__s, पूर्णाङ्क __c) __THROW
{
  प्रत्यागम __builtin_strrchr (__s, __c);
}

__extern_always_inline ध्रुव वर्ण *
strrchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c) __THROW
{
  प्रत्यागम __builtin_strrchr (__s, __c);
}
# endif
}
#अन्यथा
बाह्य वर्ण *strrchr (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __attribute_pure__ __nonnull ((1));
# यदि __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ध्रुव वर्ण *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" वर्ण *strchrnul (वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
बाह्य "C++" ध्रुव वर्ण *strchrnul (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# अन्यथा
बाह्य वर्ण *strchrnul (ध्रुव वर्ण *__s, पूर्णाङ्क __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
बाह्य size_t strcspn (ध्रुव वर्ण *__s, ध्रुव वर्ण *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
बाह्य size_t strspn (ध्रुव वर्ण *__s, ध्रुव वर्ण *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य वर्ण *strpbrk (वर्ण *__s, ध्रुव वर्ण *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
बाह्य ध्रुव वर्ण *strpbrk (ध्रुव वर्ण *__s, ध्रुव वर्ण *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline वर्ण *
strpbrk (वर्ण *__s, ध्रुव वर्ण *__accept) __THROW
{
  प्रत्यागम __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ध्रुव वर्ण *
strpbrk (ध्रुव वर्ण *__s, ध्रुव वर्ण *__accept) __THROW
{
  प्रत्यागम __builtin_strpbrk (__s, __accept);
}
# endif
}
#अन्यथा
बाह्य वर्ण *strpbrk (ध्रुव वर्ण *__s, ध्रुव वर्ण *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# यदि __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ध्रुव वर्ण *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++"
{
बाह्य वर्ण *strstr (वर्ण *__haystack, ध्रुव वर्ण *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
बाह्य ध्रुव वर्ण *strstr (ध्रुव वर्ण *__haystack, ध्रुव वर्ण *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline वर्ण *
strstr (वर्ण *__haystack, ध्रुव वर्ण *__needle) __THROW
{
  प्रत्यागम __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ध्रुव वर्ण *
strstr (ध्रुव वर्ण *__haystack, ध्रुव वर्ण *__needle) __THROW
{
  प्रत्यागम __builtin_strstr (__haystack, __needle);
}
# endif
}
#अन्यथा
बाह्य वर्ण *strstr (ध्रुव वर्ण *__haystack, ध्रुव वर्ण *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# यदि __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ध्रुव वर्ण *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
बाह्य वर्ण *strtok (वर्ण *__restrict __s, ध्रुव वर्ण *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
बाह्य वर्ण *__strtok_r (वर्ण *__restrict __s,
			 ध्रुव वर्ण *__restrict __delim,
			 वर्ण **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
बाह्य वर्ण *strtok_r (वर्ण *__restrict __s, ध्रुव वर्ण *__restrict __delim,
		       वर्ण **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" वर्ण *strcasestr (वर्ण *__haystack, ध्रुव वर्ण *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
बाह्य "C++" ध्रुव वर्ण *strcasestr (ध्रुव वर्ण *__haystack,
				     ध्रुव वर्ण *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# अन्यथा
बाह्य वर्ण *strcasestr (ध्रुव वर्ण *__haystack, ध्रुव वर्ण *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
बाह्य शून्य *memmem (ध्रुव शून्य *__haystack, size_t __haystacklen,
		     ध्रुव शून्य *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
बाह्य शून्य *__mempcpy (शून्य *__restrict __dest,
			ध्रुव शून्य *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
बाह्य शून्य *mempcpy (शून्य *__restrict __dest,
		      ध्रुव शून्य *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
बाह्य size_t strlen (ध्रुव वर्ण *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
बाह्य size_t strnlen (ध्रुव वर्ण *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
बाह्य वर्ण *strerror (पूर्णाङ्क __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# यदि defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
बाह्य पूर्णाङ्क __REDIRECT_NTH (strerror_r,
			   (पूर्णाङ्क __errnum, वर्ण *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  अन्यथा
बाह्य पूर्णाङ्क __xpg_strerror_r (पूर्णाङ्क __errnum, वर्ण *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# अन्यथा
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
बाह्य वर्ण *strerror_r (पूर्णाङ्क __errnum, वर्ण *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
बाह्य ध्रुव वर्ण *strerrordesc_np (पूर्णाङ्क __err) __THROW;
/* Return a string with the error name in ERR.  */
बाह्य ध्रुव वर्ण *strerrorname_np (पूर्णाङ्क __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
बाह्य वर्ण *strerror_l (पूर्णाङ्क __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
बाह्य शून्य explicit_bzero (शून्य *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
बाह्य वर्ण *strsep (वर्ण **__restrict __stringp,
		     ध्रुव वर्ण *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
बाह्य वर्ण *strsignal (पूर्णाङ्क __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
बाह्य ध्रुव वर्ण *sigabbrev_np (पूर्णाङ्क __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
बाह्य ध्रुव वर्ण *sigdescr_np (पूर्णाङ्क __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
बाह्य वर्ण *__stpcpy (वर्ण *__restrict __dest, ध्रुव वर्ण *__restrict __src)
     __THROW __nonnull ((1, 2));
बाह्य वर्ण *stpcpy (वर्ण *__restrict __dest, ध्रुव वर्ण *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
बाह्य वर्ण *__stpncpy (वर्ण *__restrict __dest,
			ध्रुव वर्ण *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
बाह्य वर्ण *stpncpy (वर्ण *__restrict __dest,
		      ध्रुव वर्ण *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
बाह्य size_t strlcpy (वर्ण *__restrict __dest,
		       ध्रुव वर्ण *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
बाह्य size_t strlcat (वर्ण *__restrict __dest,
		       ध्रुव वर्ण *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
बाह्य पूर्णाङ्क strverscmp (ध्रुव वर्ण *__s1, ध्रुव वर्ण *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
बाह्य वर्ण *strfry (वर्ण *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
बाह्य शून्य *memfrob (शून्य *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
बाह्य "C++" वर्ण *basename (वर्ण *__filename)
     __THROW __asm ("basename") __nonnull ((1));
बाह्य "C++" ध्रुव वर्ण *basename (ध्रुव वर्ण *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  अन्यथा
बाह्य वर्ण *basename (ध्रुव वर्ण *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#यदि __GNUC_PREREQ (3,4)
# यदि __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
