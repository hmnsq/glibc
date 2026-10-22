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

#അന്തര്ഭാവ <signal.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <libintl.h>
#അന്തര്ഭാവ <tls-internal.h>
#അന്തര്ഭാവ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
അക്ഷരം *
strsignal (പൂർണ്ണസംഖ്യ signum)
{
  സ്ഥിരം അക്ഷരം *desc = __sigdescr_np (signum);
  എങ്കിൽ (desc != ശൂന്യ)
    തിരികെ _(desc);

  എങ്കിൽ (__libc_initial)
    {
      ഘടന tls_internal_t *tls_internal = __glibc_tls_internal ();
      സ്വതന്ത്രം (tls_internal->strsignal_buf);

      പൂർണ്ണസംഖ്യ r;
#ifdef SIGRTMIN
      എങ്കിൽ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      അല്ലെങ്കിൽ
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      എങ്കിൽ (r >= 0)
	തിരികെ tls_internal->strsignal_buf;
      അല്ലെങ്കിൽ
	tls_internal->strsignal_buf = ശൂന്യ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  തിരികെ _("Unknown signal");
}
