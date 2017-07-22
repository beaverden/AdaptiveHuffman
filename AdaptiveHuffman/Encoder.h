#pragma once
#include "HuffmanTree.h"

typedef uint_fast8_t BITS;

class FKG_Encoder
{
public:
	FKG_Encoder();
	bool Encode(std::ostream& output, BITS ch);
	void End(std::ostream& output);
	void SetBits(std::ostream& output, std::vector <bool> &v);
private:
	HuffmanTree tree;
	BITS buffer;
	size_t buffer_position;
};