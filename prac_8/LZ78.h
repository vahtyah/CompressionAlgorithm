#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Encode a string using the LZ78 algorithm
string encodeLZ78(string s) {
    string result;
    unordered_map<string, int> dict;
    int dict_size = 0;
    string p = "";
    for (char c : s) {
        string pc = p + c;
        if (dict.count(pc)) {
            p = pc;
        }
        else {
            dict[pc] = ++dict_size;
            result += "(" + to_string(dict[p]) + "," + c + ")";
            p = "";
        }
    }
    if (!p.empty()) {
        result += "(" + to_string(dict[p]) + "," + '\0' + ")";
    }
    return result;
}

// Decode a string encoded with the LZ78 algorithm
string decodeLZ78(string input) {
    // Initialize the dictionary
    unordered_map<int, string> dictionary;
    int next_code = 1; // The next code to assign to a new entry in the dictionary

    // Initialize the output string
    string output;

    // Split the input string into a vector of pairs
    vector<pair<int, char>> v;
    int i = 0;
    while (i < input.size()) {
        int code = 0;
        while (i < input.size() && input[i] != ',') {
            code = code * 10 + (input[i] - '0');
            i++;
        }
        i++; // skip the comma
        char c = input[i];
        v.emplace_back(code, c);
        i++;
    }

    // Decode the vector of pairs
    for (pair<int, char> p : v) {
        int code = p.first;
        char c = p.second;
        string s;
        if (code == 0) {
            s = c;
        }
        else {
            s = dictionary[code] + c;
        }
        output += s;
        if (c != '\0') {
            dictionary[next_code++] = s;
        }
    }

    return output;
}