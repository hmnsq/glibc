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

#অন্তর্ভাব <signal.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <libintl.h>
#অন্তর্ভাব <tls-internal.h>
#অন্তর্ভাব <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
অক্ষর *
strsignal (পূর্ণসংখ্যা signum)
{
  ধ্রুবক অক্ষর *desc = __sigdescr_np (signum);
  যদি (desc != ফাঁকা)
    ফেরত _(desc);

  যদি (__libc_initial)
    {
      কাঠামো tls_internal_t *tls_internal = __glibc_tls_internal ();
      মুক্ত (tls_internal->strsignal_buf);

      পূর্ণসংখ্যা r;
#ifdef SIGRTMIN
      যদি (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      অন্যথা
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      যদি (r >= 0)
	ফেরত tls_internal->strsignal_buf;
      অন্যথা
	tls_internal->strsignal_buf = ফাঁকা;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ফেরত _("Unknown signal");
}
