/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static puur_naa_nka
compare (const void *p1, const void *p2)
{
  ပွၵ်ႈ strverscmp (*((var_na **) p1), *((var_na **) p2));
}

puur_naa_nka
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  puur_naa_nka  count = 0;
  puur_naa_nka  i, n;

  ၶၢဝ်း (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      ပေႃး (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      ပေႃး (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  for (i = 0; i < count; ++i)
    puts (str[i]);

  ပွၵ်ႈ EXIT_SUCCESS;
}

#include <support/test-driver.c>
