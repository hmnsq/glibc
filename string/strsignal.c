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
वर्ण *
strsignal (पूर्णाङ्क signum)
{
  ध्रुव वर्ण *desc = __sigdescr_np (signum);
  यदि (desc != रिक्त)
    प्रत्यागम _(desc);

  यदि (__libc_initial)
    {
      संरचना tls_आन्तरिकम्_t *tls_आन्तरिकम् = __glibc_tls_internal ();
      मुक्त (tls_आन्तरिकम्->strsignal_buf);

      पूर्णाङ्क r;
#यदि_परिभाषितम् SIGRTMIN
      यदि (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_आन्तरिकम्->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      अन्यथा
#यदि_अन्तः
	r = __asprintf (&tls_आन्तरिकम्->strsignal_buf, _("Unknown signal %d"),
			signum);

      यदि (r >= 0)
	प्रत्यागम tls_आन्तरिकम्->strsignal_buf;
      अन्यथा
	tls_आन्तरिकम्->strsignal_buf = रिक्त;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  प्रत्यागम _("Unknown signal");
}
