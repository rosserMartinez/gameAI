#include "Node.h"

const float infinityTM = 50000.0f;


Node::Node()
:mId(BAD_NODE_ID)
{
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	mTotalCost = infinityTM;
}

Node::~Node()
{
}
//
//bool const Node::CompareNodes::operator()(const Node* lhs, const Node* rhs)
//{
//	return lhs->getCost() < rhs->getCost();
//}