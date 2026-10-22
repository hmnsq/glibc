#undef __USE_STRING_INLINES
#define __USE_STRING_INLINES
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <libc-diag.h>

முழு
முதன்மை (வெறுமை)
{
  மாறிலி எழுத்து *a = "abc";
  மாறிலி எழுத்து *b = a;

  DIAG_தள்ளு_NEEDS_COMMENT;
  /* GCC 9 correctly warns that this call to strpbrk is useless.  That
     is deliberate; this test is verifying that a side effect in an
     argument still occurs when the call itself is useless and could
     be optimized to return a constant.  */
  DIAG_IGNORE_NEEDS_COMMENT (9, "-Wunused-value");
  strpbrk (b++, "");
  DIAG_எடு_NEEDS_COMMENT;
  எனில் (b != a + 1)
    திரும்பு 1;

  திரும்பு 0;
}
