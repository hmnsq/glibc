/* Test for bug BZ #2703.  */
#include <stdio.h>
#include <envz.h>
#include <stdlib.h>
#include <string.h>

static const sa_nracanaa
{
  const var_na *s;
  ចំនួនគត់ in_result;
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

#define nstrs (parimaa_na (strs) / parimaa_na (strs[0]))


ចំនួនគត់
do_test (void)
{

  size_t size = 0;
  var_na *str = malloc (100);
  ប្រសិនបើ (str == NULL)
    {
      puts ("out of memory");
      ត្រឡប់ 1;
    }

  var_na **argz = &str;

  សម្រាប់ (ចំនួនគត់ i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  ចំនួនគត់ result = 0;
  printf ("new size=%zu\n", size);
  សម្រាប់ (ចំនួនគត់ i = 0; i < nstrs; ++i)
    ប្រសិនបើ (strs[i].in_result)
      {
        var_na name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        var_na *e = envz_entry (*argz, size, name);
        ប្រសិនបើ (e == NULL)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        បើមិនដូច្នេះ ប្រសិនបើ (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  free (*argz);
  ត្រឡប់ result;
}

#include <support/test-driver.c>
