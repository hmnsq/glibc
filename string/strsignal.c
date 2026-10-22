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

#समावेश <signal.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <libintl.h>
#समावेश <tls-internal.h>
#समावेश <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
अक्षर *
strsignal (पूर्णांक signum)
{
  स्थिर अक्षर *desc = __sigdescr_np (signum);
  अगर (desc != शून्य)
    वापस _(desc);

  अगर (__libc_initial)
    {
      काष्ठा tls_internal_t *tls_internal = __glibc_tls_internal ();
      मुक्त (tls_internal->strsignal_buf);

      पूर्णांक r;
#अगर_घोषित SIGRTMIN
      अगर (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      अन्यथा
#पूर्ण_अगर
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      अगर (r >= 0)
	वापस tls_internal->strsignal_buf;
      अन्यथा
	tls_internal->strsignal_buf = शून्य;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  वापस _("Unknown signal");
}
