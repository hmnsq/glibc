/* Test memchr functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#وصف_ڪريو TEST_MAIN
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define TEST_NAME "memchr"
#وإلا
# define TEST_NAME "wmemchr"
#جيڪڏهن_پورو /* WIDE */

#ضمن "test-string.h"
#ضمن <stdint.h>

#جيڪڏهن_وصف_نه_ٿيل WIDE
# define MEMCHR memchr
# define CHAR حرف
# define UCHAR بنانشان حرف
# define BIG_CHAR CHAR_MAX
# define SMALL_CHAR 127
#وإلا
# include <wchar.h>
# define MEMCHR wmemchr
# define CHAR wchar_t
# define UCHAR wchar_t
# define BIG_CHAR WCHAR_MAX
# define SMALL_CHAR 1273
#جيڪڏهن_پورو /* WIDE */

تعريفنوع CHAR *(*proto_t) (ثابت CHAR *, صحيح, size_t);

IMPL (MEMCHR, 1)

/* Also check the generic implementation.  */
#وصف_رد MEMCHR
#وصف_رد static_weak_alias
#وصف_ڪريو static_weak_alias(a, b)
#وصف_رد libc_hidden_builtin_def
#وصف_ڪريو libc_hidden_builtin_def(a)
#وصف_رد libc_hidden_def
#وصف_ڪريو libc_hidden_def(a)
#وصف_رد libc_hidden_weak
#وصف_ڪريو libc_hidden_weak(a)
#جيڪڏهن_وصف_نه_ٿيل WIDE
# define MEMCHR __memchr_default
# include "string/memchr.c"
# define MEMCHR_DEFAULT MEMCHR
#وإلا
# define WMEMCHR __wmemchr_default
# include "wcsmbs/wmemchr.c"
# define MEMCHR_DEFAULT WMEMCHR
#جيڪڏهن_پورو
IMPL (MEMCHR_DEFAULT, 1)

ساكن فراغ
do_one_test (impl_t *impl, ثابت CHAR *s, صحيح c, size_t n, CHAR *exp_res)
{
  CHAR *res = CALL (impl, s, c, n);
  إذا (res != exp_res)
    {
      error (0, 0, "Wrong result in function %s (%p, %d, %zu) -> %p != %p",
             impl->name, s, c, n, res, exp_res);
      ret = 1;
      أرجع;
    }
}

ساكن فراغ
do_test (size_t align, size_t pos, size_t len, size_t n, صحيح seek_char)
{
  size_t i;
  CHAR *نتيجو;

  إذا ((align + len) * حجم (CHAR) >= صفحو_سائيز)
    أرجع;

  CHAR *buf = (CHAR *) (buf1);

  لكل (i = 0; i < len; ++i)
    {
      buf[align + i] = 1 + 23 * i % SMALL_CHAR;
      إذا (buf[align + i] == seek_char)
	buf[align + i] = seek_char + 1;
    }
  buf[align + len] = 0;

  إذا (pos < MIN(n, len))
    {
      buf[align + pos] = seek_char;
      buf[align + len] = -seek_char;
      نتيجو = (CHAR *) (buf + align + pos);
    }
  وإلا
    {
      نتيجو = عدم;
      buf[align + len] = seek_char;
    }

  FOR_EACH_IMPL (impl, 0)
    do_one_test (impl, (CHAR *) (buf + align), seek_char, n, نتيجو);
}

ساكن فراغ
do_حد_کان_مٿي_tests (فراغ)
{
  size_t i, j, len;
  ثابت size_t one = 1;
  uintptr_t buf_addr = (uintptr_t) buf1;

  لكل (i = 0; i < 750; ++i)
    {
        do_test (0, i, 751, SIZE_MAX - i, BIG_CHAR);
        do_test (0, i, 751, i - buf_addr, BIG_CHAR);
        do_test (0, i, 751, -buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr - i, BIG_CHAR);
        do_test (0, i, 751, SIZE_MAX - buf_addr + i, BIG_CHAR);

      len = 0;
      لكل (j = 8 * حجم(size_t) - 1; j ; --j)
        {
          len |= one << j;
          do_test (0, i, 751, len - i, BIG_CHAR);
          do_test (0, i, 751, len + i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, len - buf_addr + i, BIG_CHAR);

          do_test (0, i, 751, ~len - i, BIG_CHAR);
          do_test (0, i, 751, ~len + i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr - i, BIG_CHAR);
          do_test (0, i, 751, ~len - buf_addr + i, BIG_CHAR);
        }
    }
}

ساكن فراغ
do_random_tests (فراغ)
{
  size_t i, j, n, align, pos, len;
  صحيح seek_char;
  CHAR *نتيجو;
  UCHAR *p = (UCHAR *) (buf1 + صفحو_سائيز) - 512;

  لكل (n = 0; n < ITERATIONS; n++)
    {
      align = random () & 15;
      pos = random () & 511;
      إذا (pos + align >= 512)
	pos = 511 - align - (random () & 7);
      len = random () & 511;
      إذا (pos >= len)
	len = pos + (random () & 7);
      إذا (len + align >= 512)
	len = 512 - align - (random () & 7);
      seek_char = random () & BIG_CHAR;
      j = len + align + 64;
      إذا (j > 512)
	j = 512;

      لكل (i = 0; i < j; i++)
	{
	  إذا (i == pos + align)
	    p[i] = seek_char;
	  وإلا
	    {
	      p[i] = random () & BIG_CHAR;
	      إذا (i < pos + align && p[i] == seek_char)
		p[i] = seek_char + 13;
	    }
	}

      إذا (pos < len)
	{
	  size_t r = random ();
	  إذا ((r & 31) == 0)
	    len = ~(uintptr_t) (p + align) - ((r >> 5) & 31);
	  نتيجو = (CHAR *) (p + pos + align);
	}
      وإلا
	نتيجو = عدم;

      FOR_EACH_IMPL (impl, 1)
	إذا (CALL (impl, (CHAR *) (p + align), seek_char, len) != نتيجو)
	  {
	    error (0, 0, "Iteration %zd - wrong result in function %s (%zd, %d, %zd, %zd) %p != %p, p %p",
		   n, impl->name, align, seek_char, len, pos,
		   CALL (impl, (CHAR *) (p + align), seek_char, len),
		   نتيجو, p);
	    ret = 1;
	  }
    }
}

صحيح
test_main (فراغ)
{
  size_t i, j;

  test_init ();

  لکو ("%20s", "");
  FOR_EACH_IMPL (impl, 0)
    لکو ("\t%s", impl->name);
  اکر_لکو ('\n');

  لكل (i = 1; i < 8; ++i)
    {
      /* Test n == 0.  */
      do_test (i, i, 0, 0, 23);
      do_test (i, i, 0, 0, 0);

      do_test (0, 16 << i, 2048, 2048, 23);
      do_test (i, 64, 256, 256, 23);
      do_test (0, 16 << i, 2048, 2048, 0);
      do_test (i, 64, 256, 256, 0);

      /* Check for large input sizes and for these cases we need to
	 make sure the byte is within the size range (that's why
	 7 << i must be smaller than 2048).  */
      do_test (0, 7 << i, 2048, SIZE_MAX, 23);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 23);
      do_test (i, 64, 256, SIZE_MAX, 23);
      do_test (0, 7 << i, 2048, SIZE_MAX, 0);
      do_test (0, 2048 - i, 2048, SIZE_MAX, 0);
      do_test (i, 64, 256, SIZE_MAX, 0);
    }

  لكل (i = 1; i < 64; ++i)
    {
      لكل (j = 1; j < 64; j++)
        {
	  do_test (0, 64 - j, 64, SIZE_MAX, 23);
	  do_test (i, 64 - j, 64, SIZE_MAX, 23);
        }
    }

  لكل (i = 1; i < 32; ++i)
    {
      do_test (0, i, i + 1, i + 1, 23);
      do_test (0, i, i + 1, i + 1, 0);
    }

  /* BZ#21182 - wrong overflow calculation for i686 implementation
     with address near end of the page.  */
  لكل (i = 2; i < 16; ++i)
    {
      /* page_size is in fact getpagesize() * 2.  */
      do_test (صفحو_سائيز / 2 - i, i, i, 1, 0x9B);
      do_test (صفحو_سائيز / 2 - i, i - 1, i - 1, 1, 0x9B);
      do_test (صفحو_سائيز / 2 - (i * 4), i + 128, i + 128, i, 0x9B);
    }

  do_random_tests ();
  do_حد_کان_مٿي_tests ();
  أرجع ret;
}

#ضمن <support/test-driver.c>
