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

#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <libintl.h>
#અન્તર્ભાવ <tls-internal.h>
#અન્તર્ભાવ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
અક્ષર *
strsignal (પૂર્ણાંક signum)
{
  અચલ અક્ષર *desc = __sigdescr_np (signum);
  જો (desc != ખાલી)
    પાછા _(desc);

  જો (__libc_initial)
    {
      સંરચના tls_internal_t *tls_internal = __glibc_tls_internal ();
      મુક્ત (tls_internal->strsignal_buf);

      પૂર્ણાંક r;
#ifdef SIGRTMIN
      જો (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      નહીંતર
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      જો (r >= 0)
	પાછા tls_internal->strsignal_buf;
      નહીંતર
	tls_internal->strsignal_buf = ખાલી;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  પાછા _("Unknown signal");
}
