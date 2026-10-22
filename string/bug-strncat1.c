#నిర్వచనం_రద్దు __USE_STRING_INLINES
#నిర్వచించు __USE_STRING_INLINES
#అన్తర్భావ <sys/cdefs.h>
#అన్తర్భావ <libc-diag.h>
#ఒకవేళ __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#అయితే_ముగింపు
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

అక్షరం d[3] = "\0\1\2";

పూర్ణాంకం
ప్రధాన (శూన్య)
{
  DIAG_నెట్టు_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_తీయి_NEEDS_COMMENT;
  ఒకవేళ (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      నిష్క్రమించు (1);
    }
  ఒకవేళ (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      నిష్క్రమించు (1);
    }
  ఒకవేళ (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      నిష్క్రమించు (1);
    }

  తిరిగి 0;
}
