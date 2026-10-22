#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#ଅନ୍ତର୍ଭାଵ <sys/cdefs.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>
#ଯଦି __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ଅକ୍ଷର d[3] = "\0\1\2";

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
ମୁଖ୍ୟ (ଶୂନ୍ୟ)
{
  DIAG_ଠେଲ_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_କାଢ଼_NEEDS_COMMENT;
  ଯଦି (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  ଯଦି (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  ଯଦି (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  ଫେରନ୍ତୁ 0;
}
