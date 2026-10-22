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

#ifndef	_STRINGS_H
#define	_STRINGS_H	1

#include <features.h>
#define __need_size_t
#include <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ᱡᱩᱫᱤ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#ᱡᱩᱫᱤ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
extern puur_naa_nka bcmp (const void *__s1, const void *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
extern void bcopy (const void *__src, void *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
extern void bzero (void *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
extern "C++"
{
extern var_na *index (var_na *__s, puur_naa_nka __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
extern const var_na *index (const var_na *__s, puur_naa_nka __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ᱡᱩᱫᱤ defined __OPTIMIZE__
__extern_always_inline var_na *
index (var_na *__s, puur_naa_nka __c) __THROW
{
  ᱨᱩᱣᱟᱹᱲ __builtin_index (__s, __c);
}

__extern_always_inline const var_na *
index (const var_na *__s, puur_naa_nka __c) __THROW
{
  ᱨᱩᱣᱟᱹᱲ __builtin_index (__s, __c);
}
#  endif
}
# ᱵᱟᱝ
extern var_na *index (const var_na *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
extern "C++"
{
extern var_na *rindex (var_na *__s, puur_naa_nka __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
extern const var_na *rindex (const var_na *__s, puur_naa_nka __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ᱡᱩᱫᱤ defined __OPTIMIZE__
__extern_always_inline var_na *
rindex (var_na *__s, puur_naa_nka __c) __THROW
{
  ᱨᱩᱣᱟᱹᱲ __builtin_rindex (__s, __c);
}

__extern_always_inline const var_na *
rindex (const var_na *__s, puur_naa_nka __c) __THROW
{
  ᱨᱩᱣᱟᱹᱲ __builtin_rindex (__s, __c);
}
#  endif
}
# ᱵᱟᱝ
extern var_na *rindex (const var_na *__s, puur_naa_nka __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#ᱡᱩᱫᱤ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
extern puur_naa_nka ffs (puur_naa_nka __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
extern puur_naa_nka ffsl (long puur_naa_nka __l) __THROW __attribute_const__;
__extension__ extern puur_naa_nka ffsll (long long puur_naa_nka __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
extern puur_naa_nka strcasecmp (const var_na *__s1, const var_na *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
extern puur_naa_nka strncasecmp (const var_na *__s1, const var_na *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
extern puur_naa_nka strcasecmp_l (const var_na *__s1, const var_na *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
extern puur_naa_nka strncasecmp_l (const var_na *__s1, const var_na *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#ᱡᱩᱫᱤ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ᱡᱩᱫᱤ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
