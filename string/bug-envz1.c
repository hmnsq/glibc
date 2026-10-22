/* Test for bug BZ #2703.  */
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <envz.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

స్థిర స్థిరరాశి నిర్మాణం
{
  స్థిరరాశి అక్షరం *s;
  పూర్ణాంకం లోపల_ఫలితం;
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

#నిర్వచించు nstrs (పరిమాణం (strs) / పరిమాణం (strs[0]))


పూర్ణాంకం
do_test (శూన్య)
{

  size_t కొలత = 0;
  అక్షరం *str = జ్ఞాపకం_ఇవ్వు (100);
  ఒకవేళ (str == ఖాళీ)
    {
      puts ("out of memory");
      తిరిగి 1;
    }

  అక్షరం **argz = &str;

  కొరకు (పూర్ణాంకం i = 0; i < nstrs; ++i)
    argz_కూడు_sep (argz, &కొలత, strs[i].s, '\0');

  రాయి ("calling envz_strip with size=%zu\n", కొలత);
  envz_strip (argz, &కొలత);

  పూర్ణాంకం ఫలితం = 0;
  రాయి ("new size=%zu\n", కొలత);
  కొరకు (పూర్ణాంకం i = 0; i < nstrs; ++i)
    ఒకవేళ (strs[i].లోపల_ఫలితం)
      {
        అక్షరం name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        అక్షరం *e = envz_నమోదు (*argz, కొలత, name);
        ఒకవేళ (e == ఖాళీ)
          {
            రాయి ("entry '%s' not found\n", name);
            ఫలితం = 1;
          }
        లేకపోతే ఒకవేళ (strcmp (e, strs[i].s) != 0)
          {
            రాయి ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            ఫలితం = 1;
          }
      }

  విడుదల (*argz);
  తిరిగి ఫలితం;
}

#అన్తర్భావ <support/test-driver.c>
