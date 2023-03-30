#pragma once
#include "Date.h"
#include "Airplane.h"
#include "KeyValue.h"
#include "Ticket.h"
#include <iostream>

typedef struct _FLight
{
	char idFlight[16];
	char arrivalAir[41];
	char *idAir;
	Date date;
	int status;
	// TicketList ticketList;
} Flight, *PFlight;

typedef struct _NodeFli
{
	Flight data;
	struct _NodeFli *pNext;
} NodeFli, *PNodeFli;

void InitFlight(PFlight);
bool FlightDataIsEmpty(Flight &flight);
PNodeFli CreateFlight(Flight &);
int CancleFlight(PNodeFli);
void InsertFlight(PNodeFli &, Flight &);
PNodeFli FindFlight(PNodeFli &, const char *);
PNodeFli FindFlightByIdPlane(PNodeFli &, const char *);
int FindIndexFlight(PNodeFli, const char *);
int FindDestination(PNodeFli, const char *);

void InitFlight(PFlight pFlight)
{
	// pFlight->ticketList.size = 0;
	pFlight->status = CONVE;
}

bool FlightDataIsEmpty(Flight &flight)
{
	return 
		strlen(flight.idAir) == 0 ||
		strlen(flight.arrivalAir) == 0;
}

PNodeFli CreateFlight(Flight &flight)
{
	PNodeFli tmp = new NodeFli;
	tmp->data = flight;
	tmp->pNext = NULL;
	return tmp;
}

int CancleFlight(PNodeFli pFlight)
{
	if (pFlight->data.status == CONVE || pFlight->data.status == HETVE)
	{
		pFlight->data.status = HUYCHUYEN;
		return 1;
	}
	return 0;
}

void InsertFlight(PNodeFli &first, Flight &flight)
{
	PNodeFli tmp = CreateFlight(flight);
	if (first == NULL)
	{
		first = tmp;
		first->pNext = NULL;
	}
	else
	{
		PNodeFli p = first;
		while (p->pNext != NULL)
		{
			p = p->pNext;
		}
		p->pNext = tmp;
	}
}

PNodeFli FindFlight(PNodeFli &first, const char *id)
{
	if (first == NULL)
		return NULL;
	for (PNodeFli p = first; p != NULL; p = p->pNext)
		if (strcmp(p->data.idFlight, id) == 0)
			return p;
	return NULL;
}

PNodeFli FindFlightByIdPlane(PNodeFli &first, const char *id)
{
	if (first == NULL)
		return NULL;
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.idAir, id) == 0)
			return p;
	}
	return NULL;
}

int FindIndexFlight(PNodeFli first, const char *id)
{
	int index = 0;
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.idFlight, id) == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}

int FindDestination(PNodeFli first, const char *arrival)
{
	int index = 0;
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.arrivalAir, arrival) == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}

void InputFlight(Flight &flight){
	std::cout << "Ma chuyen bay: ";        std::cin.getline(flight.idFlight, sizeof(flight.idFlight));
    std::cout << "So hieu may bay: ";      std::cin.getline(flight.idAir, sizeof(flight.idAir));
    std::cout << "San bay den: ";        std::cin.getline(flight.arrivalAir, sizeof(flight.arrivalAir));
    std::cout << "Thoi gian di: ";            std::cin >> flight.date.day;
}

//void ShowFlight(Flight flight, int position)
//{
//	gotoxy(35, 15);
//	std::cout << "Quan Ly Chuyen Bay";
//	int yDisplay = 15;
//	int xKeyDisplay[4] = {1,20,45,63};
//	
//	gotoxy(xKeyDisplay[0] + 3, yDisplay + position +3);
//    std::cout << flight.idFlight;
//    gotoxy(xKeyDisplay[1] + 3, yDisplay + position +3);
//    std::cout << flight.idAir;
//    gotoxy(xKeyDisplay[2] + 3, yDisplay + position +3);
//    std::cout << flight.arrivalAir;
//    gotoxy(xKeyDisplay[3] + 3, yDisplay + position +3);
//    std::cout << flight.date.day;
//}
//
//void ShowListFlight(PNodeFli first)
//{
//	int i = -1;
//	for(PNodeFli p = first; p != NULL; p = p->pNext){
//		while(p != NULL && i < 6-1){
//			ShowFlight(p->data, ++i);
//			p = p->pNext;
//		}
//	}
//}
