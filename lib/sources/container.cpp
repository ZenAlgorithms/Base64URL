#include <base64url/container.hpp>

namespace base64url {
    std::string container::encode(const std::string &input, bool padding) {
        std::string output;
        int value = 0;
        int value_b = -6;

        for (const unsigned char character : input) {
            value = (value << 8) + character;
            value_b += 8;
            while (value_b >= 0) {
                output.push_back(chars[(value >> value_b) & 0x3F]);
                value_b -= 6;
            }
        }
        if (value_b > -6)
            output.push_back(chars[((value << 8) >> (value_b + 8)) & 0x3F]);

        if (padding)
            while (output.size() % 4 != 0)
                output.push_back('=');

        return output;
    }

    std::string container::decode(const std::string &input) {
        std::string output;
        int value = 0;
        int value_b = -8;
        for (const char character : input) {
            if (character == '=') break;
            auto position = chars.find(character);
            value = (value << 6) + position;
            value_b += 6;
            if (value_b >= 0) {
                output.push_back(static_cast<char>((value >> value_b) & 0xFF));
                value_b -= 8;
            }
        }
        return output;
    }
}
