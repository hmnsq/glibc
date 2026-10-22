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
ಅಕ್ಷರ *
strsignal (ಪೂರ್ಣಾಂಕ signum)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desc = __sigdescr_np (signum);
  ಆದರೆ (desc != ಖಾಲಿ)
    ಹಿಂತಿರುಗಿ _(desc);

  ಆದರೆ (__libc_initial)
    {
      ರಚನೆ tls_ಆಂತರಿಕ_t *tls_ಆಂತರಿಕ = __glibc_tls_internal ();
      ಬಿಡುಗಡೆ (tls_ಆಂತರಿಕ->strsignal_buf);

      ಪೂರ್ಣಾಂಕ r;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SIGRTMIN
      ಆದರೆ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_ಆಂತರಿಕ->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
	r = __asprintf (&tls_ಆಂತರಿಕ->strsignal_buf, _("Unknown signal %d"),
			signum);

      ಆದರೆ (r >= 0)
	ಹಿಂತಿರುಗಿ tls_ಆಂತರಿಕ->strsignal_buf;
      ಇಲ್ಲದಿದ್ದರೆ
	tls_ಆಂತರಿಕ->strsignal_buf = ಖಾಲಿ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ಹಿಂತಿರುಗಿ _("Unknown signal");
}
