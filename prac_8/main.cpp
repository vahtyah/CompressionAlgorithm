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

	//LZ77
	std::cout << "LZ77" << std::endl;
	// Input string
	input = "aabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaabcaab";
	std::cout << "Input: " << input << std::endl;
	// Encode the input string
	encoded = encodeLZ77(input);
	// Encode the encoded message
	std::cout << "Encoded message: " << encoded << std::endl; // 3A3B3C1D
	// Decode the input string
	decoded = decodeLZ77(encoded);
	// Decode the encoded message
	std::cout << "Decoded message: " << decoded << std::endl << std::endl;

	//LZ78
	cout << "LZ78" << endl;
	//// Input string
	//input = "sionsinossionsinos";
	//std::cout << "Input: " << input << std::endl;
	//// Encode the input string
	//encoded = encodeLZ78(input);
	//// Encode the encoded message
	//std::cout << "Encoded message: " << encoded << std::endl; // 3A3B3C1D
	//// Decode the input string
	encoded = "(0,s)(0,i)(1,o)(1,n)(2,s)(2,i)(2,n)(3,o)(3,s)(4,i)(4,o)(4,n)(4,s)(5,i)(5,o)(5,n)(5,o)(6,s)(6,i)(6,o)(6,n)(6,o)(6,s)";
	decoded = decodeLZ78(encoded);
	// Decode the encoded message
	std::cout << "Decoded message: " << decoded << std::endl << std::endl;

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


