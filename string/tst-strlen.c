/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  സ്ഥിതം സ്ഥിരം size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  അക്ഷരം basebuf[24 + 32];
  size_t base;

  വേണ്ടി (base = 0; base < 32; ++base)
    {
      അക്ഷരം *buf = basebuf + base;
      size_t വാക്കുകൾ;

      വേണ്ടി (വാക്കുകൾ = 0; വാക്കുകൾ < 4; ++വാക്കുകൾ)
	{
	  size_t last;
	  memset (buf, 'a', വാക്കുകൾ * 4);

	  വേണ്ടി (last = 0; last < 16; ++last)
	    {
	      buf[വാക്കുകൾ * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[വാക്കുകൾ * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[വാക്കുകൾ * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[വാക്കുകൾ * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[വാക്കുകൾ * 4 + 4] = '\0';

	      എങ്കിൽ (strlen (buf) != വാക്കുകൾ * 4 + lens[last])
		{
		  printf ("\
strlen failed വേണ്ടി base=%zu, വാക്കുകൾ=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, വാക്കുകൾ, last,
			  strlen (buf), വാക്കുകൾ * 4 + lens[last]);
		  തിരികെ 1;
		}

	      എങ്കിൽ (strnlen (buf, -1) != വാക്കുകൾ * 4 + lens[last])
		{
		  printf ("\
strnlen failed വേണ്ടി base=%zu, വാക്കുകൾ=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, വാക്കുകൾ, last,
			  strnlen (buf, -1), വാക്കുകൾ * 4 + lens[last]);
		  തിരികെ 1;
		}
	    }
	}
    }
  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
