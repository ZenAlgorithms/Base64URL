#pragma once

#include <string>
#include <map>

namespace zen_algorithms::base64url {
	static const std::string chars =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789-_";

	static std::map<char, int> chars_map = {
		{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9},
		{'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19},
		{'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25},
		{'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32}, {'h', 33}, {'i', 34}, {'j', 35},
		{'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40}, {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45},
		{'u', 46}, {'v', 47}, {'w', 48}, {'x', 49}, {'y', 50}, {'z', 51},
		{'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56}, {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61},
		{'-', 62}, {'_', 63}
	};

	static std::string encode(const std::string & input, bool padding = true) {
		std::string output;
		int value = 0;
		int value_b = -6;

		for (const unsigned char character: input) {
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

	static std::string decode(const std::string & input) {
		std::string output;
		int value = 0;
		int value_b = -8;
		for (const char character: input) {
			if (character == '=') break;
			value = (value << 6) + chars_map[character];
			value_b += 6;
			if (value_b >= 0) {
				output.push_back(static_cast<char>((value >> value_b) & 0xFF));
				value_b -= 8;
			}
		}
		return output;
	}
}
