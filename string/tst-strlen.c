/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#شامل <stdio.h>
#شامل <string.h>

صحیح
do_test (تهی)
{
  ایستا ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  نویسه basebuf[24 + 32];
  size_t base;

  برای (base = 0; base < 32; ++base)
    {
      نویسه *buf = basebuf + base;
      size_t واژگان;

      برای (واژگان = 0; واژگان < 4; ++واژگان)
	{
	  size_t last;
	  memset (buf, 'a', واژگان * 4);

	  برای (last = 0; last < 16; ++last)
	    {
	      buf[واژگان * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[واژگان * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[واژگان * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[واژگان * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[واژگان * 4 + 4] = '\0';

	      اگر (strlen (buf) != واژگان * 4 + lens[last])
		{
		  printf ("\
strlen failed برای base=%zu, واژگان=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, واژگان, last,
			  strlen (buf), واژگان * 4 + lens[last]);
		  بازگشت 1;
		}

	      اگر (strnlen (buf, -1) != واژگان * 4 + lens[last])
		{
		  printf ("\
strnlen failed برای base=%zu, واژگان=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, واژگان, last,
			  strnlen (buf, -1), واژگان * 4 + lens[last]);
		  بازگشت 1;
		}
	    }
	}
    }
  بازگشت 0;
}

#شامل <support/test-driver.c>
