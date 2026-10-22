/* Copyright (C) 1992-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <unistd.h>

శూన్య
swab (స్థిరరాశి శూన్య *bfrom, శూన్య *bto, ssize_t n)
{
  స్థిరరాశి అక్షరం *from = (స్థిరరాశి అక్షరం *) bfrom;
  అక్షరం *గమ్యం = (అక్షరం *) bto;

  n &= ~((ssize_t) 1);
  అయితే (n > 1)
    {
      స్థిరరాశి అక్షరం b0 = from[--n], b1 = from[--n];
      గమ్యం[n] = b0;
      గమ్యం[n + 1] = b1;
    }
}
