/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण buf[1] = { 0 };
  पूर्णाङ्क result = 0;

  जइ (strtok (buf, " ") != रिक्त)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  अण्णहा जइ (strtok (रिक्त, " ") != रिक्त)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  प्रत्यागम result;
}

#अन्तर्भाव <support/test-driver.c>
