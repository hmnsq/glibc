/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

정수
do_test (void)
{
  char buf[1] = { 0 };
  정수 result = 0;

  만약 (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  아니면 만약 (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  반환 result;
}

#include <support/test-driver.c>
