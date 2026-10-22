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
نویسه *
strsignal (صحیح signum)
{
  ثابت نویسه *desc = __sigdescr_np (signum);
  اگر (desc != پوچ)
    بازگشت _(desc);

  اگر (__libc_initial)
    {
      ساختار tls_internal_t *tls_internal = __glibc_tls_internal ();
      آزاد (tls_internal->strsignal_buf);

      صحیح r;
#ifdef SIGRTMIN
      اگر (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      وگرنه
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      اگر (r >= 0)
	بازگشت tls_internal->strsignal_buf;
      وگرنه
	tls_internal->strsignal_buf = پوچ;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  بازگشت _("Unknown signal");
}
