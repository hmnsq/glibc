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

#അന്തര്ഭാവ <features.h>
#define __need_size_t
#അന്തര്ഭാവ <stddef.h>

/* Tell the caller that we provide correct C++ prototypes.  */
#എങ്കിൽ defined __cplusplus && __GNUC_PREREQ (4, 4)
# define __CORRECT_ISO_CPP_STRINGS_H_PROTO
#endif

__BEGIN_DECLS

#എങ്കിൽ defined __USE_MISC || !defined __USE_XOPEN2K8
/* Compare N bytes of S1 and S2 (same as memcmp).  */
ബാഹ്യ പൂർണ്ണസംഖ്യ bcmp (സ്ഥിരം ശൂന്യം *__s1, സ്ഥിരം ശൂന്യം *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
ബാഹ്യ ശൂന്യം bcopy (സ്ഥിരം ശൂന്യം *__src, ശൂന്യം *__dest, size_t __n)
  __THROW __nonnull ((1, 2));

/* Set N bytes of S to 0.  */
ബാഹ്യ ശൂന്യം bzero (ശൂന്യം *__s, size_t __n) __THROW __nonnull ((1));

/* Find the first occurrence of C in S (same as strchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *index (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));
ബാഹ്യ സ്ഥിരം അക്ഷരം *index (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("index") __attribute_pure__ __nonnull ((1));

#  എങ്കിൽ defined __OPTIMIZE__
__extern_always_inline അക്ഷരം *
index (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_index (__s, __c);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
index (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_index (__s, __c);
}
#  endif
}
# അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *index (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif

/* Find the last occurrence of C in S (same as strrchr).  */
# ifdef __CORRECT_ISO_CPP_STRINGS_H_PROTO
ബാഹ്യ "C++"
{
ബാഹ്യ അക്ഷരം *rindex (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));
ബാഹ്യ സ്ഥിരം അക്ഷരം *rindex (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __asm ("rindex") __attribute_pure__ __nonnull ((1));

#  എങ്കിൽ defined __OPTIMIZE__
__extern_always_inline അക്ഷരം *
rindex (അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_rindex (__s, __c);
}

__extern_always_inline സ്ഥിരം അക്ഷരം *
rindex (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c) __THROW
{
  തിരികെ __builtin_rindex (__s, __c);
}
#  endif
}
# അല്ലെങ്കിൽ
ബാഹ്യ അക്ഷരം *rindex (സ്ഥിരം അക്ഷരം *__s, പൂർണ്ണസംഖ്യ __c)
     __THROW __attribute_pure__ __nonnull ((1));
# endif
#endif

#എങ്കിൽ defined __USE_MISC || !defined __USE_XOPEN2K8 || defined __USE_XOPEN2K8XSI
/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ ffs (പൂർണ്ണസംഖ്യ __i) __THROW __attribute_const__;
#endif

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_MISC
ബാഹ്യ പൂർണ്ണസംഖ്യ ffsl (long പൂർണ്ണസംഖ്യ __l) __THROW __attribute_const__;
__extension__ ബാഹ്യ പൂർണ്ണസംഖ്യ ffsll (long long പൂർണ്ണസംഖ്യ __ll)
     __THROW __attribute_const__;
# endif

/* Compare S1 and S2, ignoring case.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strcasecmp (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2)
     __THROW __attribute_pure__ __nonnull ((1, 2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strncasecmp (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2, size_t __n)
     __THROW __attribute_pure__ __nonnull ((1, 2));

#ifdef	__USE_XOPEN2K8
/* POSIX.1-2008 extended locale interface (see locale.h).  */
# include <bits/types/locale_t.h>

/* Compare S1 and S2, ignoring case, using collation rules from LOC.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strcasecmp_l (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 3));

/* Compare no more than N chars of S1 and S2, ignoring case, using
   collation rules from LOC.  */
ബാഹ്യ പൂർണ്ണസംഖ്യ strncasecmp_l (സ്ഥിരം അക്ഷരം *__s1, സ്ഥിരം അക്ഷരം *__s2,
			  size_t __n, locale_t __loc)
     __THROW __attribute_pure__ __nonnull ((1, 2, 4));
#endif

__END_DECLS

#എങ്കിൽ __GNUC_PREREQ (3,4) && __USE_FORTIFY_LEVEL > 0 \
    && defined __fortify_function
/* Functions with security checks.  */
# എങ്കിൽ defined __USE_MISC || !defined __USE_XOPEN2K8
#  include <bits/strings_fortified.h>
# endif
#endif

#endif	/* strings.h  */
