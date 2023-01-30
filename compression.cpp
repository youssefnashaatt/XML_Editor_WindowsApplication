#include "compression.h"
#include <vector>
void generateCode(string XML_Text)
{
	// calc freq 
	vector <unsigned int> charFreq(256,0);
	for (auto c : XML_Text) charFreq[c]++;
	// generate nodes 
	HuffmanTree *tree = new HuffmanTree();
	for (int i = 0; i < 256; i++)
	{
		HuffmanTreeNode* temp = new HuffmanTreeNode(i, charFreq[i]);
		tree->MainTree.push(temp);
	}
	// push to tree
	tree->generateTree(); // kedaa 3ndy tree
	// generate bitstring of each char 
	tree->generatebitCode(tree->MainTree.top(), 0);


}
