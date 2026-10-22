/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#अघोषित __USE_STRING_INLINES

#समावेश <stdio.h>
#समावेश <string.h>

पूर्णांक
do_test (व्योम)
{
  अटल स्थिर माप_प्रकार lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  अक्षर basebuf[24 + 32];
  माप_प्रकार base;

  क्रम (base = 0; base < 32; ++base)
    {
      अक्षर *buf = basebuf + base;
      माप_प्रकार शब्दगण;

      क्रम (शब्दगण = 0; शब्दगण < 4; ++शब्दगण)
	{
	  माप_प्रकार last;
	  स_रखो (buf, 'a', शब्दगण * 4);

	  क्रम (last = 0; last < 16; ++last)
	    {
	      buf[शब्दगण * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[शब्दगण * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[शब्दगण * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[शब्दगण * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[शब्दगण * 4 + 4] = '\0';

	      अगर (म_माप (buf) != शब्दगण * 4 + lens[last])
		{
		  म_लिखो ("\
म_माप failed क्रम base=%zu, शब्दगण=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दगण, last,
			  म_माप (buf), शब्दगण * 4 + lens[last]);
		  वापस 1;
		}

	      अगर (strnlen (buf, -1) != शब्दगण * 4 + lens[last])
		{
		  म_लिखो ("\
strnlen failed क्रम base=%zu, शब्दगण=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, शब्दगण, last,
			  strnlen (buf, -1), शब्दगण * 4 + lens[last]);
		  वापस 1;
		}
	    }
	}
    }
  वापस 0;
}

#समावेश <support/test-driver.c>
