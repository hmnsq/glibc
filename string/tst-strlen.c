/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#تعریف_منسوخ __USE_STRING_INLINES

#شامل <stdio.h>
#شامل <string.h>

صحیح
do_test (خالی)
{
  ساکن ثابت size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  حرف basebuf[24 + 32];
  size_t بنیاد;

  برائے (بنیاد = 0; بنیاد < 32; ++بنیاد)
    {
      حرف *buf = basebuf + بنیاد;
      size_t الفاظ;

      برائے (الفاظ = 0; الفاظ < 4; ++الفاظ)
	{
	  size_t آخری;
	  memset (buf, 'a', الفاظ * 4);

	  برائے (آخری = 0; آخری < 16; ++آخری)
	    {
	      buf[الفاظ * 4 + 0] = (آخری & 1) != 0 ? 'b' : '\0';
	      buf[الفاظ * 4 + 1] = (آخری & 2) != 0 ? 'c' : '\0';
	      buf[الفاظ * 4 + 2] = (آخری & 4) != 0 ? 'd' : '\0';
	      buf[الفاظ * 4 + 3] = (آخری & 8) != 0 ? 'e' : '\0';
	      buf[الفاظ * 4 + 4] = '\0';

	      اگر (لڑی_لمبائی (buf) != الفاظ * 4 + lens[آخری])
		{
		  لکھو ("\
لڑی_لمبائی failed برائے بنیاد=%zu, الفاظ=%zu, and آخری=%zu (is %zd, expected %zd)\n",
			  بنیاد, الفاظ, آخری,
			  لڑی_لمبائی (buf), الفاظ * 4 + lens[آخری]);
		  واپس 1;
		}

	      اگر (strnlen (buf, -1) != الفاظ * 4 + lens[آخری])
		{
		  لکھو ("\
strnlen failed برائے بنیاد=%zu, الفاظ=%zu, and آخری=%zu (is %zd, expected %zd)\n",
			  بنیاد, الفاظ, آخری,
			  strnlen (buf, -1), الفاظ * 4 + lens[آخری]);
		  واپس 1;
		}
	    }
	}
    }
  واپس 0;
}

#شامل <support/test-driver.c>
