/* Test for bug BZ #2703.  */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <envz.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
  ಪೂರ್ಣಾಂಕ ಒಳ_ಫಲಿತಾಂಶ;
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

#ವ್ಯಾಖ್ಯಾನಿಸು nstrs (ಗಾತ್ರ (strs) / ಗಾತ್ರ (strs[0]))


ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{

  size_t ಗಾತ್ರ_2 = 0;
  ಅಕ್ಷರ *str = ಸ್ಮರಣೆ_ಕೊಡು (100);
  ಆದರೆ (str == ಖಾಲಿ)
    {
      puts ("out of memory");
      ಹಿಂತಿರುಗಿ 1;
    }

  ಅಕ್ಷರ **argz = &str;

  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nstrs; ++i)
    argz_ಕೂಡಿಸು_sep (argz, &ಗಾತ್ರ_2, strs[i].s, '\0');

  ಬರೆ ("calling envz_strip with size=%zu\n", ಗಾತ್ರ_2);
  envz_strip (argz, &ಗಾತ್ರ_2);

  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;
  ಬರೆ ("new size=%zu\n", ಗಾತ್ರ_2);
  ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nstrs; ++i)
    ಆದರೆ (strs[i].ಒಳ_ಫಲಿತಾಂಶ)
      {
        ಅಕ್ಷರ name[2];
        name[0] = strs[i].s[0];
        name[1] = '\0';

        ಅಕ್ಷರ *e = envz_ನಮೂದು (*argz, ಗಾತ್ರ_2, name);
        ಆದರೆ (e == ಖಾಲಿ)
          {
            ಬರೆ ("entry '%s' not found\n", name);
            ಫಲಿತಾಂಶ = 1;
          }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (e, strs[i].s) != 0)
          {
            ಬರೆ ("entry '%s' does not match: is '%s', expected '%s'\n",
                    name, e, strs[i].s);
            ಫಲಿತಾಂಶ = 1;
          }
      }

  ಬಿಡುಗಡೆ (*argz);
  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
