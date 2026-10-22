/* Test for bug BZ #2703.  */
#شامل <stdio.h>
#شامل <envz.h>
#شامل <stdlib.h>
#شامل <string.h>

ایستا ثابت ساختار
{
  ثابت نویسه *s;
  صحیح in_result;
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

#define nstrs (اندازه (strs) / اندازه (strs[0]))


صحیح
do_test (تهی)
{

  size_t size = 0;
  نویسه *str = malloc (100);
  اگر (str == پوچ)
    {
      puts ("out of memory");
      بازگشت 1;
    }

  نویسه **argz = &str;

  برای (صحیح i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  صحیح result = 0;
  printf ("new size=%zu\n", size);
  برای (صحیح i = 0; i < nstrs; ++i)
    اگر (strs[i].in_result)
      {
        نویسه name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        نویسه *e = envz_entry (*argz, size, name);
        اگر (e == پوچ)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        وگرنه اگر (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  آزاد (*argz);
  بازگشت result;
}

#شامل <support/test-driver.c>
