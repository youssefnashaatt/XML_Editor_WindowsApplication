#ifndef Helper_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <fstream>


using namespace std;

bool isData(char x);
string Erase_Spaces(string str);
char Get_Type(string str);
string Get_Tag(string Open_Tag);
bool Compare_Tags(string Open_Tag, string Close_Tag);

#endif // HELPER_FUNCTIONS_H
