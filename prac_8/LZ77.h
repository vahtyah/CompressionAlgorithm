#pragma once
#include <iostream>
#include <string>

// LZ77 encoding function
std::string encodeLZ77(const std::string& s)
{
	std::string result;
	// Keep track of the current position in the input string
	size_t i = 0;
	while (i < s.size())
	{
		// Search backwards in the input string for the longest matching substring
		size_t len = 0;
		size_t offset = 0;
		for (size_t j = i; j > 0; --j)
		{
			size_t k = 0;
			while (s[i + k] == s[j + k] && k < i - j)
			{
				++k;
			}
			if (k > len)
			{
				len = k;
				offset = i - j;
			}
		}
		if (len == 0)
		{
			result += s[i];
			++i;
		}
		else {

			// Append the matching substring to the result
			result += '(' + std::to_string(offset) + ',' + std::to_string(len) + ')';

			// Append any remaining characters to the result
			i += len;
			while (i < s.size() && s[i] != s[i - len])
			{
				result += s[i];
				++i;
			}
		}
	}

	return result;
}



// LZ77 decoding function
std::string decodeLZ77(const std::string& s)
{
	std::string result;

	// Keep track of the current position in the input string
	size_t i = 0;
	while (i < s.size())
	{
		// Check if the next character is the start of a matching substring
		if (s[i] == '(')
		{
			// Extract the offset and length of the matching substring
			size_t j = s.find(',', i);
			size_t offset = std::stoul(s.substr(i + 1, j - i - 1));
			size_t k = s.find(')', j);
			size_t len = std::stoul(s.substr(j + 1, k - j - 1));

			// Append the matching substring to the result
			size_t m = result.size() - offset;
			for (size_t n = 0; n < len; ++n)
			{
				result += result[m + n];
			}

			// Update the current position
			i = k + 1;
		}
		else
		{
			// Append the next character to the result
			result += s[i];
			++i;
		}
	}

	return result;
}