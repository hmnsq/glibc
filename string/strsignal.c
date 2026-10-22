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

#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <libintl.h>
#ಅನ್ತರ್ಭಾವ <tls-internal.h>
#ಅನ್ತರ್ಭಾವ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
ವರ್ಣ *
strsignal (ಪೂರ್ಣಾಙ್ಕ signum)
{
  ಧ್ರುವ ವರ್ಣ *desc = __sigdescr_np (signum);
  ಯದಿ (desc != ರಿಕ್ತ)
    ಪ್ರತ್ಯಾಗಮ _(desc);

  ಯದಿ (__libc_initial)
    {
      ಸಂರಚನಾ tls_internal_t *tls_internal = __glibc_tls_internal ();
      ಮುಕ್ತ (tls_internal->strsignal_buf);

      ಪೂರ್ಣಾಙ್ಕ r;
#ifdef SIGRTMIN
      ಯದಿ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ಅನ್ಯಥಾ
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      ಯದಿ (r >= 0)
	ಪ್ರತ್ಯಾಗಮ tls_internal->strsignal_buf;
      ಅನ್ಯಥಾ
	tls_internal->strsignal_buf = ರಿಕ್ತ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ಪ್ರತ್ಯಾಗಮ _("Unknown signal");
}
