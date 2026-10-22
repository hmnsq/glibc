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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <tls-internal.h>
#include <libc-internal.h>

/* Return a string describing the meaning of the signal number SIGNUM.  */
var_na *
strsignal (ຈຳນວນເຕັມ signum)
{
  const var_na *desc = __sigdescr_np (signum);
  ຖ້າ (desc != NULL)
    ສົ່ງຄືນ _(desc);

  ຖ້າ (__libc_initial)
    {
      sa_nracanaa tls_internal_t *tls_internal = __glibc_tls_internal ();
      free (tls_internal->strsignal_buf);

      ຈຳນວນເຕັມ r;
#ifdef SIGRTMIN
      ຖ້າ (signum >= SIGRTMIN && signum <= SIGRTMAX)
	r = __asprintf (&tls_internal->strsignal_buf, _("Real-time signal %d"),
			signum - SIGRTMIN);
      ບໍ່ດັ່ງນັ້ນ
#endif
	r = __asprintf (&tls_internal->strsignal_buf, _("Unknown signal %d"),
			signum);

      ຖ້າ (r >= 0)
	ສົ່ງຄືນ tls_internal->strsignal_buf;
      ບໍ່ດັ່ງນັ້ນ
	tls_internal->strsignal_buf = NULL;
    }
  /* Fall through on asprintf error, and for !__libc_initial:
     secondary namespaces use a different malloc and cannot
     participate in the buffer management.  */
  ສົ່ງຄືນ _("Unknown signal");
}
