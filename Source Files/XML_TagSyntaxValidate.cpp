#include "XML_TagSyntaxValidate.h"

using namespace std;


bool XML_TagSyntaxValidate(string XML_Text)
{
	stack <string> stack;

	int index;
	int line_index = 0;
	int char_index = 0;

	while(index < XML_Text.length())
	{

		if(XML_Text.at(index) == '\n')
		{
			line_index++;
			char_index = 0;
		}

		else
		{
			char_index++;
		}



		if(XML_Text.at(index) == '<')
		{
			index++;

			if(XML_Text.at(index) != '/')
			{
				string temp_open;
				temp_open = XML_Text.at(index);
				index++;

				while(XML_Text.at(index) != '>')
				{
					temp_open = temp_open + XML_Text.at(index);
					index++;
				}

				stack.push(temp_open);
			}

			else if(XML_Text.at(index) == '/')
			{
				string temp_close;
				index++;
				temp_close = XML_Text.at(index);

				index++;

				while(XML_Text.at(index) != '>')
				{
					temp_close = temp_close + XML_Text.at(index);
					index++;
				}


				//Checking if syntax is correct
				if(!(temp_close.compare(stack.top())))
				{
					stack.pop();
				}

				else
				{
					cout << "\n\nSyntax Error  Line:" << line_index << " Character: " << char_index << endl;
					stack.pop();
					return false;
				}
			}

		}


		index++;
	}


	if(!stack.empty())
	{
		//Return false (XML incorrect)
		cout << "\n\n" <<stack.top() << " tag is not closed\n\n" << endl;
		return false;
	}

	else
	{
		//Else if empty return true
		return true;
	}

}
