#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <sys/cdefs.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>
#ಯದಿ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ವರ್ಣ d[3] = "\0\1\2";

ಪೂರ್ಣಾಙ್ಕ
main (ಶೂನ್ಯ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  ಯದಿ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  ಯದಿ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  ಯದಿ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  ಪ್ರತ್ಯಾಗಮ 0;
}
