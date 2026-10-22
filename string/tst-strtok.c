/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ଅକ୍ଷର buf[1] = { 0 };
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;

  ଯଦି (strtok (buf, " ") != ଖାଲି)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  ଅନ୍ୟଥା ଯଦି (strtok (ଖାଲି, " ") != ଖାଲି)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ଫେରନ୍ତୁ result;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
