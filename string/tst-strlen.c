/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ସ୍ଥିର ଅଚଳ size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  ଅକ୍ଷର basebuf[24 + 32];
  size_t base;

  ପାଇଁ (base = 0; base < 32; ++base)
    {
      ଅକ୍ଷର *buf = basebuf + base;
      size_t ଶବ୍ଦଗୁଡ଼ିକ;

      ପାଇଁ (ଶବ୍ଦଗୁଡ଼ିକ = 0; ଶବ୍ଦଗୁଡ଼ିକ < 4; ++ଶବ୍ଦଗୁଡ଼ିକ)
	{
	  size_t last;
	  memset (buf, 'a', ଶବ୍ଦଗୁଡ଼ିକ * 4);

	  ପାଇଁ (last = 0; last < 16; ++last)
	    {
	      buf[ଶବ୍ଦଗୁଡ଼ିକ * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[ଶବ୍ଦଗୁଡ଼ିକ * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[ଶବ୍ଦଗୁଡ଼ିକ * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[ଶବ୍ଦଗୁଡ଼ିକ * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[ଶବ୍ଦଗୁଡ଼ିକ * 4 + 4] = '\0';

	      ଯଦି (strlen (buf) != ଶବ୍ଦଗୁଡ଼ିକ * 4 + lens[last])
		{
		  printf ("\
strlen failed ପାଇଁ base=%zu, ଶବ୍ଦଗୁଡ଼ିକ=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ଶବ୍ଦଗୁଡ଼ିକ, last,
			  strlen (buf), ଶବ୍ଦଗୁଡ଼ିକ * 4 + lens[last]);
		  ଫେରନ୍ତୁ 1;
		}

	      ଯଦି (strnlen (buf, -1) != ଶବ୍ଦଗୁଡ଼ିକ * 4 + lens[last])
		{
		  printf ("\
strnlen failed ପାଇଁ base=%zu, ଶବ୍ଦଗୁଡ଼ିକ=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ଶବ୍ଦଗୁଡ଼ିକ, last,
			  strnlen (buf, -1), ଶବ୍ଦଗୁଡ଼ିକ * 4 + lens[last]);
		  ଫେରନ୍ତୁ 1;
		}
	    }
	}
    }
  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
