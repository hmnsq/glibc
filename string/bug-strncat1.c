#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#અન્તર્ભાવ <sys/cdefs.h>
#અન્તર્ભાવ <libc-diag.h>
#જો __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

અક્ષર d[3] = "\0\1\2";

પૂર્ણાંક
મુખ્ય (શૂન્ય)
{
  DIAG_ધકેલો_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_કાઢો_NEEDS_COMMENT;
  જો (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  જો (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  જો (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  પાછા 0;
}
