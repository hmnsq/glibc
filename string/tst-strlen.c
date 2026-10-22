/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

পূর্ণাঙ্ক
do_test (শূন্য)
{
  স্থির ধ্রুব size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  বর্ণ basebuf[24 + 32];
  size_t base;

  প্রতি (base = 0; base < 32; ++base)
    {
      বর্ণ *buf = basebuf + base;
      size_t শব্দগুলি;

      প্রতি (শব্দগুলি = 0; শব্দগুলি < 4; ++শব্দগুলি)
	{
	  size_t last;
	  memset (buf, 'a', শব্দগুলি * 4);

	  প্রতি (last = 0; last < 16; ++last)
	    {
	      buf[শব্দগুলি * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[শব্দগুলি * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[শব্দগুলি * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[শব্দগুলি * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[শব্দগুলি * 4 + 4] = '\0';

	      যদি (strlen (buf) != শব্দগুলি * 4 + lens[last])
		{
		  printf ("\
strlen failed প্রতি base=%zu, শব্দগুলি=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, শব্দগুলি, last,
			  strlen (buf), শব্দগুলি * 4 + lens[last]);
		  প্রত্যাগম 1;
		}

	      যদি (strnlen (buf, -1) != শব্দগুলি * 4 + lens[last])
		{
		  printf ("\
strnlen failed প্রতি base=%zu, শব্দগুলি=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, শব্দগুলি, last,
			  strnlen (buf, -1), শব্দগুলি * 4 + lens[last]);
		  প্রত্যাগম 1;
		}
	    }
	}
    }
  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>
