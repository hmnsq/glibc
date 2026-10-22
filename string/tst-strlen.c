/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#وصف_رد __USE_STRING_INLINES

#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t بنياد;

  لكل (بنياد = 0; بنياد < 32; ++بنياد)
    {
      حرف *buf = basebuf + بنياد;
      size_t لفظ_2;

      لكل (لفظ_2 = 0; لفظ_2 < 4; ++لفظ_2)
	{
	  size_t آخري;
	  memset (buf, 'a', لفظ_2 * 4);

	  لكل (آخري = 0; آخري < 16; ++آخري)
	    {
	      buf[لفظ_2 * 4 + 0] = (آخري & 1) != 0 ? 'b' : '\0';
	      buf[لفظ_2 * 4 + 1] = (آخري & 2) != 0 ? 'c' : '\0';
	      buf[لفظ_2 * 4 + 2] = (آخري & 4) != 0 ? 'd' : '\0';
	      buf[لفظ_2 * 4 + 3] = (آخري & 8) != 0 ? 'e' : '\0';
	      buf[لفظ_2 * 4 + 4] = '\0';

	      إذا (لڙي_ڊيگهه (buf) != لفظ_2 * 4 + lens[آخري])
		{
		  لکو ("\
لڙي_ڊيگهه failed لكل بنياد=%zu, لفظ_2=%zu, and آخري=%zu (is %zd, expected %zd)\n",
			  بنياد, لفظ_2, آخري,
			  لڙي_ڊيگهه (buf), لفظ_2 * 4 + lens[آخري]);
		  أرجع 1;
		}

	      إذا (strnlen (buf, -1) != لفظ_2 * 4 + lens[آخري])
		{
		  لکو ("\
strnlen failed لكل بنياد=%zu, لفظ_2=%zu, and آخري=%zu (is %zd, expected %zd)\n",
			  بنياد, لفظ_2, آخري,
			  strnlen (buf, -1), لفظ_2 * 4 + lens[آخري]);
		  أرجع 1;
		}
	    }
	}
    }
  أرجع 0;
}

#ضمن <support/test-driver.c>
