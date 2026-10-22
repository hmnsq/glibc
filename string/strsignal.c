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

#شامل <signal.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <libintl.h>
#شامل <tls-internal.h>
#شامل <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
حرف *
strsignal (صحیح signum)
{
  ثابت حرف *desc = __sigdescr_np (signum);
  اگر (desc != تہی)
    واپس _(desc);

  اگر (__libc_initial)
    {
      ساخت tls_اندرونی_t *tls_اندرونی = __glibc_tls_internal ();
      آزاد (tls_اندرونی->strsignal_buf);

      صحیح r;
#اگر_تعریف_شدہ SIGRTMIN
      اگر (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_اندرونی->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ورنہ
#اگر_ختم
	r = __asprintf (&tls_اندرونی->strsignal_buf, _("Unknown signal %d"),
			signum);

      اگر (r >= 0)
	واپس tls_اندرونی->strsignal_buf;
      ورنہ
	tls_اندرونی->strsignal_buf = تہی;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  واپس _("Unknown signal");
}
