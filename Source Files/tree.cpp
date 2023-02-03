/******************************************************************************
 * File Name: tree.c
 * Description: cpp file for the tree DS
 * Author: Engy Mohamed
 *******************************************************************************/
#include "tree.h"

/* we use the scope resolution operator to define a function outside its class "XML_tree" */

XML_tree::XML_tree()   /* Define the constructor of the XML_tree class */
{
	root = NULL;       /* root points to null at the begaining as there's no nodes in the tree*/
}


bool XML_tree::have_children(Node* n)
{
	if (n->TAG_children.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/***************************Define Adders of the class******************************************/
void XML_tree::add_root(Node* r)
{
	root = r;
}

Node* XML_tree::add_node(string name)
{
	Node* n;
	n = new Node(name);
	return n;
}

void XML_tree::add_data(Node* n, string text)
{
	n->TAG_data += text;
}

void XML_tree::add_child(Node* parent, Node* child)
{
	parent->TAG_children.push_back(child);
	child->TAG_parent = parent;
}


/***************************Define Getters of the class******************************************/
Node* XML_tree::get_root()
{
	return root;
}

vector<Node*> XML_tree::get_children(Node* n)
{
	return n->TAG_children;
}

string XML_tree::get_data(Node* n)
{
	return n->TAG_data;
}

string XML_tree::get_tag(Node* n)
{
	return n->TAG_name;
}


void XML_tree_creation(vector<string> file_lines, vector<Node*>& nodes, XML_tree& tree, stack<int>& tags)
{


	for (int i = 0; i < file_lines.size(); i++)
	{
		// opening tags
		if (file_lines[i][0] == '<' && file_lines[i][1] != '/')
		{
			int index;

			// get tag and att
			for (int j = 1; j < file_lines[i].length(); j++)
			{
				index = j;
				if (file_lines[i][j] == ' ')
				{
					//First white space in the tag
					break;
				}
			}

			string tag = file_lines[i].substr(1, index - 1);

			nodes.push_back(tree.add_node(tag));//decalre a new tag
			if (tags.size() == 0)
			{
				tree.add_root(nodes[nodes.size() - 1]);//add thre root to the tree
			}
			else
			{
				tree.add_child(nodes[tags.top()], nodes[nodes.size() - 1]);//add a child to the last opened tag
			}
			tags.push(nodes.size() - 1);
			//self closing tag
			if (file_lines[i][file_lines[i].length() - 2] == '/')
				tags.pop();
		}

		//Closing tag
		else if (file_lines[i][0] == '<' && file_lines[i][1] == '/')
		{
			tags.pop();//remove the last opend tag (closed) to deal with the next tag to it
		}
		//Data
		else
		{
			tree.add_data(nodes[tags.top()], file_lines[i]);//add data to the last opened tag

		}
	}

}

// function to sort children
void XML_tree_sort_children(vector<Node*>& children)
{
	Node* temp_ptr;
	for (int i = 0; i < children.size(); i++)
	{
		for (int j = i + 1; j < children.size(); j++)
		{
			if ((children[j]->TAG_name) < (children[i]->TAG_name))
			{
				temp_ptr = children[j];
				children[j] = children[i];
				children[i] = temp_ptr;
			}
		}
	}
}



