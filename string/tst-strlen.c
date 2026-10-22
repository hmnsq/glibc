/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

પૂર્ણાંક
do_test (શૂન્ય)
{
  સ્થિર અચલ size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  અક્ષર basebuf[24 + 32];
  size_t base;

  માટે (base = 0; base < 32; ++base)
    {
      અક્ષર *buf = basebuf + base;
      size_t શબ્દો;

      માટે (શબ્દો = 0; શબ્દો < 4; ++શબ્દો)
	{
	  size_t last;
	  memset (buf, 'a', શબ્દો * 4);

	  માટે (last = 0; last < 16; ++last)
	    {
	      buf[શબ્દો * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[શબ્દો * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[શબ્દો * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[શબ્દો * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[શબ્દો * 4 + 4] = '\0';

	      જો (strlen (buf) != શબ્દો * 4 + lens[last])
		{
		  printf ("\
strlen failed માટે base=%zu, શબ્દો=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, શબ્દો, last,
			  strlen (buf), શબ્દો * 4 + lens[last]);
		  પાછા 1;
		}

	      જો (strnlen (buf, -1) != શબ્દો * 4 + lens[last])
		{
		  printf ("\
strnlen failed માટે base=%zu, શબ્દો=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, શબ્દો, last,
			  strnlen (buf, -1), શબ્દો * 4 + lens[last]);
		  પાછા 1;
		}
	    }
	}
    }
  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>
