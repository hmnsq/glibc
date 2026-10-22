/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#تعریف_کن  MAX_رشتهها      256
#تعریف_کن  MAX_سطر_اندازه    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف سطر[MAX_سطر_اندازه + 1];
  حرف *str[MAX_رشتهها];
  صحيح  شمار = 0;
  صحيح  i, n;

  طالما (شمار < MAX_رشتهها && fgets (سطر, MAX_سطر_اندازه, stdin) != عدم)
    {
      n = طول_رشته (سطر) - 1;

      إذا (سطر[n] == '\n')
        سطر[n] = '\0';

      str[شمار] = strdup (سطر);

      إذا (str[شمار] == عدم)
        خروج (EXIT_FAILURE);

      ++شمار;
    }

  qsort (str, شمار, حجم (حرف *), compare);

  لكل (i = 0; i < شمار; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
