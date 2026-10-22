/* Test for bug BZ #2703.  */
#समावेश <stdio.h>
#समावेश <envz.h>
#समावेश <stdlib.h>
#समावेश <string.h>

अटल स्थिर काष्ठा
{
  स्थिर अक्षर *s;
  पूर्णांक in_परिणाम;
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

#घोषणा nstrs (माप (strs) / माप (strs[0]))


पूर्णांक
do_test (व्योम)
{

  माप_प्रकार आकार = 0;
  अक्षर *str = दो_स्मृति (100);
  अगर (str == शून्य)
    {
      माला_दो ("out of memory");
      वापस 1;
    }

  अक्षर **argz = &str;

  क्रम (पूर्णांक i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &आकार, strs[i].s, '\0');

  म_लिखो ("calling envz_strip with size=%zu\n", आकार);
  envz_strip (argz, &आकार);

  पूर्णांक परिणाम = 0;
  म_लिखो ("new size=%zu\n", आकार);
  क्रम (पूर्णांक i = 0; i < nstrs; ++i)
    अगर (strs[i].in_परिणाम)
      {
        अक्षर name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        अक्षर *e = envz_entry (*argz, आकार, name);
        अगर (e == शून्य)
          {
            म_लिखो ("entry '%s' not found\n", name);
            परिणाम = 1;
          }
        अन्यथा अगर (म_भेद (e, strs[i].s) != 0)
          {
            म_लिखो ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            परिणाम = 1;
          }
      }

  मुक्त (*argz);
  वापस परिणाम;
}

#समावेश <support/test-driver.c>
