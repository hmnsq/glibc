#अघोषित __USE_STRING_INLINES
#घोषणा __USE_STRING_INLINES
#समावेश <sys/cdefs.h>
#समावेश <libc-diag.h>
#अगर __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#पूर्ण_अगर
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>

अक्षर d[3] = "\0\1\2";

पूर्णांक
मुख्य (व्योम)
{
  DIAG_धकेलो_NEEDS_COMMENT;
  म_जोड़न (d, "\5\6", 1);
  DIAG_निकालो_NEEDS_COMMENT;
  अगर (d[0] != '\5')
    {
      माला_दो ("d[0] != '\\5'");
      निकास (1);
    }
  अगर (d[1] != '\0')
    {
      माला_दो ("d[1] != '\\0'");
      निकास (1);
    }
  अगर (d[2] != '\2')
    {
      माला_दो ("d[2] != '\\2'");
      निकास (1);
    }

  वापस 0;
}
