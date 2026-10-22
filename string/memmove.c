/* Copy memory to memory until the specified number of bytes
   has been copied.  Overlap is handled correctly.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <string.h>
#అన్తర్భావ <memcopy.h>

/* All this is so that bcopy.c can #include
   this file after defining some things.  */
#నిర్వచితం_కాకపోతే	a1
#నిర్వచించు	a1	dest	/* First arg is DEST.  */
#నిర్వచించు	a1const
#నిర్వచించు	a2	src	/* Second arg is SRC.  */
#నిర్వచించు	a2const	స్థిరరాశి
#నిర్వచనం_రద్దు memmove
#అయితే_ముగింపు
#ఒకవేళ	!defined(RETURN) || !defined(rettype)
#నిర్వచించు	RETURN(s)	తిరిగి (s)	/* Return DEST.  */
#నిర్వచించు	rettype		శూన్య *
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే MEMMOVE
#నిర్వచించు MEMMOVE memmove
#అయితే_ముగింపు

rettype
inhibit_loop_గమ్యం_libcall
MEMMOVE (a1const శూన్య *a1, a2const శూన్య *a2, size_t len)
{
  గుర్తులేని దీర్ఘ పూర్ణాంకం dstp = (దీర్ఘ పూర్ణాంకం) dest;
  గుర్తులేని దీర్ఘ పూర్ణాంకం srcp = (దీర్ఘ పూర్ణాంకం) src;

  /* This test makes the forward copying code be used whenever possible.
     Reduces the working set.  */
  ఒకవేళ (dstp - srcp >= len)	/* *Unsigned* compare!  */
    {
      /* Copy from the beginning to the end.  */

#ఒకవేళ MEMCPY_OK_FOR_FWD_MEMMOVE
      dest = జ్ఞాపకం_నకలు (dest, src, len);
#లేకపోతే
      /* If there not too few bytes to copy, use word copy.  */
      ఒకవేళ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= (-dstp) % OPSIZ;
	  BYTE_COPY_FWD (dstp, srcp, (-dstp) % OPSIZ);

	  /* Copy whole pages from SRCP to DSTP by virtual address
	     manipulation, as much as possible.  */

	  పుట_COPY_FWD_MAYBE (dstp, srcp, len, len);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  మాట_COPY_FWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_FWD (dstp, srcp, len);
#అయితే_ముగింపు /* MEMCPY_OK_FOR_FWD_MEMMOVE */
    }
  లేకపోతే
    {
      /* Copy from the end to the beginning.  */
      srcp += len;
      dstp += len;

      /* If there not too few bytes to copy, use word copy.  */
      ఒకవేళ (len >= OP_T_THRES)
	{
	  /* Copy just a few bytes to make DSTP aligned.  */
	  len -= dstp % OPSIZ;
	  BYTE_COPY_BWD (dstp, srcp, dstp % OPSIZ);

	  /* Copy from SRCP to DSTP taking advantage of the known
	     alignment of DSTP.  Number of bytes remaining is put
	     in the third argument, i.e. in LEN.  This number may
	     vary from machine to machine.  */

	  మాట_COPY_BWD (dstp, srcp, len, len);

	  /* Fall out and copy the tail.  */
	}

      /* There are just a few bytes to copy.  Use byte memory operations.  */
      BYTE_COPY_BWD (dstp, srcp, len);
    }

  RETURN (dest);
}
#నిర్వచితం_కాకపోతే memmove
libc_hidden_builtin_def (memmove)
#అయితే_ముగింపు
