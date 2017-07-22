#include "stdafx.h"
#include "BitStream.h"



BitIO::~BitIO()
{
}

inline bool BitIO::NextBit(int_fast8_t* buffer_to)
{
	if (buffer_to == nullptr) return false;
	if (buffer_position == CHAR_BIT)
	{
		buffer_position = 0;
		if (buffer_index == BUFFER_LENGTH)
		{
			buffer_index = 0;
			if (!GetBuffer())
			{
				return false;
			}
		}
		else
		{
			buffer_index++;
		}
	}
	else {
		buffer_position++;
	}
	(*buffer_to) = GET_BIT(bit_buffer[buffer_index], buffer_position);
	SET_BIT((*buffer_to), CHAR_BIT - 1);
	return true;
}

bool BitIO::GetBits(int_fast8_t* buffer_to, size_t count)
{
	if (buffer_to == nullptr) return false;
	while (count--)
	{

	}
}
