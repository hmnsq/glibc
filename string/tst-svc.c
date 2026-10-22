/* Test for strverscmp() */

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <string.h>

#define  MAX_STRINGS      256
#define  MAX_سطر_SIZE    32

ایستا صحیح
compare (ثابت تهی *p1, ثابت تهی *p2)
{
  بازگشت strverscmp (*((نویسه **) p1), *((نویسه **) p2));
}

صحیح
do_test (تهی)
{
  نویسه سطر[MAX_سطر_SIZE + 1];
  نویسه *str[MAX_STRINGS];
  صحیح  شمار = 0;
  صحیح  i, n;

  وقتی (شمار < MAX_STRINGS && fgets (سطر, MAX_سطر_SIZE, stdin) != پوچ)
    {
      n = strlen (سطر) - 1;

      اگر (سطر[n] == '\n')
        سطر[n] = '\0';

      str[شمار] = strdup (سطر);

      اگر (str[شمار] == پوچ)
        exit (EXIT_FAILURE);

      ++شمار;
    }

  qsort (str, شمار, اندازه (نویسه *), compare);

  برای (i = 0; i < شمار; ++i)
    puts (str[i]);

  بازگشت EXIT_SUCCESS;
}

#شامل <support/test-driver.c>
