/* Test for bug BZ #2703.  */
#ضمن <stdio.h>
#ضمن <envz.h>
#ضمن <stdlib.h>
#ضمن <string.h>

ساكن ثابت بنية
{
  ثابت حرف *s;
  صحيح وچ_نتیجہ;
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

#تعریف_کرو nstrs (حجم (strs) / حجم (strs[0]))


صحيح
do_test (فراغ)
{

  size_t ناپ = 0;
  حرف *str = حافظہ_دیو (100);
  إذا (str == عدم)
    {
      puts ("out of memory");
      أرجع 1;
    }

  حرف **argz = &str;

  لكل (صحيح i = 0; i < nstrs; ++i)
    argz_جوڑو_sep (argz, &ناپ, strs[i].s, '\0');

  لکھو ("calling envz_strip with size=%zu\n", ناپ);
  envz_strip (argz, &ناپ);

  صحيح نتیجہ = 0;
  لکھو ("new size=%zu\n", ناپ);
  لكل (صحيح i = 0; i < nstrs; ++i)
    إذا (strs[i].وچ_نتیجہ)
      {
        حرف name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        حرف *e = envz_اندراج (*argz, ناپ, name);
        إذا (e == عدم)
          {
            لکھو ("entry '%s' not found\n", name);
            نتیجہ = 1;
          }
        وإلا إذا (strcmp (e, strs[i].s) != 0)
          {
            لکھو ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            نتیجہ = 1;
          }
      }

  حرر (*argz);
  أرجع نتیجہ;
}

#ضمن <support/test-driver.c>
