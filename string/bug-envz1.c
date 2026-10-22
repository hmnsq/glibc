/* Test for bug BZ #2703.  */
#ضمن <stdio.h>
#ضمن <envz.h>
#ضمن <stdlib.h>
#ضمن <string.h>

ساكن ثابت بنية
{
  ثابت حرف *s;
  صحيح دننه_پایله;
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

#تعریف_کړه nstrs (حجم (strs) / حجم (strs[0]))


صحيح
do_test (فراغ)
{

  size_t اندازه = 0;
  حرف *str = حافظه_ورکړه (100);
  إذا (str == عدم)
    {
      puts ("out of memory");
      أرجع 1;
    }

  حرف **argz = &str;

  لكل (صحيح i = 0; i < nstrs; ++i)
    argz_جمع_کړه_sep (argz, &اندازه, strs[i].s, '\0');

  چاپ_کړه ("calling envz_strip with size=%zu\n", اندازه);
  envz_strip (argz, &اندازه);

  صحيح پایله = 0;
  چاپ_کړه ("new size=%zu\n", اندازه);
  لكل (صحيح i = 0; i < nstrs; ++i)
    إذا (strs[i].دننه_پایله)
      {
        حرف name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        حرف *e = envz_ثبت (*argz, اندازه, name);
        إذا (e == عدم)
          {
            چاپ_کړه ("entry '%s' not found\n", name);
            پایله = 1;
          }
        وإلا إذا (strcmp (e, strs[i].s) != 0)
          {
            چاپ_کړه ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            پایله = 1;
          }
      }

  حرر (*argz);
  أرجع پایله;
}

#ضمن <support/test-driver.c>
