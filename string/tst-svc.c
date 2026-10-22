/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static ចំនួនគត់
compare (const void *p1, const void *p2)
{
  ត្រឡប់ strverscmp (*((var_na **) p1), *((var_na **) p2));
}

ចំនួនគត់
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  ចំនួនគត់  count = 0;
  ចំនួនគត់  i, n;

  ខណៈពេល (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      ប្រសិនបើ (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      ប្រសិនបើ (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  សម្រាប់ (i = 0; i < count; ++i)
    puts (str[i]);

  ត្រឡប់ EXIT_SUCCESS;
}

#include <support/test-driver.c>
