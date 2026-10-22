/* Test for strverscmp() */

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#define  MAX_STRINGS      256
#define  MAX_വരി_SIZE    32

സ്ഥിതം പൂർണ്ണസംഖ്യ
compare (സ്ഥിരം ശൂന്യം *p1, സ്ഥിരം ശൂന്യം *p2)
{
  തിരികെ strverscmp (*((അക്ഷരം **) p1), *((അക്ഷരം **) p2));
}

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  അക്ഷരം വരി[MAX_വരി_SIZE + 1];
  അക്ഷരം *str[MAX_STRINGS];
  പൂർണ്ണസംഖ്യ  എണ്ണം = 0;
  പൂർണ്ണസംഖ്യ  i, n;

  ആകുമ്പോൾ (എണ്ണം < MAX_STRINGS && fgets (വരി, MAX_വരി_SIZE, stdin) != ശൂന്യ)
    {
      n = strlen (വരി) - 1;

      എങ്കിൽ (വരി[n] == '\n')
        വരി[n] = '\0';

      str[എണ്ണം] = strdup (വരി);

      എങ്കിൽ (str[എണ്ണം] == ശൂന്യ)
        exit (EXIT_FAILURE);

      ++എണ്ണം;
    }

  qsort (str, എണ്ണം, വലുപ്പം (അക്ഷരം *), compare);

  വേണ്ടി (i = 0; i < എണ്ണം; ++i)
    puts (str[i]);

  തിരികെ EXIT_SUCCESS;
}

#അന്തര്ഭാവ <support/test-driver.c>
