#include <iostream>
#include <string>

// RLE encode
std::string encodeRLE(const std::string& input) {
	std::string output;
	char current = input[0];
	int count = 1;
	for (size_t i = 1; i < input.size(); i++) {
		if (input[i] == current) {
			count++;
		}
		else {
			output += std::to_string(count) + current;
			current = input[i];
			count = 1;
		}
	}
	output += std::to_string(count) + current;
	return output;
}

// RLE decode
std::string decodeRLE(const std::string& input) {
	std::string output;
	for (size_t i = 0; i < input.size(); i++) {
		if (isdigit(input[i])) {
			int count = input[i] - '0';
			i++;
			while (isdigit(input[i])) {
				count = count * 10 + input[i] - '0';
				i++;
			}
			for (int j = 0; j < count; j++) {
				output += input[i];
			}
		}
		else {
			output += input[i];
		}
	}
	return output;
}
