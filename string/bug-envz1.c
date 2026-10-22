/* Test for bug BZ #2703.  */
#ضمن <stdio.h>
#ضمن <envz.h>
#ضمن <stdlib.h>
#ضمن <string.h>

ساكن ثابت بنية
{
  ثابت حرف *s;
  صحيح اندريون_نتيجو;
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

#وصف_ڪريو nstrs (حجم (strs) / حجم (strs[0]))


صحيح
do_test (فراغ)
{

  size_t سائيز = 0;
  حرف *str = يادگيري_ڏيو (100);
  إذا (str == عدم)
    {
      puts ("out of memory");
      أرجع 1;
    }

  حرف **argz = &str;

  لكل (صحيح i = 0; i < nstrs; ++i)
    argz_جوڙيو_sep (argz, &سائيز, strs[i].s, '\0');

  لکو ("calling envz_strip with size=%zu\n", سائيز);
  envz_strip (argz, &سائيز);

  صحيح نتيجو = 0;
  لکو ("new size=%zu\n", سائيز);
  لكل (صحيح i = 0; i < nstrs; ++i)
    إذا (strs[i].اندريون_نتيجو)
      {
        حرف name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        حرف *e = envz_داخلا (*argz, سائيز, name);
        إذا (e == عدم)
          {
            لکو ("entry '%s' not found\n", name);
            نتيجو = 1;
          }
        وإلا إذا (strcmp (e, strs[i].s) != 0)
          {
            لکو ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            نتيجو = 1;
          }
      }

  حرر (*argz);
  أرجع نتيجو;
}

#ضمن <support/test-driver.c>
