/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  स्थिर ध्रुव माप_प्रकार lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  वर्ण basebuf[24 + 32];
  माप_प्रकार base;

  प्रति (base = 0; base < 32; ++base)
    {
      वर्ण *buf = basebuf + base;
      माप_प्रकार शब्दगण;

      प्रति (शब्दगण = 0; शब्दगण < 4; ++शब्दगण)
	{
	  माप_प्रकार last;
	  स_रखो (buf, 'a', शब्दगण * 4);

	  प्रति (last = 0; last < 16; ++last)
	    {
	      buf[शब्दगण * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[शब्दगण * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[शब्दगण * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[शब्दगण * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[शब्दगण * 4 + 4] = '\0';

	      यदि (म_माप (buf) != शब्दगण * 4 + lens[last])
		{
		  म_लिखो ("\
म_माप failed प्रति base=%zu, शब्दगण=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दगण, last,
			  म_माप (buf), शब्दगण * 4 + lens[last]);
		  प्रत्यागम 1;
		}

	      यदि (strnlen (buf, -1) != शब्दगण * 4 + lens[last])
		{
		  म_लिखो ("\
strnlen failed प्रति base=%zu, शब्दगण=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दगण, last,
			  strnlen (buf, -1), शब्दगण * 4 + lens[last]);
		  प्रत्यागम 1;
		}
	    }
	}
    }
  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>
