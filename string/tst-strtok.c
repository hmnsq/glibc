/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

పూర్ణాంకం
do_test (శూన్య)
{
  అక్షరం buf[1] = { 0 };
  పూర్ణాంకం ఫలితం = 0;

  ఒకవేళ (strtok (buf, " ") != ఖాళీ)
    {
      puts ("first strtok call did not return NULL");
      ఫలితం = 1;
    }
  లేకపోతే ఒకవేళ (strtok (ఖాళీ, " ") != ఖాళీ)
    {
      puts ("second strtok call did not return NULL");
      ఫలితం = 1;
    }

  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
