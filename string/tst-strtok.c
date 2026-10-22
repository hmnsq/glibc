/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

ကိန်းပြည့်
do_test (void)
{
  var_na buf[1] = { 0 };
  ကိန်းပြည့် result = 0;

  အကယ်၍ (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  မဟုတ်ပါက အကယ်၍ (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ပြန်ပေး result;
}

#include <support/test-driver.c>
