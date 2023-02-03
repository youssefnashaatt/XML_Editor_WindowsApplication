/******************************************************************************
 * File Name: tree.h
 * Description: Header file for the tree DS
 * Author: Engy Mohamed
 *******************************************************************************/
#ifndef TREE_H
#define TREE_H


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*the node include the name of each tag and data within this tag also pointers to
 * parent and children of this tag*/
struct Node
{
	string TAG_data;               /*data which included within the tag*/
	string TAG_name;           /*the tag name in the xml file */
	Node* TAG_parent;              /*pointer to the parent node */
	vector<Node*>TAG_children;     /*a vector of pointers to the children nodes */



	Node(string tag_name, string Data = "")   /* Public constructor to the Node struct which*/
	{                                     /* initialize all the members of the struct */
		TAG_parent = NULL;
		TAG_data = Data;
		TAG_name = tag_name;
		TAG_children = {};
	}
};


/* Defining the tree class */
class XML_tree
{
	Node* root;

public:
	XML_tree();                                /* Public constructor of the class */

	bool have_children(Node* n);

	/*******************************Adders of the class******************************************/
	Node* add_node(string tag_name);
	void add_data(Node* n, string text);
	void add_child(Node* parent, Node* child);
	void add_root(Node* r);

	/********************************Getters of the class ***************************************/
	vector<Node*> get_children(Node* n);
	string get_data(Node* n);
	string get_tag(Node* n);
	Node* get_root();

};

/********************************Functions Prototype ********************************************/
void XML_tree_creation(vector<string> file_lines, vector<Node*>& nodes, XML_tree& tree, stack<int>& tags);
void XML_tree_sort_children(vector<Node*>& children);

#endif
