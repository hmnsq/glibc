/* Copyright (C) 1996-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <argz.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>


error_t
__argz_create_sep (స్థిరరాశి అక్షరం *string, పూర్ణాంకం delim, అక్షరం **argz, size_t *len)
{
  size_t nlen = అక్షరశ్రేణి_పొడవు (string) + 1;

  ఒకవేళ (nlen > 1)
    {
      స్థిరరాశి అక్షరం *rp;
      అక్షరం *wp;

      *argz = (అక్షరం *) జ్ఞాపకం_ఇవ్వు (nlen);
      ఒకవేళ (*argz == ఖాళీ)
	తిరిగి ENOMEM;

      rp = string;
      wp = *argz;
      చేయి
	ఒకవేళ (*rp == delim)
	  {
	    ఒకవేళ (wp > *argz && wp[-1] != '\0')
	      *wp++ = '\0';
	    లేకపోతే
	      --nlen;
	  }
	లేకపోతే
	  *wp++ = *rp;
      అయితే (*rp++ != '\0');

      ఒకవేళ (nlen == 0)
	{
	  విడుదల (*argz);
	  *argz = ఖాళీ;
	  *len = 0;
	}

      *len = nlen;
    }
  లేకపోతే
    {
      *argz = ఖాళీ;
      *len = 0;
    }

  తిరిగి 0;
}
weak_alias (__argz_create_sep, argz_create_sep)
