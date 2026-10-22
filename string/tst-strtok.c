/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

পূর্ণসংখ্যা
do_test (শূন্য)
{
  অক্ষর buf[1] = { 0 };
  পূর্ণসংখ্যা ফলাফল = 0;

  যদি (strtok (buf, " ") != ফাঁকা)
    {
      puts ("first strtok call did not return NULL");
      ফলাফল = 1;
    }
  অন্যথা যদি (strtok (ফাঁকা, " ") != ফাঁকা)
    {
      puts ("second strtok call did not return NULL");
      ফলাফল = 1;
    }

  ফেরত ফলাফল;
}

#অন্তর্ভাব <support/test-driver.c>
