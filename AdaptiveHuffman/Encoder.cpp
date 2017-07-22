#include "stdafx.h"
#include "Encoder.h"
#include <bitset>

FKG_Encoder::FKG_Encoder() : 
	buffer(0), 
	buffer_position(0)
{
}

/*
	Output each bit to the buffer until the buffer is full.
	If it is full, output it and reset the counter and the
	buffer itself
*/
bool FKG_Encoder::Encode(std::ostream& output, BITS ch)
{
	std::vector<bool> esc = tree.EscCode();
	std::vector<bool> code = tree.Encode(ch);

	SetBits(output, code);
	//std::cout << "============================" << std::endl;
	// TODO reteurn
	return true;
}

void FKG_Encoder::End(std::ostream& output)
{
	std::vector <bool> code = tree.EofCode();
	SetBits(output, code);
	if (buffer_position != 0)
	{
		output << buffer;
	}
}

void FKG_Encoder::SetBits(std::ostream& output, std::vector<bool> &v)
{
	for (bool value : v)
	{
		if (buffer_position == CHAR_BIT)
		{
			output.put(buffer);
			buffer = 0;
			buffer_position = 0;
			
		}
		if (value)
		{
			SET_BIT(buffer, CHAR_BIT - buffer_position - 1);
		}
		buffer_position++;
	}
}
