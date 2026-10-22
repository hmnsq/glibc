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

#ضمن <features.h>
#define __need_size_t
#ضمن <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#إذا defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#إذا defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
خارجي صحيح bcmp (ثابت فراغ *__s1, ثابت فراغ *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
خارجي فراغ bcopy (ثابت فراغ *__src, فراغ *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
خارجي فراغ bzero (فراغ *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
خارجي "C++"
{
خارجي حرف *index (حرف *__s, صحيح __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
خارجي ثابت حرف *index (ثابت حرف *__s, صحيح __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  إذا defined __OPTIMIZE__
__extern_always_inline حرف *
index (حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_index (__s, __c);
}

__extern_always_inline ثابت حرف *
index (ثابت حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_index (__s, __c);
}
#  endif
}
# وإلا
خارجي حرف *index (ثابت حرف *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
خارجي "C++"
{
خارجي حرف *rindex (حرف *__s, صحيح __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
خارجي ثابت حرف *rindex (ثابت حرف *__s, صحيح __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  إذا defined __OPTIMIZE__
__extern_always_inline حرف *
rindex (حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_rindex (__s, __c);
}

__extern_always_inline ثابت حرف *
rindex (ثابت حرف *__s, صحيح __c) __THROW
{
  أرجع __builtin_rindex (__s, __c);
}
#  endif
}
# وإلا
خارجي حرف *rindex (ثابت حرف *__s, صحيح __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#إذا defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
خارجي صحيح ffs (صحيح __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
خارجي صحيح ffsl (long صحيح __l) __THROW __attribute_const__;
__extension__ خارجي صحيح ffsll (long long صحيح __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
خارجي صحيح strcasecmp (ثابت حرف *__s1, ثابت حرف *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
خارجي صحيح strncasecmp (ثابت حرف *__s1, ثابت حرف *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
خارجي صحيح strcasecmp_l (ثابت حرف *__s1, ثابت حرف *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
خارجي صحيح strncasecmp_l (ثابت حرف *__s1, ثابت حرف *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#إذا __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# إذا defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
