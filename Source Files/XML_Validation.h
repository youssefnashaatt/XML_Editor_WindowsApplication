/*
 * XMLValidation.h
 *
 *  Created on: Feb 2, 2023
 *      Author: Youssef
 */

#ifndef XMLVALIDATION_H_
#define XMLVALIDATION_H_

#include <iostream>

using namespace std;

#define TAG_OPENING '<'
#define TAG_CLOSING '>'

class XML_Validation {
public:
    XML_Validation();
    virtual ~XML_Validation();
    int XML_Validate(string XML_Text);
    bool Inconsistent_Bracket;
    bool Incorrect_Tag_Syntax;


private:


};

#endif /* XMLVALIDATION_H_ */
