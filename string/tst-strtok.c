/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  حرف buf[1] = { 0 };
  صحيح پایله = 0;

  إذا (strtok (buf, " ") != عدم)
    {
      puts ("first strtok call did not return NULL");
      پایله = 1;
    }
  وإلا إذا (strtok (عدم, " ") != عدم)
    {
      puts ("second strtok call did not return NULL");
      پایله = 1;
    }

  أرجع پایله;
}

#ضمن <support/test-driver.c>
