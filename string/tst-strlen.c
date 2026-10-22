/* Make sure we don't test the optimized inline functions if we want to
   test the real implementation.  */
#undef __USE_STRING_INLINES

#include <stdio.h>
#include <string.h>

පූර්ණ_සංඛ්‍යා
do_test (void)
{
  static const size_t lens[] = { 0, 1, 0, 2, 0, 1, 0, 3,
				 0, 1, 0, 2, 0, 1, 0, 4 };
  var_na basebuf[24 + 32];
  size_t base;

  සඳහා (base = 0; base < 32; ++base)
    {
      var_na *buf = basebuf + base;
      size_t words;

      සඳහා (words = 0; words < 4; ++words)
	{
	  size_t last;
	  memset (buf, 'a', words * 4);

	  සඳහා (last = 0; last < 16; ++last)
	    {
	      buf[words * 4 + 0] = (last & 1) != 0 ? 'b' : '\0';
	      buf[words * 4 + 1] = (last & 2) != 0 ? 'c' : '\0';
	      buf[words * 4 + 2] = (last & 4) != 0 ? 'd' : '\0';
	      buf[words * 4 + 3] = (last & 8) != 0 ? 'e' : '\0';
	      buf[words * 4 + 4] = '\0';

	      නම් (strlen (buf) != words * 4 + lens[last])
		{
		  printf ("\
strlen failed සඳහා base=%zu, words=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, words, last,
			  strlen (buf), words * 4 + lens[last]);
		  ආපසු 1;
		}

	      නම් (strnlen (buf, -1) != words * 4 + lens[last])
		{
		  printf ("\
strnlen failed සඳහා base=%zu, words=%zu, and last=%zu (is %zd, expected %zd)\n",
			  base, words, last,
			  strnlen (buf, -1), words * 4 + lens[last]);
		  ආපසු 1;
		}
	    }
	}
    }
  ආපසු 0;
}

#include <support/test-driver.c>
