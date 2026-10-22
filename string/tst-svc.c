/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static จำนวนเต็ม
compare (const void *p1, const void *p2)
{
  คืน strverscmp (*((var_na **) p1), *((var_na **) p2));
}

จำนวนเต็ม
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  จำนวนเต็ม  count = 0;
  จำนวนเต็ม  i, n;

  ขณะ (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      ถ้า (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      ถ้า (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  สำหรับ (i = 0; i < count; ++i)
    puts (str[i]);

  คืน EXIT_SUCCESS;
}

#include <support/test-driver.c>
