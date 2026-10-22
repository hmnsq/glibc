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

#ଅନ୍ତର୍ଭାଵ <features.h>
#define __need_size_t
#ଅନ୍ତର୍ଭାଵ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ଯଦି defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#ଯଦି defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା bcmp (ଅଚଳ ଶୂନ୍ୟ *__s1, ଅଚଳ ଶୂନ୍ୟ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
ବାହ୍ୟ ଶୂନ୍ୟ bcopy (ଅଚଳ ଶୂନ୍ୟ *__src, ଶୂନ୍ୟ *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
ବାହ୍ୟ ଶୂନ୍ୟ bzero (ଶୂନ୍ୟ *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *index (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *index (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ଯଦି defined __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
index (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_index (__s, __c);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
index (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_index (__s, __c);
}
#  endif
}
# ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *index (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ବାହ୍ୟ "C++"
{
ବାହ୍ୟ ଅକ୍ଷର *rindex (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *rindex (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ଯଦି defined __OPTIMIZE__
__extern_always_inline ଅକ୍ଷର *
rindex (ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_rindex (__s, __c);
}

__extern_always_inline ଅଚଳ ଅକ୍ଷର *
rindex (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c) __THROW
{
  ଫେରନ୍ତୁ __builtin_rindex (__s, __c);
}
#  endif
}
# ଅନ୍ୟଥା
ବାହ୍ୟ ଅକ୍ଷର *rindex (ଅଚଳ ଅକ୍ଷର *__s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#ଯଦି defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ffs (ପୂର୍ଣ୍ଣସଂଖ୍ୟା __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ffsl (long ପୂର୍ଣ୍ଣସଂଖ୍ୟା __l) __THROW __attribute_const__;
__extension__ ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ffsll (long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strcasecmp (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strncasecmp (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strcasecmp_l (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା strncasecmp_l (ଅଚଳ ଅକ୍ଷର *__s1, ଅଚଳ ଅକ୍ଷର *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#ଯଦି __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ଯଦି defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
