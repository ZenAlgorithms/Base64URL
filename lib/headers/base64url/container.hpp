#pragma once

#include <string>
#include <vector>
#include <memory>
#include <regex>

namespace base64url {
    static const std::string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789-_";

    struct container {
        std::string static encode(const std::string & input, bool padding = true);
        std::string static decode(const std::string & input);
    };
}
