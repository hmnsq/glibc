/* Test for bug BZ #2703.  */
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <envz.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

স্থির ধ্রুবক কাঠামো
{
  ধ্রুবক অক্ষর *s;
  পূর্ণসংখ্যা in_ফলাফল;
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

#define nstrs (আকার (strs) / আকার (strs[0]))


পূর্ণসংখ্যা
do_test (শূন্য)
{

  size_t আকার_2 = 0;
  অক্ষর *str = malloc (100);
  যদি (str == ফাঁকা)
    {
      puts ("out of memory");
      ফেরত 1;
    }

  অক্ষর **argz = &str;

  জন্য (পূর্ণসংখ্যা i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &আকার_2, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", আকার_2);
  envz_strip (argz, &আকার_2);

  পূর্ণসংখ্যা ফলাফল = 0;
  printf ("new size=%zu\n", আকার_2);
  জন্য (পূর্ণসংখ্যা i = 0; i < nstrs; ++i)
    যদি (strs[i].in_ফলাফল)
      {
        অক্ষর name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        অক্ষর *e = envz_entry (*argz, আকার_2, name);
        যদি (e == ফাঁকা)
          {
            printf ("entry '%s' not found\n", name);
            ফলাফল = 1;
          }
        অন্যথা যদি (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            ফলাফল = 1;
          }
      }

  মুক্ত (*argz);
  ফেরত ফলাফল;
}

#অন্তর্ভাব <support/test-driver.c>
