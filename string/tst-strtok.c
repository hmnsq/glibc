/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

จำนวนเต็ม
do_test (void)
{
  var_na buf[1] = { 0 };
  จำนวนเต็ม result = 0;

  ถ้า (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  มิฉะนั้น ถ้า (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  คืน result;
}

#include <support/test-driver.c>
