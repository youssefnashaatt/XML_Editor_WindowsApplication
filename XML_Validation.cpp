/*
 * XMLValidation.cpp
 *
 *  Created on: Feb 2, 2023
 *      Author: Youssef
 */

#include "XML_Validation.h"
#include <stack>

XML_Validation::XML_Validation() {
    // TODO Auto-generated constructor stub

}

XML_Validation::~XML_Validation() {
    // TODO Auto-generated destructor stub
}




int XML_Validation::XML_Validate(string XML_Text)
{
    stack <string> Tags_stack;
    stack <char> Brackets_stack;

    Inconsistent_Bracket = false;
    Incorrect_Tag_Syntax = false;

    int index = 0;
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

        /************************************************************************************/

        if(XML_Text.at(index) == TAG_OPENING)
        {
            /*Check on Brackets Consistency*/

            if(Brackets_stack.empty())
            {
                Brackets_stack.push(XML_Text.at(index));		//Push open tag into stack if empty
            }

            else
            {
                //if stack contain another open tag display error message on console with line and character index of error and return false (XML incorrect)
                //Return Index
                Inconsistent_Bracket = true;
                return (line_index*500) + (char_index);
            }


            /*Check for Code Syntax Consistency*/
            index++;

            if(XML_Text.at(index) != '/')
            {
                string temp_open;
                temp_open = XML_Text.at(index);
                index++;

                while(XML_Text.at(index) != TAG_CLOSING)
                {
                    temp_open = temp_open + XML_Text.at(index);
                    index++;
                }

                /*Checking for Bracket Consistency*/
                /*Check if stack contains its opened tag*/
                if(Brackets_stack.top() == TAG_OPENING)
                {
                    Brackets_stack.pop();	//Pop opened tag from stack (Tag opened and closed properly)
                }

                else
                {
                    //The top of stack isn't opened tag
                    //Display error message on console with line and character index of error and return false (XML incorrect)
                    Inconsistent_Bracket = true;
                    return (line_index*500) + (char_index);
                }

                /*Push Tag to Tags_stack*/
                Tags_stack.push(temp_open);
            }

            else if(XML_Text.at(index) == '/')
            {
                string temp_close;
                index++;
                temp_close = XML_Text.at(index);

                index++;

                while(XML_Text.at(index) != TAG_CLOSING)
                {
                    temp_close = temp_close + XML_Text.at(index);
                    index++;
                }


                /*Checking for Bracket Consistency*/
                /*Check if stack contains its opened tag*/
                if(Brackets_stack.top() == TAG_OPENING)
                {
                    Brackets_stack.pop();	//Pop opened tag from stack (Tag opened and closed properly)
                }

                else
                {
                    //The top of stack isn't opened tag
                    //Display error message on console with line and character index of error and return false (XML incorrect)
                    Inconsistent_Bracket = true;
                    return (line_index*500) + (char_index);
                }


                //Checking if syntax is correct
                if(!(temp_close.compare(Tags_stack.top())))
                {
                    Tags_stack.pop();
                }

                else
                {
                    Tags_stack.pop();
                    Incorrect_Tag_Syntax = true;
                    return (line_index * 500) + char_index;
                }
            }

        }


        index++;
    }


    /*Both stacks aren't empty*/
    if(!(Tags_stack.empty() || Brackets_stack.empty()))
    {
        //InConsistent XML
        Inconsistent_Bracket = true;
        Incorrect_Tag_Syntax = true;
        return (line_index * 500) + char_index;
    }

    /*Tags stack is empty & Brackets stack is not*/
    else if(Tags_stack.empty() && !Brackets_stack.empty())
    {
        Inconsistent_Bracket = true;
        return (line_index * 500) + char_index;
    }

    /*Tags stack is not empty & Brackets stack is empty*/
    else if(!Tags_stack.empty() && Brackets_stack.empty())
    {
        Incorrect_Tag_Syntax = true;
        return (line_index * 500) + char_index;
    }

    else
    {
        return 0;
    }

}
