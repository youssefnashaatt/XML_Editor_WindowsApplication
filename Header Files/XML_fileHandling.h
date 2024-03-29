/************************************************************************************************
 *MODULE:     Function used in Control Ecu
 *FILE NAME:   control_functions.c
 *FILE :       Description
 *AUTHOR:      Engy Mohamed
 ***********************************************************************************************/

#ifndef XMLCUTTER_H
#define XMLCUTTER_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define TAB  9



/*******************************************************************************
 *                                Functions Prototype                          *
 *******************************************************************************/
vector<string> XML_Parsing_Data(string data);
vector<string> xml_cutter(string filepath);
string vectortostring(vector<string>v);
void FileWithoutComments(vector <string>& file_lines_without_comments, vector <string>file_lines);

#endif
