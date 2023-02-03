#include "compression.h"
#include <vector>
#include <stack>
string generateCompressedCode(string XML_Text, vector<unsigned int>& charFreq)
{
	//calc freq 
	for (auto c : XML_Text) charFreq[c]++;
	// generate nodes 
	HuffmanTree *tree = new HuffmanTree();
	for (int i = 0; i < 256; i++)
	{
		if (charFreq[i] == 0) continue;
		HuffmanTreeNode* temp = new HuffmanTreeNode(i, charFreq[i]);
		tree->MainTree.push(temp);
	}
	// push to tree
	tree->generateTree(); // kedaa 3ndy tree
	// generate bitstring of each char 
	tree->generatebitCode(tree->MainTree.top(), "", true);
	//loop 3al string w badel
	bitstring compressed_file = bitstring("",0);
	string XML_COMPRESS;
	for (int i = 0; i<XML_Text.size(); i++)
	{
		if (XML_Text[i] == 0) continue;
		XML_COMPRESS.push_back(XML_Text[i]);
	}
	

	for (unsigned long long i = 0; i < XML_COMPRESS.size(); i++)
	{

		if (tree->alphaBitstring[XML_COMPRESS[i]] == nullptr) cout << "accessing null";
		compressed_file.bitstring_append(tree->alphaBitstring[XML_COMPRESS[i]]);
	}
	
	compressed_file.data.resize((compressed_file.bitCount / 8) + 1);
	string s;
	for (int i = 0; i < (compressed_file.bitCount / 8)+1; i++)
	{
		s.push_back(compressed_file.data[i]);
	}
	return s;
}

string generateDecompressedCode(string compressed_file,vector<unsigned int> freq)
{
	HuffmanTree* tree = new HuffmanTree();
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] == 0) continue;
		HuffmanTreeNode* temp = new HuffmanTreeNode(i, freq[i]);
		tree->MainTree.push(temp);
	}
	// push to tree
	tree->generateTree(); // kedaa 3ndy tree
	// generate bitstring of each char 
	tree->generatebitCode(tree->MainTree.top(), "", false);//keda 3ndy el bitstrings
	string XML_Text;
	bitstring *codedChar= new bitstring("",0);
	bool found = false;
	char foundChar;
	
	HuffmanTreeNode* node = tree->MainTree.top();
	int start = 0;
	
	for (int i = 0; i < compressed_file.size(); i++)
	{
		
		for (int j = 0; j < 8; j++)
		{
			
			char bit = (compressed_file[i ] >> (j % 8)) & 1;
			
			
			if (bit == 0)
			{
				node = node->leftNode;
			}
			if (bit == 1)
			{
				node = node->rightNode;
			}
			if (node->leftNode == nullptr && node->rightNode == nullptr)
			{
				XML_Text.push_back(node->data);
				node = tree->MainTree.top();
			}
		}
	}
	return XML_Text;
}

