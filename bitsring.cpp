#include "bitsring.h"

void bitstring::bitstring_append(int bitOffset,string strdata )
{
	bitCount += strdata.size();
	if (byteCapacity < ceil(bitCount / 8))
	{
	byteCapacity = ((bitCount+7) >>3)*2; //doubling size dayman
	//data.resize(byteCapacity);
	}
	
	
		for (int b = 0; b <= strdata.size(); b++)
		{
			int i =( b +bitOffset)>> 3;
			int bit = strdata[ b >> 3] >> ((bitOffset + b) & 7) & 1; //khdt el byte eli 3yzaha ba3d keda el bit w 3mlt shift w safart ba2y el bits
			data[i] |= bit << (b & 7); // &7 == rakam el bit kam fel byte 
		}
		
}

int bitstring::bitstring_get(int bitIndex)
{
	int i = bitIndex >> 3;
	if (bitIndex >= bitCount) return -1;
	return data[i] >> (bitIndex & 7) & 1;
}



void bitstring::bitstring_set(int bit, int bitIndex)
{
	int i = bitIndex >> 3;
	if (bit)
		data[i] |= 1 << (bitIndex & 7);
	else
		data[i] &= 0 << (bitIndex & 7);
}
