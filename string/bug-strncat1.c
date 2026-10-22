#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#include <sys/cdefs.h>
#include <libc-diag.h>
#если __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char d[3] = "\0\1\2";

целое
основной (void)
{
  DIAG_PUSH_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_POP_NEEDS_COMMENT;
  если (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  если (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  если (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  вернуть 0;
}
