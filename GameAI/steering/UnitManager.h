#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <vector>
#include "Trackable.h"

class KinematicUnit;
class GraphicsBuffer;

class UnitManager : public Trackable
{
private:
	std::vector<KinematicUnit*> mpUnitList;
	//std::vector<KinematicUnit*> mpWallList;

	//KinematicUnit* mpPlayerUnit;

	float mCurrentReactionRadius;

public:
	UnitManager();
	~UnitManager();

	//KinematicUnit* getPlayerUnit();
	KinematicUnit* getUnit(int index);

	void addUnit(KinematicUnit* unitToAdd);
	void deleteRandomUnit();

	void updateAndDrawAllUnits(float dt, GraphicsBuffer* targetBuffer);

	//lolllll
	inline std::vector<KinematicUnit*> getUnitList() { return mpUnitList; };
	inline size_t getUnitListSize() { return mpUnitList.size(); };

	inline float getReactionRadius() { return mCurrentReactionRadius; };
	void updateFlockWeights();
};

#endif //
