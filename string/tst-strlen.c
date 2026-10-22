/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#تعریف_رد __USE_STRING_INLINES

#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  ساكن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t ادھار;

  لكل (ادھار = 0; ادھار < 32; ++ادھار)
    {
      حرف *buf = basebuf + ادھار;
      size_t الفاظ;

      لكل (الفاظ = 0; الفاظ < 4; ++الفاظ)
	{
	  size_t آخری;
	  memset (buf, 'a', الفاظ * 4);

	  لكل (آخری = 0; آخری < 16; ++آخری)
	    {
	      buf[الفاظ * 4 + 0] = (آخری & 1) != 0 ? 'b' : '\0';
	      buf[الفاظ * 4 + 1] = (آخری & 2) != 0 ? 'c' : '\0';
	      buf[الفاظ * 4 + 2] = (آخری & 4) != 0 ? 'd' : '\0';
	      buf[الفاظ * 4 + 3] = (آخری & 8) != 0 ? 'e' : '\0';
	      buf[الفاظ * 4 + 4] = '\0';

	      إذا (لڑی_لمبائی (buf) != الفاظ * 4 + lens[آخری])
		{
		  لکھو ("\
لڑی_لمبائی failed لكل ادھار=%zu, الفاظ=%zu, and آخری=%zu (is %zd, expected %zd)\n",
			  ادھار, الفاظ, آخری,
			  لڑی_لمبائی (buf), الفاظ * 4 + lens[آخری]);
		  أرجع 1;
		}

	      إذا (strnlen (buf, -1) != الفاظ * 4 + lens[آخری])
		{
		  لکھو ("\
strnlen failed لكل ادھار=%zu, الفاظ=%zu, and آخری=%zu (is %zd, expected %zd)\n",
			  ادھار, الفاظ, آخری,
			  strnlen (buf, -1), الفاظ * 4 + lens[آخری]);
		  أرجع 1;
		}
	    }
	}
    }
  أرجع 0;
}

#ضمن <support/test-driver.c>
