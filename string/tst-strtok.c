/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#समावेश <stdio.h>
#समावेश <string.h>

पूर्णांक
do_test (व्योम)
{
  अक्षर buf[1] = { 0 };
  पूर्णांक परिणाम = 0;

  अगर (म_मोहर (buf, " ") != शून्य)
    {
      माला_दो ("first strtok call did not return NULL");
      परिणाम = 1;
    }
  अन्यथा अगर (म_मोहर (शून्य, " ") != शून्य)
    {
      माला_दो ("second strtok call did not return NULL");
      परिणाम = 1;
    }

  वापस परिणाम;
}

#समावेश <support/test-driver.c>
