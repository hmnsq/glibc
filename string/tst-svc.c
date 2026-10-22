/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_قۇر_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف قۇر[MAX_قۇر_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  سانى = 0;
  صحيح  i, n;

  طالما (سانى < MAX_STRINGS && fgets (قۇر, MAX_قۇر_SIZE, stdin) != عدم)
    {
      n = strlen (قۇر) - 1;

      إذا (قۇر[n] == '\n')
        قۇر[n] = '\0';

      str[سانى] = strdup (قۇر);

      إذا (str[سانى] == عدم)
        exit (EXIT_FAILURE);

      ++سانى;
    }

  qsort (str, سانى, حجم (حرف *), compare);

  لكل (i = 0; i < سانى; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
