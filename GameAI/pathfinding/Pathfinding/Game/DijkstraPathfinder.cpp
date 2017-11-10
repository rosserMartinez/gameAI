#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const float infinityTM = 50000.0f;
const float baseUnitDist = 1.0f; //set weight on grid

DijkstraPathfinder::DijkstraPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

DijkstraPathfinder::~DijkstraPathfinder()
{
}

bool isInVector(std::vector<Node*> vec, Node* toCheck)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == toCheck)
		{
			return true;
		}
	}

	return false;
}

const Path& DijkstraPathfinder::findPath(Node* pFrom, Node* pTo)
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

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (/*pCurrentNode != pTo &&*/ nodesToVisit.size() > 0)
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
	//	mPath.addNode(pCurrentNode);

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

					//pushtown
					nodesToVisit.push( pTempToNode );
					mVisitedNodes.push_back( pTempToNode );
				}

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

