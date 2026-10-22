/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण buf[1] = { 0 };
  पूर्णाङ्क परिणाम = 0;

  यदि (strtok (buf, " ") != रिक्त)
    {
      पङ्क्तिं_लिख ("first strtok call did not return NULL");
      परिणाम = 1;
    }
  अन्यथा यदि (strtok (रिक्त, " ") != रिक्त)
    {
      पङ्क्तिं_लिख ("second strtok call did not return NULL");
      परिणाम = 1;
    }

  प्रत्यागम परिणाम;
}

#अन्तर्भाव <support/test-driver.c>
