/* Test for bug BZ #2703.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <envz.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

स्थिर स्थिरांक संरचना
{
  स्थिरांक अक्षर *s;
  पूर्णांक in_result;
} strs[] =
{
  { "a=1", 1 },
  { "b=2", 1 },
  { "(*)", 0 },
  { "(*)", 0 },
  { "e=5", 1 },
  { "f=", 1 },
  { "(*)", 0 },
  { "h=8", 1 },
  { "i=9", 1 },
  { "j", 0 }
};

#define nstrs (आकार (strs) / आकार (strs[0]))


पूर्णांक
do_test (शून्य)
{

  माप_प्रकार size = 0;
  अक्षर *str = दो_स्मृति (100);
  जर (str == रिक्त)
    {
      माला_दो ("out of memory");
      परत 1;
    }

  अक्षर **argz = &str;

  साठी (पूर्णांक i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  म_लिखो ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  पूर्णांक result = 0;
  म_लिखो ("new size=%zu\n", size);
  साठी (पूर्णांक i = 0; i < nstrs; ++i)
    जर (strs[i].in_result)
      {
        अक्षर name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        अक्षर *e = envz_entry (*argz, size, name);
        जर (e == रिक्त)
          {
            म_लिखो ("entry '%s' not found\n", name);
            result = 1;
          }
        अन्यथा जर (म_भेद (e, strs[i].s) != 0)
          {
            म_लिखो ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  मुक्त (*argz);
  परत result;
}

#अन्तर्भाव <support/test-driver.c>
