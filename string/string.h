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

#నిర్వచితం_కాకపోతే	_STRING_H
#నిర్వచించు	_STRING_H	1

#నిర్వచించు __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#అన్తర్భావ <bits/libc-header-start.h>

__BEGIN_DECLS

#ఒకవేళ __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#అయితే_ముగింపు

/* Get size_t and NULL from <stddef.h>.  */
#నిర్వచించు	__need_size_t
#నిర్వచించు	__need_NULL
#అన్తర్భావ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ఒకవేళ defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#అయితే_ముగింపు


/* Copy N bytes of SRC to DEST.  */
బాహ్య శూన్య *జ్ఞాపకం_నకలు (శూన్య *__restrict __dest, స్థిరరాశి శూన్య *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
బాహ్య శూన్య *memmove (శూన్య *__dest, స్థిరరాశి శూన్య *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#ఒకవేళ defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
బాహ్య శూన్య *memccpy (శూన్య *__restrict __dest, స్థిరరాశి శూన్య *__restrict __src,
		      పూర్ణాంకం __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#అయితే_ముగింపు /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
బాహ్య శూన్య *memset (శూన్య *__s, పూర్ణాంకం __c, size_t __n) __THROW __nonnull ((1));

#ఒకవేళ defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
బాహ్య శూన్య *memset_explicit (శూన్య *__s, పూర్ణాంకం __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#అయితే_ముగింపు

/* Compare N bytes of S1 and S2.  */
బాహ్య పూర్ణాంకం memcmp (స్థిరరాశి శూన్య *__s1, స్థిరరాశి శూన్య *__s2, size_t __n)
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
బాహ్య పూర్ణాంకం __memcmpeq (స్థిరరాశి శూన్య *__s1, స్థిరరాశి శూన్య *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#నిర్వచితమైతే __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++"
{
బాహ్య శూన్య *memchr (శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
బాహ్య స్థిరరాశి శూన్య *memchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline శూన్య *
memchr (శూన్య *__s, పూర్ణాంకం __c, size_t __n) __THROW
{
  తిరిగి __builtin_memchr (__s, __c, __n);
}

__extern_always_inline స్థిరరాశి శూన్య *
memchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c, size_t __n) __THROW
{
  తిరిగి __builtin_memchr (__s, __c, __n);
}
# endif
}
#లేకపోతే
బాహ్య శూన్య *memchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# ఒకవేళ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, స్థిరరాశి శూన్య *, memchr (S, C, N))
# endif
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++" శూన్య *rawmemchr (శూన్య *__s, పూర్ణాంకం __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
బాహ్య "C++" స్థిరరాశి శూన్య *rawmemchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# లేకపోతే
బాహ్య శూన్య *rawmemchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++" శూన్య *memrchr (శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
బాహ్య "C++" స్థిరరాశి శూన్య *memrchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# లేకపోతే
బాహ్య శూన్య *memrchr (స్థిరరాశి శూన్య *__s, పూర్ణాంకం __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#అయితే_ముగింపు


/* Copy SRC to DEST.  */
బాహ్య అక్షరం *strcpy (అక్షరం *__restrict __dest, స్థిరరాశి అక్షరం *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
బాహ్య అక్షరం *strncpy (అక్షరం *__restrict __dest,
		      స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
బాహ్య అక్షరం *strcat (అక్షరం *__restrict __dest, స్థిరరాశి అక్షరం *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
బాహ్య అక్షరం *strncat (అక్షరం *__restrict __dest, స్థిరరాశి అక్షరం *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
బాహ్య పూర్ణాంకం strcmp (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
బాహ్య పూర్ణాంకం అక్షరశ్రేణి_పోలిక (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
బాహ్య పూర్ణాంకం strcoll (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
బాహ్య size_t strxfrm (అక్షరం *__restrict __dest,
		       స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#నిర్వచితమైతే __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
బాహ్య పూర్ణాంకం strcoll_l (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
బాహ్య size_t strxfrm_l (అక్షరం *__dest, స్థిరరాశి అక్షరం *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#అయితే_ముగింపు

#ఒకవేళ (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
బాహ్య అక్షరం *strdup (స్థిరరాశి అక్షరం *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#అయితే_ముగింపు

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#ఒకవేళ defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
బాహ్య అక్షరం *strndup (స్థిరరాశి అక్షరం *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#అయితే_ముగింపు

#ఒకవేళ defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      స్థిరరాశి అక్షరం *__old = (s);						      \
      size_t __len = అక్షరశ్రేణి_పొడవు (__old) + 1;				      \
      అక్షరం *__new = (అక్షరం *) __builtin_alloca (__len);			      \
      (అక్షరం *) జ్ఞాపకం_నకలు (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      స్థిరరాశి అక్షరం *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      అక్షరం *__new = (అక్షరం *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (అక్షరం *) జ్ఞాపకం_నకలు (__new, __old, __len);				      \
    }))
#అయితే_ముగింపు

/* Find the first occurrence of C in S.  */
#నిర్వచితమైతే __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *strchr (అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
బాహ్య స్థిరరాశి అక్షరం *strchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline అక్షరం *
strchr (అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_strchr (__s, __c);
}

__extern_always_inline స్థిరరాశి అక్షరం *
strchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_strchr (__s, __c);
}
# endif
}
#లేకపోతే
బాహ్య అక్షరం *strchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ఒకవేళ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, స్థిరరాశి అక్షరం *, strchr (S, C))
# endif
#అయితే_ముగింపు
/* Find the last occurrence of C in S.  */
#నిర్వచితమైతే __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *strrchr (అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
బాహ్య స్థిరరాశి అక్షరం *strrchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline అక్షరం *
strrchr (అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_strrchr (__s, __c);
}

__extern_always_inline స్థిరరాశి అక్షరం *
strrchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_strrchr (__s, __c);
}
# endif
}
#లేకపోతే
బాహ్య అక్షరం *strrchr (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# ఒకవేళ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, స్థిరరాశి అక్షరం *, strrchr (S, C))
# endif
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++" అక్షరం *strchrnul (అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
బాహ్య "C++" స్థిరరాశి అక్షరం *strchrnul (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# లేకపోతే
బాహ్య అక్షరం *strchrnul (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#అయితే_ముగింపు

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
బాహ్య size_t strcspn (స్థిరరాశి అక్షరం *__s, స్థిరరాశి అక్షరం *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
బాహ్య size_t strspn (స్థిరరాశి అక్షరం *__s, స్థిరరాశి అక్షరం *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#నిర్వచితమైతే __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *strpbrk (అక్షరం *__s, స్థిరరాశి అక్షరం *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
బాహ్య స్థిరరాశి అక్షరం *strpbrk (స్థిరరాశి అక్షరం *__s, స్థిరరాశి అక్షరం *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline అక్షరం *
strpbrk (అక్షరం *__s, స్థిరరాశి అక్షరం *__accept) __THROW
{
  తిరిగి __builtin_strpbrk (__s, __accept);
}

__extern_always_inline స్థిరరాశి అక్షరం *
strpbrk (స్థిరరాశి అక్షరం *__s, స్థిరరాశి అక్షరం *__accept) __THROW
{
  తిరిగి __builtin_strpbrk (__s, __accept);
}
# endif
}
#లేకపోతే
బాహ్య అక్షరం *strpbrk (స్థిరరాశి అక్షరం *__s, స్థిరరాశి అక్షరం *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ఒకవేళ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, స్థిరరాశి అక్షరం *, strpbrk (S, ACCEPT))
# endif
#అయితే_ముగింపు
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#నిర్వచితమైతే __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *అక్షరశ్రేణి_శోధన (అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
బాహ్య స్థిరరాశి అక్షరం *అక్షరశ్రేణి_శోధన (స్థిరరాశి అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline అక్షరం *
అక్షరశ్రేణి_శోధన (అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle) __THROW
{
  తిరిగి __builtin_strstr (__haystack, __needle);
}

__extern_always_inline స్థిరరాశి అక్షరం *
అక్షరశ్రేణి_శోధన (స్థిరరాశి అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle) __THROW
{
  తిరిగి __builtin_strstr (__haystack, __needle);
}
# endif
}
#లేకపోతే
బాహ్య అక్షరం *అక్షరశ్రేణి_శోధన (స్థిరరాశి అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# ఒకవేళ __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define అక్షరశ్రేణి_శోధన(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, స్థిరరాశి అక్షరం *,	\
			 అక్షరశ్రేణి_శోధన (HAYSTACK, NEEDLE))
# endif
#అయితే_ముగింపు


/* Divide S into tokens separated by characters in DELIM.  */
బాహ్య అక్షరం *strtok (అక్షరం *__restrict __s, స్థిరరాశి అక్షరం *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
బాహ్య అక్షరం *__strtok_r (అక్షరం *__restrict __s,
			 స్థిరరాశి అక్షరం *__restrict __delim,
			 అక్షరం **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#నిర్వచితమైతే __USE_POSIX
బాహ్య అక్షరం *strtok_r (అక్షరం *__restrict __s, స్థిరరాశి అక్షరం *__restrict __delim,
		       అక్షరం **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++" అక్షరం *strcasestr (అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
బాహ్య "C++" స్థిరరాశి అక్షరం *strcasestr (స్థిరరాశి అక్షరం *__haystack,
				     స్థిరరాశి అక్షరం *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# లేకపోతే
బాహ్య అక్షరం *strcasestr (స్థిరరాశి అక్షరం *__haystack, స్థిరరాశి అక్షరం *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
బాహ్య శూన్య *memmem (స్థిరరాశి శూన్య *__haystack, size_t __haystacklen,
		     స్థిరరాశి శూన్య *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
బాహ్య శూన్య *__mempcpy (శూన్య *__restrict __dest,
			స్థిరరాశి శూన్య *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
బాహ్య శూన్య *mempcpy (శూన్య *__restrict __dest,
		      స్థిరరాశి శూన్య *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#అయితే_ముగింపు


/* Return the length of S.  */
బాహ్య size_t అక్షరశ్రేణి_పొడవు (స్థిరరాశి అక్షరం *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#నిర్వచితమైతే	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
బాహ్య size_t strnlen (స్థిరరాశి అక్షరం *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#అయితే_ముగింపు


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
బాహ్య అక్షరం *strerror (పూర్ణాంకం __errnum) __THROW;
#నిర్వచితమైతే __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# ఒకవేళ defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
బాహ్య పూర్ణాంకం __REDIRECT_NTH (strerror_r,
			   (పూర్ణాంకం __errnum, అక్షరం *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  లేకపోతే
బాహ్య పూర్ణాంకం __xpg_strerror_r (పూర్ణాంకం __errnum, అక్షరం *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# లేకపోతే
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
బాహ్య అక్షరం *strerror_r (పూర్ణాంకం __errnum, అక్షరం *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
బాహ్య స్థిరరాశి అక్షరం *strerrordesc_np (పూర్ణాంకం __err) __THROW;
/* Return a string with the error name in ERR.  */
బాహ్య స్థిరరాశి అక్షరం *strerrorname_np (పూర్ణాంకం __err) __THROW;
# endif
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
బాహ్య అక్షరం *strerror_l (పూర్ణాంకం __errnum, locale_t __l) __THROW;
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
బాహ్య శూన్య explicit_bzero (శూన్య *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
బాహ్య అక్షరం *strsep (అక్షరం **__restrict __stringp,
		     స్థిరరాశి అక్షరం *__restrict __delim)
     __THROW __nonnull ((1, 2));
#అయితే_ముగింపు

#నిర్వచితమైతే	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
బాహ్య అక్షరం *strsignal (పూర్ణాంకం __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
బాహ్య స్థిరరాశి అక్షరం *sigabbrev_np (పూర్ణాంకం __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
బాహ్య స్థిరరాశి అక్షరం *sigdescr_np (పూర్ణాంకం __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
బాహ్య అక్షరం *__stpcpy (అక్షరం *__restrict __dest, స్థిరరాశి అక్షరం *__restrict __src)
     __THROW __nonnull ((1, 2));
బాహ్య అక్షరం *stpcpy (అక్షరం *__restrict __dest, స్థిరరాశి అక్షరం *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
బాహ్య అక్షరం *__stpncpy (అక్షరం *__restrict __dest,
			స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
బాహ్య అక్షరం *stpncpy (అక్షరం *__restrict __dest,
		      స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#అయితే_ముగింపు

#నిర్వచితమైతే __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
బాహ్య size_t strlcpy (అక్షరం *__restrict __dest,
		       స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
బాహ్య size_t strlcat (అక్షరం *__restrict __dest,
		       స్థిరరాశి అక్షరం *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#అయితే_ముగింపు

#నిర్వచితమైతే	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
బాహ్య పూర్ణాంకం strverscmp (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
బాహ్య అక్షరం *strfry (అక్షరం *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
బాహ్య శూన్య *memfrob (శూన్య *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
బాహ్య "C++" అక్షరం *basename (అక్షరం *__filename)
     __THROW __asm ("basename") __nonnull ((1));
బాహ్య "C++" స్థిరరాశి అక్షరం *basename (స్థిరరాశి అక్షరం *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  లేకపోతే
బాహ్య అక్షరం *basename (స్థిరరాశి అక్షరం *__filename) __THROW __nonnull ((1));
#  endif
# endif
#అయితే_ముగింపు

#ఒకవేళ __GNUC_PREREQ (3,4)
# ఒకవేళ __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#అయితే_ముగింపు

__END_DECLS

#అయితే_ముగింపు /* string.h  */
