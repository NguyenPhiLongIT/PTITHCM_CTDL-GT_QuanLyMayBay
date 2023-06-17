#ifndef __FLIGHT__TYPES__
#define __FLIGHT__TYPES__

#include "../Date/types.h"
#include "../Ticket/types.h"
#include "../../types/KeyValue.h"

typedef struct _FLight
{
	char idFlight[16];
	char arrivalAir[41];
	char idAir[16];
	Date date;
	int status;
	ListTicket listTicket;
} Flight, *PFlight;

typedef struct _NodeFli
{
	Flight data;
	struct _NodeFli *pNext;
} NodeFli, *PNodeFli;

#endif
