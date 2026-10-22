#अपरिभाषय __USE_STRING_INLINES
#परिभाषय __USE_STRING_INLINES
#अन्तर्भाव <sys/cdefs.h>
#अन्तर्भाव <libc-diag.h>
#यदि __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#यदि_अन्तः
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

वर्ण d[3] = "\0\1\2";

पूर्णाङ्क
मुख्यम् (शून्य)
{
  DIAG_प्रक्षिप_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_निष्कासय_NEEDS_COMMENT;
  यदि (d[0] != '\5')
    {
      पङ्क्तिं_लिख ("d[0] != '\\5'");
      निर्गच्छ (1);
    }
  यदि (d[1] != '\0')
    {
      पङ्क्तिं_लिख ("d[1] != '\\0'");
      निर्गच्छ (1);
    }
  यदि (d[2] != '\2')
    {
      पङ्क्तिं_लिख ("d[2] != '\\2'");
      निर्गच्छ (1);
    }

  प्रत्यागम 0;
}
