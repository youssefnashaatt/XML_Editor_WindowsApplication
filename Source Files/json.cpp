/******************************************************************************
 * File Name: json.cpp
 * Description: Convert the xml into a json file
 * Author: Engy Mohamed
 *******************************************************************************/
#include "json.h"


/*******************************************************************************
 *                               Functions Definitions                         *
 *******************************************************************************/

//to determine type of data
bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789.") == std::string::npos;
}

//function used to split attr
vector <string> split(string s, string delimiter)
{
	vector<string> v;
	int pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {

		token = s.substr(0, pos);
		v.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	v.push_back(s);
	return v;
}

string tab(int n)
{
	string s = "";
	if (n < 0)
		return s;
	for (int i = 0; i < n; i++)
	{
		s += "\t";
	}

	return s;
}


vector <int> sortchildren(vector<Node*> &children)
{
	vector <int> repeated;
	Node* temp_ptr;
	string temp;

	for (int i = 0; i < children.size()-1; i++)
	{
		for (int j = i + 1; j < children.size(); j++) {
			if ((children[j]->TAG_name) < (children[i]->TAG_name))
			{
				temp_ptr = children[j];
				children[j] = children[i];
				children[i] = temp_ptr;
			}
		}
	}
	if (children.size() > 0) {
		temp = children[0]->TAG_name;
		repeated.push_back(1);
		int j = 0;
		for (int i = 1; i < children.size(); i++) {
			if ((children[i]->TAG_name) == temp) {
				repeated[j]++;
			}
			else
			{
				repeated.push_back(1);
				j++;
				temp = children[i]->TAG_name;
			}
		}

	}
	return repeated;
}

vector <int> firstrepeats(vector <int> repeated)
{
	vector <int> first_repeats;
	for (int i = 0; i < repeated.size(); i++)
	{
		if (repeated[i] == 1)
		{
			first_repeats.push_back(0);
		}
		else
		{
			first_repeats.push_back(1);
			for (int j = 0; j < repeated[i] - 1; j++)
			{
				first_repeats.push_back(0);
			}
		}
	}

	return first_repeats;
}


vector <int> isrepeated(vector <int> repeated)
{
	vector <int> isrepeated;
	for (int i = 0; i < repeated.size(); i++)
	{
		if (repeated[i] == 1)
		{
			isrepeated.push_back(1);
		}
		else
		{
			for (int j = 0; j < repeated[i]; j++)
			{
				isrepeated.push_back(repeated[i]);
			}
		}
	}

	return isrepeated;
}


void print_node(Node* node_ptr, int& tab,string& json ,int repeated )
{

	if (repeated == 1)
	{
		if (node_ptr->TAG_children.size())
		{
			for (int i = 0; i < tab; i++)
			{
				json += "  ";
			}
			json += "\"" + node_ptr->TAG_name + "\": {\n";
			tab++;

			for (int i = 0; i < tab; i++)
			{
				json += "  ";

			}
			vector <int> rep = sortchildren(node_ptr->TAG_children);
			vector <int> isrep = isrepeated(rep);
			vector <int> fistrepeated = firstrepeats(rep);
			for (int i = 0; i < node_ptr->TAG_children.size(); i++)
			{
				if ( !fistrepeated[i]  && isrep[i] > 1 && !node_ptr->TAG_children[i]->TAG_children.size())
				{
					continue;
				}
				print_node(node_ptr->TAG_children[i], tab, json, isrep[i]);
			}
			tab--;
			for (int i = 0; i < tab; i++)
			{
				json += "  ";

			}
			json += "}\n";

		}
		else
		{

			vector<int> repeated = sortchildren(node_ptr->TAG_parent->TAG_children);
			for (int i = 0; i < tab; i++)
			{
				json += "  ";
			}
			json += "\"" + node_ptr->TAG_name + "\": " + "\"" + node_ptr->TAG_data +"\"";
			if (node_ptr != node_ptr->TAG_parent->TAG_children[node_ptr->TAG_parent->TAG_children.size()-1])
			{
				json += ",\n";
				for (int i = 0; i < tab; i++)
				{
					json += "  ";
				}
			}
			else
			{
				tab--;
				json += "\n";
				for (int i = 0; i < tab; i++)
				{
					json += "  ";
				}
				json += " }\n";



			}

		}

	}

	if (repeated > 1)
	{
		vector <int> repeatedd = sortchildren(node_ptr->TAG_parent->TAG_children);
		vector <int> fistrepeated = firstrepeats(repeatedd);
		int num;
		for (int j = 0; j < node_ptr->TAG_parent->TAG_children.size(); j++)
		{
			if (node_ptr == node_ptr->TAG_parent->TAG_children[j])
			{
				num = j;
			}
		}
		if (fistrepeated[num])
		{
			json += "\"" + node_ptr->TAG_name + "\": [\n";
		}
		tab++;
		for (int i = 0; i <tab; i++)
		{
			json += "  ";
		}

		if (node_ptr->TAG_children.size())
		{
			json += " {\n";
			tab++;
			vector <int> rep = sortchildren(node_ptr->TAG_children);
			vector <int> isrep = isrepeated(rep);
			for (int i = 0; i < node_ptr->TAG_children.size(); i++)
			{
				print_node(node_ptr->TAG_children[i], tab, json, isrep[i]);
				if (i != node_ptr->TAG_children.size() -1)
				{
					json += ",";
				}
				json += "\n";
			}

			if (!fistrepeated[num])
			{
				for (int i = 0; i < tab; i++)
				{
					json += "  ";
				}
				json += "]\n";
			}


			tab--;
		}

		else
		{
			vector <int> isrep = isrepeated(repeatedd);
			for (int i = 0; i < isrep[num]; i++)
			{
				json += node_ptr->TAG_parent->TAG_children[num+i]->TAG_data;
				if (i != isrep[num]-1)
				{
					json += ",\n";
					for (int k = 0; k < tab; k++)
					{
						json += "  ";
					}

				}
				else
				{
					json += "\n";
					tab--;
					for (int k = 0; k < tab; k++)
					{
						json += "  ";
					}
					json += "]\n";
					for (int k = 0; k < tab; k++)
					{
						json += "  ";
					}
				}
			}
		}
	}
}


string xml_to_json(XML_tree tree) {

	string  json = "";
	int tab = 1;
	json += "{\n" ;
	print_node(tree.get_root(), tab ,json , 1);
	json+="\n";
	json += "}\n" ;
	return json;
}


