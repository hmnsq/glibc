/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ضمن <stdio.h>
#ضمن <string.h>

صحيح
do_test (فراغ)
{
  حرف buf[1] = { 0 };
  صحيح result = 0;

  𐤀𐤌 (strtok (buf, " ") != عدم)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  وإلا 𐤀𐤌 (strtok (عدم, " ") != عدم)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  أرجع result;
}

#ضمن <support/test-driver.c>
