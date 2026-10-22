#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#அந்தர்பாவ <sys/cdefs.h>
#அந்தர்பாவ <libc-diag.h>
#எனில் __GNUC_PREREQ (8, 0)
/* GCC warns about strncat truncating output; this is deliberately
   tested here.  If fortify is enabled, it is also triggered by the
   wrappers. */
DIAG_IGNORE_NEEDS_COMMENT (8, "-Wstringop-truncation");
#endif
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

எழுத்து d[3] = "\0\1\2";

முழு
முதன்மை (வெறுமை)
{
  DIAG_தள்ளு_NEEDS_COMMENT;
  strncat (d, "\5\6", 1);
  DIAG_எடு_NEEDS_COMMENT;
  எனில் (d[0] != '\5')
    {
      puts ("d[0] != '\\5'");
      exit (1);
    }
  எனில் (d[1] != '\0')
    {
      puts ("d[1] != '\\0'");
      exit (1);
    }
  எனில் (d[2] != '\2')
    {
      puts ("d[2] != '\\2'");
      exit (1);
    }

  திரும்பு 0;
}
