#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include "Vector2D.h"
#include "GameApp.h"
#include "Grid.h"
#include <math.h>

using namespace std;

const float infinityTM = 50000.0f;
const float baseUnitDist = 1.0f; //set weight on grid

AStarPathfinder::AStarPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

AStarPathfinder::~AStarPathfinder()
{
}

float getDistBetweenNodes(Node* a, Node* b)
{
	Vector2D aPos, bPos;
	
	aPos = dynamic_cast<GameApp*>(gpGame)->getGrid()->getULCornerOfSquare(a->getId());
	bPos = dynamic_cast<GameApp*>(gpGame)->getGrid()->getULCornerOfSquare(b->getId());

	float newX, newY, ecSquared;

	newX = aPos.getX() - bPos.getX();
	newX *= newX;

	newY = aPos.getY() - bPos.getY();
	newY *= newX;

	ecSquared = newX + newY;

	return (float)sqrt(ecSquared);
}

const Path& AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	priority_queue<Node*, vector<Node*>, Node::CompareNodes> nodesToVisit;
	//std::vector<Node*> openList; //open list

	nodesToVisit.push(pFrom); //priority q
							  //openList.push_back(pFrom);

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom); //closed list
#endif

	float shortestPath = infinityTM;

	mPath.clear();

	//source node as null
	pTo->setPreviousNode(NULL);
	pTo->setCostSoFar(0);

	Node* pClosestToEnd = pFrom;
	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.top();
		//remove node from list
		if (pTo->getId() == pCurrentNode->getId())
		{
			break;
		}

		nodesToVisit.pop();
		//add Node to Path //not here tho
		mPath.addNode(pCurrentNode);

		//get the Connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());
		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i<connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();

			if (pCurrentNode->getCostSoFar() + baseUnitDist < pTempToNode->getCostSoFar())
			{
				//extend nodes path to be the shortest
				pTempToNode->setCostSoFar(pCurrentNode->getCostSoFar() + baseUnitDist);
				pTempToNode->setPreviousNode(pCurrentNode);
			}


			//check distance between current node and the end node
			if (getDistBetweenNodes(pClosestToEnd, pTo) > getDistBetweenNodes(pTempToNode, pTo))
			{
				//change to temp and push to priority queue
				pClosestToEnd = pTempToNode;

				nodesToVisit.push(pClosestToEnd);
			}
			else
				nodesToVisit.push(pTempToNode);

			mVisitedNodes.push_back(pTempToNode);

#ifdef VISUALIZE_PATH
#endif

		}
	}

	if (pTo->getId() != pFrom->getId())
	{

		mPath.addNode(pTo);
		Node* previous;

		previous = pTo->getPreviousNode();

		while (previous != NULL)
		{
			mPath.addNode(previous);
			previous = previous->getPreviousNode();
		}

		mPath.addNode(pFrom);

		delete previous;
	}


	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;

}

