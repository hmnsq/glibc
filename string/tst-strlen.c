/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ __USE_STRING_INLINES

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਸਥਿਰ ਅਚਲ size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  ਅੱਖਰ basebuf[24 + 32];
  size_t ਅਧਾਰ;

  ਲਈ (ਅਧਾਰ = 0; ਅਧਾਰ < 32; ++ਅਧਾਰ)
    {
      ਅੱਖਰ *buf = basebuf + ਅਧਾਰ;
      size_t ਸ਼ਬਦ_2;

      ਲਈ (ਸ਼ਬਦ_2 = 0; ਸ਼ਬਦ_2 < 4; ++ਸ਼ਬਦ_2)
	{
	  size_t ਆਖਰੀ;
	  memset (buf, 'a', ਸ਼ਬਦ_2 * 4);

	  ਲਈ (ਆਖਰੀ = 0; ਆਖਰੀ < 16; ++ਆਖਰੀ)
	    {
	      buf[ਸ਼ਬਦ_2 * 4 + 0] = (ਆਖਰੀ & 1) != 0 ? 'b' : '\0';
	      buf[ਸ਼ਬਦ_2 * 4 + 1] = (ਆਖਰੀ & 2) != 0 ? 'c' : '\0';
	      buf[ਸ਼ਬਦ_2 * 4 + 2] = (ਆਖਰੀ & 4) != 0 ? 'd' : '\0';
	      buf[ਸ਼ਬਦ_2 * 4 + 3] = (ਆਖਰੀ & 8) != 0 ? 'e' : '\0';
	      buf[ਸ਼ਬਦ_2 * 4 + 4] = '\0';

	      ਜੇ (ਲੜੀ_ਲੰਬਾਈ (buf) != ਸ਼ਬਦ_2 * 4 + lens[ਆਖਰੀ])
		{
		  ਲਿਖੋ ("\
ਲੜੀ_ਲੰਬਾਈ failed ਲਈ ਅਧਾਰ=%zu, ਸ਼ਬਦ_2=%zu, and ਆਖਰੀ=%zu (is %zd, expected %zd)\n",
			  ਅਧਾਰ, ਸ਼ਬਦ_2, ਆਖਰੀ,
			  ਲੜੀ_ਲੰਬਾਈ (buf), ਸ਼ਬਦ_2 * 4 + lens[ਆਖਰੀ]);
		  ਵਾਪਸ 1;
		}

	      ਜੇ (strnlen (buf, -1) != ਸ਼ਬਦ_2 * 4 + lens[ਆਖਰੀ])
		{
		  ਲਿਖੋ ("\
strnlen failed ਲਈ ਅਧਾਰ=%zu, ਸ਼ਬਦ_2=%zu, and ਆਖਰੀ=%zu (is %zd, expected %zd)\n",
			  ਅਧਾਰ, ਸ਼ਬਦ_2, ਆਖਰੀ,
			  strnlen (buf, -1), ਸ਼ਬਦ_2 * 4 + lens[ਆਖਰੀ]);
		  ਵਾਪਸ 1;
		}
	    }
	}
    }
  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
