#include "LZ78.h"
#include "LZ77.h"
#include "RLE.h"
#include "Huffman.h"
#include "ShannonFano.h"
#include <Windows.h>

int main() {
	//RLE
	std::cout << "RLE" << std::endl;
	// Input string
	std::string input = "AAABBBCCCD";
	std::cout << "Input: " << input << std::endl;
	// Encode the input string
	std::string encoded = encodeRLE(input);
	// Encode the encoded message
	std::cout << "Encoded message: " << encoded << std::endl; // 3A3B3C1D
	// Decode the input string
	std::string decoded = decodeRLE(encoded);
	// Decode the encoded message
	std::cout << "Decoded message: " << decoded << std::endl << std::endl;

	////LZ77
	//cout << "LZ77" << endl;
	//original = "1110100110111001101";
	//vector<Node*> encoded = Encode(original);
	//cout << "Adaptive LZ77 code for " << original << " is: ";
	//for (auto& node : encoded)
	//	cout << "(" << node->offset << " " << node->length << ") " << node->next << " ";

	//compressed = "0 0 1 1 2 0 2 2 0 6 4 1 8 7";
	//cout << "\nAdaptive LZ77 decode for " << compressed << " is: ";
	//vector<Node*> decoded;
	//vector<string> _split = split(compressed);
	//for (int i = 0;i < _split.size();)
	//{
	//	int offset = stoi(_split[i++]);
	//	int length = stoi(_split[i++]);
	//	char next = i >= _split.size() ? ' ' : _split[i++][0];
	//	decoded.push_back(new Node(offset, length, next));
	//}
	//original = Decode(decoded);
	//cout << original << endl << endl;

	////LZ78
	//cout << "LZ78" << endl;
	//original = "sionsinossionsinos";
	//compressed = LZ78(original, 1); 
	//cout << "Adaptive LZ78 code for " << original << " is: " << compressed << endl;
	//original = LZ78(compressed,2);
	//cout << "Adaptive LZ78 decode for " << compressed << " is: " << original << endl << endl;

	////Shannon Fano
	//cout << "Shannon Fano" << endl;
	///*Дрынцы-брынцыбубен-цы, Раз-звонилисьудальцы, Диги-диги-диги-дон, Выхо-ди-скорее-вон!*/
	////getline(cin, original);
	//original = "One, two, Freddy's coning for you Three, four, aetter lock your door Five, six, graa a crucifix Seven, eight, gonna stay up late.";
	//shannon_fano sh(original);
	//sh.encode();
	//compressed = sh.print(2);
	//cout << "Adaptive Shannon Fano code for " << original << " is: " << compressed << endl;
	//original = sh.decode(compressed);
	//cout << "Adaptive Shannon Fano decode for " << compressed << " is: " << original << endl << endl;
	

	//Huffman
	// Input string
	std::cout << "Huffman" << std::endl;
	input = "this is an example for huffman encoding";
	std::cout << "Input: " << input << std::endl;
	// Count the frequency of each character in the input string
	std::unordered_map<char, int> frequencies;
	for (char ch : input) {
		frequencies[ch]++; 
	}

	// Build the Huffman tree
	NodeHuffman* root = buildHuffmanTree(frequencies);

	// Generate the Huffman codes
	std::unordered_map<char, std::string> codes;
	generateCodes(root, "", codes);

	// Encode the input string
	encoded = encodeHuffman(input, codes);

	std::cout << "Encoded message: " << encoded << std::endl;

	// Decode the encoded message
	decoded = decodeHuffman(encoded, root);

	std::cout << "Decoded message: " << decoded << std::endl;

	return 0;
}


