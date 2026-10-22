/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#تعریف_لغوه __USE_STRING_INLINES

#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t بنسټ;

  لكل (بنسټ = 0; بنسټ < 32; ++بنسټ)
    {
      حرف *buf = basebuf + بنسټ;
      size_t ټکي;

      لكل (ټکي = 0; ټکي < 4; ++ټکي)
	{
	  size_t وروستی;
	  memset (buf, 'a', ټکي * 4);

	  لكل (وروستی = 0; وروستی < 16; ++وروستی)
	    {
	      buf[ټکي * 4 + 0] = (وروستی & 1) != 0 ? 'b' : '\0';
	      buf[ټکي * 4 + 1] = (وروستی & 2) != 0 ? 'c' : '\0';
	      buf[ټکي * 4 + 2] = (وروستی & 4) != 0 ? 'd' : '\0';
	      buf[ټکي * 4 + 3] = (وروستی & 8) != 0 ? 'e' : '\0';
	      buf[ټکي * 4 + 4] = '\0';

	      إذا (مزي_اوږدوالی (buf) != ټکي * 4 + lens[وروستی])
		{
		  چاپ_کړه ("\
مزي_اوږدوالی failed لكل بنسټ=%zu, ټکي=%zu, and وروستی=%zu (is %zd, expected %zd)\n",
			  بنسټ, ټکي, وروستی,
			  مزي_اوږدوالی (buf), ټکي * 4 + lens[وروستی]);
		  أرجع 1;
		}

	      إذا (strnlen (buf, -1) != ټکي * 4 + lens[وروستی])
		{
		  چاپ_کړه ("\
strnlen failed لكل بنسټ=%zu, ټکي=%zu, and وروستی=%zu (is %zd, expected %zd)\n",
			  بنسټ, ټکي, وروستی,
			  strnlen (buf, -1), ټکي * 4 + lens[وروستی]);
		  أرجع 1;
		}
	    }
	}
    }
  أرجع 0;
}

#ضمن <support/test-driver.c>
