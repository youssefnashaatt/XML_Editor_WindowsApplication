/************************************************************************************************
 *FILE NAME:   XML_fileHandling.cpp
 *Description: This file is used to convert the xml file into a vector of strings
 *AUTHOR:      Engy Mohamed
 ***********************************************************************************************/
#include "XML_fileHandling.h"

/*******************************************************************************
 *                              Functions  Definitions                         *
 *******************************************************************************/


//make one tag per line atmost
vector<string> xml_cutter(string filePath)
{
	vector <string> xmlcutted;
	ifstream FILE_text;
	int startindex, endindex;
	string input;
	string line;

	FILE_text.open(filePath);

	while (getline(FILE_text, input))
	{
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == '<')
			{
				startindex = i;
				for (i; i < input.length(); i++)
				{
					if (input[i] == '>')
					{
						endindex = i;
						break;
					}
					else
					{
						endindex = i;
					}


				}
			}
			else
			{
				if (int(input[i]== TAB))
				{
					continue;
				}
				else
				{
					startindex = i;
					for (i; i < input.length(); i++)
					{
						if (input[i] == '<')
						{
							endindex = i - 1;
							i--;
							break;
						}
						else
						{
							endindex = i;
						}

					}
				}

			}
			line = input.substr(startindex, (endindex - startindex + 1));
			if (line[0] != '<')
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == '"')
						line.replace(i, 1, " ");
				}
			// to avoid multi lines comments
			if (line[0] != ' ' || line[1] != ' ' || line[2] != ' ')
			{
				if (line.find_first_not_of(' ') != -1)
				{
					if (int(line[line.find_first_not_of(' ')]) != 9)
					{
						xmlcutted.push_back(line);
					}
				}
			}
		}
	}

	FILE_text.close();
	return xmlcutted;
}

string vectortostring(vector<string>v)
{
	string s = "";
	for (int i = 0; i < v.size(); i++)
	{
		s = s + v[i] + "\n";
	}
	return s;
}

void FileWithoutComments(vector <string>& file_lines_without_comments, vector <string>file_lines) {
	for (int i = 0; i < file_lines.size(); i++)
	{
		if (file_lines[i][0] == '<' && file_lines[i][1] == '?')
		{
			continue;
		}
		if (file_lines[i][0] == '<' && file_lines[i][1] == '!')
		{
			continue;
		}
		else
		{
			file_lines_without_comments.push_back(file_lines[i]);
		}
	}
}
