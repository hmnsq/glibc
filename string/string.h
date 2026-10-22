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
#شامل <bits/libc-header-start.h>

__BEGIN_DECLS

#اگر __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#شامل <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#اگر defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
بیرونی تهی *memcpy (تهی *__restrict __dest, ثابت تهی *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
بیرونی تهی *memmove (تهی *__dest, ثابت تهی *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#اگر defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
بیرونی تهی *memccpy (تهی *__restrict __dest, ثابت تهی *__restrict __src,
		      صحیح __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
بیرونی تهی *memset (تهی *__s, صحیح __c, size_t __n) __THROW __nonnull ((1));

#اگر defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
بیرونی تهی *memset_explicit (تهی *__s, صحیح __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
بیرونی صحیح memcmp (ثابت تهی *__s1, ثابت تهی *__s2, size_t __n)
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
بیرونی صحیح __memcmpeq (ثابت تهی *__s1, ثابت تهی *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++"
{
بیرونی تهی *memchr (تهی *__s, صحیح __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
بیرونی ثابت تهی *memchr (ثابت تهی *__s, صحیح __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline تهی *
memchr (تهی *__s, صحیح __c, size_t __n) __THROW
{
  بازگشت __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ثابت تهی *
memchr (ثابت تهی *__s, صحیح __c, size_t __n) __THROW
{
  بازگشت __builtin_memchr (__s, __c, __n);
}
# endif
}
#وگرنه
بیرونی تهی *memchr (ثابت تهی *__s, صحیح __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# اگر __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ثابت تهی *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++" تهی *rawmemchr (تهی *__s, صحیح __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
بیرونی "C++" ثابت تهی *rawmemchr (ثابت تهی *__s, صحیح __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# وگرنه
بیرونی تهی *rawmemchr (ثابت تهی *__s, صحیح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++" تهی *memrchr (تهی *__s, صحیح __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
بیرونی "C++" ثابت تهی *memrchr (ثابت تهی *__s, صحیح __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# وگرنه
بیرونی تهی *memrchr (ثابت تهی *__s, صحیح __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
بیرونی نویسه *strcpy (نویسه *__restrict __dest, ثابت نویسه *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
بیرونی نویسه *strncpy (نویسه *__restrict __dest,
		      ثابت نویسه *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
بیرونی نویسه *strcat (نویسه *__restrict __dest, ثابت نویسه *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
بیرونی نویسه *strncat (نویسه *__restrict __dest, ثابت نویسه *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
بیرونی صحیح strcmp (ثابت نویسه *__s1, ثابت نویسه *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
بیرونی صحیح strncmp (ثابت نویسه *__s1, ثابت نویسه *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
بیرونی صحیح strcoll (ثابت نویسه *__s1, ثابت نویسه *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
بیرونی size_t strxfrm (نویسه *__restrict __dest,
		       ثابت نویسه *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
بیرونی صحیح strcoll_l (ثابت نویسه *__s1, ثابت نویسه *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
بیرونی size_t strxfrm_l (نویسه *__dest, ثابت نویسه *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#اگر (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
بیرونی نویسه *strdup (ثابت نویسه *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#اگر defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
بیرونی نویسه *strndup (ثابت نویسه *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#اگر defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ثابت نویسه *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      نویسه *__new = (نویسه *) __builtin_alloca (__len);			      \
      (نویسه *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ثابت نویسه *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      نویسه *__new = (نویسه *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (نویسه *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++"
{
بیرونی نویسه *strchr (نویسه *__s, صحیح __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
بیرونی ثابت نویسه *strchr (ثابت نویسه *__s, صحیح __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline نویسه *
strchr (نویسه *__s, صحیح __c) __THROW
{
  بازگشت __builtin_strchr (__s, __c);
}

__extern_always_inline ثابت نویسه *
strchr (ثابت نویسه *__s, صحیح __c) __THROW
{
  بازگشت __builtin_strchr (__s, __c);
}
# endif
}
#وگرنه
بیرونی نویسه *strchr (ثابت نویسه *__s, صحیح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# اگر __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ثابت نویسه *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++"
{
بیرونی نویسه *strrchr (نویسه *__s, صحیح __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
بیرونی ثابت نویسه *strrchr (ثابت نویسه *__s, صحیح __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline نویسه *
strrchr (نویسه *__s, صحیح __c) __THROW
{
  بازگشت __builtin_strrchr (__s, __c);
}

__extern_always_inline ثابت نویسه *
strrchr (ثابت نویسه *__s, صحیح __c) __THROW
{
  بازگشت __builtin_strrchr (__s, __c);
}
# endif
}
#وگرنه
بیرونی نویسه *strrchr (ثابت نویسه *__s, صحیح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# اگر __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ثابت نویسه *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++" نویسه *strchrnul (نویسه *__s, صحیح __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
بیرونی "C++" ثابت نویسه *strchrnul (ثابت نویسه *__s, صحیح __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# وگرنه
بیرونی نویسه *strchrnul (ثابت نویسه *__s, صحیح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
بیرونی size_t strcspn (ثابت نویسه *__s, ثابت نویسه *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
بیرونی size_t strspn (ثابت نویسه *__s, ثابت نویسه *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++"
{
بیرونی نویسه *strpbrk (نویسه *__s, ثابت نویسه *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
بیرونی ثابت نویسه *strpbrk (ثابت نویسه *__s, ثابت نویسه *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline نویسه *
strpbrk (نویسه *__s, ثابت نویسه *__accept) __THROW
{
  بازگشت __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ثابت نویسه *
strpbrk (ثابت نویسه *__s, ثابت نویسه *__accept) __THROW
{
  بازگشت __builtin_strpbrk (__s, __accept);
}
# endif
}
#وگرنه
بیرونی نویسه *strpbrk (ثابت نویسه *__s, ثابت نویسه *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# اگر __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ثابت نویسه *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++"
{
بیرونی نویسه *strstr (نویسه *__haystack, ثابت نویسه *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
بیرونی ثابت نویسه *strstr (ثابت نویسه *__haystack, ثابت نویسه *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline نویسه *
strstr (نویسه *__haystack, ثابت نویسه *__needle) __THROW
{
  بازگشت __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ثابت نویسه *
strstr (ثابت نویسه *__haystack, ثابت نویسه *__needle) __THROW
{
  بازگشت __builtin_strstr (__haystack, __needle);
}
# endif
}
#وگرنه
بیرونی نویسه *strstr (ثابت نویسه *__haystack, ثابت نویسه *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# اگر __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ثابت نویسه *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
بیرونی نویسه *strtok (نویسه *__restrict __s, ثابت نویسه *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
بیرونی نویسه *__strtok_r (نویسه *__restrict __s,
			 ثابت نویسه *__restrict __delim,
			 نویسه **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
بیرونی نویسه *strtok_r (نویسه *__restrict __s, ثابت نویسه *__restrict __delim,
		       نویسه **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++" نویسه *strcasestr (نویسه *__haystack, ثابت نویسه *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
بیرونی "C++" ثابت نویسه *strcasestr (ثابت نویسه *__haystack,
				     ثابت نویسه *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# وگرنه
بیرونی نویسه *strcasestr (ثابت نویسه *__haystack, ثابت نویسه *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
بیرونی تهی *memmem (ثابت تهی *__haystack, size_t __haystacklen,
		     ثابت تهی *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
بیرونی تهی *__mempcpy (تهی *__restrict __dest,
			ثابت تهی *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
بیرونی تهی *mempcpy (تهی *__restrict __dest,
		      ثابت تهی *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
بیرونی size_t strlen (ثابت نویسه *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
بیرونی size_t strnlen (ثابت نویسه *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
بیرونی نویسه *strerror (صحیح __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# اگر defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
بیرونی صحیح __REDIRECT_NTH (strerror_r,
			   (صحیح __errnum, نویسه *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  وگرنه
بیرونی صحیح __xpg_strerror_r (صحیح __errnum, نویسه *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# وگرنه
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
بیرونی نویسه *strerror_r (صحیح __errnum, نویسه *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
بیرونی ثابت نویسه *strerrordesc_np (صحیح __err) __THROW;
/* Return a string with the error name in ERR.  */
بیرونی ثابت نویسه *strerrorname_np (صحیح __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
بیرونی نویسه *strerror_l (صحیح __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
بیرونی تهی explicit_bzero (تهی *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
بیرونی نویسه *strsep (نویسه **__restrict __stringp,
		     ثابت نویسه *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
بیرونی نویسه *strsignal (صحیح __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
بیرونی ثابت نویسه *sigabbrev_np (صحیح __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
بیرونی ثابت نویسه *sigdescr_np (صحیح __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
بیرونی نویسه *__stpcpy (نویسه *__restrict __dest, ثابت نویسه *__restrict __src)
     __THROW __nonnull ((1, 2));
بیرونی نویسه *stpcpy (نویسه *__restrict __dest, ثابت نویسه *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
بیرونی نویسه *__stpncpy (نویسه *__restrict __dest,
			ثابت نویسه *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
بیرونی نویسه *stpncpy (نویسه *__restrict __dest,
		      ثابت نویسه *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
بیرونی size_t strlcpy (نویسه *__restrict __dest,
		       ثابت نویسه *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
بیرونی size_t strlcat (نویسه *__restrict __dest,
		       ثابت نویسه *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
بیرونی صحیح strverscmp (ثابت نویسه *__s1, ثابت نویسه *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
بیرونی نویسه *strfry (نویسه *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
بیرونی تهی *memfrob (تهی *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
بیرونی "C++" نویسه *basename (نویسه *__filename)
     __THROW __asm ("basename") __nonnull ((1));
بیرونی "C++" ثابت نویسه *basename (ثابت نویسه *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  وگرنه
بیرونی نویسه *basename (ثابت نویسه *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#اگر __GNUC_PREREQ (3,4)
# اگر __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
