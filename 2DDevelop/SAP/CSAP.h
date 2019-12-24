#pragma once
#include "CBoxCollider.h"

/// Implementation of the Sweep And Prune algorithm

struct SEndPoint
{
	CBoxCollider* mOwner;
	float		  mValue;
	bool		  mIsMin;
};

class CSAP
{

};

