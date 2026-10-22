#నిర్వచనం_రద్దు __USE_STRING_INLINES
#నిర్వచించు __USE_STRING_INLINES
#అన్తర్భావ <string.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <libc-diag.h>

పూర్ణాంకం
ప్రధాన (శూన్య)
{
  స్థిరరాశి అక్షరం *a = "abc";
  స్థిరరాశి అక్షరం *b = a;

  DIAG_నెట్టు_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_తీయి_NEEDS_COMMENT;
  ఒకవేళ (b != a + 1)
    తిరిగి 1;

  తిరిగి 0;
}
