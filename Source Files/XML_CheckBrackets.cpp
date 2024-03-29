#include "XML_CheckBrackets.h"

using namespace std;



bool XML_CheckBrackets(string XML_Text)
{
	stack <char> stack;		//Creating a stack object named (stack) with data type char to push and pop brackets

	int line_index = 0;		//Line index of XML file increment each line
	int char_index = 0;		//Character index of each line in XML file

	//Looping on XML file character by character
	for(long long unsigned int i = 0 ; i < XML_Text.length() ; i++)
	{
		//if character is equivalent to ASCII of enter
		if(XML_Text.at(i) == '\n')
		{
			line_index++;	//Increment line index
			char_index = 0;	//Character index clear
		}

		//else any other character
		else
		{
			char_index++;	//increment character index
		}

		//if character is equivalent to tag opening '<'
		if(XML_Text.at(i) == TAG_OPENING)
		{
			//Check whether stack is empty or if there is another opened tag
			if(stack.empty())
			{
				stack.push(XML_Text.at(i));		//Push open tag into stack if empty
			}

			else
			{
				//if stack contain another open tag display error message on console with line and character index of error and return false (XML incorrect)
				cout << "\n\nUnclosed Bracket  Line: " << line_index << " Character: " << char_index << endl;
				return false;
			}
		}

		//if character is equivalent to tag closing '>'
		else if(XML_Text.at(i) == TAG_CLOSING)
		{
			//Check if stack contains its opened tag
			if(stack.top() == TAG_OPENING)
			{
				stack.pop();	//Pop opened tag from stack (Tag opened and closed properly)
			}

			else
			{
				//The top of stack isn't opened tag
				//Display error message on console with line and character index of error and return false (XML incorrect)
				cout << "\nError happened Line: " << line_index << " Character: " << char_index << endl;
				return false;
			}
		}
	}

	//At the end if stack not empty
	if(!stack.empty())
	{
		//Return false (XML incorrect)
		return false;
	}

	else
	{
		//Else if empty return true
		return true;
	}



}
