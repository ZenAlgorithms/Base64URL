#include <gtest/gtest.h>
#include <base64url/container.hpp>

TEST(Base64URL, Encode) {
    using namespace base64url;
    const std::string input = "hello world";
    const std::string output = container::encode(input);
    ASSERT_EQ(output, "aGVsbG8gd29ybGQ=");

    const std::string output_no_padding = container::encode(input, false);
    ASSERT_EQ(output_no_padding, "aGVsbG8gd29ybGQ");
}

TEST(Base64URL, Decode) {
    using namespace base64url;
    const std::string input = "aGVsbG8gd29ybGQ=";
    const std::string output = container::decode(input);
    ASSERT_EQ(output, "hello world");

    const std::string input_no_padding = "aGVsbG8gd29ybGQ";
    const std::string output_no_padding = container::decode(input_no_padding);
    ASSERT_EQ(output_no_padding, "hello world");
}
