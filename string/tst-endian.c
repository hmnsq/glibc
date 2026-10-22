#ଅନ୍ତର୍ଭାଵ <byteswap.h>
#ଅନ୍ତର୍ଭାଵ <endian.h>
#ଅନ୍ତର୍ଭାଵ <inttypes.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <libc-diag.h>

#ଯଦି __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#ଅନ୍ୟଥା
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା result = 0;

  ପାଇଁ (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      ଯଦି (i < UINT64_C (65536))
	{
	  DIAG_ଠେଲ_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ଯଦି (htobe16 (be16toh (i)) != i)
	    {
	      printf ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      result = 1;
	    }
	  ଯଦି (htole16 (le16toh (i)) != i)
	    {
	      printf ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      result = 1;
	    }
	  DIAG_କାଢ଼_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ଯଦି (htole16 (i) != n[0])
	    {
	      printf ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      result = 1;
	    }
	  ଯଦି (htobe16 (i) != n[1])
	    {
	      printf ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      result = 1;
	    }
	}

      ଯଦି (i < UINT64_C (4294967296))
	{
	  DIAG_ଠେଲ_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ଯଦି (htobe32 (be32toh (i)) != i)
	    {
	      printf ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      result = 1;
	    }
	  ଯଦି (htole32 (le32toh (i)) != i)
	    {
	      printf ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      result = 1;
	    }
	  DIAG_କାଢ଼_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ଯଦି (htole32 (i) != n[0])
	    {
	      printf ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      result = 1;
	    }
	  ଯଦି (htobe32 (i) != n[1])
	    {
	      printf ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      result = 1;
	    }
	}

      DIAG_ଠେଲ_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      ଯଦି (htobe64 (be64toh (i)) != i)
	{
	  printf ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  result = 1;
	}
      ଯଦି (htole64 (le64toh (i)) != i)
	{
	  printf ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  result = 1;
	}
      DIAG_କାଢ଼_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      ଯଦି (htole64 (i) != n[0])
	{
	  printf ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  result = 1;
	}
      ଯଦି (htobe64 (i) != n[1])
	{
	  printf ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  result = 1;
	}
    }

  ଫେରନ୍ତୁ result;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>
