/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static 整数
compare (const void *p1, const void *p2)
{
  戻る strverscmp (*((char **) p1), *((char **) p2));
}

整数
do_test (void)
{
  char line[MAX_LINE_SIZE + 1];
  char *str[MAX_STRINGS];
  整数  count = 0;
  整数  i, n;

  ながら (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      もし (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      もし (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, sizeof (char *), compare);

  ために (i = 0; i < count; ++i)
    puts (str[i]);

  戻る EXIT_SUCCESS;
}

#include <support/test-driver.c>
