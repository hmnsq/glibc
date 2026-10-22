/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static පූර්ණ_සංඛ්‍යා
compare (const void *p1, const void *p2)
{
  ආපසු strverscmp (*((var_na **) p1), *((var_na **) p2));
}

පූර්ණ_සංඛ්‍යා
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  පූර්ණ_සංඛ්‍යා  count = 0;
  පූර්ණ_සංඛ්‍යා  i, n;

  අතරතුර (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      නම් (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      නම් (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  සඳහා (i = 0; i < count; ++i)
    puts (str[i]);

  ආපසු EXIT_SUCCESS;
}

#include <support/test-driver.c>
