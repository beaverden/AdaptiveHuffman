#include "stdafx.h"
#include "HuffmanTree.h"

TreeNode::TreeNode() :
	order(0),
	type(INTERNAL),
	parent(nullptr),
	left(nullptr),
	right(nullptr),
	character(0),
	frequency(0)
{
}

TreeNode::TreeNode(NodeType type, TreeNode * parent, unsigned int order, unsigned char character) :
	order(order),
	type(type),
	parent(parent),
	left(nullptr),
	right(nullptr),
	character(character),
	frequency(0)
{
	if (type != ESC) this->frequency = 1;
}


HuffmanTree::HuffmanTree()
{
	currentOrder = (2 << CHAR_BIT) + 1;
	root		= new TreeNode(INTERNAL, nullptr, --currentOrder);
	root->right = new TreeNode(END_OF_INPUT, root, --currentOrder);
	root->left	= new TreeNode(ESC, root, --currentOrder);

	input_end = root->right;
	esc = root->left;

	decodeBuffer = nullptr;
}

std::vector<bool> HuffmanTree::Encode(unsigned char ch)
{
	if (!TreeContains(ch))
	{
		std::vector<bool> code = EscCode();	
		for (int i = 0; i < CHAR_BIT; i++)
		{
			code.push_back(GET_BIT(ch, CHAR_BIT - i - 1));
		}
		AddNode(ch);
		return code;
	}
	else
	{
		std::vector<bool> encoding = GetCode(ch);
		TreeNode* containing = positions[ch];
		UpdateSums(containing);
		containing->frequency++;	
		return encoding;
	}
}

bool HuffmanTree::TreeContains(unsigned char ch)
{
	return (positions.find(ch) != positions.end());
}

void HuffmanTree::AddNode(unsigned char ch)
{
	TreeNode* newNode = new TreeNode(
		INTERNAL,
		esc->parent,
		esc->order
	);

	newNode->right = new TreeNode(
		LEAF,
		newNode,
		--currentOrder,
		ch
	);

	newNode->left = new TreeNode(
		ESC,
		newNode,
		--currentOrder
	);

	positions[ch] = newNode->right;

	if (esc->parent == nullptr)
	{
		root = newNode;
	}
	else
	{
		esc->parent->left = newNode;
	}
	delete esc;

	esc = newNode->left;

	UpdateSums(newNode->parent);
}


std::vector<bool> HuffmanTree::GetCode(unsigned char ch)
{
	std::vector<bool> code;
	if (!TreeContains(ch)) return code;
	
	TreeNode* node = positions[ch];
	do
	{
		if (node == node->parent->left)
		{
			code.push_back(0);
		}
		else
		{
			code.push_back(1);
		}
		node = node->parent;
	} while (node->parent != nullptr);

	std::reverse(code.begin(), code.end());
	return code;
}

std::vector<bool> HuffmanTree::EofCode()
{
	TreeNode* node = input_end;
	std::vector<bool> code;

	while (node->parent != nullptr)
	{
		if (node == node->parent->left)
		{
			code.push_back(0);
		}
		else
		{
			code.push_back(1);
		}
		node = node->parent;
	}

	std::reverse(code.begin(), code.end());
	return code;
}

std::vector<bool> HuffmanTree::EscCode()
{
	TreeNode* node = esc;
	std::vector<bool> code;
	
	while (node->parent != nullptr)
	{
		if (node == node->parent->left)
		{
			code.push_back(0);
		}
		else
		{
			code.push_back(1);
		}
		node = node->parent;
	}

	std::reverse(code.begin(), code.end());
	return code;
}


void HuffmanTree::UpdateSums(TreeNode * start)
{
	if (start == nullptr) return;
	
	while (start != nullptr)
	{
		TreeNode* highestOrder = FindHigherOrder(start->frequency, start->order);
		if (highestOrder != start &&
			highestOrder != nullptr &&
			start->parent != nullptr)
		{
			SwapNodes(start, highestOrder);
		}
		if (start->type == INTERNAL)
		{
			start->frequency++;
		}	
		start = start->parent;
	}
}

void HuffmanTree::SwapNodes(TreeNode* first, TreeNode* second)
{
	if (first == nullptr || second == nullptr) return;
	if (first->parent == nullptr || second->parent == nullptr) return;
	if (first->parent == second || second->parent == first) return;
	TreeNode* firstParent = first->parent;
	TreeNode* secondParent = second->parent;
		
	if (first == first->parent->left)
	{
		first->parent->left = second;
	}
	else
	{
		first->parent->right = second;
	}

	if (second == second->parent->left)
	{
		second->parent->left = first;
	}
	else
	{
		second->parent->right = first;
	}

	std::swap(first->order, second->order);
	std::swap(first->parent, second->parent);
}

TreeNode * HuffmanTree::FindHigherOrder(uint_fast64_t weight, unsigned int order)
{
	std::queue <TreeNode*> q;
	q.push(root);
	
	while (!q.empty())
	{
		TreeNode* current = q.front();
		q.pop();
		if (current != nullptr)
		{
			if (current->frequency == weight && 
				current->parent != nullptr)
			{
				return current;
			}
			if (current->order <= order)
			{
				return nullptr;
			}
			q.push(current->right);
			q.push(current->left);
		}
	}
	return nullptr;
}

void HuffmanTree::ResetDecodeBuffer()
{
	decodeBuffer = root;
}

unsigned char HuffmanTree::UpdateCode(bool value, NodeType& found)
{
	if (decodeBuffer == nullptr)
	{
		found = NULL_NODE;
		return NULL;
	}

	if (value == 1)
	{
		decodeBuffer = decodeBuffer->right;
	}

	if (value == 0)
	{
		decodeBuffer = decodeBuffer->left;
	}

	found = decodeBuffer->type;
	return decodeBuffer->character;

}