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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ	_STRINGS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ	_STRINGS_H	1

#ਅਨ੍ਤਰ੍ਭਾਵ <features.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __need_size_t
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ਜੇ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#ਜੇ_ਅੰਤ

__BEGIN_DECLS

#ਜੇ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
ਬਾਹਰੀ ਪੂਰਨ bcmp (ਅਚਲ ਖਾਲੀ *__s1, ਅਚਲ ਖਾਲੀ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
ਬਾਹਰੀ ਖਾਲੀ bcopy (ਅਚਲ ਖਾਲੀ *__src, ਖਾਲੀ *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
ਬਾਹਰੀ ਖਾਲੀ bzero (ਖਾਲੀ *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *ਸੂਚਕਾਂਕ (ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *ਸੂਚਕਾਂਕ (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ਜੇ defined __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
ਸੂਚਕਾਂਕ (ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_index (__s, __c);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
ਸੂਚਕਾਂਕ (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_index (__s, __c);
}
#  endif
}
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *ਸੂਚਕਾਂਕ (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ਬਾਹਰੀ "C++"
{
ਬਾਹਰੀ ਅੱਖਰ *rindex (ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *rindex (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ਜੇ defined __OPTIMIZE__
__extern_always_inline ਅੱਖਰ *
rindex (ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_rindex (__s, __c);
}

__extern_always_inline ਅਚਲ ਅੱਖਰ *
rindex (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c) __THROW
{
  ਵਾਪਸ __builtin_rindex (__s, __c);
}
#  endif
}
# ਨਹੀਂਤਾਂ
ਬਾਹਰੀ ਅੱਖਰ *rindex (ਅਚਲ ਅੱਖਰ *__s, ਪੂਰਨ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#ਜੇ_ਅੰਤ

#ਜੇ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
ਬਾਹਰੀ ਪੂਰਨ ffs (ਪੂਰਨ __i) __THROW __attribute_const__;
#ਜੇ_ਅੰਤ

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
ਬਾਹਰੀ ਪੂਰਨ ffsl (ਲੰਮਾ ਪੂਰਨ __l) __THROW __attribute_const__;
__extension__ ਬਾਹਰੀ ਪੂਰਨ ffsll (ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
ਬਾਹਰੀ ਪੂਰਨ strcasecmp (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
ਬਾਹਰੀ ਪੂਰਨ strncasecmp (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
ਬਾਹਰੀ ਪੂਰਨ strcasecmp_l (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
ਬਾਹਰੀ ਪੂਰਨ strncasecmp_l (ਅਚਲ ਅੱਖਰ *__s1, ਅਚਲ ਅੱਖਰ *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#ਜੇ_ਅੰਤ

__END_DECLS

#ਜੇ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ਜੇ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ	/* strings.h  */
