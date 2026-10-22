/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static ཧྲིལ
compare (const void *p1, const void *p2)
{
  ལོག strverscmp (*((var_na **) p1), *((var_na **) p2));
}

ཧྲིལ
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  ཧྲིལ  count = 0;
  ཧྲིལ  i, n;

  སྐབས (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      གལ་སྲིད (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      གལ་སྲིད (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  དོན་ལུ (i = 0; i < count; ++i)
    puts (str[i]);

  ལོག EXIT_SUCCESS;
}

#include <support/test-driver.c>
