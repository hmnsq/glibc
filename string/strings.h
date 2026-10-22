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

#ಅನ್ತರ್ಭಾವ <features.h>
#define __need_size_t
#ಅನ್ತರ್ಭಾವ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ಯದಿ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#ಯದಿ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ bcmp (ಧ್ರುವ ಶೂನ್ಯ *__s1, ಧ್ರುವ ಶೂನ್ಯ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
ಬಾಹ್ಯ ಶೂನ್ಯ bcopy (ಧ್ರುವ ಶೂನ್ಯ *__src, ಶೂನ್ಯ *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
ಬಾಹ್ಯ ಶೂನ್ಯ bzero (ಶೂನ್ಯ *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ವರ್ಣ *index (ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಧ್ರುವ ವರ್ಣ *index (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ಯದಿ defined __OPTIMIZE__
__extern_always_inline ವರ್ಣ *
index (ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c) __THROW
{
  ಪ್ರತ್ಯಾಗಮ __builtin_index (__s, __c);
}

__extern_always_inline ಧ್ರುವ ವರ್ಣ *
index (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c) __THROW
{
  ಪ್ರತ್ಯಾಗಮ __builtin_index (__s, __c);
}
#  endif
}
# ಅನ್ಯಥಾ
ಬಾಹ್ಯ ವರ್ಣ *index (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ವರ್ಣ *rindex (ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಧ್ರುವ ವರ್ಣ *rindex (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ಯದಿ defined __OPTIMIZE__
__extern_always_inline ವರ್ಣ *
rindex (ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c) __THROW
{
  ಪ್ರತ್ಯಾಗಮ __builtin_rindex (__s, __c);
}

__extern_always_inline ಧ್ರುವ ವರ್ಣ *
rindex (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c) __THROW
{
  ಪ್ರತ್ಯಾಗಮ __builtin_rindex (__s, __c);
}
#  endif
}
# ಅನ್ಯಥಾ
ಬಾಹ್ಯ ವರ್ಣ *rindex (ಧ್ರುವ ವರ್ಣ *__s, ಪೂರ್ಣಾಙ್ಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#ಯದಿ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ffs (ಪೂರ್ಣಾಙ್ಕ __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ffsl (long ಪೂರ್ಣಾಙ್ಕ __l) __THROW __attribute_const__;
__extension__ ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ffsll (long long ಪೂರ್ಣಾಙ್ಕ __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ strcasecmp (ಧ್ರುವ ವರ್ಣ *__s1, ಧ್ರುವ ವರ್ಣ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ strncasecmp (ಧ್ರುವ ವರ್ಣ *__s1, ಧ್ರುವ ವರ್ಣ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ strcasecmp_l (ಧ್ರುವ ವರ್ಣ *__s1, ಧ್ರುವ ವರ್ಣ *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ strncasecmp_l (ಧ್ರುವ ವರ್ಣ *__s1, ಧ್ರುವ ವರ್ಣ *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#ಯದಿ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ಯದಿ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
