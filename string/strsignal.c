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

#ଅନ୍ତର୍ଭାଵ <signal.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <libintl.h>
#ଅନ୍ତର୍ଭାଵ <tls-internal.h>
#ଅନ୍ତର୍ଭାଵ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
ଅକ୍ଷର *
strsignal (ପୂର୍ଣ୍ଣସଂଖ୍ୟା signum)
{
  ଅଚଳ ଅକ୍ଷର *desc = __sigdescr_np (signum);
  ଯଦି (desc != ଖାଲି)
    ଫେରନ୍ତୁ _(desc);

  ଯଦି (__libc_initial)
    {
      ସଂରଚନା tls_internal_t *tls_internal = __glibc_tls_internal ();
      ମୁକ୍ତ (tls_internal->strsignal_buf);

      ପୂର୍ଣ୍ଣସଂଖ୍ୟା r;
#ifdef SIGRTMIN
      ଯଦି (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ଅନ୍ୟଥା
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      ଯଦି (r >= 0)
	ଫେରନ୍ତୁ tls_internal->strsignal_buf;
      ଅନ୍ୟଥା
	tls_internal->strsignal_buf = ଖାଲି;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ଫେରନ୍ତୁ _("Unknown signal");
}
