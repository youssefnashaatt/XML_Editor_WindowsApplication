#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class bitstring {
public:
	unsigned int bitCount=0, byteCapacity; //bits number and bytes number
	vector<unsigned char> data = { 0 };
	bitstring(string strdata,int bitOffset)
	{
		if (strdata == "") { bitCount = 0; byteCapacity = 0; return; }
		byteCapacity = (int(strdata.size() >> 3) + 1) *2;

		
		// changing bits to bytes to allocate data memory 
		data.resize(byteCapacity); 
		
		//memset(&data, 0, byteCapacity);//o(N)
		for (int i = 0; i < byteCapacity; i++) { data.push_back(0);   }
			bitCount = strdata.size();
		
		
			
			for(int b=0;b<bitCount;b++)
			{

				int i = (b) >> 3;
				int bit = strdata[b] & 1; //khdt el byte eli 3yzaha ba3d keda el bit w 3mlt shift w safart ba2y el bits
				data[i] |= bit << ((bitCount + bitOffset - b-1 ) & 7);  //(b & 7);
				 
			}
			
	}  
	bitstring(string strdata, int bitOffset, int bytesNumber)
	{ 
		byteCapacity = bytesNumber;
		if (strdata == "") { bitCount = 0; return; }
		
		// changing bits to bytes to allocate data memory 
		data.resize(byteCapacity);

		//memset(&data, 0, byteCapacity);//o(N)
		for (int i = 0; i < byteCapacity; i++) { data.push_back(0); }
		bitCount = strdata.size();
		for (int b = 0; b < bitCount; b++)
		{

			int i = (b + bitOffset) >> 3;
			int bit = strdata[b] & 1; //khdt el byte eli 3yzaha ba3d keda el bit w 3mlt shift w safart ba2y el bits
			data[i] |= bit << ((bitCount + bitOffset - b - 1) & 7);
			
		}
	}
~bitstring(){}
void bitstring_append(bitstring* code);
char bitstring_get(int bitIndex);
void bitstring_set(int bit, int bitindex);
void bitstringclear();
void bitstring_char_append(char c);
};