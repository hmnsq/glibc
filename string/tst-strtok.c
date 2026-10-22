/* Testcase for strtok reported by Andrew Church <achurch@achurch.org>.  */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಅಕ್ಷರ buf[1] = { 0 };
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  ಆದರೆ (strtok (buf, " ") != ಖಾಲಿ)
    {
      puts ("first strtok call did not return NULL");
      ಫಲಿತಾಂಶ = 1;
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strtok (ಖಾಲಿ, " ") != ಖಾಲಿ)
    {
      puts ("second strtok call did not return NULL");
      ಫಲಿತಾಂಶ = 1;
    }

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
