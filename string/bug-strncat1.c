#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು __USE_STRING_INLINES
#ವ್ಯಾಖ್ಯಾನಿಸು __USE_STRING_INLINES
#ಅನ್ತರ್ಭಾವ <sys/cdefs.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>
#ಆದರೆ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಅಕ್ಷರ d[3] = "\0\1\2";

ಪೂರ್ಣಾಂಕ
ಮುಖ್ಯ (ಶೂನ್ಯ)
{
  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_ತೆಗೆ_NEEDS_COMMENT;
  ಆದರೆ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      ನಿರ್ಗಮಿಸು (1);
    }
  ಆದರೆ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      ನಿರ್ಗಮಿಸು (1);
    }
  ಆದರೆ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      ನಿರ್ಗಮಿಸು (1);
    }

  ಹಿಂತಿರುಗಿ 0;
}
