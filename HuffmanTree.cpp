#include "HuffmanTree.h"
		void HuffmanTree::generateTree()
		{
			while (MainTree.size() > 1)
			{
				//hashel asghar etnen fel queue w a3mlhom left w right 
				HuffmanTreeNode* tempLeft = MainTree.top();
				MainTree.pop();
				HuffmanTreeNode* tempRight = MainTree.top();
				MainTree.pop();
				// create node with $ (3shan a3raf enaha msh character) its left and right are left and right
				HuffmanTreeNode* Node = new HuffmanTreeNode('$', (tempLeft->frequancy + tempRight->frequancy));
				Node->leftNode = tempLeft;
				Node->rightNode = tempRight;
				// push el node de 
				MainTree.push(Node);
			}
		}



		void HuffmanTree::generatebitCode(HuffmanTreeNode* root,string s)
		{
			*root->bitscode = bitstring(s, '0');
			cout << root->data << "/t" << s<<endl;
			if (root->leftNode )
			{
				string ss = { '0' };
				generatebitCode(root->leftNode, s + ss);
				
			}
			if (root->rightNode)
			{
				string ss = { '1' };
				generatebitCode(root->rightNode,s+ss);
			}
		}
		
