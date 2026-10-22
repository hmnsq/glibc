/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static 정수
compare (const void *p1, const void *p2)
{
  반환 strverscmp (*((char **) p1), *((char **) p2));
}

정수
do_test (void)
{
  char line[MAX_LINE_SIZE + 1];
  char *str[MAX_STRINGS];
  정수  count = 0;
  정수  i, n;

  동안 (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      만약 (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      만약 (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, sizeof (char *), compare);

  위해 (i = 0; i < count; ++i)
    puts (str[i]);

  반환 EXIT_SUCCESS;
}

#include <support/test-driver.c>
