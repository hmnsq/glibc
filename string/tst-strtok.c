/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णांक
do_test (शून्य)
{
  अक्षर buf[1] = { 0 };
  पूर्णांक result = 0;

  जर (म_मोहर (buf, " ") != रिक्त)
    {
      माला_दो ("first strtok call did not return NULL");
      result = 1;
    }
  अन्यथा जर (म_मोहर (रिक्त, " ") != रिक्त)
    {
      माला_दो ("second strtok call did not return NULL");
      result = 1;
    }

  परत result;
}

#अन्तर्भाव <support/test-driver.c>
