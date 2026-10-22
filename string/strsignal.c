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

#अन्तर्भाव <signal.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <libintl.h>
#अन्तर्भाव <tls-internal.h>
#अन्तर्भाव <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
अक्षर *
strsignal (पूर्णांक signum)
{
  स्थिरांक अक्षर *desc = __sigdescr_np (signum);
  जर (desc != रिक्त)
    परत _(desc);

  जर (__libc_initial)
    {
      संरचना tls_internal_t *tls_internal = __glibc_tls_internal ();
      मुक्त (tls_internal->strsignal_buf);

      पूर्णांक r;
#ifdef SIGRTMIN
      जर (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      अन्यथा
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      जर (r >= 0)
	परत tls_internal->strsignal_buf;
      अन्यथा
	tls_internal->strsignal_buf = रिक्त;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  परत _("Unknown signal");
}
