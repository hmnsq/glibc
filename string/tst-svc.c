/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static số_nguyên
compare (const void *p1, const void *p2)
{
  trả_về strverscmp (*((char **) p1), *((char **) p2));
}

số_nguyên
do_test (void)
{
  char line[MAX_LINE_SIZE + 1];
  char *str[MAX_STRINGS];
  số_nguyên  count = 0;
  số_nguyên  i, n;

  trong_khi (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      nếu (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      nếu (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, sizeof (char *), compare);

  cho (i = 0; i < count; ++i)
    puts (str[i]);

  trả_về EXIT_SUCCESS;
}

#include <support/test-driver.c>
