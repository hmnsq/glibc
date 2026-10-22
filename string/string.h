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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ	_STRING_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	_STRING_H	1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#ਅਨ੍ਤਰ੍ਭਾਵ <bits/libc-header-start.h>

__BEGIN_DECLS

#ਜੇ __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#ਜੇ_ਅੰਤ

/* Get size_t and NULL from <stddef.h>.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	__need_size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	__need_NULL
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ਜੇ defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#ਜੇ_ਅੰਤ


/* Copy N bytes of SRC to DEST.  */
ਬਾਹਰੀ ਖਾਲੀ *ਸਮ੍ਰਿਤੀ_ਨਕਲ (ਖਾਲੀ *__restrict __dest, ਅਚਲ ਖਾਲੀ *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
ਬਾਹਰੀ ਖਾਲੀ *memmove (ਖਾਲੀ *__dest, ਅਚਲ ਖਾਲੀ *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#ਜੇ defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
ਬਾਹਰੀ ਖਾਲੀ *memccpy (ਖਾਲੀ *__restrict __dest, ਅਚਲ ਖਾਲੀ *__restrict __src,
		      ਪੂਰਨ __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#ਜੇ_ਅੰਤ /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
ਬਾਹਰੀ ਖਾਲੀ *memset (ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n) __THROW __nonnull ((1));

#ਜੇ defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
ਬਾਹਰੀ ਖਾਲੀ *memset_explicit (ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#ਜੇ_ਅੰਤ

/* Compare N bytes of S1 and S2.  */
ਬਾਹਰੀ ਪੂਰਨ memcmp (ਅਚਲ ਖਾਲੀ *__s1, ਅਚਲ ਖਾਲੀ *__s2, size_t __n)
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
ਬਾਹਰੀ ਪੂਰਨ __memcmpeq (ਅਚਲ ਖਾਲੀ *__s1, ਅਚਲ ਖਾਲੀ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਖਾਲੀ *memchr (ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ ਅਚਲ ਖਾਲੀ *memchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ਖਾਲੀ *
memchr (ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n) __THROW
{
  ਵਾਪਸ __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ਅਚਲ ਖਾਲੀ *
memchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n) __THROW
{
  ਵਾਪਸ __builtin_memchr (__s, __c, __n);
}
# endif
}
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਖਾਲੀ *memchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# ਜੇ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ਅਚਲ ਖਾਲੀ *, memchr (S, C, N))
# endif
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++" ਖਾਲੀ *rawmemchr (ਖਾਲੀ *__s, ਪੂਰਨ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ "C++" ਅਚਲ ਖਾਲੀ *rawmemchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਖਾਲੀ *rawmemchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++" ਖਾਲੀ *memrchr (ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
ਬਾਹਰੀ "C++" ਅਚਲ ਖਾਲੀ *memrchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਖਾਲੀ *memrchr (ਅਚਲ ਖਾਲੀ *__s, ਪੂਰਨ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#ਜੇ_ਅੰਤ


/* Copy SRC to DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *strcpy (ਅੱਖਰ *__restrict __dest, ਅਚਲ ਅੱਖਰ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *strncpy (ਅੱਖਰ *__restrict __dest,
		      ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *strcat (ਅੱਖਰ *__restrict __dest, ਅਚਲ ਅੱਖਰ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *strncat (ਅੱਖਰ *__restrict __dest, ਅਚਲ ਅੱਖਰ *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
ਬਾਹਰੀ ਪੂਰਨ strcmp (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
ਬਾਹਰੀ ਪੂਰਨ ਲੜੀ_ਤੁਲਨਾ (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
ਬਾਹਰੀ ਪੂਰਨ strcoll (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
ਬਾਹਰੀ size_t strxfrm (ਅੱਖਰ *__restrict __dest,
		       ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
ਬਾਹਰੀ ਪੂਰਨ strcoll_l (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
ਬਾਹਰੀ size_t strxfrm_l (ਅੱਖਰ *__dest, ਅਚਲ ਅੱਖਰ *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#ਜੇ_ਅੰਤ

#ਜੇ (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
ਬਾਹਰੀ ਅੱਖਰ *strdup (ਅਚਲ ਅੱਖਰ *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#ਜੇ_ਅੰਤ

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#ਜੇ defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
ਬਾਹਰੀ ਅੱਖਰ *strndup (ਅਚਲ ਅੱਖਰ *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#ਜੇ_ਅੰਤ

#ਜੇ defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ਅਚਲ ਅੱਖਰ *__old = (s);						      \
      size_t __len = ਲੜੀ_ਲੰਬਾਈ (__old) + 1;				      \
      ਅੱਖਰ *__new = (ਅੱਖਰ *) __builtin_alloca (__len);			      \
      (ਅੱਖਰ *) ਸਮ੍ਰਿਤੀ_ਨਕਲ (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ਅਚਲ ਅੱਖਰ *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      ਅੱਖਰ *__new = (ਅੱਖਰ *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (ਅੱਖਰ *) ਸਮ੍ਰਿਤੀ_ਨਕਲ (__new, __old, __len);				      \
    }))
#ਜੇ_ਅੰਤ

/* Find the first occurrence of C in S.  */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *strchr (ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *strchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
strchr (ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_strchr (__s, __c);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
strchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_strchr (__s, __c);
}
# endif
}
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *strchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ਜੇ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ਅਚਲ ਅੱਖਰ *, strchr (S, C))
# endif
#ਜੇ_ਅੰਤ
/* Find the last occurrence of C in S.  */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *strrchr (ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *strrchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
strrchr (ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_strrchr (__s, __c);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
strrchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_strrchr (__s, __c);
}
# endif
}
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *strrchr (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ਜੇ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ਅਚਲ ਅੱਖਰ *, strrchr (S, C))
# endif
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++" ਅੱਖਰ *strchrnul (ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ "C++" ਅਚਲ ਅੱਖਰ *strchrnul (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *strchrnul (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#ਜੇ_ਅੰਤ

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
ਬਾਹਰੀ size_t strcspn (ਅਚਲ ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
ਬਾਹਰੀ size_t strspn (ਅਚਲ ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *strpbrk (ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *strpbrk (ਅਚਲ ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
strpbrk (ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept) __THROW
{
  ਵਾਪਸ __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
strpbrk (ਅਚਲ ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept) __THROW
{
  ਵਾਪਸ __builtin_strpbrk (__s, __accept);
}
# endif
}
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *strpbrk (ਅਚਲ ਅੱਖਰ *__s, ਅਚਲ ਅੱਖਰ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ਜੇ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ਅਚਲ ਅੱਖਰ *, strpbrk (S, ACCEPT))
# endif
#ਜੇ_ਅੰਤ
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *ਲੜੀ_ਖੋਜ (ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *ਲੜੀ_ਖੋਜ (ਅਚਲ ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
ਲੜੀ_ਖੋਜ (ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle) __THROW
{
  ਵਾਪਸ __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
ਲੜੀ_ਖੋਜ (ਅਚਲ ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle) __THROW
{
  ਵਾਪਸ __builtin_strstr (__haystack, __needle);
}
# endif
}
#ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *ਲੜੀ_ਖੋਜ (ਅਚਲ ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ਜੇ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define ਲੜੀ_ਖੋਜ(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ਅਚਲ ਅੱਖਰ *,	\
			 ਲੜੀ_ਖੋਜ (HAYSTACK, NEEDLE))
# endif
#ਜੇ_ਅੰਤ


/* Divide S into tokens separated by characters in DELIM.  */
ਬਾਹਰੀ ਅੱਖਰ *strtok (ਅੱਖਰ *__restrict __s, ਅਚਲ ਅੱਖਰ *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
ਬਾਹਰੀ ਅੱਖਰ *__strtok_r (ਅੱਖਰ *__restrict __s,
			 ਅਚਲ ਅੱਖਰ *__restrict __delim,
			 ਅੱਖਰ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_POSIX
ਬਾਹਰੀ ਅੱਖਰ *strtok_r (ਅੱਖਰ *__restrict __s, ਅਚਲ ਅੱਖਰ *__restrict __delim,
		       ਅੱਖਰ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++" ਅੱਖਰ *strcasestr (ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
ਬਾਹਰੀ "C++" ਅਚਲ ਅੱਖਰ *strcasestr (ਅਚਲ ਅੱਖਰ *__haystack,
				     ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *strcasestr (ਅਚਲ ਅੱਖਰ *__haystack, ਅਚਲ ਅੱਖਰ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
ਬਾਹਰੀ ਖਾਲੀ *memmem (ਅਚਲ ਖਾਲੀ *__haystack, size_t __haystacklen,
		     ਅਚਲ ਖਾਲੀ *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
ਬਾਹਰੀ ਖਾਲੀ *__mempcpy (ਖਾਲੀ *__restrict __dest,
			ਅਚਲ ਖਾਲੀ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ਬਾਹਰੀ ਖਾਲੀ *mempcpy (ਖਾਲੀ *__restrict __dest,
		      ਅਚਲ ਖਾਲੀ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#ਜੇ_ਅੰਤ


/* Return the length of S.  */
ਬਾਹਰੀ size_t ਲੜੀ_ਲੰਬਾਈ (ਅਚਲ ਅੱਖਰ *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
ਬਾਹਰੀ size_t strnlen (ਅਚਲ ਅੱਖਰ *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#ਜੇ_ਅੰਤ


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
ਬਾਹਰੀ ਅੱਖਰ *strerror (ਪੂਰਨ __errnum) __THROW;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# ਜੇ defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
ਬਾਹਰੀ ਪੂਰਨ __REDIRECT_NTH (strerror_r,
			   (ਪੂਰਨ __errnum, ਅੱਖਰ *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਪੂਰਨ __xpg_strerror_r (ਪੂਰਨ __errnum, ਅੱਖਰ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# ਨਹੀਂਤਾਂ
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
ਬਾਹਰੀ ਅੱਖਰ *strerror_r (ਪੂਰਨ __errnum, ਅੱਖਰ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *strerrordesc_np (ਪੂਰਨ __err) __THROW;
/* Return a string with the error name in ERR.  */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *strerrorname_np (ਪੂਰਨ __err) __THROW;
# endif
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
ਬਾਹਰੀ ਅੱਖਰ *strerror_l (ਪੂਰਨ __errnum, locale_t __l) __THROW;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
ਬਾਹਰੀ ਖਾਲੀ explicit_bzero (ਖਾਲੀ *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
ਬਾਹਰੀ ਅੱਖਰ *strsep (ਅੱਖਰ **__restrict __stringp,
		     ਅਚਲ ਅੱਖਰ *__restrict __delim)
     __THROW __nonnull ((1, 2));
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
ਬਾਹਰੀ ਅੱਖਰ *strsignal (ਪੂਰਨ __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *sigabbrev_np (ਪੂਰਨ __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *sigdescr_np (ਪੂਰਨ __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *__stpcpy (ਅੱਖਰ *__restrict __dest, ਅਚਲ ਅੱਖਰ *__restrict __src)
     __THROW __nonnull ((1, 2));
ਬਾਹਰੀ ਅੱਖਰ *stpcpy (ਅੱਖਰ *__restrict __dest, ਅਚਲ ਅੱਖਰ *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
ਬਾਹਰੀ ਅੱਖਰ *__stpncpy (ਅੱਖਰ *__restrict __dest,
			ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ਬਾਹਰੀ ਅੱਖਰ *stpncpy (ਅੱਖਰ *__restrict __dest,
		      ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
ਬਾਹਰੀ size_t strlcpy (ਅੱਖਰ *__restrict __dest,
		       ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
ਬਾਹਰੀ size_t strlcat (ਅੱਖਰ *__restrict __dest,
		       ਅਚਲ ਅੱਖਰ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
ਬਾਹਰੀ ਪੂਰਨ strverscmp (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
ਬਾਹਰੀ ਅੱਖਰ *strfry (ਅੱਖਰ *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
ਬਾਹਰੀ ਖਾਲੀ *memfrob (ਖਾਲੀ *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ਬਾਹਰੀ "C++" ਅੱਖਰ *basename (ਅੱਖਰ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
ਬਾਹਰੀ "C++" ਅਚਲ ਅੱਖਰ *basename (ਅਚਲ ਅੱਖਰ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *basename (ਅਚਲ ਅੱਖਰ *__filename) __THROW __nonnull ((1));
#  endif
# endif
#ਜੇ_ਅੰਤ

#ਜੇ __GNUC_PREREQ (3,4)
# ਜੇ __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#ਜੇ_ਅੰਤ

__END_DECLS

#ਜੇ_ਅੰਤ /* string.h  */
