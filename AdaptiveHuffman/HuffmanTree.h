#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

#define GET_BIT(byte, i) ((byte) & (1 << (i)))
#define SET_BIT(byte, i) ((byte) |= (1 << (i)))
#define CLS_BIT(byte, i) ((byte) &= (~(1 << (i))))

enum NodeType {
	END_OF_INPUT,
	NULL_NODE,
	LEAF, 
	INTERNAL, 
	ESC
};

class TreeNode
{
public:
	TreeNode();
	TreeNode(NodeType type, TreeNode * parent, unsigned int order, unsigned char character = 0);

	unsigned int order;
	unsigned char character;
	uint_fast64_t frequency;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
	NodeType type;
};


class HuffmanTree
{
public:
	HuffmanTree();
	std::vector<bool> Encode(unsigned char ch);
	
	std::vector<bool> GetCode(unsigned char ch);
	std::vector<bool> EofCode();
	std::vector<bool> EscCode();

	void ResetDecodeBuffer();
	unsigned char UpdateCode(bool value, NodeType &found);

private:
	bool TreeContains(unsigned char ch);
	void AddNode(unsigned char ch);
	void SwapNodes(TreeNode* first, TreeNode* second);
	void UpdateSums(TreeNode* start);
	TreeNode* FindHigherOrder(uint_fast64_t weight, unsigned int order);


	TreeNode* root;
	TreeNode* esc;
	TreeNode* input_end;
	TreeNode* decodeBuffer;
	std::map <unsigned char, TreeNode*> positions;
	unsigned int currentOrder;
};