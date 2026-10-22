/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  स्थिर ध्रुव size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  वर्ण basebuf[24 + 32];
  size_t base;

  प्रति (base = 0; base < 32; ++base)
    {
      वर्ण *buf = basebuf + base;
      size_t शब्दाः;

      प्रति (शब्दाः = 0; शब्दाः < 4; ++शब्दाः)
	{
	  size_t last;
	  memset (buf, 'a', शब्दाः * 4);

	  प्रति (last = 0; last < 16; ++last)
	    {
	      buf[शब्दाः * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[शब्दाः * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[शब्दाः * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[शब्दाः * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[शब्दाः * 4 + 4] = '\0';

	      जइ (strlen (buf) != शब्दाः * 4 + lens[last])
		{
		  printf ("\
strlen failed प्रति base=%zu, शब्दाः=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दाः, last,
			  strlen (buf), शब्दाः * 4 + lens[last]);
		  प्रत्यागम 1;
		}

	      जइ (strnlen (buf, -1) != शब्दाः * 4 + lens[last])
		{
		  printf ("\
strnlen failed प्रति base=%zu, शब्दाः=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दाः, last,
			  strnlen (buf, -1), शब्दाः * 4 + lens[last]);
		  प्रत्यागम 1;
		}
	    }
	}
    }
  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
