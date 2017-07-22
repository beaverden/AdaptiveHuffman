#pragma once
#include <istream>
#include "HuffmanTree.h"

typedef uint_fast8_t BITS;

class FKG_Decoder
{
public:
	FKG_Decoder();
	void Decode(std::istream& input, std::ostream& output);
	bool EndReached();

private:
	void FKG_Decoder::NextInputBit(std::istream& input, BITS &value);
	void FKG_Decoder::ReadWholeCharacter(std::istream& input, BITS &value);

	BITS buffer;
	HuffmanTree tree;
	bool endOfInput;
	bool firstCharacter;
	unsigned int bufferPosition;
	
	
};