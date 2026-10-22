/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_باريس_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف باريس[MAX_باريس_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  کيراءن = 0;
  صحيح  i, n;

  طالما (کيراءن < MAX_STRINGS && fgets (باريس, MAX_باريس_SIZE, stdin) != عدم)
    {
      n = strlen (باريس) - 1;

      إذا (باريس[n] == '\n')
        باريس[n] = '\0';

      str[کيراءن] = strdup (باريس);

      إذا (str[کيراءن] == عدم)
        exit (EXIT_FAILURE);

      ++کيراءن;
    }

  qsort (str, کيراءن, حجم (حرف *), compare);

  لكل (i = 0; i < کيراءن; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
