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

#అన్తర్భావ <signal.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <libintl.h>
#అన్తర్భావ <tls-internal.h>
#అన్తర్భావ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
అక్షరం *
strsignal (పూర్ణాంకం signum)
{
  స్థిరరాశి అక్షరం *desc = __sigdescr_np (signum);
  ఒకవేళ (desc != ఖాళీ)
    తిరిగి _(desc);

  ఒకవేళ (__libc_initial)
    {
      నిర్మాణం tls_అంతర్గత_t *tls_అంతర్గత = __glibc_tls_internal ();
      విడుదల (tls_అంతర్గత->strsignal_buf);

      పూర్ణాంకం r;
#నిర్వచితమైతే SIGRTMIN
      ఒకవేళ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_అంతర్గత->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      లేకపోతే
#అయితే_ముగింపు
	r = __asprintf (&tls_అంతర్గత->strsignal_buf, _("Unknown signal %d"),
			signum);

      ఒకవేళ (r >= 0)
	తిరిగి tls_అంతర్గత->strsignal_buf;
      లేకపోతే
	tls_అంతర్గత->strsignal_buf = ఖాళీ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  తిరిగి _("Unknown signal");
}
