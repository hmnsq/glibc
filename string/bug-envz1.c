/* Test for bug BZ #2703.  */
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <envz.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ସ୍ଥିର ଅଚଳ ସଂରଚନା
{
  ଅଚଳ ଅକ୍ଷର *s;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_result;
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

#define nstrs (ଆକାର (strs) / ଆକାର (strs[0]))


ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{

  size_t size = 0;
  ଅକ୍ଷର *str = malloc (100);
  ଯଦି (str == ଖାଲି)
    {
      puts ("out of memory");
      ଫେରନ୍ତୁ 1;
    }

  ଅକ୍ଷର **argz = &str;

  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;
  printf ("new size=%zu\n", size);
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nstrs; ++i)
    ଯଦି (strs[i].in_result)
      {
        ଅକ୍ଷର name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        ଅକ୍ଷର *e = envz_entry (*argz, size, name);
        ଯଦି (e == ଖାଲି)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        ଅନ୍ୟଥା ଯଦି (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  ମୁକ୍ତ (*argz);
  ଫେରନ୍ତୁ result;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
