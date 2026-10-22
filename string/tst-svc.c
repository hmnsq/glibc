/* Test for strverscmp() */

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>

#تعریف_کرو  MAX_لڑیاں      256
#تعریف_کرو  MAX_سطر_ناپ    32

ساكن صحيح
compare (ثابت فراغ *p1, ثابت فراغ *p2)
{
  أرجع strverscmp (*((حرف **) p1), *((حرف **) p2));
}

صحيح
do_test (فراغ)
{
  حرف سطر[MAX_سطر_ناپ + 1];
  حرف *str[MAX_لڑیاں];
  صحيح  گنتی = 0;
  صحيح  i, n;

  طالما (گنتی < MAX_لڑیاں && fgets (سطر, MAX_سطر_ناپ, stdin) != عدم)
    {
      n = لڑی_لمبائی (سطر) - 1;

      إذا (سطر[n] == '\n')
        سطر[n] = '\0';

      str[گنتی] = strdup (سطر);

      إذا (str[گنتی] == عدم)
        باہر_نکلو (EXIT_FAILURE);

      ++گنتی;
    }

  qsort (str, گنتی, حجم (حرف *), compare);

  لكل (i = 0; i < گنتی; ++i)
    puts (str[i]);

  أرجع EXIT_SUCCESS;
}

#ضمن <support/test-driver.c>
