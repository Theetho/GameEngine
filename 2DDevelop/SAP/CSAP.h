#pragma once

#include <vector>
#include "../Physics/CBoxCollider.h"

/// Implementation of the Sweep And Prune algorithm

struct SPoint
{
	CBoxCollider* mOwner; // Owner &CBoxCollider
	bool		  mIsMin; // MinMax Flag
	const float*  mValue; // Value of the point
	SPoint(CBoxCollider* owner, bool isMin, const float* value)
		: mOwner(owner)
		, mIsMin(isMin)
		, mValue(value)
	{}
};

struct SPairManager
{
};

class CSAP
{
	SPairManager			   mPairManager;
	std::vector<CBoxCollider*> mBoxColliders;
	std::vector<SPoint>		   mX;
	std::vector<SPoint>		   mY;
	std::vector<SPoint>		   mZ;
public:
	void AddObject(CBoxCollider* boxCollider);
	void RemoveObject(CBoxCollider* boxCollider);
	void UpdateObject();
};

