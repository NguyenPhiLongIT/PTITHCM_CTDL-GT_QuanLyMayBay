#ifndef __PASSENGER__TYPES__
#define __PASSENGER__TYPES__

#include "../../types/KeyValue.h"

typedef struct _Passenger
{
//	char id[13];
	int id;
	char firstName[31];
	char lastName[11];
	bool gender; // 0 la nam , 1 la nu
}Passenger, *PPassenger;

typedef struct _PassNode
{
	Passenger data;
	struct _PassNode *pLeft;
	struct _PassNode *pRight;
} PassNode, *PPassNode, *TreePass;

#endif