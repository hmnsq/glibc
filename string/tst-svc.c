/* Test for strverscmp() */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#define  MAX_STRINGS      256
#define  MAX_पंक्ति_SIZE    32

स्थिर पूर्णाङ्क
compare (ध्रुव शून्य *p1, ध्रुव शून्य *p2)
{
  प्रत्यागम strverscmp (*((वर्ण **) p1), *((वर्ण **) p2));
}

पूर्णाङ्क
do_test (शून्य)
{
  वर्ण पंक्ति[MAX_पंक्ति_SIZE + 1];
  वर्ण *str[MAX_STRINGS];
  पूर्णाङ्क  गिनती = 0;
  पूर्णाङ्क  i, n;

  यावत् (गिनती < MAX_STRINGS && fgets (पंक्ति, MAX_पंक्ति_SIZE, stdin) != रिक्त)
    {
      n = strlen (पंक्ति) - 1;

      यदि (पंक्ति[n] == '\n')
        पंक्ति[n] = '\0';

      str[गिनती] = strdup (पंक्ति);

      यदि (str[गिनती] == रिक्त)
        exit (EXIT_FAILURE);

      ++गिनती;
    }

  qsort (str, गिनती, परिमाण (वर्ण *), compare);

  प्रति (i = 0; i < गिनती; ++i)
    puts (str[i]);

  प्रत्यागम EXIT_SUCCESS;
}

#अन्तर्भाव <support/test-driver.c>
