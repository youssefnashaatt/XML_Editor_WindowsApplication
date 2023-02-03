#ifndef HUFFMANTREE
#define HUFFMANTREE
#include <queue>
#include <vector>
using namespace std;
#include "Prettify_DS_28_1/bitsring.h"



class HuffmanTreeNode
{
public:
	unsigned char data;//unsigned character
	int frequancy; //number of repeatation 

	HuffmanTreeNode* leftNode;
	HuffmanTreeNode* rightNode;
	bitstring *bitscode;
	HuffmanTreeNode(unsigned char data, int frequancy)
	{
		this->data = data;
		this->frequancy = frequancy;
		leftNode = rightNode = nullptr;
		bitscode = nullptr;
	}
};

class compare {
public:
	bool operator() (HuffmanTreeNode* a, HuffmanTreeNode* b) {
		return (a->frequancy > b->frequancy);
	}
};

class HuffmanTree
{
public:
	vector<bitstring*> alphaBitstring;
	priority_queue <HuffmanTreeNode*, vector<HuffmanTreeNode*>, compare> MainTree;
	HuffmanTree()
	{
		for (int i = 0; i < 256; i++) alphaBitstring.push_back(nullptr);
	}
	void generateTree(); 
	void generatebitCode(HuffmanTreeNode* root, string s, bool firstNodeFlag);
	char bitstringSearch(bitstring* code, bool* found);
	void degeneratebitCode(HuffmanTreeNode* root, string s, bool firstNodeFlag);

};
#endif