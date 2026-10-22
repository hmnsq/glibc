/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

ចំនួនគត់
do_test (void)
{
  var_na buf[1] = { 0 };
  ចំនួនគត់ result = 0;

  ប្រសិនបើ (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  បើមិនដូច្នេះ ប្រសិនបើ (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ត្រឡប់ result;
}

#include <support/test-driver.c>
