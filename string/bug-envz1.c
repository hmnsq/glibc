/* Test for bug BZ #2703.  */
#شامل <stdio.h>
#شامل <envz.h>
#شامل <stdlib.h>
#شامل <string.h>

ساکن ثابت ساخت
{
  ثابت حرف *s;
  صحیح اندر_نتیجہ;
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


صحیح
do_test (خالی)
{

  size_t سائز = 0;
  حرف *str = حافظہ_دو (100);
  اگر (str == تہی)
    {
      puts ("out of memory");
      واپس 1;
    }

  حرف **argz = &str;

  برائے (صحیح i = 0; i < nstrs; ++i)
    argz_جوڑو_sep (argz, &سائز, strs[i].s, '\0');

  لکھو ("calling envz_strip with size=%zu\n", سائز);
  envz_strip (argz, &سائز);

  صحیح نتیجہ = 0;
  لکھو ("new size=%zu\n", سائز);
  برائے (صحیح i = 0; i < nstrs; ++i)
    اگر (strs[i].اندر_نتیجہ)
      {
        حرف name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        حرف *e = envz_اندراج (*argz, سائز, name);
        اگر (e == تہی)
          {
            لکھو ("entry '%s' not found\n", name);
            نتیجہ = 1;
          }
        ورنہ اگر (strcmp (e, strs[i].s) != 0)
          {
            لکھو ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            نتیجہ = 1;
          }
      }

  آزاد (*argz);
  واپس نتیجہ;
}

#شامل <support/test-driver.c>
