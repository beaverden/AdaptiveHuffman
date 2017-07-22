// AdaptiveHuffman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Adaptive.h"
#include "HuffmanTree.h"
#include <string>
#include <time.h>
#include "Test.h"
#include "Encoder.h"
#include "Decoder.h"

#include <iostream>
#include <fstream>
//#define CODE_TEST

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}


int main(int args, const char* argv[])
{

	#ifdef CODE_TEST
		srand(time(0));
		if (!TestEncodingDecoding()) std::cout << "Failed brute force test\n";
		else std::cout << "Brute force OK\n";
		if (!TestBinaryData()) std::cout << "Failed binary data test\n";
		else std::cout << "Binary data OK\n";
		
		return 0;
	#endif

	if (args != 4)
	{
		std::cout << "Wrong number of parameters\n";
		return 0;
	}

	std::string infilename = argv[1];
	std::string outfilename = argv[2];

	std::ifstream infile(infilename, std::ios::binary);
	std::ofstream outfile(outfilename, std::ios::binary);

	clock_t begin = clock();
	
	unsigned char type = argv[3][0];
	if (strcmp(argv[3], "-encode") == 0)
	{
		FKG_Encoder huff;
		while (!infile.eof())
		{
			unsigned char ch = infile.get();
			huff.Encode(outfile, ch);
		}
		huff.End(outfile);
	}
	else if (strcmp(argv[3], "-decode") == 0)
	{
		FKG_Decoder dec;
		while (!infile.eof() && !dec.EndReached())
		{
			dec.Decode(infile, outfile);
		}
	}  
	else
	{
		std::cout << "Accepts -encode and -decode arguments";
	}
	outfile.close();

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time: " << elapsed_secs << std::endl;

	size_t original_file_size = filesize(infilename.c_str());
	size_t resulting_file_size = filesize(outfilename.c_str());
	printf("Original file size   %f KB \n", original_file_size / 1024.0);
	printf("Output file size     %f KB \n", resulting_file_size / 1024.0);
	printf("Compression rate     %d KB (%f%%)\n", (original_file_size - resulting_file_size)/1024.0, (1 - (double)resulting_file_size / original_file_size) * 100);

    return 0;
}

