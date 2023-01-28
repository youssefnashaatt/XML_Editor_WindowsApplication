#include "prettify.h"

vector<string> TextToString(string file) {
    string copyString;
    vector<string> fileStrings(1000);
    int counter = 0;
    for (auto c : file)
    {
        if (c == ' ')
        {
            fileStrings[counter] = copyString;
            counter++;
            copyString.clear();
        }
        else if (c == '>')
        {
            copyString += c;
            fileStrings[counter] = copyString;
            counter++;
            fileStrings[counter] = "\n";
            counter++;
            copyString.clear();

        }
        else if (c == '<')
        {
            fileStrings[counter] = copyString;
            counter++;
            fileStrings[counter] = "\n";
            counter++;
            copyString.clear();
            copyString += c;
        }
        else if (c == '-'|| c=='\t'||c=='\n') continue;
        else copyString += c;
    }
    fileStrings[counter] = copyString;
    counter++;
    copyString.clear();


   // for (auto c : fileStrings) cout << c ;
    return fileStrings;
}
vector<string> prettify(string file)
{
    //removing tabs and making strings
    vector<string> strings = TextToString(file);
    // adding tabs 
    int counters = 0;
    string TabsString="";
   
    for (int i=0;i<strings.size();i++)
    {
       
        
        if (strings[i][0] == '\t') continue;
        if (strings[i][0] == '<' && strings[i][1] != '/')
        {
            TabsString.push_back('\t');
           
        }
        else if (strings[i][0] == '<' && strings[i][1] == '/')
        {
            TabsString.pop_back();
            strings[i - 1].pop_back();
        }
        if (strings[i] == "\n")
        {
            if (TabsString.empty()) continue;
           strings.insert(strings.begin()+i+1, TabsString);
        }
    }
    return strings;
}