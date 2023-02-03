#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class bitstring {
public:
	unsigned int bitCount=0, byteCapacity; //bits number and bytes number
	vector<char> data = { 0 };
	bitstring(string strdata,int bitOffset)
	{
		
		byteCapacity = (int(strdata.size() >> 3) + 1) *2;

		//std::cout << "whyyynott!!!";
		// changing bits to bytes to allocate data memory 
		data.resize(byteCapacity); 
		
		//memset(&data, 0, byteCapacity);//o(N)
		for (int i = 0; i < byteCapacity; i++) { data.push_back(0);   }
			bitCount = strdata.size() ;
			//std::cout << bitCount;
		
			for (int b = 0; b < bitCount; b++)
			{
				int i = (b+bitOffset) >> 3;
				int bit = strdata[b] & 1; //khdt el byte eli 3yzaha ba3d keda el bit w 3mlt shift w safart ba2y el bits
				data[i] |= bit << ((b+bitOffset) & 7); // &7 == rakam el bit kam fel byte 
				cout << int(bit) << endl;
			}
			//cout << "khlsna bits";
	}  

~bitstring(){}
void bitstring_append(int bitOffset,string strdata);
int bitstring_get(int bitIndex);
void bitstring_set(int bit, int bitindex);

};