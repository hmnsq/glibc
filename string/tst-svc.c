/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_سطر_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف سطر[MAX_سطر_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  عدد = 0;
  صحيح  i, n;

  طالما (عدد < MAX_STRINGS && fgets (سطر, MAX_سطر_SIZE, stdin) != عدم)
    {
      n = strlen (سطر) - 1;

      إذا (سطر[n] == '\n')
        سطر[n] = '\0';

      str[عدد] = strdup (سطر);

      إذا (str[عدد] == عدم)
        exit (EXIT_FAILURE);

      ++عدد;
    }

  qsort (str, عدد, حجم (حرف *), compare);

  لكل (i = 0; i < عدد; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
