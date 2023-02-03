#include "XML_Data.h"

vector<string> XML_Parsing_Data(string data){
    bool Inside_Tag = false, Inside_Data = false, Outside_Tag = false, Outside_Data = false;
    vector<string> XML;
    string New_Str = "", Temp = "";

    for (unsigned int i = 0; i < data.length(); i++){
        // Add Begin of Tag
        if (data[i] == '<'){
            Inside_Tag = true;		Outside_Tag = false;
            Inside_Data = false;	Outside_Data = false;
            if (New_Str != ""){
                XML.push_back(Erase_Spaces(New_Str));
                New_Str = "";
            }
        }

        // Add end of Tag
        else if (data[i] == '>'){
            Inside_Tag = false;		Outside_Tag = true;
            Inside_Data = false;	Outside_Data = false;
            New_Str += data[i];
            XML.push_back(New_Str);
            New_Str = "";
        }

        // Get Data characters and the middle spaces
        if (isData(data[i]) && !Inside_Tag){
            Outside_Tag = false;
            Inside_Data = true;		Outside_Data = false;
            New_Str += Temp;
            Temp = "";
        }

        // Add Spaces to Temperory string to check if they are mid spaces or last spaces
        if ((data[i] == ' ' || data[i] == '\n' || data[i] == '\t') && Inside_Data){
            Inside_Tag = false;
            Inside_Data = false;	Outside_Data = true;
            Temp += data[i];
        }

        // Add Tag Names and Attributes
        if (Inside_Tag)
            New_Str += data[i];

        // Add Tag Value without begin (Spaces or \t or \n)
        if (Inside_Data && !Outside_Tag)
            New_Str += data[i];
    }

    return XML;
}
