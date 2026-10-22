#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#अन्तर्भाव <sys/cdefs.h>
#अन्तर्भाव <libc-diag.h>
#जइ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

वर्ण d[3] = "\0\1\2";

पूर्णाङ्क
main (शून्य)
{
  DIAG_प्रक्षिप_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_निष्कासय_NEEDS_COMMENT;
  जइ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  जइ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  जइ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  प्रत्यागम 0;
}
