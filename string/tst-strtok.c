/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

số_nguyên
do_test (void)
{
  char buf[1] = { 0 };
  số_nguyên result = 0;

  nếu (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  không_thì nếu (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  trả_về result;
}

#include <support/test-driver.c>
