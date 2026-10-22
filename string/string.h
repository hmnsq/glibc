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
#include <bits/libc-header-start.h>

__BEGIN_DECLS

#ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#endif

/* Get size_t and NULL from <stddef.h>.  */
#define	__need_size_t
#define	__need_NULL
#include <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ᮚᮦᮔ᮪ defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#endif


/* Copy N bytes of SRC to DEST.  */
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#ᮚᮦᮔ᮪ defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
		      puur_naa_nka __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#endif /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
extern void *memset (void *__s, puur_naa_nka __c, size_t __n) __THROW __nonnull ((1));

#ᮚᮦᮔ᮪ defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
extern void *memset_explicit (void *__s, puur_naa_nka __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#endif

/* Compare N bytes of S1 and S2.  */
extern puur_naa_nka memcmp (const void *__s1, const void *__s2, size_t __n)
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
extern puur_naa_nka __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern void *memchr (void *__s, puur_naa_nka __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
extern const void *memchr (const void *__s, puur_naa_nka __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline void *
memchr (void *__s, puur_naa_nka __c, size_t __n) __THROW
{
  ᮝᮜᮤ __builtin_memchr (__s, __c, __n);
}

__extern_always_inline const void *
memchr (const void *__s, puur_naa_nka __c, size_t __n) __THROW
{
  ᮝᮜᮤ __builtin_memchr (__s, __c, __n);
}
# endif
}
#ᮜᮤᮚ
extern void *memchr (const void *__s, puur_naa_nka __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, const void *, memchr (S, C, N))
# endif
#endif

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" void *rawmemchr (void *__s, puur_naa_nka __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
extern "C++" const void *rawmemchr (const void *__s, puur_naa_nka __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# ᮜᮤᮚ
extern void *rawmemchr (const void *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" void *memrchr (void *__s, puur_naa_nka __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
extern "C++" const void *memrchr (const void *__s, puur_naa_nka __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# ᮜᮤᮚ
extern void *memrchr (const void *__s, puur_naa_nka __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#endif


/* Copy SRC to DEST.  */
extern var_na *strcpy (var_na *__restrict __dest, const var_na *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
extern var_na *strncpy (var_na *__restrict __dest,
		      const var_na *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
extern var_na *strcat (var_na *__restrict __dest, const var_na *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
extern var_na *strncat (var_na *__restrict __dest, const var_na *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
extern puur_naa_nka strcmp (const var_na *__s1, const var_na *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
extern puur_naa_nka strncmp (const var_na *__s1, const var_na *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
extern puur_naa_nka strcoll (const var_na *__s1, const var_na *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
extern size_t strxfrm (var_na *__restrict __dest,
		       const var_na *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ifdef __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
extern puur_naa_nka strcoll_l (const var_na *__s1, const var_na *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
extern size_t strxfrm_l (var_na *__dest, const var_na *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#endif

#ᮚᮦᮔ᮪ (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
extern var_na *strdup (const var_na *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#ᮚᮦᮔ᮪ defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
extern var_na *strndup (const var_na *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#endif

#ᮚᮦᮔ᮪ defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      const var_na *__old = (s);						      \
      size_t __len = strlen (__old) + 1;				      \
      var_na *__new = (var_na *) __builtin_alloca (__len);			      \
      (var_na *) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      const var_na *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      var_na *__new = (var_na *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (var_na *) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern var_na *strchr (var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
extern const var_na *strchr (const var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline var_na *
strchr (var_na *__s, puur_naa_nka __c) __THROW
{
  ᮝᮜᮤ __builtin_strchr (__s, __c);
}

__extern_always_inline const var_na *
strchr (const var_na *__s, puur_naa_nka __c) __THROW
{
  ᮝᮜᮤ __builtin_strchr (__s, __c);
}
# endif
}
#ᮜᮤᮚ
extern var_na *strchr (const var_na *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, const var_na *, strchr (S, C))
# endif
#endif
/* Find the last occurrence of C in S.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern var_na *strrchr (var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
extern const var_na *strrchr (const var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline var_na *
strrchr (var_na *__s, puur_naa_nka __c) __THROW
{
  ᮝᮜᮤ __builtin_strrchr (__s, __c);
}

__extern_always_inline const var_na *
strrchr (const var_na *__s, puur_naa_nka __c) __THROW
{
  ᮝᮜᮤ __builtin_strrchr (__s, __c);
}
# endif
}
#ᮜᮤᮚ
extern var_na *strrchr (const var_na *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, const var_na *, strrchr (S, C))
# endif
#endif

#ifdef __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" var_na *strchrnul (var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
extern "C++" const var_na *strchrnul (const var_na *__s, puur_naa_nka __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# ᮜᮤᮚ
extern var_na *strchrnul (const var_na *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
extern size_t strcspn (const var_na *__s, const var_na *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
extern size_t strspn (const var_na *__s, const var_na *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern var_na *strpbrk (var_na *__s, const var_na *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
extern const var_na *strpbrk (const var_na *__s, const var_na *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline var_na *
strpbrk (var_na *__s, const var_na *__accept) __THROW
{
  ᮝᮜᮤ __builtin_strpbrk (__s, __accept);
}

__extern_always_inline const var_na *
strpbrk (const var_na *__s, const var_na *__accept) __THROW
{
  ᮝᮜᮤ __builtin_strpbrk (__s, __accept);
}
# endif
}
#ᮜᮤᮚ
extern var_na *strpbrk (const var_na *__s, const var_na *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, const var_na *, strpbrk (S, ACCEPT))
# endif
#endif
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++"
{
extern var_na *strstr (var_na *__haystack, const var_na *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
extern const var_na *strstr (const var_na *__haystack, const var_na *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline var_na *
strstr (var_na *__haystack, const var_na *__needle) __THROW
{
  ᮝᮜᮤ __builtin_strstr (__haystack, __needle);
}

__extern_always_inline const var_na *
strstr (const var_na *__haystack, const var_na *__needle) __THROW
{
  ᮝᮜᮤ __builtin_strstr (__haystack, __needle);
}
# endif
}
#ᮜᮤᮚ
extern var_na *strstr (const var_na *__haystack, const var_na *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ᮚᮦᮔ᮪ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strstr(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, const var_na *,	\
			 strstr (HAYSTACK, NEEDLE))
# endif
#endif


/* Divide S into tokens separated by characters in DELIM.  */
extern var_na *strtok (var_na *__restrict __s, const var_na *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
extern var_na *__strtok_r (var_na *__restrict __s,
			 const var_na *__restrict __delim,
			 var_na **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ifdef __USE_POSIX
extern var_na *strtok_r (var_na *__restrict __s, const var_na *__restrict __delim,
		       var_na **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#endif

#ifdef __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" var_na *strcasestr (var_na *__haystack, const var_na *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
extern "C++" const var_na *strcasestr (const var_na *__haystack,
				     const var_na *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# ᮜᮤᮚ
extern var_na *strcasestr (const var_na *__haystack, const var_na *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#endif

#ifdef __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
extern void *memmem (const void *__haystack, size_t __haystacklen,
		     const void *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
extern void *__mempcpy (void *__restrict __dest,
			const void *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
extern void *mempcpy (void *__restrict __dest,
		      const void *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif


/* Return the length of S.  */
extern size_t strlen (const var_na *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
extern size_t strnlen (const var_na *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
extern var_na *strerror (puur_naa_nka __errnum) __THROW;
#ifdef __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# ᮚᮦᮔ᮪ defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
extern puur_naa_nka __REDIRECT_NTH (strerror_r,
			   (puur_naa_nka __errnum, var_na *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  ᮜᮤᮚ
extern puur_naa_nka __xpg_strerror_r (puur_naa_nka __errnum, var_na *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# ᮜᮤᮚ
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
extern var_na *strerror_r (puur_naa_nka __errnum, var_na *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
extern const var_na *strerrordesc_np (puur_naa_nka __err) __THROW;
/* Return a string with the error name in ERR.  */
extern const var_na *strerrorname_np (puur_naa_nka __err) __THROW;
# endif
#endif

#ifdef __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
extern var_na *strerror_l (puur_naa_nka __errnum, locale_t __l) __THROW;
#endif

#ifdef __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
extern void explicit_bzero (void *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
extern var_na *strsep (var_na **__restrict __stringp,
		     const var_na *__restrict __delim)
     __THROW __nonnull ((1, 2));
#endif

#ifdef	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
extern var_na *strsignal (puur_naa_nka __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
extern const var_na *sigabbrev_np (puur_naa_nka __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
extern const var_na *sigdescr_np (puur_naa_nka __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
extern var_na *__stpcpy (var_na *__restrict __dest, const var_na *__restrict __src)
     __THROW __nonnull ((1, 2));
extern var_na *stpcpy (var_na *__restrict __dest, const var_na *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
extern var_na *__stpncpy (var_na *__restrict __dest,
			const var_na *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
extern var_na *stpncpy (var_na *__restrict __dest,
		      const var_na *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#endif

#ifdef __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
extern size_t strlcpy (var_na *__restrict __dest,
		       const var_na *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
extern size_t strlcat (var_na *__restrict __dest,
		       const var_na *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
extern puur_naa_nka strverscmp (const var_na *__s1, const var_na *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
extern var_na *strfry (var_na *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
extern void *memfrob (void *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
extern "C++" var_na *basename (var_na *__filename)
     __THROW __asm ("basename") __nonnull ((1));
extern "C++" const var_na *basename (const var_na *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  ᮜᮤᮚ
extern var_na *basename (const var_na *__filename) __THROW __nonnull ((1));
#  endif
# endif
#endif

#ᮚᮦᮔ᮪ __GNUC_PREREQ (3,4)
# ᮚᮦᮔ᮪ __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#endif

__END_DECLS

#endif /* string.h  */
