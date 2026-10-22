/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#شامل <stdio.h>
#شامل <string.h>

صحیح
do_test (خالی)
{
  حرف buf[1] = { 0 };
  صحیح نتیجہ = 0;

  اگر (strtok (buf, " ") != تہی)
    {
      puts ("first strtok call did not return NULL");
      نتیجہ = 1;
    }
  ورنہ اگر (strtok (تہی, " ") != تہی)
    {
      puts ("second strtok call did not return NULL");
      نتیجہ = 1;
    }

  واپس نتیجہ;
}

#شامل <support/test-driver.c>
