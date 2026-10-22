/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __USE_STRING_INLINES

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  ಅಕ್ಷರ basebuf[24 + 32];
  size_t ತಳ;

  ಗಾಗಿ (ತಳ = 0; ತಳ < 32; ++ತಳ)
    {
      ಅಕ್ಷರ *buf = basebuf + ತಳ;
      size_t ಪದಗಳು;

      ಗಾಗಿ (ಪದಗಳು = 0; ಪದಗಳು < 4; ++ಪದಗಳು)
	{
	  size_t ಕೊನೆಯ;
	  memset (buf, 'a', ಪದಗಳು * 4);

	  ಗಾಗಿ (ಕೊನೆಯ = 0; ಕೊನೆಯ < 16; ++ಕೊನೆಯ)
	    {
	      buf[ಪದಗಳು * 4 + 0] = (ಕೊನೆಯ & 1) != 0 ? 'b' : '\0';
	      buf[ಪದಗಳು * 4 + 1] = (ಕೊನೆಯ & 2) != 0 ? 'c' : '\0';
	      buf[ಪದಗಳು * 4 + 2] = (ಕೊನೆಯ & 4) != 0 ? 'd' : '\0';
	      buf[ಪದಗಳು * 4 + 3] = (ಕೊನೆಯ & 8) != 0 ? 'e' : '\0';
	      buf[ಪದಗಳು * 4 + 4] = '\0';

	      ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf) != ಪದಗಳು * 4 + lens[ಕೊನೆಯ])
		{
		  ಬರೆ ("\
ಅಕ್ಷರಸರಣಿ_ಉದ್ದ failed ಗಾಗಿ ತಳ=%zu, ಪದಗಳು=%zu, and ಕೊನೆಯ=%zu (is %zd, expected %zd)\n",
			  ತಳ, ಪದಗಳು, ಕೊನೆಯ,
			  ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (buf), ಪದಗಳು * 4 + lens[ಕೊನೆಯ]);
		  ಹಿಂತಿರುಗಿ 1;
		}

	      ಆದರೆ (strnlen (buf, -1) != ಪದಗಳು * 4 + lens[ಕೊನೆಯ])
		{
		  ಬರೆ ("\
strnlen failed ಗಾಗಿ ತಳ=%zu, ಪದಗಳು=%zu, and ಕೊನೆಯ=%zu (is %zd, expected %zd)\n",
			  ತಳ, ಪದಗಳು, ಕೊನೆಯ,
			  strnlen (buf, -1), ಪದಗಳು * 4 + lens[ಕೊನೆಯ]);
		  ಹಿಂತಿರುಗಿ 1;
		}
	    }
	}
    }
  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
