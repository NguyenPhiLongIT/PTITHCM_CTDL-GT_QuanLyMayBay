#pragma once

#include <fstream>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

#include "Date.h"
#include "Airplane.h"
#include "Constraint.h"
#include "KeyValue.h"
#include "Ticket.h"
#include "UserInterface.h"

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

//Thong tin vi tri chuyen bay
int CurPosFlight = 0;
int CurFlightPage = 1;
int TotalFlightPage = 0;
extern string ContentFlight[5];

void InitFlight(Flight &);
bool FlightDataIsEmpty(Flight &);
int size(PNodeFli &);

PNodeFli CreateFlight(Flight &);
void InsertListFlight(PNodeFli &, Flight);
bool CancleFlight(PNodeFli &);
PNodeFli FindFlight(PNodeFli &, const char *);
PNodeFli FindFlightByIdPlane(PNodeFli &, const char *);
int FindIndexFlight(PNodeFli, const char *);
int FindDestination(PNodeFli, const char *);

void InputFlight(Flight &);
void ShowFlight(Flight, int);
void ShowListFlightOnePage(PNodeFli, int);
void ChangeFlightMenuManagerPage(PNodeFli);
void MenuManageFlight(PNodeFli &);

bool LoadFlight(PNodeFli &);
bool SaveFlight(PNodeFli);


//Khoi tao chuyen bay
void InitFlight(Flight &flight) {
	flight.status = CONVE;	
}

bool FlightDataIsEmpty(Flight &flight)
{
	return 
		strlen(flight.idAir) == 0 ||
		strlen(flight.arrivalAir) == 0;
}

//So luong chuyen bay co trong danh sach
int size(PNodeFli &first) {
	int count = 0;
	if (first == NULL) return count;
	PNodeFli p;
	for (p = first; p!= NULL; p=p->pNext) count++;
	return count;
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
	PNodeFli tmp = CreateFlight(flight);
	if (first == NULL) first = tmp;
	else {
		PNodeFli p;
		for (p = first; p->pNext != NULL; p = p->pNext);
		p->pNext = tmp;
	}
}

bool CancleFlight(PNodeFli &first)
{
	if (first->data.status == CONVE || first->data.status == HETVE)
	{
		first->data.status = HUYCHUYEN;
		return true;
	}
	return false;
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

//void AutoUpdateFlightStatus(PNodeFli &first)
//{
//	for( PNodeFli p = first; p != NULL ; p = p->pNext)
//	{
//		if( IsValidDate(&p->data.date) == false )
//			//// 1: con ve, 2: het ve, 3: hoan tat, 4: huy chuyen; 
//			p->data.status = 3;
//	}
//}

//Khung nhap
void InputFlight(Flight &flight){
	ShowCursor(true);
	CreateForm(ContentFlight, 0, 5, 32);
    gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
    gotoxy(X_Add+11,Y_Add+3);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), Text));
    gotoxy(X_Add+10,Y_Add+6);     	strcpy(flight.idAir, Input(sizeof(flight.idAir), ID));
    gotoxy(X_Add+13,Y_Add+9);		InputDate(&flight.date); 
//    gotoxy(X_Add+10,Y_Add+12);		char t[2]; strcpy(t, Input(sizeof(t), Number)); flight.listTicket.size_max = atoi(t);
	gotoxy(X_Add+10,Y_Add+12);   	char s[2]; strcpy(s, Input(sizeof(s), Number)); flight.status = atoi(s);
}

//Hien thi thong tin 1 chuyen bay
void ShowFlight(Flight fli, int position)
{	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idFlight;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.arrivalAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idAir;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    PrintDate(&fli.date);
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position + 3);
    switch(fli.status){
    	case 1: cout << "Huy chuyen";
    		break;
    	case 2: cout << "Con ve";
    		break;
    	case 3: cout << "Het ve";
    		break;
    	case 4: cout << "Hoan tat";
    		break;
    	default: break;
	}
}

//Hien thi 1 trang gom nhieu chuyen bay
void ShowListFlightOnePage(PNodeFli first, int startIndex)
{
	gotoxy(21,3);
	cout << " So luong chuyen bay : " << size(first);
	if(first == NULL) return;
	
	int count = -1;
//	AutoUpdateFlightStatus(first);
	for(PNodeFli p = first; p != NULL; p = p->pNext)
	{
		count++;
		if(count == startIndex){
			int i = -1;
			while(p != NULL && i < NumberPerPage - 1){
				ShowFlight(p->data, ++i);
				p = p->pNext;
			}
			RemoveExceedMember(i+1, 6);
			break;
		}
	} 
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurFlightPage <<"/"<< TotalFlightPage; 
}

//Chuyen trang
void ChangeFlightMenuManagerPage(PNodeFli first)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";

	Display( ContentFlight,sizeof(ContentFlight)/sizeof(string) );
	ShowListFlightOnePage(first,(CurFlightPage-1)*NumberPerPage);
}

//Menu thao tac voi chuyen bay
void MenuManageFlight(PNodeFli &first){
//	ShowCursor(false);
//	system("cls");
	CurFlightPage = 1;
	TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentFlight, sizeof(ContentFlight)/sizeof(string));
	ShowListFlightOnePage(first, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";
	
	Flight cb_tmp;
	int signal;
	while(true)
	{
		menu:
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentThaoTac);
		switch(signal) {
			case 1: // Insert
			{
				InputFlight(cb_tmp);
				InsertListFlight(first, cb_tmp);
//				if(CurFlightPage == 0) CurFlightPage = 1;
//				gotoxy(X_Add, Y_Add-1);
//				InputListFlight(first);
//				
//				if(SaveFlight(first)){
//					Notification("Them thanh cong");
//				}
//				
			TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage);
				RemoveForm(0, 5, 32);
				ShowListFlightOnePage(first, (CurFlightPage-1)*NumberPerPage);
//				ShowCursor(false);
//				goto menu;
				break;
			}
			case 2: //Delete
			{
				break;		
			}
			case 3: //Edit
			{
				break;
			}
			case 4: //Chuyen trang truoc
			{
				break;
			}
			case 5:	//Chuyen trang tiep
			{
				break;
			}
			default: return;
			
		}
	}
}

bool LoadFlight(PNodeFli &First)
{
    ifstream file("DSCB.TXT", ios_base::in);
    char str[1000];

    if (!file.is_open())
        return false;
	
	while(!file.eof())
    {
        PNodeFli pNodeFli = new NodeFli;
        file.getline(pNodeFli->data.idFlight, sizeof(pNodeFli->data.idFlight), ';');
        file.getline(pNodeFli->data.arrivalAir, sizeof(pNodeFli->data.arrivalAir), ';');
        file.getline(pNodeFli->data.idAir, sizeof(pNodeFli->data.idAir), ';');
        file.getline(str, sizeof(str), '/');
        pNodeFli->data.date.day = atoi(str);
        file.getline(str, sizeof(str), '/');
        pNodeFli->data.date.month = atoi(str);
        file.getline(str, sizeof(str), ',');
        pNodeFli->data.date.year = atoi(str);
        file.getline(str, sizeof(str), ':');
        pNodeFli->data.date.second = atoi(str);
        file.getline(str, sizeof(str), ':');
        pNodeFli->data.date.minute = atoi(str);
        file.getline(str, sizeof(str), ';');
        pNodeFli->data.date.hour = atoi(str);
        file.getline(str, sizeof(str));
        pNodeFli->data.status = atoi(str);

//        file.getline(str, sizeof(str), ';');
//        pNodeFli->data.ticketList.size = atoi(str);
//        for (int i = 0; i < pNodeFli->data.ticketList.size; i++)
//        {
//            PTicket pTicket = new Ticket;
//
//            file.getline(pTicket->idPass, sizeof(pTicket->idPass), ';');
//            file.getline(str, sizeof(str), ';');
//            pTicket->col = atoi(str);
//            file.getline(str, sizeof(str), ';');
//            pTicket->col = atoi(str);
//            if (i == pNodeFli->data.ticketList.size - 1)
//            {
//                file.getline(str, sizeof(str));
//            }
//            else
//            {
//                file.getline(str, sizeof(str), ';');
//            }
//            pTicket->statusTicket = atoi(str);
//
//            pNodeFli->data.ticketList.DSV[pNodeFli->data.ticketList.size++] = pTicket;
//        }
        InsertListFlight(First, pNodeFli->data);
    }
    file.close();
    return true;
}

bool SaveFlight(PNodeFli First)
{
    ofstream file("DSCB.TXT", ios_base::out);

    if (!file.is_open())
        return false;

    while (First != NULL)
    {
        file << First->data.idFlight << ";"
             << First->data.arrivalAir << ";"
             << First->data.idAir << ";"
             << First->data.date.day << "/"
             << First->data.date.month << "/"
             << First->data.date.year << ","
             << First->data.date.second << ":"
             << First->data.date.minute << ":"
             << First->data.date.hour << ";"
             << First->data.status << ";";
//        for (int i = 0; i < First->data.ticketList.size; i++)
//        {
//            file << First->data.ticketList.DSV[i]->idPass << ";"
//                 << First->data.ticketList.DSV[i]->col << ";"
//                 << First->data.ticketList.DSV[i]->row << ";"
//                 << First->data.ticketList.DSV[i]->statusTicket;
//            if (i == First->data.ticketList.size - 1)
//            {
//                file << endl;
//            }
//            else
//            {
//                file << ";";
//            }
//        }
//        First = First->pNext;
    }

    file.close();
    return true;
}
