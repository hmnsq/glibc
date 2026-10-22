/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

целое
do_test (void)
{
  char buf[1] = { 0 };
  целое result = 0;

  если (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  иначе если (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  вернуть result;
}

#include <support/test-driver.c>
