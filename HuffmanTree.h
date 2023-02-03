#ifndef HUFFMANTREE
#define HUFFMANTREE
#include <queue>
#include <vector>
using namespace std;
#include "Prettify_DS_28_1/bitsring.h"


class HuffmanTreeNode
{
public:
	char data;//character
	int frequancy; //number of repeatation 

	HuffmanTreeNode* leftNode;
	HuffmanTreeNode* rightNode;
	bitstring *bitscode;
	HuffmanTreeNode(char data, int frequancy)
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
	priority_queue <HuffmanTreeNode*, vector<HuffmanTreeNode*>, compare> MainTree;
	void generateTree(); 
	void generatebitCode(HuffmanTreeNode* root, string s);
};
#endif