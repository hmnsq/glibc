/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ವರ್ಣ buf[1] = { 0 };
  ಪೂರ್ಣಾಙ್ಕ result = 0;

  ಯದಿ (strtok (buf, " ") != ರಿಕ್ತ)
    {
      puts ("first strtok call did not return NULL");
      result = 1;
    }
  ಅನ್ಯಥಾ ಯದಿ (strtok (ರಿಕ್ತ, " ") != ರಿಕ್ತ)
    {
      puts ("second strtok call did not return NULL");
      result = 1;
    }

  ಪ್ರತ್ಯಾಗಮ result;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
