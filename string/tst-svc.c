/* Test for strverscmp() */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#define  MAX_STRINGS      256
#define  MAX_ओळ_SIZE    32

स्थिर पूर्णाङ्क
compare (ध्रुव शून्य *p1, ध्रुव शून्य *p2)
{
  प्रत्यागम strverscmp (*((वर्ण **) p1), *((वर्ण **) p2));
}

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण ओळ[MAX_ओळ_SIZE + 1];
  वर्ण *str[MAX_STRINGS];
  पूर्णाङ्क  मोजणी = 0;
  पूर्णाङ्क  i, n;

  यावत् (मोजणी < MAX_STRINGS && fgets (ओळ, MAX_ओळ_SIZE, stdin) != रिक्त)
    {
      n = strlen (ओळ) - 1;

      यदि (ओळ[n] == '\n')
        ओळ[n] = '\0';

      str[मोजणी] = strdup (ओळ);

      यदि (str[मोजणी] == रिक्त)
        exit (EXIT_FAILURE);

      ++मोजणी;
    }

  qsort (str, मोजणी, परिमाण (वर्ण *), compare);

  प्रति (i = 0; i < मोजणी; ++i)
    puts (str[i]);

  प्रत्यागम EXIT_SUCCESS;
}

#अन्तर्भाव <support/test-driver.c>
