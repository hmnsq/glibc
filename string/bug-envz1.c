/* Test for bug BZ #2703.  */
#ضمن <stdio.h>
#ضمن <envz.h>
#ضمن <stdlib.h>
#ضمن <string.h>

ساكن ثابت بنية
{
  ثابت حرف *s;
  صحيح in_result;
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

#define nstrs (حجم (strs) / حجم (strs[0]))


صحيح
do_test (فراغ)
{

  size_t size = 0;
  حرف *str = malloc (100);
  אם (str == عدم)
    {
      puts ("out of memory");
      החזר 1;
    }

  حرف **argz = &str;

  עבור (صحيح i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  صحيح result = 0;
  printf ("new size=%zu\n", size);
  עבור (صحيح i = 0; i < nstrs; ++i)
    אם (strs[i].in_result)
      {
        حرف name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        حرف *e = envz_entry (*argz, size, name);
        אם (e == عدم)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        אחרת אם (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  حرر (*argz);
  החזר result;
}

#ضمن <support/test-driver.c>
