#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "json.h"
#include "tree.h"
#include "prettify.h"
#include "XML_CheckBrackets.h"
#include "XML_fileHandling.h"
#include "XML_Minifying.h"
#include "XML_TagSyntaxValidate.h"


using namespace std;

string File_Path;


string Open_File(string File_Path);
void Operations_Processing(void);

int main(void)
{
	cout << "Please enter File Path:" << endl;
	cin >> File_Path;


	Operations_Processing();



	while(1)
	{

	}

	return 0;
}



void Operations_Processing(void)
{
	char Operation_Choice;



	cout << "\nEnter a character to choose an operation" << endl;
	cout << "A) XML_Validation		B)Convert XML to JSON		C)XML_Minifying 		D)Prettifying" << endl;
	cin >> Operation_Choice;


	if(Operation_Choice == 'a' || Operation_Choice == 'A')
	{
		string XML_Text = Open_File(File_Path);

		/*****************************************************************/

		if(XML_CheckBrackets(XML_Text))
		{
			if(XML_TagSyntaxValidate(XML_Text))
			{
				cout << "\nXML File Validate correctly" << endl;
				Operations_Processing();
			}

			else
			{
				cout << "\nIncorrect XML..Please Try again\n\n\n" << endl;
				main();
			}
		}

	}



	else if(Operation_Choice == 'b' || Operation_Choice == 'B')
	{
		vector <string> file_lines = xml_cutter(File_Path);
		vector <string> file_lines_without_comments;
		FileWithoutComments(file_lines_without_comments, file_lines);
		file_lines = file_lines_without_comments;
		vector <Node*> nodes;
		XML_tree tree;
		stack <int> tags;
		XML_tree_creation(file_lines, nodes ,tree , tags);
		string ss = xml_to_json(tree);
		cout << ss<<endl;

		Operations_Processing();
	}



	else if(Operation_Choice == 'c' || Operation_Choice == 'C')
	{
		string XML_Text = Open_File(File_Path);

		if(XML_CheckBrackets(XML_Text))
		{
			cout << "\n\n" << endl;
			cout << XML_Minifying(XML_Text) << endl;
			cout << "\n" << endl;

			Operations_Processing();
		}

		else
		{
			cout << "Incorrect XML..Please Try again" << endl;
			main();
		}
	}


	else if(Operation_Choice == 'd' || Operation_Choice == 'D')
	{
		string XML_Text = Open_File(File_Path);

		if(XML_CheckBrackets(XML_Text))
		{
			vector<string> m = prettify(XML_Text);
			for (auto x : m) cout << x;

			Operations_Processing();
		}

		else
		{
			cout << "Incorrect XML..Please Try again" << endl;
			main();
		}

	}

	else
	{
		cout << "No correct character" << endl;
	}

}



string Open_File(string File_Path)
{
	fstream File;			//Creating an fstream object named (File)
	stringstream XML_File;		//Creating stringstream object to store text in file


	//Open File in C++ Project
	File.open(File_Path, ios_base::in);


	//Reading File in streamstring object
	XML_File << File.rdbuf();

	string XML_Text;

	XML_Text = XML_File.str();

	return XML_Text;

}


