#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Node
{
	int offset;
	int length;
	char next;

	Node(int of, int le, char ne)
	{
		offset = of;
		length = le;
		next = ne;
	}
};

vector<Node*> Encode(string original) {
	vector<Node*> compressed;

	const int buf_size = 3072;
	const int preview_size = 1024;

	int position = 0;

	while (position < original.length() - 1)
	{
		int max_index = 0, max_length = 0, cur_index, cur_length;
		for (int j = max(0, (position - buf_size)); j < position; j++)
		{
			cur_index = j, cur_length = 0;

			while (original[cur_index] == original[cur_length + position] && cur_index < min((position + preview_size), (int)original.length()))
			{
				cur_index++;
				cur_length++;
			}

			if (cur_length > max_length)
			{
				max_index = position - j;
				max_length = cur_length;
			}
		}

		position += max_length;
		compressed.push_back(new Node(max_index, max_length, original[position]));
		position++;
	}

	return compressed;
}
string Decode(const vector<Node*>& encoded) {
	std::string original;
	for (auto& node : encoded)
	{
		if (node->length > 0)
		{
			int start = original.length() - node->offset;
			for (int k = 0; k < node->length; k++)
			{
				original += original[start + k];
			}
		}
		original += node->next;
	}
	return original;
}

vector<string> split(string str, string delimiter = " ") {
	size_t pos = 0;
	string token;
	vector<string> arr;
	while ((pos = str.find(delimiter)) != string::npos) {
		token = str.substr(0, pos);
		arr.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	arr.push_back(str);
	return arr;
}