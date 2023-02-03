#pragma once
#include "../HuffmanTree.h"
#include <string>
using namespace std;
//calculate frequancy .. generate tree ..e3ml bitsring

string generateCompressedCode(string XML_Text, vector<unsigned int> &freq);
string generateDecompressedCode(string compressed_Text, vector<unsigned int> freq);

