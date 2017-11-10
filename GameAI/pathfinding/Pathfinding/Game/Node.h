#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:

	struct CompareNodes
	{
		bool const operator() (const Node* lhs, const Node* rhs) {return lhs->getCostSoFar() < rhs->getCostSoFar(); };
	};

	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};

	const float& getCostSoFar() const { return mTotalCost; };
	void setCostSoFar(float newCost) { mTotalCost = newCost; };

	Node* getPreviousNode() { return mPreviousNode;  };
	void setPreviousNode(Node* newPrev) { mPreviousNode = newPrev; };

private:
	const NODE_ID mId;
	Node* mPreviousNode;
	float mTotalCost;
};