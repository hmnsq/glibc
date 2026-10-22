/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#لغو_تعریف __USE_STRING_INLINES

#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t پایه;

  لكل (پایه = 0; پایه < 32; ++پایه)
    {
      حرف *buf = basebuf + پایه;
      size_t واژگان;

      لكل (واژگان = 0; واژگان < 4; ++واژگان)
	{
	  size_t آخرین;
	  memset (buf, 'a', واژگان * 4);

	  لكل (آخرین = 0; آخرین < 16; ++آخرین)
	    {
	      buf[واژگان * 4 + 0] = (آخرین & 1) != 0 ? 'b' : '\0';
	      buf[واژگان * 4 + 1] = (آخرین & 2) != 0 ? 'c' : '\0';
	      buf[واژگان * 4 + 2] = (آخرین & 4) != 0 ? 'd' : '\0';
	      buf[واژگان * 4 + 3] = (آخرین & 8) != 0 ? 'e' : '\0';
	      buf[واژگان * 4 + 4] = '\0';

	      إذا (طول_رشته (buf) != واژگان * 4 + lens[آخرین])
		{
		  چاپ_کن ("\
طول_رشته failed لكل پایه=%zu, واژگان=%zu, and آخرین=%zu (is %zd, expected %zd)\n",
			  پایه, واژگان, آخرین,
			  طول_رشته (buf), واژگان * 4 + lens[آخرین]);
		  أرجع 1;
		}

	      إذا (strnlen (buf, -1) != واژگان * 4 + lens[آخرین])
		{
		  چاپ_کن ("\
strnlen failed لكل پایه=%zu, واژگان=%zu, and آخرین=%zu (is %zd, expected %zd)\n",
			  پایه, واژگان, آخرین,
			  strnlen (buf, -1), واژگان * 4 + lens[آخرین]);
		  أرجع 1;
		}
	    }
	}
    }
  أرجع 0;
}

#ضمن <support/test-driver.c>
