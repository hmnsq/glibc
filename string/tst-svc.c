/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#define  MAX_STRINGS      256
#define  MAX_لي_SIZE    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف لي[MAX_لي_SIZE + 1];
  حرف *str[MAX_STRINGS];
  صحيح  كدي = 0;
  صحيح  i, n;

  طالما (كدي < MAX_STRINGS && fgets (لي, MAX_لي_SIZE, stdin) != عدم)
    {
      n = strlen (لي) - 1;

      إذا (لي[n] == '\n')
        لي[n] = '\0';

      str[كدي] = strdup (لي);

      إذا (str[كدي] == عدم)
        exit (EXIT_FAILURE);

      ++كدي;
    }

  qsort (str, كدي, حجم (حرف *), compare);

  لكل (i = 0; i < كدي; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
