/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

පූර්ණ_සංඛ්‍යා
do_test (void)
{
  var_na buf[1] = { 0 };
  පූර්ණ_සංඛ්‍යා result = 0;

  නම් (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  නැතහොත් නම් (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ආපසු result;
}

#include <support/test-driver.c>
