#include "stdafx.h"
#include "Decoder.h"

FKG_Decoder::FKG_Decoder() : 
	firstCharacter(true),
	endOfInput(false),
	buffer(0),
	bufferPosition(CHAR_BIT) 
{}


void FKG_Decoder::NextInputBit(std::istream& input, BITS &value)
{
	if (bufferPosition == CHAR_BIT)
	{
		buffer = (BITS)input.get();
		bufferPosition = 0;
	}
	value = GET_BIT(buffer, CHAR_BIT - bufferPosition - 1);
	value = (value != 0);
	bufferPosition++;
}

void FKG_Decoder::ReadWholeCharacter(std::istream& input, BITS &value)
{
	for (size_t i = 0; i < CHAR_BIT; i++)
	{
		if (bufferPosition == CHAR_BIT)
		{
			buffer = input.get();
			bufferPosition = 0;
		}
		BITS b = GET_BIT(buffer, CHAR_BIT - bufferPosition - 1);
		if (b) SET_BIT(value, CHAR_BIT - i - 1);
		bufferPosition++;
		
	}
}

void FKG_Decoder::Decode(std::istream& input, std::ostream& output)
{
	tree.ResetDecodeBuffer();

	bool found = false;
	NodeType type = NULL_NODE;
	unsigned char foundChar = NULL;

	while (!found)
	{
		BITS res = 0;
		NextInputBit(input, res);
	
		foundChar = tree.UpdateCode(res, type);
		if (type == LEAF || type == ESC || type == END_OF_INPUT)
		{
			found = true;
			break;
		}
	}
	if (type == ESC)
	{
		BITS res = 0;
		ReadWholeCharacter(input, res);
		tree.Encode(res);
		output << res;
	}
	if (type == LEAF)
	{
		tree.Encode(foundChar);
		output << foundChar;
	}
	if (type == END_OF_INPUT)
	{
		endOfInput = true;
	}
}

bool FKG_Decoder::EndReached()
{
	return endOfInput;
}
