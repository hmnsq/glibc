/* Test for bug BZ #2703.  */
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <envz.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

স্থির ধ্রুব সংরচনা
{
  ধ্রুব বর্ণ *s;
  পূর্ণাঙ্ক in_result;
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

#define nstrs (পরিমাণ (strs) / পরিমাণ (strs[0]))


পূর্ণাঙ্ক
do_test (শূন্য)
{

  size_t size = 0;
  বর্ণ *str = malloc (100);
  যদি (str == রিক্ত)
    {
      puts ("out of memory");
      প্রত্যাগম 1;
    }

  বর্ণ **argz = &str;

  প্রতি (পূর্ণাঙ্ক i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  পূর্ণাঙ্ক result = 0;
  printf ("new size=%zu\n", size);
  প্রতি (পূর্ণাঙ্ক i = 0; i < nstrs; ++i)
    যদি (strs[i].in_result)
      {
        বর্ণ name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        বর্ণ *e = envz_entry (*argz, size, name);
        যদি (e == রিক্ত)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        অন্যথা যদি (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  মুক্ত (*argz);
  প্রত্যাগম result;
}

#অন্তর্ভাব <support/test-driver.c>
