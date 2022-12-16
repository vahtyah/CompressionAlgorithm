#pragma once
#include <iostream>
#include <string>
using namespace std;

string CompressRLE(string original) {
	string compressData;
	int temp = 1;
	for (int i = 0; i < original.length(); i++)
	{
		if (original[i] == original[i + 1])
			temp++;
		else
		{
			compressData += to_string(temp);
			compressData += original[i];
			temp = 1;
		}
	}
	return compressData;
}

string DecompressRLE(string compressed) {
	string original;
	int num = 0;
	for (auto c : compressed)
	{
		if (isdigit(static_cast<unsigned char>(c)))
			num = num * 10 + c - '0';
		else
		{
			num += num == 0 ? 2 : 1;
			while (--num)
				original += c;
		}
	}
	return original;
}