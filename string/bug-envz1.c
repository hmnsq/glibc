/* Test for bug BZ #2703.  */
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <envz.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

સ્થિર અચલ સંરચના
{
  અચલ અક્ષર *s;
  પૂર્ણાંક in_result;
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

#define nstrs (કદ (strs) / કદ (strs[0]))


પૂર્ણાંક
do_test (શૂન્ય)
{

  size_t size = 0;
  અક્ષર *str = malloc (100);
  જો (str == ખાલી)
    {
      puts ("out of memory");
      પાછા 1;
    }

  અક્ષર **argz = &str;

  માટે (પૂર્ણાંક i = 0; i < nstrs; ++i)
    argz_add_sep (argz, &size, strs[i].s, '\0');

  printf ("calling envz_strip with size=%zu\n", size);
  envz_strip (argz, &size);

  પૂર્ણાંક result = 0;
  printf ("new size=%zu\n", size);
  માટે (પૂર્ણાંક i = 0; i < nstrs; ++i)
    જો (strs[i].in_result)
      {
        અક્ષર name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        અક્ષર *e = envz_entry (*argz, size, name);
        જો (e == ખાલી)
          {
            printf ("entry '%s' not found\n", name);
            result = 1;
          }
        નહીંતર જો (strcmp (e, strs[i].s) != 0)
          {
            printf ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            result = 1;
          }
      }

  મુક્ત (*argz);
  પાછા result;
}

#અન્તર્ભાવ <support/test-driver.c>
