/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#include <stdio.h>
#include <string.h>

int
do_test (void)
{
  static const size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  char basebuf[24 + 32];
  size_t base;

  for (base = 0; base < 32; ++base)
    {
      char *buf = basebuf + base;
      size_t मगा_सालिता;

      for (मगा_सालिता = 0; मगा_सालिता < 4; ++मगा_सालिता)
	{
	  size_t last;
	  memset (buf, 'a', मगा_सालिता * 4);

	  for (last = 0; last < 16; ++last)
	    {
	      buf[मगा_सालिता * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[मगा_सालिता * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[मगा_सालिता * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[मगा_सालिता * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[मगा_सालिता * 4 + 4] = '\0';

	      if (strlen (buf) != मगा_सालिता * 4 + lens[last])
		{
		  printf ("\
strlen failed for base=%zu, मगा_सालिता=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, मगा_सालिता, last,
			  strlen (buf), मगा_सालिता * 4 + lens[last]);
		  return 1;
		}

	      if (strnlen (buf, -1) != मगा_सालिता * 4 + lens[last])
		{
		  printf ("\
strnlen failed for base=%zu, मगा_सालिता=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, मगा_सालिता, last,
			  strnlen (buf, -1), मगा_सालिता * 4 + lens[last]);
		  return 1;
		}
	    }
	}
    }
  return 0;
}

#include <support/test-driver.c>
