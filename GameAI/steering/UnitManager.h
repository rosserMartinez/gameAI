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

	KinematicUnit* mpPlayerUnit;

public:
	UnitManager(KinematicUnit* playerUnit);
	~UnitManager();

	void addUnit(KinematicUnit* unitToAdd);
	void deleteRandomUnit();

	void updateAndDrawAllUnits(float dt, GraphicsBuffer* targetBuffer);

};

#endif //
