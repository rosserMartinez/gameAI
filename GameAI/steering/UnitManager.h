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
	std::vector<KinematicUnit*> mpWallList;

	KinematicUnit* mpPlayerUnit;

	float mCurrentReactionRadius;

public:
	UnitManager(KinematicUnit* playerUnit);
	~UnitManager();

	KinematicUnit* getPlayerUnit();

	void addUnit(KinematicUnit* unitToAdd);
	void deleteRandomUnit();

	void updateAndDrawAllUnits(float dt, GraphicsBuffer* targetBuffer);

	//lolllll
	inline std::vector<KinematicUnit*> getUnitList() { return mpUnitList; };
	inline size_t getUnitListSize() { return mpUnitList.size(); };

	//enter janktown
	void setUnitWalls();
	inline void addWall(KinematicUnit* unitToAdd) {mpWallList.push_back(unitToAdd); };

	inline float getReactionRadius() { return mCurrentReactionRadius; };
	void setReactionRadius(float newRadius);
};

#endif //
