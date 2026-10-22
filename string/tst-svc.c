/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static ціле
compare (const void *p1, const void *p2)
{
  повернути strverscmp (*((char **) p1), *((char **) p2));
}

ціле
do_test (void)
{
  char line[MAX_LINE_SIZE + 1];
  char *str[MAX_STRINGS];
  ціле  count = 0;
  ціле  i, n;

  поки (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      якщо (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      якщо (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, sizeof (char *), compare);

  для (i = 0; i < count; ++i)
    puts (str[i]);

  повернути EXIT_SUCCESS;
}

#include <support/test-driver.c>
