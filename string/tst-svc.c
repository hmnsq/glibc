/* Test for strverscmp() */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#define  MAX_STRINGS      256
#define  MAX_पङ्क्तिः_SIZE    32

स्थिर पूर्णाङ्क
compare (ध्रुव शून्य *p1, ध्रुव शून्य *p2)
{
  प्रत्यागम strverscmp (*((वर्ण **) p1), *((वर्ण **) p2));
}

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण पङ्क्तिः[MAX_पङ्क्तिः_SIZE + 1];
  वर्ण *str[MAX_STRINGS];
  पूर्णाङ्क  गणनम् = 0;
  पूर्णाङ्क  i, n;

  जाव (गणनम् < MAX_STRINGS && fgets (पङ्क्तिः, MAX_पङ्क्तिः_SIZE, stdin) != रिक्त)
    {
      n = strlen (पङ्क्तिः) - 1;

      जइ (पङ्क्तिः[n] == '\n')
        पङ्क्तिः[n] = '\0';

      str[गणनम्] = strdup (पङ्क्तिः);

      जइ (str[गणनम्] == रिक्त)
        exit (EXIT_FAILURE);

      ++गणनम्;
    }

  qsort (str, गणनम्, परिमाण (वर्ण *), compare);

  प्रति (i = 0; i < गणनम्; ++i)
    puts (str[i]);

  प्रत्यागम EXIT_SUCCESS;
}

#अन्तर्भाव <support/test-driver.c>
