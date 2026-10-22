/* Copyright (C) 1994-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <support/check.h>

ശൂന്യം try (സ്ഥിരം അക്ഷരം *name, long long പൂർണ്ണസംഖ്യ param, പൂർണ്ണസംഖ്യ മൂല്യം, പൂർണ്ണസംഖ്യ expected)
{
  എങ്കിൽ (മൂല്യം != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, മൂല്യം);
      support_record_failure ();
    }
  അല്ലെങ്കിൽ
    printf ("%s(%#llx) as expected %d\n", name, param, മൂല്യം);
}

പൂർണ്ണസംഖ്യ
do_test (ശൂന്യം)
{
  പൂർണ്ണസംഖ്യ i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  വേണ്ടി (i=0 ; i < 8 * വലുപ്പം (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  വേണ്ടി (i=0 ; i < 8 * വലുപ്പം (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, പൂർണ്ണസംഖ്യ);
  TEST (ffsl, long പൂർണ്ണസംഖ്യ);
  TEST (ffsll, long long പൂർണ്ണസംഖ്യ);

  തിരികെ 0;
}

#അന്തര്ഭാവ <support/test-driver.c>
