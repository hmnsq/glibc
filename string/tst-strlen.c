/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t base;

  لكل (base = 0; base < 32; ++base)
    {
      حرف *buf = basebuf + base;
      size_t ڤرکاتاءن;

      لكل (ڤرکاتاءن = 0; ڤرکاتاءن < 4; ++ڤرکاتاءن)
	{
	  size_t last;
	  memset (buf, 'a', ڤرکاتاءن * 4);

	  لكل (last = 0; last < 16; ++last)
	    {
	      buf[ڤرکاتاءن * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[ڤرکاتاءن * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[ڤرکاتاءن * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[ڤرکاتاءن * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[ڤرکاتاءن * 4 + 4] = '\0';

	      إذا (strlen (buf) != ڤرکاتاءن * 4 + lens[last])
		{
		  printf ("\
strlen failed لكل base=%zu, ڤرکاتاءن=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ڤرکاتاءن, last,
			  strlen (buf), ڤرکاتاءن * 4 + lens[last]);
		  أرجع 1;
		}

	      إذا (strnlen (buf, -1) != ڤرکاتاءن * 4 + lens[last])
		{
		  printf ("\
strnlen failed لكل base=%zu, ڤرکاتاءن=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ڤرکاتاءن, last,
			  strnlen (buf, -1), ڤرکاتاءن * 4 + lens[last]);
		  أرجع 1;
		}
	    }
	}
    }
  أرجع 0;
}

#ضمن <support/test-driver.c>
