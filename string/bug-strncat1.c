#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#অন্তর্ভাৱ <sys/cdefs.h>
#অন্তর্ভাৱ <libc-diag.h>
#যদি __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>

ৱর্ণ d[3] = "\0\1\2";

পূর্ণাঙ্ক
main (শূন্য)
{
  DIAG_ঠেলো_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_বেৰ_কৰো_NEEDS_COMMENT;
  যদি (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  যদি (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  যদি (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  ঘূৰাই 0;
}
