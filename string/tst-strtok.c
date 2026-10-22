/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

ຈຳນວນເຕັມ
do_test (void)
{
  var_na buf[1] = { 0 };
  ຈຳນວນເຕັມ result = 0;

  ຖ້າ (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  ບໍ່ດັ່ງນັ້ນ ຖ້າ (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ສົ່ງຄືນ result;
}

#include <support/test-driver.c>
