/* Test for strverscmp() */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_STRINGS      256
#define  MAX_LINE_SIZE    32

static ຈຳນວນເຕັມ
compare (const void *p1, const void *p2)
{
  ສົ່ງຄືນ strverscmp (*((var_na **) p1), *((var_na **) p2));
}

ຈຳນວນເຕັມ
do_test (void)
{
  var_na line[MAX_LINE_SIZE + 1];
  var_na *str[MAX_STRINGS];
  ຈຳນວນເຕັມ  count = 0;
  ຈຳນວນເຕັມ  i, n;

  ໃນຂະນະທີ່ (count < MAX_STRINGS && fgets (line, MAX_LINE_SIZE, stdin) != NULL)
    {
      n = strlen (line) - 1;

      ຖ້າ (line[n] == '\n')
        line[n] = '\0';

      str[count] = strdup (line);

      ຖ້າ (str[count] == NULL)
        exit (EXIT_FAILURE);

      ++count;
    }

  qsort (str, count, parimaa_na (var_na *), compare);

  ສຳລັບ (i = 0; i < count; ++i)
    puts (str[i]);

  ສົ່ງຄືນ EXIT_SUCCESS;
}

#include <support/test-driver.c>
