/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static ကိန်းပြည့်
compare (const void *p1, const void *p2)
{
  ပြန်ပေး strverscmp (*((var_na **) p1), *((var_na **) p2));
}

ကိန်းပြည့်
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  ကိန်းပြည့်  count = 0;
  ကိန်းပြည့်  i, n;

  နေစဉ် (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      အကယ်၍ (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      အကယ်၍ (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  အတွက် (i = 0; i < count; ++i)
    puts (str[i]);

  ပြန်ပေး EXIT_SUCCESS;
}

#include <support/test-driver.c>
