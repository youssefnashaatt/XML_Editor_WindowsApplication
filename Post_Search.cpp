/*
 * Post_Search.cpp
 *
 *  Created on: Feb 3, 2023
 *      Author: engy
 */
#include "Post_Search.h"

string PostSearch(std::string word,vector<string> xml_cutted)
{
    int i = 0;
    std::string print = "";


    while(i < xml_cutted.size())
    {
        if(!(xml_cutted[i].compare(word + " ")))
        {
            if(!(xml_cutted[i - 1].compare("<topic>")))
            {
                while(xml_cutted[i].compare("<body>"))
                {
                    i--;
                }

                i++;
                print = xml_cutted[i];
           break;
            }
        }
        i++;
    }
    return print;
}


