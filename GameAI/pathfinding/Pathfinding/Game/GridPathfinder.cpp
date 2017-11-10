#include <allegro5/allegro.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"
#include "GameApp.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest )
{
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}

	//change color?
	bool isDijkstra = dynamic_cast<GameApp*>(gpGame)->checkDijkstra();
	

	static ALLEGRO_COLOR pathColor;
	static ALLEGRO_COLOR startColor;
	static ALLEGRO_COLOR stopColor;

	if (isDijkstra)
	{
		pathColor = al_map_rgb(255, 0, 0);
		startColor = al_map_rgb(255, 40, 40);
		stopColor = al_map_rgb(255, 119, 0);
	}
	else
	{
		 pathColor = al_map_rgb( 0, 0, 255 );
		 startColor = al_map_rgb(64, 64, 255);
		 stopColor = al_map_rgb(20, 255, 255);
	}


	unsigned int numNodes = mPath.getNumNodes();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
		{
			mpVisualizer->addColor(mPath.peekNode(i)->getId(), currentPathColor);
			float lerpVal = lerp( i, 0, numNodes );
			currentPathColor.r = 1.0f - lerpVal;
		}

		//add beginning and ending color
		mpVisualizer->addColor(mPath.peekNode(0)->getId(), startColor);
		mpVisualizer->addColor(mPath.peekNode(numNodes - 1)->getId(), stopColor);
	}

	mpVisualizer->draw(*pDest);
}
#endif