/*
 * main.cpp
 *
 *  Created on: Dec 13, 2022
 *      Author: engy
 */


#include "main.h"


int main(void)
{
	vector <string> file_lines = xml_cutter("C:\\D\\Senior 1\\Data Structure Project\\New Text Document.txt");

	vector <string> file_lines_without_comments;
	FileWithoutComments(file_lines_without_comments, file_lines);
	        file_lines = file_lines_without_comments;

	vector <Node*> nodes;
	        XML_tree tree;
	        stack <int> tags;
	        XML_tree_creation(file_lines, nodes ,tree , tags);

	        string ss = xml_to_json(tree);
cout << ss<<endl;
}
