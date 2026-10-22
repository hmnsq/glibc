#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#अन्तर्भाव <string.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <libc-diag.h>

पूर्णाङ्क
main (शून्य)
{
  ध्रुव वर्ण *a = "abc";
  ध्रुव वर्ण *b = a;

  DIAG_प्रक्षिप_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_निष्कासय_NEEDS_COMMENT;
  जइ (b != a + 1)
    प्रत्यागम 1;

  प्रत्यागम 0;
}
