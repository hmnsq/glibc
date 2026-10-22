/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಸ್ಥಿರ ಧ್ರುವ size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  ವರ್ಣ basebuf[24 + 32];
  size_t base;

  ಪ್ರತಿ (base = 0; base < 32; ++base)
    {
      ವರ್ಣ *buf = basebuf + base;
      size_t ಪದಗಳು;

      ಪ್ರತಿ (ಪದಗಳು = 0; ಪದಗಳು < 4; ++ಪದಗಳು)
	{
	  size_t last;
	  memset (buf, 'a', ಪದಗಳು * 4);

	  ಪ್ರತಿ (last = 0; last < 16; ++last)
	    {
	      buf[ಪದಗಳು * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[ಪದಗಳು * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[ಪದಗಳು * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[ಪದಗಳು * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[ಪದಗಳು * 4 + 4] = '\0';

	      ಯದಿ (strlen (buf) != ಪದಗಳು * 4 + lens[last])
		{
		  printf ("\
strlen failed ಪ್ರತಿ base=%zu, ಪದಗಳು=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ಪದಗಳು, last,
			  strlen (buf), ಪದಗಳು * 4 + lens[last]);
		  ಪ್ರತ್ಯಾಗಮ 1;
		}

	      ಯದಿ (strnlen (buf, -1) != ಪದಗಳು * 4 + lens[last])
		{
		  printf ("\
strnlen failed ಪ್ರತಿ base=%zu, ಪದಗಳು=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, ಪದಗಳು, last,
			  strnlen (buf, -1), ಪದಗಳು * 4 + lens[last]);
		  ಪ್ರತ್ಯಾಗಮ 1;
		}
	    }
	}
    }
  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
