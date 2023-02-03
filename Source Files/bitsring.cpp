#include "bitsring.h"


void bitstring::bitstring_append(bitstring* code)
{
	int old = byteCapacity;
	if (byteCapacity <=(bitCount+code->bitCount)>>3)
	{
		
		byteCapacity = ((bitCount + code->bitCount + 7) >> 3) * 2; //doubling size dayman
		data.resize(byteCapacity);
		for (int i = old; i < byteCapacity; i++) { data.push_back(0); }

	}

	
	for (int b = 0; b < code->bitCount; b++)
	{
		
		int bit = (code->data[b >> 3] >> ((  b) & 7)) & 1;
		int i = (b + bitCount) >> 3;
		
		data[i] |= (bit << ((b +bitCount)& 7)); // &7 == rakam el bit kam fel byte 
	}
	bitCount += code->bitCount;
	
}

char bitstring::bitstring_get(int bitIndex)
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

void bitstring::bitstringclear()
{
	bitCount = 0;
	for (auto& c : data) c = 0;
}

void bitstring::bitstring_char_append(char c)
{
	bitCount++;
	if ((bitCount>>3)>byteCapacity)
	{
		if (byteCapacity == 0) byteCapacity = 1;
		byteCapacity *= 2;
		data.resize(byteCapacity);
		for (int i = byteCapacity/2; i < byteCapacity; i++) { data.push_back(0);
		}
	}
	data[bitCount >> 3] = (data[bitCount >> 3]) << 1;
	data[bitCount >> 3] |= (c&1);
	//data[bitCount >> 3] |= c << ((bitCount-1) & 7);
}
