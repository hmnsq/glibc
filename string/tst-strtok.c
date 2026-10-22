/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

ཧྲིལ
do_test (void)
{
  var_na buf[1] = { 0 };
  ཧྲིལ result = 0;

  གལ་ཏེ (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  དེ་མིན གལ་ཏེ (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ཕྱིར result;
}

#include <support/test-driver.c>
