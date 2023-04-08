#pragma once

#include <iostream>

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
	char *idAir;
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

void InitFlight(PFlight);
void InitListFlight(PNodeFli &);
bool FlightDataIsEmpty(Flight &flight);
PNodeFli CreateFlight(Flight &);
int CancleFlight(PNodeFli);
void InsertFlight(PNodeFli &, Flight &);
PNodeFli FindFlight(PNodeFli &, const char *);
PNodeFli FindFlightByIdPlane(PNodeFli &, const char *);
int FindIndexFlight(PNodeFli, const char *);
int FindDestination(PNodeFli, const char *);

bool LoadFlight(PNodeFli &);
bool SaveFlight(PNodeFli);

void InitFlight(Flight &flight)
{
	flight.listTicket.size_datve = 0;
	flight.status = CONVE;
}

void InitListFlight(PNodeFli &first){
	first == NULL;
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

bool CancleFlight(PNodeFli &first)
{
	if (first->data.status == CONVE || first->data.status == HETVE)
	{
		first->data.status = HUYCHUYEN;
		return true;
	}
	return false;
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
		PNodeFli p;
		for(p = first; p->pNext != NULL; p = p->pNext);
			p->pNext = tmp;
	}
}

int size(PNodeFli &first){
	int count = 0;
	if(first == NULL) return count;
	for(PNodeFli p = first; p != NULL; p = p->pNext){
		count++;
	}
	return count;
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

void InputFlight(Flight &flight){
	ShowCursor(true);
	CreateForm(ContentFlight, 0, 5, 27);
    gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
    gotoxy(X_Add+11,Y_Add+3);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), Text));
    gotoxy(X_Add+10,Y_Add+6);     	strcpy(flight.idAir, Input(sizeof(flight.idAir), ID));
    gotoxy(X_Add+13,Y_Add+9);		char h[2]; strcpy(h, Input(sizeof(h), Number)); flight.date.hour = atoi(h);
									char mi[2]; strcpy(mi, Input(sizeof(mi), Number)); flight.date.minute = atoi(mi);
									char d[2]; strcpy(d, Input(sizeof(d), Number)); flight.date.day = atoi(d); 
									char m[2]; strcpy(m, Input(sizeof(m), Number)); flight.date.month = atoi(m);
									char y[4]; strcpy(y, Input(sizeof(y), Number)); flight.date.year = atoi(y);   
//    gotoxy(X_Add+10,Y_Add+12);		char t[2]; strcpy(t, Input(sizeof(t), Number)); flight.listTicket.size_max = atoi(t);
	gotoxy(X_Add+10,Y_Add+12);   	char s[2]; strcpy(s, Input(sizeof(s), Number)); flight.status = atoi(s);
}

void InputListFlight(PNodeFli &first){
	int size; 
	cout << "So luong chuyen bay: "; cin >> size;
    for(int i = 0; i < size; i++){
    	Flight fli;
    	cin.ignore();
    	InputFlight(fli);
    	InsertFlight(first, fli);
	}
}

void ShowFlight(Flight fli, int position)
{
	int xKeyDisplay[10] = {20,35,55,70,85,102,115,130,145,160};
	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idFlight;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.arrivalAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idAir;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.date.hour << fli.date.minute << fli.date.day << fli.date.month << fli.date.year;
//    gotoxy(xKeyDisplay[4] + 3, Y_Display + position +3);
//    cout << left << setw(10) << fli.listTicket.size_max;
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position + 3);
    switch(fli.status){
    	case 1: cout << "Huy chuyen";
    		break;
    	case 2: cout << "Con ve		";
    		break;
    	case 3: cout << "Het ve		";
    		break;
    	case 4: cout << "Hoan tat	";
    		break;
    	default: break;
	}
}

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

void ChangeFlightMenuManagerPage(PNodeFli first)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";

	Display( ContentFlight,sizeof(ContentFlight)/sizeof(string) );
	ShowListFlightOnePage(first,(CurFlightPage-1)*NumberPerPage);
}

void MenuManageFlight(PNodeFli &first, Flight fli){
//	ShowCursor(false);
//	system("cls");
	CurFlightPage = 1;
	TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentFlight, sizeof(ContentFlight)/sizeof(string));
	ShowListFlightOnePage(first, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";
	
	int signal;
	while(true)
	{
		menu:
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentThaoTac);
		switch(signal) {
			case 1: // Insert
			{
//				if(CurFlightPage == 0) CurFlightPage = 1;
//				gotoxy(X_Add, Y_Add-1);
//				InputListFlight(first);
//				
//				if(SaveFlight(first)){
//					Notification("Them thanh cong");
//				}
//				
//				system("color 0E");
//				TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage);
//				RemoveForm(0, 6, 27);
//				ShowListFlightOnePage(first, (CurFlightPage-1)*NumberPerPage);
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

    if (!file.is_open())
        return false;

    while (!file.eof())
    {
        PNodeFli pNodeFli = new NodeFli;
        char str[1000];
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
        InsertFlight(First, pNodeFli->data);
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
