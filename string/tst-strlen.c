/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

পূর্ণসংখ্যা
do_test (শূন্য)
{
  স্থির ধ্রুবক size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  অক্ষর basebuf[24 + 32];
  size_t base;

  জন্য (base = 0; base < 32; ++base)
    {
      অক্ষর *buf = basebuf + base;
      size_t শব্দগুলি;

      জন্য (শব্দগুলি = 0; শব্দগুলি < 4; ++শব্দগুলি)
	{
	  size_t last;
	  memset (buf, 'a', শব্দগুলি * 4);

	  জন্য (last = 0; last < 16; ++last)
	    {
	      buf[শব্দগুলি * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[শব্দগুলি * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[শব্দগুলি * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[শব্দগুলি * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[শব্দগুলি * 4 + 4] = '\0';

	      যদি (strlen (buf) != শব্দগুলি * 4 + lens[last])
		{
		  printf ("\
strlen failed জন্য base=%zu, শব্দগুলি=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, শব্দগুলি, last,
			  strlen (buf), শব্দগুলি * 4 + lens[last]);
		  ফেরত 1;
		}

	      যদি (strnlen (buf, -1) != শব্দগুলি * 4 + lens[last])
		{
		  printf ("\
strnlen failed জন্য base=%zu, শব্দগুলি=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, শব্দগুলি, last,
			  strnlen (buf, -1), শব্দগুলি * 4 + lens[last]);
		  ফেরত 1;
		}
	    }
	}
    }
  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>
