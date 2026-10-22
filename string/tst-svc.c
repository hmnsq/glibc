/* Test for strverscmp() */

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#define  MAX_STRINGS      256
#define  MAX_ಸಾಲು_SIZE    32

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
compare (ಧ್ರುವ ಶೂನ್ಯ *p1, ಧ್ರುವ ಶೂನ್ಯ *p2)
{
  ಪ್ರತ್ಯಾಗಮ strverscmp (*((ವರ್ಣ **) p1), *((ವರ್ಣ **) p2));
}

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ವರ್ಣ ಸಾಲು[MAX_ಸಾಲು_SIZE + 1];
  ವರ್ಣ *str[MAX_STRINGS];
  ಪೂರ್ಣಾಙ್ಕ  ಎಣಿಕೆ = 0;
  ಪೂರ್ಣಾಙ್ಕ  i, n;

  ಯಾವತ್ (ಎಣಿಕೆ < MAX_STRINGS && fgets (ಸಾಲು, MAX_ಸಾಲು_SIZE, stdin) != ರಿಕ್ತ)
    {
      n = strlen (ಸಾಲು) - 1;

      ಯದಿ (ಸಾಲು[n] == '\n')
        ಸಾಲು[n] = '\0';

      str[ಎಣಿಕೆ] = strdup (ಸಾಲು);

      ಯದಿ (str[ಎಣಿಕೆ] == ರಿಕ್ತ)
        exit (EXIT_FAILURE);

      ++ಎಣಿಕೆ;
    }

  qsort (str, ಎಣಿಕೆ, ಪರಿಮಾಣ (ವರ್ಣ *), compare);

  ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ; ++i)
    puts (str[i]);

  ಪ್ರತ್ಯಾಗಮ EXIT_SUCCESS;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
