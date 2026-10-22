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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ	_STRINGS_H
#ವ್ಯಾಖ್ಯಾನಿಸು	_STRINGS_H	1

#ಅನ್ತರ್ಭಾವ <features.h>
#ವ್ಯಾಖ್ಯಾನಿಸು __need_size_t
#ಅನ್ತರ್ಭಾವ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ಆದರೆ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#ಆದರೆ_ಅಂತ್ಯ

__BEGIN_DECLS

#ಆದರೆ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ bcmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s1, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
ಬಾಹ್ಯ ಶೂನ್ಯ bcopy (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *__src, ಶೂನ್ಯ *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
ಬಾಹ್ಯ ಶೂನ್ಯ bzero (ಶೂನ್ಯ *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *ಸೂಚ್ಯಂಕ (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸೂಚ್ಯಂಕ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ಆದರೆ defined __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
ಸೂಚ್ಯಂಕ (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_index (__s, __c);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
ಸೂಚ್ಯಂಕ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_index (__s, __c);
}
#  endif
}
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *ಸೂಚ್ಯಂಕ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ಬಾಹ್ಯ "C++"
{
ಬಾಹ್ಯ ಅಕ್ಷರ *rindex (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *rindex (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ಆದರೆ defined __OPTIMIZE__
__extern_always_inline ಅಕ್ಷರ *
rindex (ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_rindex (__s, __c);
}

__extern_always_inline ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
rindex (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c) __THROW
{
  ಹಿಂತಿರುಗಿ __builtin_rindex (__s, __c);
}
#  endif
}
# ಇಲ್ಲದಿದ್ದರೆ
ಬಾಹ್ಯ ಅಕ್ಷರ *rindex (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s, ಪೂರ್ಣಾಂಕ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ffs (ಪೂರ್ಣಾಂಕ __i) __THROW __attribute_const__;
#ಆದರೆ_ಅಂತ್ಯ

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ffsl (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ __l) __THROW __attribute_const__;
__extension__ ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ffsll (ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strcasecmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strncasecmp (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strcasecmp_l (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ strncasecmp_l (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s1, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#ಆದರೆ_ಅಂತ್ಯ

__END_DECLS

#ಆದರೆ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ಆದರೆ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ	/* strings.h  */
