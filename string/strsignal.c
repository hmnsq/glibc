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

#অন্তর্ভাৱ <signal.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <libintl.h>
#অন্তর্ভাৱ <tls-internal.h>
#অন্তর্ভাৱ <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
ৱর্ণ *
strsignal (পূর্ণাঙ্ক signum)
{
  ধ্রুৱ ৱর্ণ *desc = __sigdescr_np (signum);
  যদি (desc != রিক্ত)
    ঘূৰাই _(desc);

  যদি (__libc_initial)
    {
      সংরচনা tls_internal_t *tls_internal = __glibc_tls_internal ();
      মুক্ত (tls_internal->strsignal_buf);

      পূর্ণাঙ্ক r;
#ifdef SIGRTMIN
      যদি (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      অন্যথা
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      যদি (r >= 0)
	ঘূৰাই tls_internal->strsignal_buf;
      অন্যথা
	tls_internal->strsignal_buf = রিক্ত;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ঘূৰাই _("Unknown signal");
}
