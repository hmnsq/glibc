/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#include <stdio.h>
#include <string.h>

puur_naa_nka
do_test (void)
{
  var_na buf[1] = { 0 };
  puur_naa_nka result = 0;

  ᨀᨘ (strtok (buf, " ") != NULL)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  ᨀᨘᨁ ᨀᨘ (strtok (NULL, " ") != NULL)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ᨀᨘᨒ result;
}

#include <support/test-driver.c>
