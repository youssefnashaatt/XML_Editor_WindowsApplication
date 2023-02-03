#include "Helper_Functions.h"

bool isData(char x){
    if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9'))
        return true;
    return false;
}

string Erase_Spaces(string str){
    int count = 0, start, end;

    // Delete Begining Spaces
    while (str[count] == ' ' || str[count] == '\n' || str[count] == '\t'){
        count++;
    }
    start = count;

    // check if the whole string is spaces
    if (start == str.length())
        return "";
    count = str.length() - 1;

    // Delete End Spaces
    while (str[count] == ' ' || str[count] == '\n' || str[count] == '\t'){
        count--;
    }
    end = count;

    return str.substr(start, end-start+1);
}

char Get_Type(string str){
    if(str[0] == '<'){
        if(str[1] == '/')	return 'C';
        else if(str[1] == '!' && str[2] == '-' && str[3] == '-')	return 'C';
        return 'O';
    }
    return 'V';
}

string Get_Tag(string Open_Tag){
    string open = "";
    for (unsigned int i = 1; i < Open_Tag.length(); i++){
        while (Open_Tag[i] != ' ' && Open_Tag[i] != '>'){
            open += Open_Tag[i++];
        }
        break;
    }
    return open;
}

bool Compare_Tags(string Open_Tag, string Close_Tag){
    string open = "";
    open = Get_Tag(Open_Tag);
    return (Erase_Spaces(open) == Erase_Spaces(Close_Tag.substr(2, Close_Tag.length()-3)));
}
