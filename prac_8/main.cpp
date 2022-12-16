#include "LZ78.h"
#include "LZ77.h"
#include "RLE.h"
#include "Huffman.h"
#include "ShannonFano.h"
#include <Windows.h>

int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(0, "");

	string original;
	string compressed;

	//RLE
	cout << "RLE" << endl;
	original = "WWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
	//original = "abcabcabcabcabc";
	compressed = CompressRLE(original);
	cout << "Adaptive RLE code for " << original << " is: " << compressed << endl;
	cout << "Compression Ratio: " << (double)original.length() / compressed.length() << endl;
	original = DecompressRLE(compressed);
	cout << "Adaptive RLE decode for " << compressed << " is: " << original << endl << endl;
	
	//LZ77
	cout << "LZ77" << endl;
	original = "1110100110111001101";
	vector<Node*> encoded = Encode(original);
	cout << "Adaptive LZ77 code for " << original << " is: ";
	for (auto& node : encoded)
		cout << "(" << node->offset << " " << node->length << ") " << node->next << " ";

	compressed = "0 0 1 1 2 0 2 2 0 6 4 1 8 7";
	cout << "\nAdaptive LZ77 decode for " << compressed << " is: ";
	vector<Node*> decoded;
	vector<string> _split = split(compressed);
	for (int i = 0;i < _split.size();)
	{
		int offset = stoi(_split[i++]);
		int length = stoi(_split[i++]);
		char next = i >= _split.size() ? ' ' : _split[i++][0];
		decoded.push_back(new Node(offset, length, next));
	}
	original = Decode(decoded);
	cout << original << endl << endl;

	//LZ78
	cout << "LZ78" << endl;
	original = "sionsinossionsinos";
	compressed = LZ78(original, 1); 
	cout << "Adaptive LZ78 code for " << original << " is: " << compressed << endl;
	original = LZ78(compressed,2);
	cout << "Adaptive LZ78 decode for " << compressed << " is: " << original << endl << endl;

	//Shannon Fano
	cout << "Shannon Fano" << endl;
	/*Дрынцы-брынцыбубен-цы, Раз-звонилисьудальцы, Диги-диги-диги-дон, Выхо-ди-скорее-вон!*/
	//getline(cin, original);
	original = "One, two, Freddy's coning for you Three, four, aetter lock your door Five, six, graa a crucifix Seven, eight, gonna stay up late.";
	shannon_fano sh(original);
	sh.encode();
	compressed = sh.print(2);
	cout << "Adaptive Shannon Fano code for " << original << " is: " << compressed << endl;
	original = sh.decode(compressed);
	cout << "Adaptive Shannon Fano decode for " << compressed << " is: " << original << endl << endl;
	

	//Huffman
	cout << "Huffman" << endl;
	std::string data = "maivantuan";
	std::string output;
	createNode("NYT", 51, 0, -1, "");
	output = encode(data);
	std::cout << "Adaptive huffman code for " << data << " is:\n" << output << endl;
	tree.clear();
	createNode("NYT", 51, 0, -1, "");
	data = decode(output);
	std::cout << "Adaptive huffman decode for " << output << " is:\n" << data << endl;
	system("pause");

	return 0;
}


