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

#ضمن <signal.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <libintl.h>
#ضمن <tls-internal.h>
#ضمن <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
حرف *
strsignal (صحيح signum)
{
  ثابت حرف *desc = __sigdescr_np (signum);
  אם (desc != عدم)
    החזר _(desc);

  אם (__libc_initial)
    {
      بنية tls_internal_t *tls_internal = __glibc_tls_internal ();
      حرر (tls_internal->strsignal_buf);

      صحيح r;
#ifdef SIGRTMIN
      אם (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      אחרת
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      אם (r >= 0)
	החזר tls_internal->strsignal_buf;
      אחרת
	tls_internal->strsignal_buf = عدم;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  החזר _("Unknown signal");
}
