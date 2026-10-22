#अन्तर्भाव <byteswap.h>
#अन्तर्भाव <endian.h>
#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <libc-diag.h>

#यदि __GNUC_PREREQ (6, 0)
/* GCC 6.0 warns on big endian systems about:
   htobeXX (beXXtoh (i)) != i
   warning: self-comparison always evaluates to false [-Wtautological-compare]
   because htobeXX(x) and beXXtoh(x) is defined to (x)
   in string/endian.h on big endian systems.
   The same applies to htoleXX/leXXtoh on little endian systems.  */
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE() \
  DIAG_IGNORE_NEEDS_COMMENT (6, "-Wtautological-compare")
#अन्यथा
# define DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE()
#यदि_अन्तः

पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क परिणाम = 0;

  प्रति (uint64_t i = 0; i < (~UINT64_C (0)) >> 2; i = (i << 1) + 3)
    {
      यदि (i < UINT64_C (65536))
	{
	  DIAG_प्रक्षिप_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  यदि (htobe16 (be16toh (i)) != i)
	    {
	      प्रारूप_लिख ("htobe16 (be16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (be16toh (i)));
	      परिणाम = 1;
	    }
	  यदि (htole16 (le16toh (i)) != i)
	    {
	      प्रारूप_लिख ("htole16 (le16toh (%" PRIx64 ")) == %" PRIx16 "\n",
		      i, (uint16_t) htole16 (le16toh (i)));
	      परिणाम = 1;
	    }
	  DIAG_निष्कासय_NEEDS_COMMENT;

	  uint16_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_16 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  यदि (htole16 (i) != n[0])
	    {
	      प्रारूप_लिख ("htole16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htole16 (i), n[0]);
	      परिणाम = 1;
	    }
	  यदि (htobe16 (i) != n[1])
	    {
	      प्रारूप_लिख ("htobe16 (%" PRIx64 ") == %" PRIx16 " != %" PRIx16 "\n",
		      i, (uint16_t) htobe16 (i), n[1]);
	      परिणाम = 1;
	    }
	}

      यदि (i < UINT64_C (4294967296))
	{
	  DIAG_प्रक्षिप_NEEDS_COMMENT;
	  DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
	  यदि (htobe32 (be32toh (i)) != i)
	    {
	      प्रारूप_लिख ("htobe32 (be32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (be32toh (i)));
	      परिणाम = 1;
	    }
	  यदि (htole32 (le32toh (i)) != i)
	    {
	      प्रारूप_लिख ("htole32 (le32toh (%" PRIx64 ")) == %" PRIx32 "\n",
		      i, (uint32_t) htole32 (le32toh (i)));
	      परिणाम = 1;
	    }
	  DIAG_निष्कासय_NEEDS_COMMENT;

	  uint32_t n[2];
	  n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_32 (i);
	  n[__BYTE_ORDER == __BIG_ENDIAN] = i;
	  यदि (htole32 (i) != n[0])
	    {
	      प्रारूप_लिख ("htole32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htole32 (i), n[0]);
	      परिणाम = 1;
	    }
	  यदि (htobe32 (i) != n[1])
	    {
	      प्रारूप_लिख ("htobe32 (%" PRIx64 ") == %" PRIx32 " != %" PRIx32 "\n",
		      i, (uint32_t) htobe32 (i), n[1]);
	      परिणाम = 1;
	    }
	}

      DIAG_प्रक्षिप_NEEDS_COMMENT;
      DIAG_IGNORE_NEEDS_COMMENT_TAUTOLOGICAL_COMPARE ();
      यदि (htobe64 (be64toh (i)) != i)
	{
	  प्रारूप_लिख ("htobe64 (be64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htobe64 (be64toh (i)));
	  परिणाम = 1;
	}
      यदि (htole64 (le64toh (i)) != i)
	{
	  प्रारूप_लिख ("htole64 (le64toh (%" PRIx64 ")) == %" PRIx64 "\n",
		  i, htole64 (le64toh (i)));
	  परिणाम = 1;
	}
      DIAG_निष्कासय_NEEDS_COMMENT;

      uint64_t n[2];
      n[__BYTE_ORDER == __LITTLE_ENDIAN] = bswap_64 (i);
      n[__BYTE_ORDER == __BIG_ENDIAN] = i;
      यदि (htole64 (i) != n[0])
	{
	  प्रारूप_लिख ("htole64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htole64 (i), n[0]);
	  परिणाम = 1;
	}
      यदि (htobe64 (i) != n[1])
	{
	  प्रारूप_लिख ("htobe64 (%" PRIx64 ") == %" PRIx64 " != %" PRIx64 "\n",
		  i, htobe64 (i), n[1]);
	  परिणाम = 1;
	}
    }

  प्रत्यागम परिणाम;
}

#अन्तर्भाव <support/test-driver.c>
