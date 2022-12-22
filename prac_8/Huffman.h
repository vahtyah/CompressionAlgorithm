#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

// A Huffman tree node
struct NodeHuffman {
	char data;
	int frequency;
	NodeHuffman* left;
	NodeHuffman* right;

	NodeHuffman(char data, int frequency, NodeHuffman* left = nullptr, NodeHuffman* right = nullptr) : data(data), frequency(frequency), left(left), right(right) {}
};

// Compare nodes based on their frequency
struct NodeComparer {
	bool operator()(const NodeHuffman* lhs, const NodeHuffman* rhs) const {
		return lhs->frequency > rhs->frequency;
	}
};

// Build the Huffman tree
NodeHuffman* buildHuffmanTree(const std::unordered_map<char, int>& frequencies) {
	std::priority_queue<NodeHuffman*, std::vector<NodeHuffman*>, NodeComparer> queue;

	// Create leaf nodes for each character and add them to the priority queue
	for (const auto& x : frequencies) {
		queue.push(new NodeHuffman(x.first, x.second));
	}

	// Keep creating new nodes and adding them to the queue until there is only one node left
	while (queue.size() > 1) {
		// Get the two nodes with the smallest frequency
		NodeHuffman* left = queue.top();
		queue.pop();
		NodeHuffman* right = queue.top();
		queue.pop();

		// Create a new node with the sum of the frequencies and the two nodes as children
		int sum = left->frequency + right->frequency;
		queue.push(new NodeHuffman('\0', sum, left, right));
	}

	// The remaining node is the root of the Huffman tree
	return queue.top();
}

void generateCodes(const NodeHuffman* node, const std::string& code, std::unordered_map<char, std::string>& codes) {
	if (node->left == nullptr && node->right == nullptr) {
		// This is a leaf node, so we have found a code for a character
		codes[node->data] = code;
	}
	else {
		// This is an internal node, so we recursively generate codes for its children
		generateCodes(node->left, code + '0', codes);
		generateCodes(node->right, code + '1', codes);
	}
}

// Encode a message using Huffman coding
std::string encodeHuffman(const std::string& message, const std::unordered_map<char, std::string>& codes) {
	std::string encoded;
	for (char ch : message) {
		encoded += codes.at(ch);
	}
	return encoded;
}


// Decode an encoded message using the Huffman tree
std::string decodeHuffman(const std::string& encoded, const NodeHuffman* root) {
	std::string decoded;
	const NodeHuffman* current = root;
	for (char ch : encoded) {
		if (ch == '0') {
			current = current->left;
		}
		else {
			current = current->right;
		}
		if (current->left == nullptr && current->right == nullptr) {
			decoded += current->data;
			current = root;
		}
	}
	return decoded;
}