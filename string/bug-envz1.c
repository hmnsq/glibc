/* Test for bug BZ #2703.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <envz.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

स्थिर ध्रुव संरचना
{
  ध्रुव वर्ण *s;
  पूर्णाङ्क in_result;
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

#define nstrs (परिमाण (strs) / परिमाण (strs[0]))


पूर्णाङ्क
do_test (शून्य)
{

  माप_प्रकार size = 0;
  वर्ण *str = दो_स्मृति (100);
  यदि (str == रिक्त)
    {
      माला_दो ("out of memory");
      प्रत्यागम 1;
    }

  वर्ण **argz = &str;

  प्रति (पूर्णाङ्क i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  म_लिखो ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  पूर्णाङ्क result = 0;
  म_लिखो ("new size=%zu\n", size);
  प्रति (पूर्णाङ्क i = 0; i < nstrs; ++i)
    यदि (strs[i].in_result)
      {
        वर्ण name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        वर्ण *e = envz_entry (*argz, size, name);
        यदि (e == रिक्त)
          {
            म_लिखो ("entry '%s' not found\n", name);
            result = 1;
          }
        अन्यथा यदि (म_भेद (e, strs[i].s) != 0)
          {
            म_लिखो ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  मुक्त (*argz);
  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
