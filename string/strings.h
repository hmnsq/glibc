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

#অন্তর্ভাৱ <features.h>
#define __need_size_t
#অন্তর্ভাৱ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#যদি defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#যদি defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
বাহ্য পূর্ণাঙ্ক bcmp (ধ্রুৱ শূন্য *__s1, ধ্রুৱ শূন্য *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
বাহ্য শূন্য bcopy (ধ্রুৱ শূন্য *__src, শূন্য *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
বাহ্য শূন্য bzero (শূন্য *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
বাহ্য "C++"
{
বাহ্য ৱর্ণ *index (ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
বাহ্য ধ্রুৱ ৱর্ণ *index (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  যদি defined __OPTIMIZE__
__extern_always_inline ৱর্ণ *
index (ৱর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  ঘূৰাই __builtin_index (__s, __c);
}

__extern_always_inline ধ্রুৱ ৱর্ণ *
index (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  ঘূৰাই __builtin_index (__s, __c);
}
#  endif
}
# অন্যথা
বাহ্য ৱর্ণ *index (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
বাহ্য "C++"
{
বাহ্য ৱর্ণ *rindex (ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
বাহ্য ধ্রুৱ ৱর্ণ *rindex (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  যদি defined __OPTIMIZE__
__extern_always_inline ৱর্ণ *
rindex (ৱর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  ঘূৰাই __builtin_rindex (__s, __c);
}

__extern_always_inline ধ্রুৱ ৱর্ণ *
rindex (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c) __THROW
{
  ঘূৰাই __builtin_rindex (__s, __c);
}
#  endif
}
# অন্যথা
বাহ্য ৱর্ণ *rindex (ধ্রুৱ ৱর্ণ *__s, পূর্ণাঙ্ক __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#যদি defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
বাহ্য পূর্ণাঙ্ক ffs (পূর্ণাঙ্ক __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
বাহ্য পূর্ণাঙ্ক ffsl (long পূর্ণাঙ্ক __l) __THROW __attribute_const__;
__extension__ বাহ্য পূর্ণাঙ্ক ffsll (long long পূর্ণাঙ্ক __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
বাহ্য পূর্ণাঙ্ক strcasecmp (ধ্রুৱ ৱর্ণ *__s1, ধ্রুৱ ৱর্ণ *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
বাহ্য পূর্ণাঙ্ক strncasecmp (ধ্রুৱ ৱর্ণ *__s1, ধ্রুৱ ৱর্ণ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
বাহ্য পূর্ণাঙ্ক strcasecmp_l (ধ্রুৱ ৱর্ণ *__s1, ধ্রুৱ ৱর্ণ *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
বাহ্য পূর্ণাঙ্ক strncasecmp_l (ধ্রুৱ ৱর্ণ *__s1, ধ্রুৱ ৱর্ণ *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#যদি __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# যদি defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
