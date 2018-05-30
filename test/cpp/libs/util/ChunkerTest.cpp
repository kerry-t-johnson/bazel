#include "util/Chunker.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(Chunker, ExpectChunkCount1)
{
    util::Chunker uut(8);

    const std::string TEST_DATA = "12345678";

    std::vector<std::string> chunks = uut.chunk(TEST_DATA);

    EXPECT_EQ(1, chunks.size());
    EXPECT_EQ(TEST_DATA, chunks[0]);
}

TEST(Chunker, ExpectChunkCount2)
{
    util::Chunker uut(4);

    const std::string TEST_DATA = "12345678";

    std::vector<std::string> chunks = uut.chunk(TEST_DATA);

    EXPECT_EQ(2, chunks.size());
    EXPECT_EQ("1234", chunks[0]);
    EXPECT_EQ("5678", chunks[1]);
}

TEST(Chunker, ExpectChunkCountRemainder)
{
    util::Chunker uut(4);

    const std::string TEST_DATA = "123456789AB";

    std::vector<std::string> chunks = uut.chunk(TEST_DATA);

    EXPECT_EQ(3, chunks.size());
    EXPECT_EQ("1234", chunks[0]);
    EXPECT_EQ("5678", chunks[1]);
    EXPECT_EQ("9AB", chunks[2]);
}
