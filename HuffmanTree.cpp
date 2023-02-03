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


		void HuffmanTree::generatebitCode(HuffmanTreeNode* root,string s, bool firstNodeFlag)
		{
			
			
			if (root->leftNode )
			{
			
				string ss = { '0' };
				
				generatebitCode(root->leftNode,  ss+s,false );
				
			}
			if (root->rightNode)
			{
				
				string ss = { '1' };
				
				generatebitCode(root->rightNode,ss+s,false);
			}

			if (root->data != '$')
			{
				
				root->bitscode = new bitstring(s, 0);
				alphaBitstring[root->data] = root->bitscode;
				
			}
		}

		/*void HuffmanTree::degeneratebitCode(HuffmanTreeNode* root, string s, bool firstNodeFlag)
		{

			if (root->leftNode)
			{
				
				string ss = { '0' };
				
				degeneratebitCode(root->leftNode, ss+s, false);

			}
			if (root->rightNode)
			{
				
				string ss = { '1' };
				
				degeneratebitCode(root->rightNode, ss+s, false);
			}

			if (root->data != '$')
			{
				
				root->bitscode = new bitstring(s, 0);
				alphaBitstring[root->data] = root->bitscode;
				
			}
		}*/
		char HuffmanTree::bitstringSearch(bitstring* code, bool* found)
		{
			*found = false;
			for (int i = 0; i < 256; i++)
			{
				if (alphaBitstring[i] == nullptr) {
					continue;
				}
				else if ((code->bitCount == alphaBitstring[i]->bitCount))// && code->data[0] == alphaBitstring[i]->data[0])
				{
					for (int j = 0; j < alphaBitstring[i]->bitCount / 8 + 1; j++)
					{
						if (code->data[j] == alphaBitstring[i]->data[j])
						{
							*found = true;
							
						}
						else {
							
							*found = false; break;
						}
					}
				}	
					if (*found == true) return i;
			}
			return 0;
		}


				
				
		
