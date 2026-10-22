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

#અન્તર્ભાવ <features.h>
#define __need_size_t
#અન્તર્ભાવ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#જો defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#જો defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
બાહ્ય પૂર્ણાંક bcmp (અચલ શૂન્ય *__s1, અચલ શૂન્ય *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
બાહ્ય શૂન્ય bcopy (અચલ શૂન્ય *__src, શૂન્ય *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
બાહ્ય શૂન્ય bzero (શૂન્ય *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *index (અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
બાહ્ય અચલ અક્ષર *index (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  જો defined __OPTIMIZE__
__extern_always_inline અક્ષર *
index (અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_index (__s, __c);
}

__extern_always_inline અચલ અક્ષર *
index (અચલ અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_index (__s, __c);
}
#  endif
}
# નહીંતર
બાહ્ય અક્ષર *index (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
બાહ્ય "C++"
{
બાહ્ય અક્ષર *rindex (અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
બાહ્ય અચલ અક્ષર *rindex (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  જો defined __OPTIMIZE__
__extern_always_inline અક્ષર *
rindex (અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_rindex (__s, __c);
}

__extern_always_inline અચલ અક્ષર *
rindex (અચલ અક્ષર *__s, પૂર્ણાંક __c) __THROW
{
  પાછા __builtin_rindex (__s, __c);
}
#  endif
}
# નહીંતર
બાહ્ય અક્ષર *rindex (અચલ અક્ષર *__s, પૂર્ણાંક __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#જો defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
બાહ્ય પૂર્ણાંક ffs (પૂર્ણાંક __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
બાહ્ય પૂર્ણાંક ffsl (long પૂર્ણાંક __l) __THROW __attribute_const__;
__extension__ બાહ્ય પૂર્ણાંક ffsll (long long પૂર્ણાંક __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
બાહ્ય પૂર્ણાંક strcasecmp (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
બાહ્ય પૂર્ણાંક strncasecmp (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
બાહ્ય પૂર્ણાંક strcasecmp_l (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
બાહ્ય પૂર્ણાંક strncasecmp_l (અચલ અક્ષર *__s1, અચલ અક્ષર *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#જો __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# જો defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
