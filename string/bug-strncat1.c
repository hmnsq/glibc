#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ضمن <sys/cdefs.h>
#ضمن <libc-diag.h>
#إذا __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>

حرف d[3] = "\0\1\2";

صحيح
main (فراغ)
{
  DIAG_پاڵنان_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_دەرهێنان_NEEDS_COMMENT;
  إذا (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  إذا (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  إذا (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  أرجع 0;
}
