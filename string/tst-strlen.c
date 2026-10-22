/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

முழு
do_test (வெறுமை)
{
  நிலையான மாறிலி size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  எழுத்து basebuf[24 + 32];
  size_t base;

  க்கு (base = 0; base < 32; ++base)
    {
      எழுத்து *buf = basebuf + base;
      size_t சொற்கள்;

      க்கு (சொற்கள் = 0; சொற்கள் < 4; ++சொற்கள்)
	{
	  size_t last;
	  memset (buf, 'a', சொற்கள் * 4);

	  க்கு (last = 0; last < 16; ++last)
	    {
	      buf[சொற்கள் * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[சொற்கள் * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[சொற்கள் * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[சொற்கள் * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[சொற்கள் * 4 + 4] = '\0';

	      எனில் (strlen (buf) != சொற்கள் * 4 + lens[last])
		{
		  printf ("\
strlen failed க்கு base=%zu, சொற்கள்=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, சொற்கள், last,
			  strlen (buf), சொற்கள் * 4 + lens[last]);
		  திரும்பு 1;
		}

	      எனில் (strnlen (buf, -1) != சொற்கள் * 4 + lens[last])
		{
		  printf ("\
strnlen failed க்கு base=%zu, சொற்கள்=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, சொற்கள், last,
			  strnlen (buf, -1), சொற்கள் * 4 + lens[last]);
		  திரும்பு 1;
		}
	    }
	}
    }
  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>
