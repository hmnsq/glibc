/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#شامل <stdio.h>
#شامل <string.h>

صحیح
do_test (تهی)
{
  نویسه buf[1] = { 0 };
  صحیح result = 0;

  اگر (strtok (buf, " ") != پوچ)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  وگرنه اگر (strtok (پوچ, " ") != پوچ)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  بازگشت result;
}

#شامل <support/test-driver.c>
