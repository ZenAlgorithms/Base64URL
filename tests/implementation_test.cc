#include <gtest/gtest.h>
#include <zen_algorithms/base64url.hpp>

TEST(Base64URL, Encode) {
    using namespace zen_algorithms;
    const std::string input = "hello world";
    const std::string output = base64url::encode(input);
    ASSERT_EQ(output, "aGVsbG8gd29ybGQ=");

    const std::string output_no_padding = base64url::encode(input, false);
    ASSERT_EQ(output_no_padding, "aGVsbG8gd29ybGQ");
}

TEST(Base64URL, Decode) {
    using namespace zen_algorithms;
    const std::string input = "aGVsbG8gd29ybGQ=";
    const std::string output = base64url::decode(input);
    ASSERT_EQ(output, "hello world");

    const std::string input_no_padding = "aGVsbG8gd29ybGQ";
    const std::string output_no_padding = base64url::decode(input_no_padding);
    ASSERT_EQ(output_no_padding, "hello world");
}
