#include "stdafx.h"
#include "Adaptive.h"

int Encode(std::istream& input)
{
	while (!input.eof() && !input.fail())
	{
		unsigned char ch = input.get();
		std::cout << ch << " ";
	}
	return 0;
}