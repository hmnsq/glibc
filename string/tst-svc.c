/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static целое
compare (const void *p1, const void *p2)
{
  вернуть strverscmp (*((char **) p1), *((char **) p2));
}

целое
do_test (void)
{
  char line[MAX_LINE_SIZE + 1];
  char *str[MAX_STRINGS];
  целое  count = 0;
  целое  i, n;

  пока (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      если (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      если (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, sizeof (char *), compare);

  для (i = 0; i < count; ++i)
    puts (str[i]);

  вернуть EXIT_SUCCESS;
}

#include <support/test-driver.c>
