/* Test for bug BZ #2703.  */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <envz.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ
{
  ಧ್ರುವ ವರ್ಣ *s;
  ಪೂರ್ಣಾಙ್ಕ in_result;
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

#define nstrs (ಪರಿಮಾಣ (strs) / ಪರಿಮಾಣ (strs[0]))


ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{

  size_t size = 0;
  ವರ್ಣ *str = malloc (100);
  ಯದಿ (str == ರಿಕ್ತ)
    {
      puts ("out of memory");
      ಪ್ರತ್ಯಾಗಮ 1;
    }

  ವರ್ಣ **argz = &str;

  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  ಪೂರ್ಣಾಙ್ಕ result = 0;
  printf ("new size=%zu\n", size);
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nstrs; ++i)
    ಯದಿ (strs[i].in_result)
      {
        ವರ್ಣ name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        ವರ್ಣ *e = envz_entry (*argz, size, name);
        ಯದಿ (e == ರಿಕ್ತ)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        ಅನ್ಯಥಾ ಯದಿ (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  ಮುಕ್ತ (*argz);
  ಪ್ರತ್ಯಾಗಮ result;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
