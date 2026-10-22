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

#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libintl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <tls-internal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
ਅੱਖਰ *
strsignal (ਪੂਰਨ signum)
{
  ਅਚਲ ਅੱਖਰ *desc = __sigdescr_np (signum);
  ਜੇ (desc != ਨਿਰਾ)
    ਵਾਪਸ _(desc);

  ਜੇ (__libc_initial)
    {
      ਬਣਤਰ tls_ਅੰਦਰੂਨੀ_t *tls_ਅੰਦਰੂਨੀ = __glibc_tls_internal ();
      ਮੁਕਤ (tls_ਅੰਦਰੂਨੀ->strsignal_buf);

      ਪੂਰਨ r;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SIGRTMIN
      ਜੇ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_ਅੰਦਰੂਨੀ->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
	r = __asprintf (&tls_ਅੰਦਰੂਨੀ->strsignal_buf, _("Unknown signal %d"),
			signum);

      ਜੇ (r >= 0)
	ਵਾਪਸ tls_ਅੰਦਰੂਨੀ->strsignal_buf;
      ਨਹੀਂਤਾਂ
	tls_ਅੰਦਰੂਨੀ->strsignal_buf = ਨਿਰਾ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ਵਾਪਸ _("Unknown signal");
}
