/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णांक
do_test (शून्य)
{
  स्थिर स्थिरांक माप_प्रकार lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  अक्षर basebuf[24 + 32];
  माप_प्रकार base;

  साठी (base = 0; base < 32; ++base)
    {
      अक्षर *buf = basebuf + base;
      माप_प्रकार शब्द;

      साठी (शब्द = 0; शब्द < 4; ++शब्द)
	{
	  माप_प्रकार last;
	  स_रखो (buf, 'a', शब्द * 4);

	  साठी (last = 0; last < 16; ++last)
	    {
	      buf[शब्द * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[शब्द * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[शब्द * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[शब्द * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[शब्द * 4 + 4] = '\0';

	      जर (म_माप (buf) != शब्द * 4 + lens[last])
		{
		  म_लिखो ("\
म_माप failed साठी base=%zu, शब्द=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्द, last,
			  म_माप (buf), शब्द * 4 + lens[last]);
		  परत 1;
		}

	      जर (strnlen (buf, -1) != शब्द * 4 + lens[last])
		{
		  म_लिखो ("\
strnlen failed साठी base=%zu, शब्द=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्द, last,
			  strnlen (buf, -1), शब्द * 4 + lens[last]);
		  परत 1;
		}
	    }
	}
    }
  परत 0;
}

#अन्तर्भाव <support/test-driver.c>
