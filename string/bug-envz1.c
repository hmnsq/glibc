/* Test for bug BZ #2703.  */
#include <stdio.h>
#include <envz.h>
#include <stdlib.h>
#include <string.h>

static const struct
{
  const char *s;
  整数 in_result;
} strs[] =
{
  { "a=1", 1 },
  { "b=2", 1 },
  { "(*)", 0 },
  { "(*)", 0 },
  { "e=5", 1 },
  { "f=", 1 },
  { "(*)", 0 },
  { "h=8", 1 },
  { "i=9", 1 },
  { "j", 0 }
};

#define nstrs (sizeof (strs) / sizeof (strs[0]))


整数
do_test (void)
{

  size_t size = 0;
  char *str = malloc (100);
  もし (str == NULL)
    {
      puts ("out of memory");
      戻る 1;
    }

  char **argz = &str;

  ために (整数 i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  整数 result = 0;
  printf ("new size=%zu\n", size);
  ために (整数 i = 0; i < nstrs; ++i)
    もし (strs[i].in_result)
      {
        char name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        char *e = envz_entry (*argz, size, name);
        もし (e == NULL)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        否则 もし (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  free (*argz);
  戻る result;
}

#include <support/test-driver.c>
