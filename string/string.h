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

#که_نه_تعریف_شوی	_STRING_H
#تعریف_کړه	_STRING_H	1

#تعریف_کړه __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
#ضمن <bits/libc-header-start.h>

__BEGIN_DECLS

#إذا __GLIBC_USE (ISOC23)
# define __STDC_VERSION_STRING_H__ 202311L
#د_که_پای

/* Get size_t and NULL from <stddef.h>.  */
#تعریف_کړه	__need_size_t
#تعریف_کړه	__need_NULL
#ضمن <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#إذا defined __cplusplus && (__GNUC_PREREQ (4, 4) \
			    || __glibc_clang_prereq (3, 5))
# define __CORRECT_ISO_CPP_STRING_H_PROTO
#د_که_پای


/* Copy N bytes of SRC to DEST.  */
خارجي فراغ *حافظه_نقل (فراغ *__restrict __dest, ثابت فراغ *__restrict __src,
		     size_t __n) __THROW __nonnull ((1, 2));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
خارجي فراغ *memmove (فراغ *__dest, ثابت فراغ *__src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#إذا defined __USE_MISC || defined __USE_XOPEN || __GLIBC_USE (ISOC23)
خارجي فراغ *memccpy (فراغ *__restrict __dest, ثابت فراغ *__restrict __src,
		      صحيح __c, size_t __n)
    __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 4));
#د_که_پای /* Misc || X/Open.  */


/* Set N bytes of S to C.  */
خارجي فراغ *memset (فراغ *__s, صحيح __c, size_t __n) __THROW __nonnull ((1));

#إذا defined __USE_MISC || __GLIBC_USE (ISOC23)
/* Like memset, but the compiler will not delete a call to this
   function, even if S is dead after the call.  */
خارجي فراغ *memset_explicit (فراغ *__s, صحيح __c, size_t __n)
     __THROW __nonnull ((1)) __fortified_attr_access (__write_only__, 1, 3);
#د_که_پای

/* Compare N bytes of S1 and S2.  */
خارجي صحيح memcmp (ثابت فراغ *__s1, ثابت فراغ *__s2, size_t __n)
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
خارجي صحيح __memcmpeq (ثابت فراغ *__s1, ثابت فراغ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Search N bytes of S for C.  */
#که_تعریف_شوی __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++"
{
خارجي فراغ *memchr (فراغ *__s, صحيح __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));
خارجي ثابت فراغ *memchr (ثابت فراغ *__s, صحيح __c, size_t __n)
      __THROW __asm ("memchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline فراغ *
memchr (فراغ *__s, صحيح __c, size_t __n) __THROW
{
  أرجع __builtin_memchr (__s, __c, __n);
}

__extern_always_inline ثابت فراغ *
memchr (ثابت فراغ *__s, صحيح __c, size_t __n) __THROW
{
  أرجع __builtin_memchr (__s, __c, __n);
}
# endif
}
#وإلا
خارجي فراغ *memchr (ثابت فراغ *__s, صحيح __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1));
# إذا __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define memchr(S, C, N)					\
  __glibc_const_generic (S, ثابت فراغ *, memchr (S, C, N))
# endif
#د_که_پای

#که_تعریف_شوی __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++" فراغ *rawmemchr (فراغ *__s, صحيح __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
خارجي "C++" ثابت فراغ *rawmemchr (ثابت فراغ *__s, صحيح __c)
     __THROW __asm ("rawmemchr") __attribute_pure__ __nonnull ((1));
# وإلا
خارجي فراغ *rawmemchr (ثابت فراغ *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Search N bytes of S for the final occurrence of C.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++" فراغ *memrchr (فراغ *__s, صحيح __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
خارجي "C++" ثابت فراغ *memrchr (ثابت فراغ *__s, صحيح __c, size_t __n)
      __THROW __asm ("memrchr") __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# وإلا
خارجي فراغ *memrchr (ثابت فراغ *__s, صحيح __c, size_t __n)
      __THROW __attribute_pure__ __nonnull ((1))
      __attr_access ((__read_only__, 1, 3));
# endif
#د_که_پای


/* Copy SRC to DEST.  */
خارجي حرف *strcpy (حرف *__restrict __dest, ثابت حرف *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Copy no more than N characters of SRC to DEST.  */
خارجي حرف *strncpy (حرف *__restrict __dest,
		      ثابت حرف *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));

/* Append SRC onto DEST.  */
خارجي حرف *strcat (حرف *__restrict __dest, ثابت حرف *__restrict __src)
     __THROW __nonnull ((1, 2));
/* Append no more than N characters from SRC onto DEST.  */
خارجي حرف *strncat (حرف *__restrict __dest, ثابت حرف *__restrict __src,
		      size_t __n) __THROW __nonnull ((1, 2));

/* Compare S1 and S2.  */
خارجي صحيح strcmp (ثابت حرف *__s1, ثابت حرف *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Compare N characters of S1 and S2.  */
خارجي صحيح مزي_پرتله (ثابت حرف *__s1, ثابت حرف *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare the collated forms of S1 and S2.  */
خارجي صحيح strcoll (ثابت حرف *__s1, ثابت حرف *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
خارجي size_t strxfrm (حرف *__restrict __dest,
		       ثابت حرف *__restrict __src, size_t __n)
    __THROW __nonnull ((2)) __attr_access ((__write_only__, 1, 3));

#که_تعریف_شوی __USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare the collated forms of S1 and S2, using sorting rules from L.  */
خارجي صحيح strcoll_l (ثابت حرف *__s1, ثابت حرف *__s2, locale_t __l)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));
/* Put a transformation of SRC into no more than N bytes of DEST,
   using sorting rules from L.  */
خارجي size_t strxfrm_l (حرف *__dest, ثابت حرف *__src, size_t __n,
			 locale_t __l) __THROW __nonnull ((2, 4))
     __attr_access ((__write_only__, 1, 3));
#د_که_پای

#إذا (defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8	\
     || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23))
/* Duplicate S, returning an identical malloc'd string.  */
خارجي حرف *strdup (ثابت حرف *__s)
     __THROW __attribute_malloc__ __nonnull ((1));
#د_که_پای

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#إذا defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC23)
خارجي حرف *strndup (ثابت حرف *__string, size_t __n)
     __THROW __attribute_malloc__ __nonnull ((1));
#د_که_پای

#إذا defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      ثابت حرف *__old = (s);						      \
      size_t __len = مزي_اوږدوالی (__old) + 1;				      \
      حرف *__new = (حرف *) __builtin_alloca (__len);			      \
      (حرف *) حافظه_نقل (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      ثابت حرف *__old = (s);						      \
      size_t __len = strnlen (__old, (n));				      \
      حرف *__new = (حرف *) __builtin_alloca (__len + 1);		      \
      __new[__len] = '\0';						      \
      (حرف *) حافظه_نقل (__new, __old, __len);				      \
    }))
#د_که_پای

/* Find the first occurrence of C in S.  */
#که_تعریف_شوی __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++"
{
خارجي حرف *strchr (حرف *__s, صحيح __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));
خارجي ثابت حرف *strchr (ثابت حرف *__s, صحيح __c)
     __THROW __asm ("strchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline حرف *
strchr (حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_strchr (__s, __c);
}

__extern_always_inline ثابت حرف *
strchr (ثابت حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_strchr (__s, __c);
}
# endif
}
#وإلا
خارجي حرف *strchr (ثابت حرف *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# إذا __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strchr(S, C)						\
  __glibc_const_generic (S, ثابت حرف *, strchr (S, C))
# endif
#د_که_پای
/* Find the last occurrence of C in S.  */
#که_تعریف_شوی __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++"
{
خارجي حرف *strrchr (حرف *__s, صحيح __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));
خارجي ثابت حرف *strrchr (ثابت حرف *__s, صحيح __c)
     __THROW __asm ("strrchr") __attribute_pure__ __nonnull ((1));

# ifdef __OPTIMIZE__
__extern_always_inline حرف *
strrchr (حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_strrchr (__s, __c);
}

__extern_always_inline ثابت حرف *
strrchr (ثابت حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_strrchr (__s, __c);
}
# endif
}
#وإلا
خارجي حرف *strrchr (ثابت حرف *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# إذا __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strrchr(S, C)						\
  __glibc_const_generic (S, ثابت حرف *, strrchr (S, C))
# endif
#د_که_پای

#که_تعریف_شوی __USE_MISC
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++" حرف *strchrnul (حرف *__s, صحيح __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
خارجي "C++" ثابت حرف *strchrnul (ثابت حرف *__s, صحيح __c)
     __THROW __asm ("strchrnul") __attribute_pure__ __nonnull ((1));
# وإلا
خارجي حرف *strchrnul (ثابت حرف *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#د_که_پای

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
خارجي size_t strcspn (ثابت حرف *__s, ثابت حرف *__reject)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
خارجي size_t strspn (ثابت حرف *__s, ثابت حرف *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
/* Find the first occurrence in S of any character in ACCEPT.  */
#که_تعریف_شوی __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++"
{
خارجي حرف *strpbrk (حرف *__s, ثابت حرف *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));
خارجي ثابت حرف *strpbrk (ثابت حرف *__s, ثابت حرف *__accept)
     __THROW __asm ("strpbrk") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline حرف *
strpbrk (حرف *__s, ثابت حرف *__accept) __THROW
{
  أرجع __builtin_strpbrk (__s, __accept);
}

__extern_always_inline ثابت حرف *
strpbrk (ثابت حرف *__s, ثابت حرف *__accept) __THROW
{
  أرجع __builtin_strpbrk (__s, __accept);
}
# endif
}
#وإلا
خارجي حرف *strpbrk (ثابت حرف *__s, ثابت حرف *__accept)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# إذا __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define strpbrk(S, ACCEPT)					\
  __glibc_const_generic (S, ثابت حرف *, strpbrk (S, ACCEPT))
# endif
#د_که_پای
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
#که_تعریف_شوی __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++"
{
خارجي حرف *مزي_پلټنه (حرف *__haystack, ثابت حرف *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));
خارجي ثابت حرف *مزي_پلټنه (ثابت حرف *__haystack, ثابت حرف *__needle)
     __THROW __asm ("strstr") __attribute_pure__ __nonnull ((1, 2));

# ifdef __OPTIMIZE__
__extern_always_inline حرف *
مزي_پلټنه (حرف *__haystack, ثابت حرف *__needle) __THROW
{
  أرجع __builtin_strstr (__haystack, __needle);
}

__extern_always_inline ثابت حرف *
مزي_پلټنه (ثابت حرف *__haystack, ثابت حرف *__needle) __THROW
{
  أرجع __builtin_strstr (__haystack, __needle);
}
# endif
}
#وإلا
خارجي حرف *مزي_پلټنه (ثابت حرف *__haystack, ثابت حرف *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# إذا __GLIBC_USE (ISOC23) && defined __glibc_const_generic && !defined _LIBC
#  define مزي_پلټنه(HAYSTACK, NEEDLE)			\
  __glibc_const_generic (HAYSTACK, ثابت حرف *,	\
			 مزي_پلټنه (HAYSTACK, NEEDLE))
# endif
#د_که_پای


/* Divide S into tokens separated by characters in DELIM.  */
خارجي حرف *strtok (حرف *__restrict __s, ثابت حرف *__restrict __delim)
     __THROW __nonnull ((2));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
خارجي حرف *__strtok_r (حرف *__restrict __s,
			 ثابت حرف *__restrict __delim,
			 حرف **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#که_تعریف_شوی __USE_POSIX
خارجي حرف *strtok_r (حرف *__restrict __s, ثابت حرف *__restrict __delim,
		       حرف **__restrict __save_ptr)
     __THROW __nonnull ((2, 3));
#د_که_پای

#که_تعریف_شوی __USE_MISC
/* Similar to `strstr' but this function ignores the case of both strings.  */
# ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++" حرف *strcasestr (حرف *__haystack, ثابت حرف *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
خارجي "C++" ثابت حرف *strcasestr (ثابت حرف *__haystack,
				     ثابت حرف *__needle)
     __THROW __asm ("strcasestr") __attribute_pure__ __nonnull ((1, 2));
# وإلا
خارجي حرف *strcasestr (ثابت حرف *__haystack, ثابت حرف *__needle)
     __THROW __attribute_pure__ __nonnull ((1, 2));
# endif
#د_که_پای

#که_تعریف_شوی __USE_MISC
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
خارجي فراغ *memmem (ثابت فراغ *__haystack, size_t __haystacklen,
		     ثابت فراغ *__needle, size_t __needlelen)
     __THROW __attribute_pure__ __nonnull ((1, 3))
    __attr_access ((__read_only__, 1, 2))
    __attr_access ((__read_only__, 3, 4));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
خارجي فراغ *__mempcpy (فراغ *__restrict __dest,
			ثابت فراغ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
خارجي فراغ *mempcpy (فراغ *__restrict __dest,
		      ثابت فراغ *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#د_که_پای


/* Return the length of S.  */
خارجي size_t مزي_اوږدوالی (ثابت حرف *__s)
     __THROW __attribute_pure__ __nonnull ((1));

#که_تعریف_شوی	__USE_XOPEN2K8
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
خارجي size_t strnlen (ثابت حرف *__string, size_t __maxlen)
     __THROW __attribute_pure__ __nonnull ((1));
#د_که_پای


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
خارجي حرف *strerror (صحيح __errnum) __THROW;
#که_تعریف_شوی __USE_XOPEN2K
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# إذا defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
خارجي صحيح __REDIRECT_NTH (strerror_r,
			   (صحيح __errnum, حرف *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2))
    __attr_access ((__write_only__, 2, 3));
#  وإلا
خارجي صحيح __xpg_strerror_r (صحيح __errnum, حرف *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __attr_access ((__write_only__, 2, 3));
#   define strerror_r __xpg_strerror_r
#  endif
# وإلا
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
خارجي حرف *strerror_r (صحيح __errnum, حرف *__buf, size_t __buflen)
     __THROW __nonnull ((2)) __wur  __attr_access ((__write_only__, 2, 3));
# endif

# ifdef __USE_GNU
/* Return a string describing the meaning of tthe error in ERR.  */
خارجي ثابت حرف *strerrordesc_np (صحيح __err) __THROW;
/* Return a string with the error name in ERR.  */
خارجي ثابت حرف *strerrorname_np (صحيح __err) __THROW;
# endif
#د_که_پای

#که_تعریف_شوی __USE_XOPEN2K8
/* Translate error number to string according to the locale L.  */
خارجي حرف *strerror_l (صحيح __errnum, locale_t __l) __THROW;
#د_که_پای

#که_تعریف_شوی __USE_MISC
# include <strings.h>

/* Set N bytes of S to 0.  The compiler will not delete a call to this
   function, even if S is dead after the call.  */
خارجي فراغ explicit_bzero (فراغ *__s, size_t __n) __THROW __nonnull ((1))
    __fortified_attr_access (__write_only__, 1, 2);

/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
خارجي حرف *strsep (حرف **__restrict __stringp,
		     ثابت حرف *__restrict __delim)
     __THROW __nonnull ((1, 2));
#د_که_پای

#که_تعریف_شوی	__USE_XOPEN2K8
/* Return a string describing the meaning of the signal number in SIG.  */
خارجي حرف *strsignal (صحيح __sig) __THROW;

# ifdef __USE_GNU
/* Return an abbreviation string for the signal number SIG.  */
خارجي ثابت حرف *sigabbrev_np (صحيح __sig) __THROW;
/* Return a string describing the meaning of the signal number in SIG,
   the result is not translated.  */
خارجي ثابت حرف *sigdescr_np (صحيح __sig) __THROW;
# endif

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
خارجي حرف *__stpcpy (حرف *__restrict __dest, ثابت حرف *__restrict __src)
     __THROW __nonnull ((1, 2));
خارجي حرف *stpcpy (حرف *__restrict __dest, ثابت حرف *__restrict __src)
     __THROW __nonnull ((1, 2));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
خارجي حرف *__stpncpy (حرف *__restrict __dest,
			ثابت حرف *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
خارجي حرف *stpncpy (حرف *__restrict __dest,
		      ثابت حرف *__restrict __src, size_t __n)
     __THROW __nonnull ((1, 2));
#د_که_پای

#که_تعریف_شوی __USE_MISC
/* Copy at most N - 1 characters from SRC to DEST.  */
خارجي size_t strlcpy (حرف *__restrict __dest,
		       ثابت حرف *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));

/* Append SRC to DEST, possibly with truncation to keep the total size
   below N.  */
خارجي size_t strlcat (حرف *__restrict __dest,
		       ثابت حرف *__restrict __src, size_t __n)
  __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
#د_که_پای

#که_تعریف_شوی	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
خارجي صحيح strverscmp (ثابت حرف *__s1, ثابت حرف *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Sautee STRING briskly.  */
خارجي حرف *strfry (حرف *__string) __THROW __nonnull ((1));

/* Frobnicate N bytes of S.  */
خارجي فراغ *memfrob (فراغ *__s, size_t __n) __THROW __nonnull ((1))
    __attr_access ((__read_write__, 1, 2));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
#  ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
خارجي "C++" حرف *basename (حرف *__filename)
     __THROW __asm ("basename") __nonnull ((1));
خارجي "C++" ثابت حرف *basename (ثابت حرف *__filename)
     __THROW __asm ("basename") __nonnull ((1));
#  وإلا
خارجي حرف *basename (ثابت حرف *__filename) __THROW __nonnull ((1));
#  endif
# endif
#د_که_پای

#إذا __GNUC_PREREQ (3,4)
# إذا __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
/* Functions with security checks.  */
#  include <bits/string_fortified.h>
# endif
#د_که_پای

__END_DECLS

#د_که_پای /* string.h  */
