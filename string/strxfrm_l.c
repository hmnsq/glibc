/* Copyright (C) 1995-2026 Free Software Foundation, Inc.
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

#అన్తర్భావ <assert.h>
#అన్తర్భావ <langinfo.h>
#అన్తర్భావ <locale.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/param.h>

#నిర్వచితం_కాకపోతే STRING_TYPE
# define STRING_TYPE అక్షరం
# define USTRING_TYPE గుర్తులేని అక్షరం
# define STRXFRM __strxfrm_l
# define STRLEN అక్షరశ్రేణి_పొడవు
# define STPNCPY __stpncpy
# define బరువు_H "../locale/weight.h"
# define SUFFIX	MB
# define L(arg) arg
#అయితే_ముగింపు

#నిర్వచించు CONCAT(a,b) CONCAT1(a,b)
#నిర్వచించు CONCAT1(a,b) a##b

/* Maximum string size that is calculated with cached indices.  Right now this
   is an arbitrary value open to optimizations.  SMALL_STR_SIZE * 4 has to be
   lower than __MAX_ALLOCA_CUTOFF.  Keep localedata/xfrm-test.c in sync.  */
#నిర్వచించు SMALL_STR_కొలత 4095

#అన్తర్భావ "../locale/localeinfo.h"
#అన్తర్భావ బరువు_H

/* Group locale data for shorter parameter lists.  */
రకనిర్వచనం నిర్మాణం
{
  uint32_t nrules;
  గుర్తులేని అక్షరం *rulesets;
  USTRING_TYPE *weights;
  int32_t *పట్టిక;
  USTRING_TYPE *extra;
  int32_t *పరోక్ష;
} locale_దత్తాంశం_t;

#నిర్వచితం_కాకపోతే WIDE_CHAR_సంస్కరణ

/* We need UTF-8 encoding of numbers.  */
స్థిర పూర్ణాంకం
utf8_encode (అక్షరం *buf, పూర్ణాంకం val)
{
  పూర్ణాంకం retval;

  ఒకవేళ (val < 0x80)
    {
      *buf++ = (అక్షరం) val;
      retval = 1;
    }
  లేకపోతే
    {
      పూర్ణాంకం అడుగు;

      కొరకు (అడుగు = 2; అడుగు < 6; ++అడుగు)
	ఒకవేళ ((val & (~(uint32_t)0 << (5 * అడుగు + 1))) == 0)
	  ఆపు;
      retval = అడుగు;

      *buf = (గుర్తులేని అక్షరం) (~0xff >> అడుగు);
      --అడుగు;
      చేయి
	{
	  buf[అడుగు] = 0x80 | (val & 0x3f);
	  val >>= 6;
	}
      అయితే (--అడుగు > 0);
      *buf |= val;
    }

  తిరిగి retval;
}
#అయితే_ముగింపు

/* Find next weight and rule index.  Inlined since called for every char.  */
స్థిర __always_inline size_t
కనుగొను_idx (స్థిరరాశి USTRING_TYPE **us, int32_t *బరువు_idx,
	  గుర్తులేని అక్షరం *నియమం_idx, స్థిరరాశి locale_దత్తాంశం_t *l_దత్తాంశం, స్థిరరాశి పూర్ణాంకం pass)
{
  int32_t tmp = findidx (l_దత్తాంశం->పట్టిక, l_దత్తాంశం->పరోక్ష, l_దత్తాంశం->extra, us,
			 -1);
  *నియమం_idx = tmp >> 24;
  int32_t idx = tmp & 0xffffff;
  size_t len = l_దత్తాంశం->weights[idx++];

  /* Skip over indices of previous levels.  */
  కొరకు (పూర్ణాంకం i = 0; i < pass; i++)
    {
      idx += len;
      len = l_దత్తాంశం->weights[idx++];
    }

  *బరువు_idx = idx;
  తిరిగి len;
}

స్థిర పూర్ణాంకం
కనుగొను_position (స్థిరరాశి USTRING_TYPE *us, స్థిరరాశి locale_దత్తాంశం_t *l_దత్తాంశం,
	       స్థిరరాశి పూర్ణాంకం pass)
{
  int32_t బరువు_idx;
  గుర్తులేని అక్షరం నియమం_idx;
  స్థిరరాశి USTRING_TYPE *usrc = us;

  కనుగొను_idx (&usrc, &బరువు_idx, &నియమం_idx, l_దత్తాంశం, pass);
  తిరిగి l_దత్తాంశం->rulesets[నియమం_idx * l_దత్తాంశం->nrules + pass] & క్రమీకరించు_position;
}

/* Do the transformation.  */
స్థిర size_t
do_xfrm (స్థిరరాశి USTRING_TYPE *usrc, STRING_TYPE *dest, size_t n,
	 స్థిరరాశి locale_దత్తాంశం_t *l_దత్తాంశం)
{
  int32_t బరువు_idx;
  గుర్తులేని అక్షరం నియమం_idx;
  uint32_t pass;
  size_t needed = 0;
  size_t చివరి_needed;

  /* Now the passes over the weights.  */
  కొరకు (pass = 0; pass < l_దత్తాంశం->nrules; ++pass)
    {
      size_t backw_len = 0;
      చివరి_needed = needed;
      స్థిరరాశి USTRING_TYPE *cur = usrc;
      స్థిరరాశి USTRING_TYPE *backw_ప్రారంభం = ఖాళీ;

       /* We assume that if a rule has defined `position' in one section
         this is true for all of them.  */
      పూర్ణాంకం position = కనుగొను_position (cur, l_దత్తాంశం, pass);

      ఒకవేళ (position == 0)
	{
	  అయితే (*cur != L('\0'))
	    {
	      స్థిరరాశి USTRING_TYPE *pos = cur;
	      size_t len = కనుగొను_idx (&cur, &బరువు_idx, &నియమం_idx, l_దత్తాంశం,
				     pass);
	      పూర్ణాంకం నియమం = l_దత్తాంశం->rulesets[నియమం_idx * l_దత్తాంశం->nrules + pass];

	      ఒకవేళ ((నియమం & క్రమీకరించు_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ఒకవేళ (backw_ప్రారంభం != ఖాళీ)
		    {
		      కొరకు (size_t i = backw_len; i > 0; )
			{
			  int32_t బరువు_idx;
			  గుర్తులేని అక్షరం నియమం_idx;
			  size_t len = కనుగొను_idx (&backw_ప్రారంభం, &బరువు_idx,
						 &నియమం_idx, l_దత్తాంశం, pass);
			  ఒకవేళ (needed + i < n)
			    కొరకు (size_t j = len; j > 0; j--)
			      dest[needed + i - j] =
				l_దత్తాంశం->weights[బరువు_idx++];

			  i -= len;
			}

		      needed += backw_len;
		      backw_ప్రారంభం = ఖాళీ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ఒకవేళ (needed + len < n)
		    అయితే (len-- > 0)
		      dest[needed++] = l_దత్తాంశం->weights[బరువు_idx++];
		  లేకపోతే
		    /* No more characters fit into the buffer.  */
		    needed += len;
		}
	      లేకపోతే
		{
		  /* Remember start of the backward sequence & track length.  */
		  ఒకవేళ (backw_ప్రారంభం == ఖాళీ)
		    backw_ప్రారంభం = pos;
		  backw_len += len;
		}
	    }


	  /* Handle the pushed backward sequence.  */
	  ఒకవేళ (backw_ప్రారంభం != ఖాళీ)
	    {
	      కొరకు (size_t i = backw_len; i > 0; )
		{
		  size_t len = కనుగొను_idx (&backw_ప్రారంభం, &బరువు_idx, &నియమం_idx,
					 l_దత్తాంశం, pass);
		  ఒకవేళ (needed + i < n)
		    కొరకు (size_t j = len; j > 0; j--)
		      dest[needed + i - j] =
			l_దత్తాంశం->weights[బరువు_idx++];

		  i -= len;
		}

	      needed += backw_len;
	    }
	}
      లేకపోతే
	{
	  పూర్ణాంకం val = 1;
#నిర్వచితం_కాకపోతే WIDE_CHAR_సంస్కరణ
	  అక్షరం buf[7];
	  size_t buflen;
#అయితే_ముగింపు
	  size_t i;

	  అయితే (*cur != L('\0'))
	    {
	      స్థిరరాశి USTRING_TYPE *pos = cur;
	      size_t len = కనుగొను_idx (&cur, &బరువు_idx, &నియమం_idx, l_దత్తాంశం,
				     pass);
	      పూర్ణాంకం నియమం = l_దత్తాంశం->rulesets[నియమం_idx * l_దత్తాంశం->nrules + pass];

	      ఒకవేళ ((నియమం & క్రమీకరించు_forward) != 0)
		{
		  /* Handle the pushed backward sequence.  */
		  ఒకవేళ (backw_ప్రారంభం != ఖాళీ)
		    {
		      కొరకు (size_t p = backw_len; p > 0; p--)
			{
			  size_t len;
			  int32_t బరువు_idx;
			  గుర్తులేని అక్షరం నియమం_idx;
			  స్థిరరాశి USTRING_TYPE *backw_cur = backw_ప్రారంభం;

			  /* To prevent a warning init the used vars.  */
			  len = కనుగొను_idx (&backw_cur, &బరువు_idx,
					  &నియమం_idx, l_దత్తాంశం, pass);

			  కొరకు (i = 1; i < p; i++)
			    len = కనుగొను_idx (&backw_cur, &బరువు_idx,
					    &నియమం_idx, l_దత్తాంశం, pass);

			  ఒకవేళ (len != 0)
			    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
			      ఒకవేళ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  కొరకు (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      l_దత్తాంశం->weights[బరువు_idx + i];
				}
			      needed += 1 + len;
#లేకపోతే
			      buflen = utf8_encode (buf, val);
			      ఒకవేళ (needed + buflen + len < n)
				{
				  కొరకు (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  కొరకు (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      l_దత్తాంశం->weights[బరువు_idx + i];
				}
			      needed += buflen + len;
#అయితే_ముగింపు
			      val = 1;
			    }
			  లేకపోతే
			    ++val;
			}

		      backw_ప్రారంభం = ఖాళీ;
		      backw_len = 0;
		    }

		  /* Now handle the forward element.  */
		  ఒకవేళ (len != 0)
		    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
		      ఒకవేళ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_దత్తాంశం->weights[బరువు_idx + i];
			}
		      needed += 1 + len;
#లేకపోతే
		      buflen = utf8_encode (buf, val);
		      ఒకవేళ (needed + buflen + len < n)
			{
			  కొరకు (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_దత్తాంశం->weights[బరువు_idx + i];
			}
		      needed += buflen + len;
#అయితే_ముగింపు
		      val = 1;
		    }
		  లేకపోతే
		    ++val;
		}
	      లేకపోతే
		{
		  /* Remember start of the backward sequence & track length.  */
		  ఒకవేళ (backw_ప్రారంభం == ఖాళీ)
		    backw_ప్రారంభం = pos;
		  backw_len++;
		}
	    }

	  /* Handle the pushed backward sequence.  */
	  ఒకవేళ (backw_ప్రారంభం != ఖాళీ)
	    {
	      కొరకు (size_t p = backw_len; p > 0; p--)
		{
		  size_t len;
		  int32_t బరువు_idx;
		  గుర్తులేని అక్షరం నియమం_idx;
		  స్థిరరాశి USTRING_TYPE *backw_cur = backw_ప్రారంభం;

		  /* To prevent a warning init the used vars.  */
		  len = కనుగొను_idx (&backw_cur, &బరువు_idx,
				  &నియమం_idx, l_దత్తాంశం, pass);

		  కొరకు (i = 1; i < p; i++)
		    len = కనుగొను_idx (&backw_cur, &బరువు_idx,
				    &నియమం_idx, l_దత్తాంశం, pass);

		  ఒకవేళ (len != 0)
		    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
		      ఒకవేళ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      l_దత్తాంశం->weights[బరువు_idx + i];
			}
		      needed += 1 + len;
#లేకపోతే
		      buflen = utf8_encode (buf, val);
		      ఒకవేళ (needed + buflen + len < n)
			{
			  కొరకు (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      l_దత్తాంశం->weights[బరువు_idx + i];
			}
		      needed += buflen + len;
#అయితే_ముగింపు
		      val = 1;
		    }
		  లేకపోతే
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ఒకవేళ (needed < n)
	dest[needed] = pass + 1 < l_దత్తాంశం->nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ఒకవేళ (needed > 2 && needed == చివరి_needed + 1)
    {
      /* Remove the \1 byte.  */
      ఒకవేళ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  తిరిగి needed - 1;
}

/* Do the transformation using weight-index and rule cache.  */
స్థిర size_t
do_xfrm_cached (STRING_TYPE *dest, size_t n, స్థిరరాశి locale_దత్తాంశం_t *l_దత్తాంశం,
		size_t idxmax, int32_t *idxarr, స్థిరరాశి గుర్తులేని అక్షరం *rulearr)
{
  uint32_t nrules = l_దత్తాంశం->nrules;
  గుర్తులేని అక్షరం *rulesets = l_దత్తాంశం->rulesets;
  USTRING_TYPE *weights = l_దత్తాంశం->weights;
  uint32_t pass;
  size_t needed = 0;
  size_t చివరి_needed;
  size_t idxcnt;

  /* Now the passes over the weights.  */
  కొరకు (pass = 0; pass < nrules; ++pass)
    {
      size_t backw_stop = ~0ul;
      పూర్ణాంకం నియమం = rulesets[rulearr[0] * nrules + pass];
      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  */
      పూర్ణాంకం position = నియమం & క్రమీకరించు_position;

      చివరి_needed = needed;
      ఒకవేళ (position == 0)
	{
	  కొరకు (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ఒకవేళ ((నియమం & క్రమీకరించు_forward) != 0)
		{
		  size_t len;

		  ఒకవేళ (backw_stop != ~0ul)
		    {
		      /* Handle the pushed elements now.  */
		      size_t backw;

		      కొరకు (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];

			  ఒకవేళ (needed + len < n)
			    అయితే (len-- > 0)
			      dest[needed++] = weights[idxarr[backw]++];
			  లేకపోతే
			    {
				/* No more characters fit into the buffer.  */
			      needed += len;
			      idxarr[backw] += len;
			    }
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ఒకవేళ (needed + len < n)
		    అయితే (len-- > 0)
		      dest[needed++] = weights[idxarr[idxcnt]++];
		  లేకపోతే
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[idxcnt] += len;
		    }
		}
	      లేకపోతే
		{
		  /* Remember where the backwards series started.  */
		  ఒకవేళ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      నియమం = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }


	  ఒకవేళ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxcnt;
	      అయితే (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];

		  ఒకవేళ (needed + len < n)
		    అయితే (len-- > 0)
		      dest[needed++] = weights[idxarr[backw]++];
		  లేకపోతే
		    {
		      /* No more characters fit into the buffer.  */
		      needed += len;
		      idxarr[backw] += len;
		    }
		}
	    }
	}
      లేకపోతే
	{
	  పూర్ణాంకం val = 1;
#నిర్వచితం_కాకపోతే WIDE_CHAR_సంస్కరణ
	  అక్షరం buf[7];
	  size_t buflen;
#అయితే_ముగింపు
	  size_t i;

	  కొరకు (idxcnt = 0; idxcnt < idxmax; ++idxcnt)
	    {
	      ఒకవేళ ((నియమం & క్రమీకరించు_forward) != 0)
		{
		  size_t len;

		  ఒకవేళ (backw_stop != ~0ul)
		    {
		     /* Handle the pushed elements now.  */
		      size_t backw;

		      కొరకు (backw = idxcnt; backw > backw_stop; )
			{
			  --backw;
			  len = weights[idxarr[backw]++];
			  ఒకవేళ (len != 0)
			    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
			      ఒకవేళ (needed + 1 + len < n)
				{
				  dest[needed] = val;
				  కొరకు (i = 0; i < len; ++i)
				    dest[needed + 1 + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += 1 + len;
#లేకపోతే
			      buflen = utf8_encode (buf, val);
			      ఒకవేళ (needed + buflen + len < n)
				{
				  కొరకు (i = 0; i < buflen; ++i)
				    dest[needed + i] = buf[i];
				  కొరకు (i = 0; i < len; ++i)
				    dest[needed + buflen + i] =
				      weights[idxarr[backw] + i];
				}
			      needed += buflen + len;
#అయితే_ముగింపు
			      idxarr[backw] += len;
			      val = 1;
			    }
			  లేకపోతే
			    ++val;
			}

		      backw_stop = ~0ul;
		    }

		  /* Now handle the forward element.  */
		  len = weights[idxarr[idxcnt]++];
		  ఒకవేళ (len != 0)
		    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
		      ఒకవేళ (needed + 1+ len < n)
			{
			  dest[needed] = val;
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += 1 + len;
#లేకపోతే
		      buflen = utf8_encode (buf, val);
		      ఒకవేళ (needed + buflen + len < n)
			{
			  కొరకు (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[idxcnt] + i];
			}
		      needed += buflen + len;
#అయితే_ముగింపు
		      idxarr[idxcnt] += len;
		      val = 1;
		    }
		  లేకపోతే
		    /* Note that we don't have to increment `idxarr[idxcnt]'
		       since the length is zero.  */
		    ++val;
		}
	      లేకపోతే
		{
		  /* Remember where the backwards series started.  */
		  ఒకవేళ (backw_stop == ~0ul)
		    backw_stop = idxcnt;
		}

	      నియమం = rulesets[rulearr[idxcnt + 1] * nrules + pass];
	    }

	  ఒకవేళ (backw_stop != ~0ul)
	    {
	      /* Handle the pushed elements now.  */
	      size_t backw;

	      backw = idxmax - 1;
	      అయితే (backw > backw_stop)
		{
		  size_t len = weights[idxarr[--backw]++];
		  ఒకవేళ (len != 0)
		    {
#నిర్వచితమైతే WIDE_CHAR_సంస్కరణ
		      ఒకవేళ (needed + 1 + len < n)
			{
			  dest[needed] = val;
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + 1 + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += 1 + len;
#లేకపోతే
		      buflen = utf8_encode (buf, val);
		      ఒకవేళ (needed + buflen + len < n)
			{
			  కొరకు (i = 0; i < buflen; ++i)
			    dest[needed + i] = buf[i];
			  కొరకు (i = 0; i < len; ++i)
			    dest[needed + buflen + i] =
			      weights[idxarr[backw] + i];
			}
		      needed += buflen + len;
#అయితే_ముగింపు
		      idxarr[backw] += len;
		      val = 1;
		    }
		  లేకపోతే
		    ++val;
		}
	    }
	}

      /* Finally store the byte to separate the passes or terminate
	 the string.  */
      ఒకవేళ (needed < n)
	dest[needed] = pass + 1 < nrules ? L('\1') : L('\0');
      ++needed;
    }

  /* This is a little optimization: many collation specifications have
     a `position' rule at the end and if no non-ignored character
     is found the last \1 byte is immediately followed by a \0 byte
     signalling this.  We can avoid the \1 byte(s).  */
  ఒకవేళ (needed > 2 && needed == చివరి_needed + 1)
    {
      /* Remove the \1 byte.  */
      ఒకవేళ (--needed <= n)
	dest[needed - 1] = L('\0');
    }

  /* Return the number of bytes/words we need, but don't count the NUL
     byte/word at the end.  */
  తిరిగి needed - 1;
}

size_t
STRXFRM (STRING_TYPE *dest, స్థిరరాశి STRING_TYPE *src, size_t n, locale_t l)
{
  locale_దత్తాంశం_t l_దత్తాంశం;
  నిర్మాణం __locale_data *current = l->__locales[LC_COLLATE];
  l_దత్తాంశం.nrules = current->విలువలు[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].మాట;

  /* Handle byte comparison case.  */
  ఒకవేళ (l_దత్తాంశం.nrules == 0)
    {
      size_t srclen = STRLEN (src);

      ఒకవేళ (n != 0)
	STPNCPY (dest, src, MIN (srclen + 1, n));

      తిరిగి srclen;
    }

  /* Handle an empty string, code hereafter relies on strlen (src) > 0.  */
  ఒకవేళ (*src == L('\0'))
    {
      ఒకవేళ (n != 0)
	*dest = L('\0');
      తిరిగి 0;
    }

  /* Get the locale data.  */
  l_దత్తాంశం.rulesets = (గుర్తులేని అక్షరం *)
    current->విలువలు[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  l_దత్తాంశం.పట్టిక = (int32_t *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_పట్టిక,SUFFIX))].string;
  l_దత్తాంశం.weights = (USTRING_TYPE *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_బరువు,SUFFIX))].string;
  l_దత్తాంశం.extra = (USTRING_TYPE *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  l_దత్తాంశం.పరోక్ష = (int32_t *)
    current->విలువలు[_NL_ITEM_INDEX (CONCAT(NL_COLLATE_పరోక్ష,SUFFIX))].string;

  ప్రతిజ్ఞా (((uintptr_t) l_దత్తాంశం.పట్టిక) % __alignof__ (l_దత్తాంశం.పట్టిక[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) l_దత్తాంశం.weights) % __alignof__ (l_దత్తాంశం.weights[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) l_దత్తాంశం.extra) % __alignof__ (l_దత్తాంశం.extra[0]) == 0);
  ప్రతిజ్ఞా (((uintptr_t) l_దత్తాంశం.పరోక్ష) % __alignof__ (l_దత్తాంశం.పరోక్ష[0]) == 0);

  /* We need the elements of the string as unsigned values since they
     are used as indices.  */
  స్థిరరాశి USTRING_TYPE *usrc = (స్థిరరాశి USTRING_TYPE *) src;

  /* Allocate cache for small strings on the stack and fill it with weight and
     rule indices.  If the cache size is not sufficient, continue with the
     uncached xfrm version.  */
  size_t idxmax = 0;
  స్థిరరాశి USTRING_TYPE *cur = usrc;
  int32_t *idxarr = alloca (SMALL_STR_కొలత * పరిమాణం (int32_t));
  గుర్తులేని అక్షరం *rulearr = alloca (SMALL_STR_కొలత + 1);

  చేయి
    {
      int32_t tmp = findidx (l_దత్తాంశం.పట్టిక, l_దత్తాంశం.పరోక్ష, l_దత్తాంశం.extra, &cur,
			     -1);
      rulearr[idxmax] = tmp >> 24;
      idxarr[idxmax] = tmp & 0xffffff;

      ++idxmax;
    }
  అయితే (*cur != L('\0') && idxmax < SMALL_STR_కొలత);

  /* This element is only read, the value never used but to determine
     another value which then is ignored.  */
  rulearr[idxmax] = '\0';

  /* Do the transformation.  */
  ఒకవేళ (*cur == L('\0'))
    తిరిగి do_xfrm_cached (dest, n, &l_దత్తాంశం, idxmax, idxarr, rulearr);
  లేకపోతే
    తిరిగి do_xfrm (usrc, dest, n, &l_దత్తాంశం);
}
libc_hidden_def (STRXFRM)

#నిర్వచితం_కాకపోతే WIDE_CHAR_సంస్కరణ
weak_alias (__strxfrm_l, strxfrm_l)
#అయితే_ముగింపు
