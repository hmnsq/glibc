/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

整数
do_test (void)
{
  char buf[1] = { 0 };
  整数 result = 0;

  如果 (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  否则 如果 (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  返回 result;
}

#include <support/test-driver.c>
