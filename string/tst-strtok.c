/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण buf[1] = { 0 };
  पूर्णाङ्क result = 0;

  यदि (म_मोहर (buf, " ") != रिक्त)
    {
      माला_दो ("first strtok call did not return NULL");
      result = 1;
    }
  अन्यथा यदि (म_मोहर (रिक्त, " ") != रिक्त)
    {
      माला_दो ("second strtok call did not return NULL");
      result = 1;
    }

  फर्काऊ result;
}

#अन्तर्भाव <support/test-driver.c>
