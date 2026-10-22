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

#నిర్వచితం_కాకపోతే	_STRINGS_H
#నిర్వచించు	_STRINGS_H	1

#అన్తర్భావ <features.h>
#నిర్వచించు __need_size_t
#అన్తర్భావ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#ఒకవేళ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#అయితే_ముగింపు

__BEGIN_DECLS

#ఒకవేళ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
బాహ్య పూర్ణాంకం bcmp (స్థిరరాశి శూన్య *__s1, స్థిరరాశి శూన్య *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
బాహ్య శూన్య bcopy (స్థిరరాశి శూన్య *__src, శూన్య *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
బాహ్య శూన్య bzero (శూన్య *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *సూచీ (అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
బాహ్య స్థిరరాశి అక్షరం *సూచీ (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  ఒకవేళ defined __OPTIMIZE__
__extern_always_inline అక్షరం *
సూచీ (అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_index (__s, __c);
}

__extern_always_inline స్థిరరాశి అక్షరం *
సూచీ (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_index (__s, __c);
}
#  endif
}
# లేకపోతే
బాహ్య అక్షరం *సూచీ (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
బాహ్య "C++"
{
బాహ్య అక్షరం *rindex (అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
బాహ్య స్థిరరాశి అక్షరం *rindex (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  ఒకవేళ defined __OPTIMIZE__
__extern_always_inline అక్షరం *
rindex (అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_rindex (__s, __c);
}

__extern_always_inline స్థిరరాశి అక్షరం *
rindex (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c) __THROW
{
  తిరిగి __builtin_rindex (__s, __c);
}
#  endif
}
# లేకపోతే
బాహ్య అక్షరం *rindex (స్థిరరాశి అక్షరం *__s, పూర్ణాంకం __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#అయితే_ముగింపు

#ఒకవేళ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
బాహ్య పూర్ణాంకం ffs (పూర్ణాంకం __i) __THROW __attribute_const__;
#అయితే_ముగింపు

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
బాహ్య పూర్ణాంకం ffsl (దీర్ఘ పూర్ణాంకం __l) __THROW __attribute_const__;
__extension__ బాహ్య పూర్ణాంకం ffsll (దీర్ఘ దీర్ఘ పూర్ణాంకం __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
బాహ్య పూర్ణాంకం strcasecmp (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
బాహ్య పూర్ణాంకం strncasecmp (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#నిర్వచితమైతే	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
బాహ్య పూర్ణాంకం strcasecmp_l (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
బాహ్య పూర్ణాంకం strncasecmp_l (స్థిరరాశి అక్షరం *__s1, స్థిరరాశి అక్షరం *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#అయితే_ముగింపు

__END_DECLS

#ఒకవేళ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# ఒకవేళ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#అయితే_ముగింపు

#అయితే_ముగింపు	/* strings.h  */
