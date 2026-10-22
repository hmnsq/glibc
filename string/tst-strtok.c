/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

ціле
do_test (void)
{
  char buf[1] = { 0 };
  ціле result = 0;

  якщо (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  інакше якщо (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  повернути result;
}

#include <support/test-driver.c>
