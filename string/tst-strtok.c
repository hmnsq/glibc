/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>

পূর্ণাঙ্ক
do_test (শূন্য)
{
  ৱর্ণ buf[1] = { 0 };
  পূর্ণাঙ্ক result = 0;

  যদি (strtok (buf, " ") != রিক্ত)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  অন্যথা যদি (strtok (রিক্ত, " ") != রিক্ত)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ঘূৰাই result;
}

#অন্তর্ভাৱ <support/test-driver.c>
