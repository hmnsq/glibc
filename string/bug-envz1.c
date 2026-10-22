/* Test for bug BZ #2703.  */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <envz.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਸਥਿਰ ਅਚਲ ਬਣਤਰ
{
  ਅਚਲ ਅੱਖਰ *s;
  ਪੂਰਨ ਵਿੱਚ_ਨਤੀਜਾ;
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ nstrs (ਆਕਾਰ (strs) / ਆਕਾਰ (strs[0]))


ਪੂਰਨ
do_test (ਖਾਲੀ)
{

  size_t ਮਾਪ = 0;
  ਅੱਖਰ *str = ਸਮ੍ਰਿਤੀ_ਦਿਓ (100);
  ਜੇ (str == ਨਿਰਾ)
    {
      puts ("out of memory");
      ਵਾਪਸ 1;
    }

  ਅੱਖਰ **argz = &str;

  ਲਈ (ਪੂਰਨ i = 0; i < nstrs; ++i)
    argz_ਜੋੜੋ_sep (argz, &ਮਾਪ, strs[i].s, '\0');

  ਲਿਖੋ ("calling envz_strip with size=%zu\n", ਮਾਪ);
  envz_strip (argz, &ਮਾਪ);

  ਪੂਰਨ ਨਤੀਜਾ = 0;
  ਲਿਖੋ ("new size=%zu\n", ਮਾਪ);
  ਲਈ (ਪੂਰਨ i = 0; i < nstrs; ++i)
    ਜੇ (strs[i].ਵਿੱਚ_ਨਤੀਜਾ)
      {
        ਅੱਖਰ name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        ਅੱਖਰ *e = envz_ਇੰਦਰਾਜ (*argz, ਮਾਪ, name);
        ਜੇ (e == ਨਿਰਾ)
          {
            ਲਿਖੋ ("entry '%s' not found\n", name);
            ਨਤੀਜਾ = 1;
          }
        ਨਹੀਂਤਾਂ ਜੇ (strcmp (e, strs[i].s) != 0)
          {
            ਲਿਖੋ ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            ਨਤੀਜਾ = 1;
          }
      }

  ਮੁਕਤ (*argz);
  ਵਾਪਸ ਨਤੀਜਾ;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
