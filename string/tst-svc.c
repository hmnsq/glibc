/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_लिन्या_SIZE    32

static int
compare (const void *p1, const void *p2)
{
  return strverscmp (*((char **) p1), *((char **) p2));
}

int
do_test (void)
{
  char लिन्या[MAX_लिन्या_SIZE + 1];
  char *str[MAX_STRINGS];
  int  बिलांग = 0;
  int  i, n;

  while (बिलांग < MAX_STRINGS && fgets (लिन्या, MAX_लिन्या_SIZE, stdin) != NULL)
    {
      n = strlen (लिन्या) - 1;

      if (लिन्या[n] == '\n')
        लिन्या[n] = '\0';

      str[बिलांग] = strdup (लिन्या);

      if (str[बिलांग] == NULL)
        exit (EXIT_FAILURE);

      ++बिलांग;
    }

  qsort (str, बिलांग, sizeof (char *), compare);

  for (i = 0; i < बिलांग; ++i)
    puts (str[i]);

  return EXIT_SUCCESS;
}

#include <support/test-driver.c>
