#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "windows.h"
using namespace std;

struct NodeLZ78 {
	int index;
	string data;
	NodeLZ78* next;
};
void st_Node(NodeLZ78* head, int index, string data) {
	head->index = index;
	head->data = data;
	head->next = NULL;
}
void insert_Node(NodeLZ78* head, int index, string data) {
	NodeLZ78* new_Node = new NodeLZ78;
	new_Node->index = index;
	new_Node->data = data;
	new_Node->next = NULL;

	NodeLZ78* curr = head;
	while (curr != NULL)
	{
		if (curr->next == NULL)
		{
			curr->next = new_Node;
			return;
		}
		curr = curr->next;
	}
}
NodeLZ78* search_Node(NodeLZ78* head, string data)
{
	NodeLZ78* curr = head;
	while (curr != NULL)
	{
		if (data.compare(curr->data) == 0)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}
NodeLZ78* search_Node(NodeLZ78* head, int index)
{
	NodeLZ78* curr = head;
	while (curr != NULL)
	{
		if (index == curr->index)
			return curr;
		else
			curr = curr->next;
	}
	return NULL;
}
vector <string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while (getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}

string LZ78(string input, int option)
{
	if (option == 1)
	{
		NodeLZ78* dictionary = new NodeLZ78;
		string word, result;
		int length, last_seen, index = 1;

		length = (int)input.length();
		word = input[0];
		st_Node(dictionary, 1, word);
		result += "0," + word;

		for (int i = 1; i < length; i++)
		{
			string data;
			data = input[i];

		re_check:
			NodeLZ78* search = search_Node(dictionary, data);

			if (search)
			{
				i++;
				data += input[i];
				last_seen = search->index;
				goto re_check;
			}
			else
			{
				char zero;
				if (input[i] == ' ')
					zero = '0';
				else
					zero = input[i];

				if ((int)data.length() < 2)
					result += " " + to_string(0) + "," + zero;
				else
					result += " " + to_string(last_seen) + "," + zero;

				index++;
				if (i != length)
					insert_Node(dictionary, index, data);
			}
		}

		return result;
	}
	if (option == 2)
	{
		NodeLZ78* dictionary = new NodeLZ78;
		string result;

		vector <string> s_input = split(input, ' ');
		int zz = 2;
		for (int i = 0; i < s_input.size(); i++)
		{
			vector <string> ss_input = split(s_input[i], ',');

			if (i == 0)
			{
				st_Node(dictionary, 1, ss_input[1]);
				result += ss_input[1];
			}
			else
			{
				NodeLZ78* serched;
				string get_search = ss_input[1];
				serched = search_Node(dictionary, stoi(ss_input[0]));
				if (serched)
				{
					result += serched->data + get_search;
					get_search = serched->data + split(s_input[i], ',')[1];
					insert_Node(dictionary, zz, get_search);
				}
				else
				{
					if (stoi(ss_input[0]) == 0)
						insert_Node(dictionary, zz, get_search);
					else
						insert_Node(dictionary, zz, get_search);

					result += get_search;
				}
				zz++;
			}
		}

		if (result[(int)result.length() - 1] == '0')
			result = result.substr(0, result.size() - 1);

		return result;
	}
}