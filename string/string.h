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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ	_STRING_H
#ವ್ಯಾಖ್ಯಾನಿಸು	_STRING_H	1

#ವ್ಯಾಖ್ಯಾನಿಸು __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#ಅನ್ತರ್ಭಾವ <bits/libc-header-start.h>

__BEGIN_DECLS

#ಆದರೆ __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#ಆದರೆ_ಅಂತ್ಯ

/* Get size_t and NULL from <stddef.h>.  */
#ವ್ಯಾಖ್ಯಾನಿಸು	__need_size_t
#ವ್ಯಾಖ್ಯಾನಿಸು	__need_NULL
#ಅನ್ತರ್ಭಾವ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ಆದರೆ defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#ಆದರೆ_ಅಂತ್ಯ


/* Copy N bytes of SRC to DEST.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *ಸ್ಮರಣೆ_ನಕಲು (ಶೂನ್ಯ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *memmove (ಶೂನ್ಯ *__dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#ಆದರೆ defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
ಬಾಹ್ಯ ಶೂನ್ಯ *memccpy (ಶೂನ್ಯ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src,
		      ಪೂರ್ಣಾಂಕ __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#ಆದರೆ_ಅಂತ್ಯ /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *memset (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n) __THROW __nonnull ((1));

#ಆದರೆ defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *memset_explicit (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#ಆದರೆ_ಅಂತ್ಯ

/* Compare N bytes of S1 and S2.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ memcmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s1, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s2, size_t __n)
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
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ __memcmpeq (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s1, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಶೂನ್ಯ *memchr (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *memchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ಶೂನ್ಯ *
memchr (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *
memchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_memchr (__s, __c, __n);
}
# endif
}
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಶೂನ್ಯ *memchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# ಆದರೆ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, memchr (S, C, N))
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++" ಶೂನ್ಯ *rawmemchr (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ "C++" ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *rawmemchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಶೂನ್ಯ *rawmemchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++" ಶೂನ್ಯ *memrchr (ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
ಬಾಹ್ಯ "C++" ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *memrchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಶೂನ್ಯ *memrchr (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s, ಪೂರ್ಣಾಂಕ __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#ಆದರೆ_ಅಂತ್ಯ


/* Copy SRC to DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strcpy (ಅಕ್ಷರ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strncpy (ಅಕ್ಷರ *__restrict __dest,
		      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strcat (ಅಕ್ಷರ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strncat (ಅಕ್ಷರ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strcmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strcoll (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
ಬಾಹ್ಯ size_t strxfrm (ಅಕ್ಷರ *__restrict __dest,
		       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strcoll_l (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
ಬಾಹ್ಯ size_t strxfrm_l (ಅಕ್ಷರ *__dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strdup (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#ಆದರೆ_ಅಂತ್ಯ

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#ಆದರೆ defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
ಬಾಹ್ಯ ಅಕ್ಷರ *strndup (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__old = (s);						      \
      size_t __len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (__old) + 1;				      \
      ಅಕ್ಷರ *__new = (ಅಕ್ಷರ *) __builtin_alloca (__len);			      \
      (ಅಕ್ಷರ *) ಸ್ಮರಣೆ_ನಕಲು (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      ಅಕ್ಷರ *__new = (ಅಕ್ಷರ *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (ಅಕ್ಷರ *) ಸ್ಮರಣೆ_ನಕಲು (__new, __old, __len);				      \
    }))
#ಆದರೆ_ಅಂತ್ಯ

/* Find the first occurrence of C in S.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *strchr (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
strchr (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strchr (__s, __c);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
strchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strchr (__s, __c);
}
# endif
}
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *strchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ಆದರೆ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, strchr (S, C))
# endif
#ಆದರೆ_ಅಂತ್ಯ
/* Find the last occurrence of C in S.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *strrchr (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strrchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
strrchr (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strrchr (__s, __c);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
strrchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strrchr (__s, __c);
}
# endif
}
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *strrchr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ಆದರೆ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, strrchr (S, C))
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++" ಅಕ್ಷರ *strchrnul (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ "C++" ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strchrnul (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *strchrnul (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#ಆದರೆ_ಅಂತ್ಯ

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
ಬಾಹ್ಯ size_t strcspn (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
ಬಾಹ್ಯ size_t strspn (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *strpbrk (ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strpbrk (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
strpbrk (ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
strpbrk (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strpbrk (__s, __accept);
}
# endif
}
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *strpbrk (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ಆದರೆ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, strpbrk (S, ACCEPT))
# endif
#ಆದರೆ_ಅಂತ್ಯ
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_strstr (__haystack, __needle);
}
# endif
}
#ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ಆದರೆ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *,	\
			 ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು (HAYSTACK, NEEDLE))
# endif
#ಆದರೆ_ಅಂತ್ಯ


/* Divide S into tokens separated by characters in DELIM.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strtok (ಅಕ್ಷರ *__restrict __s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *__strtok_r (ಅಕ್ಷರ *__restrict __s,
			 ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __delim,
			 ಅಕ್ಷರ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_POSIX
ಬಾಹ್ಯ ಅಕ್ಷರ *strtok_r (ಅಕ್ಷರ *__restrict __s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __delim,
		       ಅಕ್ಷರ **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++" ಅಕ್ಷರ *strcasestr (ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
ಬಾಹ್ಯ "C++" ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strcasestr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__haystack,
				     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *strcasestr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__haystack, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *memmem (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__haystack, size_t __haystacklen,
		     ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *__mempcpy (ಶೂನ್ಯ *__restrict __dest,
			ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ಬಾಹ್ಯ ಶೂನ್ಯ *mempcpy (ಶೂನ್ಯ *__restrict __dest,
		      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#ಆದರೆ_ಅಂತ್ಯ


/* Return the length of S.  */
ಬಾಹ್ಯ size_t ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
ಬಾಹ್ಯ size_t strnlen (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#ಆದರೆ_ಅಂತ್ಯ


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strerror (ಪೂರ್ಣಾಂಕ __errnum) __THROW;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# ಆದರೆ defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ __REDIRECT_NTH (strerror_r,
			   (ಪೂರ್ಣಾಂಕ __errnum, ಅಕ್ಷರ *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ __xpg_strerror_r (ಪೂರ್ಣಾಂಕ __errnum, ಅಕ್ಷರ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# ಇಲ್ಲದಿದ್ದರೆ
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strerror_r (ಪೂರ್ಣಾಂಕ __errnum, ಅಕ್ಷರ *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strerrordesc_np (ಪೂರ್ಣಾಂಕ __err) __THROW;
/* Return a string with the error name in ERR.  */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *strerrorname_np (ಪೂರ್ಣಾಂಕ __err) __THROW;
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strerror_l (ಪೂರ್ಣಾಂಕ __errnum, locale_t __l) __THROW;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
ಬಾಹ್ಯ ಶೂನ್ಯ explicit_bzero (ಶೂನ್ಯ *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strsep (ಅಕ್ಷರ **__restrict __stringp,
		     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __delim)
     __THROW __nonnull ((1, 2));
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strsignal (ಪೂರ್ಣಾಂಕ __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sigabbrev_np (ಪೂರ್ಣಾಂಕ __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sigdescr_np (ಪೂರ್ಣಾಂಕ __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *__stpcpy (ಅಕ್ಷರ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src)
     __THROW __nonnull ((1, 2));
ಬಾಹ್ಯ ಅಕ್ಷರ *stpcpy (ಅಕ್ಷರ *__restrict __dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *__stpncpy (ಅಕ್ಷರ *__restrict __dest,
			ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
ಬಾಹ್ಯ ಅಕ್ಷರ *stpncpy (ಅಕ್ಷರ *__restrict __dest,
		      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
ಬಾಹ್ಯ size_t strlcpy (ಅಕ್ಷರ *__restrict __dest,
		       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
ಬಾಹ್ಯ size_t strlcat (ಅಕ್ಷರ *__restrict __dest,
		       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strverscmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
ಬಾಹ್ಯ ಅಕ್ಷರ *strfry (ಅಕ್ಷರ *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
ಬಾಹ್ಯ ಶೂನ್ಯ *memfrob (ಶೂನ್ಯ *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
ಬಾಹ್ಯ "C++" ಅಕ್ಷರ *basename (ಅಕ್ಷರ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
ಬಾಹ್ಯ "C++" ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *basename (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *basename (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__filename) __THROW __nonnull ((1));
#  endif
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ __GNUC_PREREQ (3,4)
# ಆದರೆ __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#ಆದರೆ_ಅಂತ್ಯ

__END_DECLS

#ಆದರೆ_ಅಂತ್ಯ /* string.h  */
