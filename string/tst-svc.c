/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_سطر_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  إرجاع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف سطر[MAX_سطر_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  تعداد_2 = 0;
  صحيح  i, n;

  بينما (تعداد_2 < MAX_STRINGS && fgets (سطر, MAX_سطر_SIZE, stdin) != عدم)
    {
      n = strlen (سطر) - 1;

      إذا (سطر[n] == '\n')
        سطر[n] = '\0';

      str[تعداد_2] = strdup (سطر);

      إذا (str[تعداد_2] == عدم)
        exit (EXIT_FAILURE);

      ++تعداد_2;
    }

  qsort (str, تعداد_2, حجم (حرف *), compare);

  لكل (i = 0; i < تعداد_2; ++i)
    puts (str[i]);

  إرجاع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
