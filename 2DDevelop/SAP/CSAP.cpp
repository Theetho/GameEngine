#include "CSAP.h"

void CSAP::AddObject(CBoxCollider* boxCollider)
{
	const float* x1 = &boxCollider->GetBounds().at("Min").x;
	const float* y1 = &boxCollider->GetBounds().at("Min").y;
	// const float* z1 = &boxCollider->GetBounds().at("Min").z;
	const float* x2 = &boxCollider->GetBounds().at("Max").x;;
	const float* y2 = &boxCollider->GetBounds().at("Max").y;;
	// const float* z2 = &boxCollider->GetBounds().at("Max").z;

	SPoint xMin(boxCollider, true, x1);
	SPoint yMin(boxCollider, true, y1);
	// SPoint zMin(boxCollider, true, z1);
	SPoint xMax(boxCollider,false, x2);
	SPoint yMax(boxCollider, false, y2);
	// SPoint zMax(boxCollider, false, z2);

	mX.push_back(xMin);
	mY.push_back(yMin);
	// mZ.push_back(zMin);
	mX.push_back(xMax);
	mY.push_back(yMax);
	// mZ.push_back(zMax);
}

void CSAP::RemoveObject(CBoxCollider* boxCollider)
{
	
}
