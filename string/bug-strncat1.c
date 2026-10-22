#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#अन्तर्भाव <sys/cdefs.h>
#अन्तर्भाव <libc-diag.h>
#जर __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

अक्षर d[3] = "\0\1\2";

पूर्णांक
main (शून्य)
{
  DIAG_ढकला_NEEDS_COMMENT;
  म_जोड़न (d, "\5\6", 1);
  DIAG_काढा_NEEDS_COMMENT;
  जर (d[0] != '\5')
    {
      माला_दो ("d[0] != '\\5'");
      निकास (1);
    }
  जर (d[1] != '\0')
    {
      माला_दो ("d[1] != '\\0'");
      निकास (1);
    }
  जर (d[2] != '\2')
    {
      माला_दो ("d[2] != '\\2'");
      निकास (1);
    }

  परत 0;
}
