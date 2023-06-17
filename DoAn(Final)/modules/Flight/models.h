#ifndef __FLIGHT__UTILS__
#define __FLIGHT__UTILS__

#include <fstream>
#include <string.h>
#include "..\Airplane\models.h"
#include "..\Ticket\models.h"
#include "..\Date\models.h"
#include "types.h"

void InitFlight(Flight &flight, ListAir listAir);
int Size(PNodeFli &first);
int SizeTicketAvailable(PNodeFli &first);
int SizeDateDes(PNodeFli &first, Date date, const char* arrival);
bool LessAmount(Airplane *&a, Airplane *&b);
PNodeFli CreateFlight(Flight &flight);
void InsertListFlight(PNodeFli &first, Flight flight);
bool CancleFlight(PNodeFli pNodeFli);
PNodeFli FindFlight(PNodeFli &first, const char *id);
PNodeFli FindFlightByIdPlane(PNodeFli &first, const char *id);
int FindIndexFlight(PNodeFli first, const char *id);
int FindDestination(PNodeFli first, const char *arrival);
bool FindDate(PNodeFli first, Flight fli);
bool CheckDate(PNodeFli first, PDate date);
void AutoUpdateFlightStatus(PNodeFli &first);

//Khoi tao chuyen bay
void InitFlight(Flight &flight, ListAir listAir) {
	flight.status = CONVE;
	flight.listTicket.sizeBooked = 0;
	int result = IndexAirplane(listAir,flight.idAir);
	flight.listTicket.sizeTotal = listAir.nodes[result]->col*listAir.nodes[result]->row;
	InitListTicket(flight.listTicket,*listAir.nodes[result]);
}

//So luong chuyen bay co trong danh sach
int Size(PNodeFli &first) {
	int count = 0;
		for (PNodeFli p = first; p!= NULL; p=p->pNext)
			count++;
	return count;
}

//So luong chuyen bay con ve 
int SizeTicketAvailable(PNodeFli &first){
	int count = 0;
	for(PNodeFli p = first; p != NULL; p = p->pNext){
		if(p->data.status == CONVE)
			count++;
	}
	return count;
}

//So luong chuyen bay theo thoi gian va dia diem
int SizeDateDes(PNodeFli &first, Date date, const char* arrival) {
	int count = 0;
	for(PNodeFli p = first; p != NULL; p = p->pNext){
		if(CheckDate(p, &date) && strcmp(p->data.arrivalAir, arrival) == 0 && p->data.status == CONVE)
			count++;
	}
	return count;
}

bool LessAmount(Airplane *&a, Airplane *&b){
	return a->amount > b->amount;
}

//Tao Node chuyen bay
PNodeFli CreateFlight(Flight &flight) {
	PNodeFli tmp = new NodeFli;
	tmp->data = flight;
	tmp->pNext = NULL;
	return tmp;
}

//Them chuyen bay vao ds
void InsertListFlight(PNodeFli &first, Flight flight) {

	PNodeFli p, t, s;		//t la nut truoc, s la nut sau
	p = CreateFlight(flight);
	for(s = first; s != NULL && strcmp(s->data.idFlight,flight.idFlight) < 0; t=s, s = s->pNext);
	if(s == first){		//Them nut vao dau ds
		p->pNext = first;
		first = p;
	}
	else{				//Them nut p vao truoc nut s
		p->pNext = s;
		t->pNext = p;
	}
}

//Huy chuyen bay
bool CancleFlight(PNodeFli pNodeFli)
{
	if (pNodeFli->data.status == CONVE || pNodeFli->data.status == HETVE)
	{
		pNodeFli->data.status = HUYCHUYEN;
		return true;
	}
	return false;
}

//Tim chuyen bay
PNodeFli FindFlight(PNodeFli &first, const char *id)
{
	if (first == NULL) return NULL;
	PNodeFli p;
	for (p = first; p != NULL; p = p->pNext)
		if (strcmp(p->data.idFlight, id) == 0)
			return p;
	return NULL;
}

//Tra ve chuyen bay theo ma may bay
PNodeFli FindFlightByIdPlane(PNodeFli &first, const char *id)
{
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.idAir, id) == 0)
			return p;
	}
	return NULL;
}

//Vi tri chuyen bay
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

//Vi tri chuyen bay theo dia diem
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

//Kiem tra cac chuyen bay tren cung 1 may bay thoa cach nhau 2 tieng
bool FindDate(PNodeFli first, Flight fli){
	for(PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if(strcmp(p->data.idFlight, fli.idFlight) != 0){
			if(strcmp(p->data.idAir, fli.idAir) == 0 &&
				p->data.date.year == fli.date.year && 
				p->data.date.month == fli.date.month)
			{
				if(p->data.date.day == fli.date.day || abs(p->data.date.day - fli.date.day) == 1) 
				{
					if(CompareDate(&p->data.date,&fli.date) < 120) return false;
				}
			}
			else if(strcmp(p->data.idAir, fli.idAir) == 0 &&
					p->data.date.year == fli.date.year)
			{
				if(abs(p->data.date.day - fli.date.day) == 30 || abs(p->data.date.day - fli.date.day) == 29 ||
					abs(p->data.date.day - fli.date.day) == 27)
				{	
					if(CompareDate(&p->data.date,&fli.date) < 120) return false;
				}
			}
			else if(strcmp(p->data.idAir, fli.idAir) == 0){
				if(abs(p->data.date.day - fli.date.day) == 30 || abs(p->data.date.day - fli.date.day) == 29 ||
					abs(p->data.date.day - fli.date.day) == 27)
				{
					if(CompareDate(&p->data.date,&fli.date) < 120) return false;
				}
			}
		}	
	}
	return true;
}

//Kiem tra trung ngay thang nam
bool CheckDate(PNodeFli first, PDate date) {
	if(	first->data.date.year == date->year &&
		first->data.date.month == date->month &&
		first->data.date.day == date->day
	  ) return true;
	return false;
}

//Tu dong cap nhat trang thai chuyen bay
void AutoUpdateFlightStatus(PNodeFli &first)
{
	for(PNodeFli p = first; p != NULL ; p = p->pNext)
	{
		//0: huy chuyen, 1: con ve, 2: het ve, 3: hoant tat 
		if(IsValidDate(&p->data.date) == false){
			p->data.status = HOANTAT;
		}
		else if(p->data.listTicket.sizeBooked == p->data.listTicket.sizeTotal){
			p->data.status = HETVE;
		}			
	}
}

//Giai phong bo nho flight
void DeleteAllListFlight(PNodeFli &list){
	PNodeFli temp;
	while(list != NULL){
		temp = list;
		list = list->pNext;
		delete temp->data.listTicket.DSV;
		temp->data.listTicket.DSV = NULL;
		delete temp;
	}
}

#endif
