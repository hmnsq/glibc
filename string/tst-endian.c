#ಅನ್ತರ್ಭಾವ <byteswap.h>
#ಅನ್ತರ್ಭಾವ <endian.h>
#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <libc-diag.h>

#ಆದರೆ __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#ಇಲ್ಲದಿದ್ದರೆ
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;

  ಗಾಗಿ (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      ಆದರೆ (i < UINT64_C (65536))
	{
	  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ಆದರೆ (htobe16 (be16toh (i)) != i)
	    {
	      ಬರೆ ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (htole16 (le16toh (i)) != i)
	    {
	      ಬರೆ ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      ಫಲಿತಾಂಶ = 1;
	    }
	  DIAG_ತೆಗೆ_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ಆದರೆ (htole16 (i) != n[0])
	    {
	      ಬರೆ ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (htobe16 (i) != n[1])
	    {
	      ಬರೆ ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      ಫಲಿತಾಂಶ = 1;
	    }
	}

      ಆದರೆ (i < UINT64_C (4294967296))
	{
	  DIAG_ತಳ್ಳು_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  ಆದರೆ (htobe32 (be32toh (i)) != i)
	    {
	      ಬರೆ ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (htole32 (le32toh (i)) != i)
	    {
	      ಬರೆ ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      ಫಲಿತಾಂಶ = 1;
	    }
	  DIAG_ತೆಗೆ_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  ಆದರೆ (htole32 (i) != n[0])
	    {
	      ಬರೆ ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      ಫಲಿತಾಂಶ = 1;
	    }
	  ಆದರೆ (htobe32 (i) != n[1])
	    {
	      ಬರೆ ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      ಫಲಿತಾಂಶ = 1;
	    }
	}

      DIAG_ತಳ್ಳು_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      ಆದರೆ (htobe64 (be64toh (i)) != i)
	{
	  ಬರೆ ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  ಫಲಿತಾಂಶ = 1;
	}
      ಆದರೆ (htole64 (le64toh (i)) != i)
	{
	  ಬರೆ ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  ಫಲಿತಾಂಶ = 1;
	}
      DIAG_ತೆಗೆ_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      ಆದರೆ (htole64 (i) != n[0])
	{
	  ಬರೆ ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  ಫಲಿತಾಂಶ = 1;
	}
      ಆದರೆ (htobe64 (i) != n[1])
	{
	  ಬರೆ ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  ಫಲಿತಾಂಶ = 1;
	}
    }

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>
