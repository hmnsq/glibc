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

#அந்தர்பாவ <signal.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <libintl.h>
#அந்தர்பாவ <tls-internal.h>
#அந்தர்பாவ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
எழுத்து *
strsignal (முழு signum)
{
  மாறிலி எழுத்து *desc = __sigdescr_np (signum);
  எனில் (desc != வெற்று)
    திரும்பு _(desc);

  எனில் (__libc_initial)
    {
      கட்டமைப்பு tls_internal_t *tls_internal = __glibc_tls_internal ();
      விடுவி (tls_internal->strsignal_buf);

      முழு r;
#ifdef SIGRTMIN
      எனில் (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      இல்லையெனில்
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      எனில் (r >= 0)
	திரும்பு tls_internal->strsignal_buf;
      இல்லையெனில்
	tls_internal->strsignal_buf = வெற்று;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  திரும்பு _("Unknown signal");
}
