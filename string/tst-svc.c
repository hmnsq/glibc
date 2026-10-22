/* Test for strverscmp() */

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <string.h>

#تعریف_کرو  MAX_لڑیاں      256
#تعریف_کرو  MAX_سطر_سائز    32

ساکن صحیح
compare (ثابت خالی *p1, ثابت خالی *p2)
{
  واپس strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحیح
do_test (خالی)
{
  حرف سطر[MAX_سطر_سائز + 1];
  حرف *str[MAX_لڑیاں];
  صحیح  گنتی = 0;
  صحیح  i, n;

  جب (گنتی < MAX_لڑیاں && fgets (سطر, MAX_سطر_سائز, stdin) != تہی)
    {
      n = لڑی_لمبائی (سطر) - 1;

      اگر (سطر[n] == '\n')
        سطر[n] = '\0';

      str[گنتی] = strdup (سطر);

      اگر (str[گنتی] == تہی)
        باہر_نکلو (EXIT_FAILURE);

      ++گنتی;
    }

  qsort (str, گنتی, حجم (حرف *), compare);

  برائے (i = 0; i < گنتی; ++i)
    puts (str[i]);

  واپس EXIT_SUCCESS;
}

#شامل <support/test-driver.c>
