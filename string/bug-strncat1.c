#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#شامل <sys/cdefs.h>
#شامل <libc-diag.h>
#اگر __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>

نویسه d[3] = "\0\1\2";

صحیح
اصلی (تهی)
{
  DIAG_افزودن_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_برداشت_NEEDS_COMMENT;
  اگر (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  اگر (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  اگر (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  بازگشت 0;
}
