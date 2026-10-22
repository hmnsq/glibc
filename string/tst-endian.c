#شامل <byteswap.h>
#شامل <endian.h>
#شامل <inttypes.h>
#شامل <stdio.h>
#شامل <stdint.h>
#شامل <libc-diag.h>

#اگر __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#وگرنه
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#endif

صحیح
do_test (تهی)
{
  صحیح result = 0;

  برای (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      اگر (i < UINT64_C (65536))
	{
	  DIAG_افزودن_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  اگر (htobe16 (be16toh (i)) != i)
	    {
	      printf ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      result = 1;
	    }
	  اگر (htole16 (le16toh (i)) != i)
	    {
	      printf ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      result = 1;
	    }
	  DIAG_برداشت_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  اگر (htole16 (i) != n[0])
	    {
	      printf ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      result = 1;
	    }
	  اگر (htobe16 (i) != n[1])
	    {
	      printf ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      result = 1;
	    }
	}

      اگر (i < UINT64_C (4294967296))
	{
	  DIAG_افزودن_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  اگر (htobe32 (be32toh (i)) != i)
	    {
	      printf ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      result = 1;
	    }
	  اگر (htole32 (le32toh (i)) != i)
	    {
	      printf ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      result = 1;
	    }
	  DIAG_برداشت_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  اگر (htole32 (i) != n[0])
	    {
	      printf ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      result = 1;
	    }
	  اگر (htobe32 (i) != n[1])
	    {
	      printf ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      result = 1;
	    }
	}

      DIAG_افزودن_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      اگر (htobe64 (be64toh (i)) != i)
	{
	  printf ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  result = 1;
	}
      اگر (htole64 (le64toh (i)) != i)
	{
	  printf ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  result = 1;
	}
      DIAG_برداشت_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      اگر (htole64 (i) != n[0])
	{
	  printf ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  result = 1;
	}
      اگر (htobe64 (i) != n[1])
	{
	  printf ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  result = 1;
	}
    }

  بازگشت result;
}

#شامل <support/test-driver.c>
