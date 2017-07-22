#include "stdafx.h"
#include "Test.h"
#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <istream>

#include "Encoder.h"
#include "Decoder.h"

 static const std::string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
std::string GetRandomStr(int len)
{
	std::string res = "";
	for (size_t i = 0; i < len; i++)
	{
		res += alphabet[rand() % alphabet.size()];
	}
	return res;
}

unsigned char* RandomBinaryStr(int len)
{
	unsigned char* str = new unsigned char[len];
	for (size_t i = 0; i < len; i++)
	{
		str[i] = rand() % 256;
	}
	return str;
}

#define TESTS_NUM 1000
#define MAX_LEN 100
bool TestEncodingDecoding()
{
	int ok = 0;
	for (int i = 0; i < TESTS_NUM; i++)
	{
		std::string toEncode = GetRandomStr(rand()% MAX_LEN +1);
		//std::cout << toEncode << std::endl;
		std::stringstream output;
		FKG_Encoder enc;
		FKG_Decoder dec;
		for (char ch : toEncode)
		{
			enc.Encode(output, ch);
		}
		enc.End(output);

		output.seekg(0, std::ios::beg);

		std::stringstream out;
		while (!dec.EndReached())
		{
			dec.Decode(output, out);
		}
		if (out.str() != toEncode)
		{
			//std::cout << "Fail at: " << toEncode << " <<<<<<<<<<<<<<<<<<<<<<<< " << std::endl;
		}	
		else ok++;

		//std::cout << "OK/TOTAL: " << ok << "/" << TESTS_NUM << std::endl;	
	}
	if (ok == TESTS_NUM) return true;
	return false;
}


bool TestBinaryData()
{
	int ok = 0;
	for (size_t test = 0; test < TESTS_NUM; test++)
	{
		int len = rand() % MAX_LEN + 1;
		unsigned char* str = RandomBinaryStr(len);

		std::stringstream output;
		FKG_Encoder enc;
		FKG_Decoder dec;

		for (size_t i = 0; i < len; i++)
		{
			enc.Encode(output, str[i]);
		}
		enc.End(output);


		output.seekg(0, std::ios::beg);

		std::stringstream out;
		while (!dec.EndReached())
		{
			dec.Decode(output, out);
		}
		
		std::string outstr = out.str();
		bool equals = true;
		for (size_t i = 0; i < outstr.length(); i++)
		{
			if ((unsigned char)outstr[i] != str[i]) equals = false;
		}
		if (outstr.length() != len) equals = false;

		if (equals)
		{
			ok++;
		}
		delete[] str;
		//std::cout << "OK/TOTAL: " << ok << "/" << TESTS_NUM << std::endl;	
	}
	if (ok == TESTS_NUM) return true;
	return false;
}