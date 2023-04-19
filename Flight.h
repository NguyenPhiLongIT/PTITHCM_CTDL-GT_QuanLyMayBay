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
extern string ContentFlight[6];

void InitFlight(Flight &, ListAir);
bool FlightDataIsEmpty(Flight &);
int size(PNodeFli &);

PNodeFli CreateFlight(Flight &);
void InsertListFlight(PNodeFli &, Flight);
int CancleFlight(PNodeFli &);
PNodeFli FindFlight(PNodeFli &, const char *);
PNodeFli FindFlightByIdPlane(PNodeFli &, const char *);
int FindIndexFlight(PNodeFli, const char *);
int FindDestination(PNodeFli, const char *);
void AutoUpdateFlightStatus(PNodeFli &);
int EditDateTime(PNodeFli &, Date);

void InputFlight(Flight &, ListAir);
void ShowFlight(Flight, int);
void ShowListFlightOnePage(PNodeFli, int);
void ChangeFlightMenuManagerPage(PNodeFli);
void MenuManageFlight(PNodeFli &, ListAir);

bool LoadFlight(PNodeFli &);
bool SaveFlight(PNodeFli);


//Khoi tao chuyen bay
void InitFlight(Flight &flight, ListAir dsmb) {
	flight.status = CONVE;
	flight.listTicket.size_datve = 0;
	int result = IndexAirplane(dsmb,flight.idAir);
	flight.listTicket.size_max = dsmb.nodes[result]->col*dsmb.nodes[result]->row;
	for (int i = 0; i < flight.listTicket.size_max; i++) {
		flight.listTicket.DSV[i].statusTicket = 0;
	}
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
	else{
		PNodeFli p;
		for (p = first; p!= NULL; p=p->pNext) count++;
		return count;
	}
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
	for(s = first; s != NULL && s->data.idFlight > flight.idFlight; t=s, s = s->pNext);
	if(s == first){		//Them nut vao dau ds
		p->pNext = first;
		first = p;
	}
	else{
		p->pNext = s;
		t->pNext = p;
	}
}

int CancleFlight(PNodeFli &first)
{
	if (first->data.status == CONVE || first->data.status == HETVE)
	{
		first->data.status = HUYCHUYEN;
		return 1;
	}
	return 0;
}

PNodeFli FindFlight(PNodeFli &first, const char *id)
{
	if (first == NULL) return NULL;
	PNodeFli p;
	for (p = first; p != NULL; p = p->pNext)
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

void AutoUpdateFlightStatus(PNodeFli &first)
{
	for( PNodeFli p = first; p != NULL ; p = p->pNext)
	{
		if( IsValidDate(&p->data.date) == false )
			//0: huy chuyen, 1: con ve, 2: het ve, 3: hoant tat 
			p->data.status = 2;
	}
}

int EditDateTime(PNodeFli &first, Date date){
	if(IsValidDate(&date)){
		first->data.date = date;
		return 1;
	}
	return 0;
}

//Khung nhap
void InputFlight(Flight &flight, ListAir dsmb){
	ShowCursor(true);
	CreateForm(ContentFlight, 0, 4, 32);
    gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
    gotoxy(X_Add+11,Y_Add+3);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), Text));
    gotoxy(X_Add+10,Y_Add+6);     	strcpy(flight.idAir, Input(sizeof(flight.idAir), ID));
    gotoxy(X_Add+13,Y_Add+9);		InputDate(&flight.date); 
    InitFlight(flight,dsmb);
//    gotoxy(X_Add+14,Y_Add+12);		char t[2]; strcpy(t, Input(sizeof(t), Number)); flight.listTicket.size_max = atoi(t);
//	gotoxy(X_Add+10,Y_Add+15);   	char s[2]; strcpy(s, Input(sizeof(s), Number)); flight.status = atoi(s);
}

//Hien thi thong tin 1 chuyen bay
void ShowFlight(Flight fli, int position)
{	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idFlight;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(12) << fli.arrivalAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idAir;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    PrintDate(&fli.date);
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position + 3);
    cout << fli.listTicket.size_datve << "/" << left << setw(10) <<  fli.listTicket.size_max;
    gotoxy(xKeyDisplay[5] + 3, Y_Display + position + 3);
    switch(fli.status){
    	case 0: cout << "Huy	  ";
    		break;
    	case 1: cout << "Con ve   ";
    		break;
    	case 2: cout << "Het ve   ";
    		break;
    	case 3: cout << "Hoan tat ";
    		break;
    	default: break;
	}
}

//Hien thi 1 trang gom nhieu chuyen bay
void ShowListFlightOnePage(PNodeFli first, int startIndex)
{
	gotoxy(3,3);
	cout << " So luong chuyen bay : " << size(first);
	if(first == NULL) return;
	
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
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
void MenuManageFlight(PNodeFli &first, ListAir dsmb){
//	ShowCursor(false);
	CurFlightPage = 1;
	TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentFlight, sizeof(ContentFlight)/sizeof(string));
	ShowListFlightOnePage(first, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";
	
	Flight fli;
	int signal;
	while(true)
	{
		menu:
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentFlight_ThaoTac);
		switch(signal) {
			case 1: // Insert
			{
				if(CurFlightPage == 0) CurFlightPage = 1;
				InputFlight(fli,dsmb);
				InsertListFlight(first, fli);
			
//				if(SaveFlight(first)){
					Notification("Them thanh cong");
//				}
		
				TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage);
				RemoveForm(0, 6, 32);
				ShowListFlightOnePage(first, (CurFlightPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			edit: case 2: //Edit date time
			{
				ShowCursor(true);
				if(first == NULL) {
					Notification("Danh sach rong");
					break;
				}
				
				CreateRow(X_Add, Y_Add, ContentFlight[0], 27);
				gotoxy(X_Add+10,Y_Add);       	strcpy(fli.idFlight, Input(sizeof(fli.idFlight), ID));
				PNodeFli p = FindFlight(first, fli.idFlight);
				if(p->data.status == CONVE || p->data.status == HETVE){
					RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
					CreateRow(X_Add, Y_Add, ContentFlight[3], 32);
					gotoxy(X_Add+13,Y_Add);		InputDate(&fli.date); 
					if(EditDateTime(p, fli.date)){
						Notification("Chinh sua thanh cong");
					}
				}
				else Notification("Khong the hieu chinh ngay gio");
				
				RemoveRow(X_Add, Y_Add, ContentFlight[3], 44);
				ShowListFlightOnePage(first, (CurFlightPage-1)*NumberPerPage);
				ShowCursor(false);
				break;		
			}
			case 3: //Cancle flight
			{
				ShowCursor(true);
				if(first == NULL) {
					Notification("Danh sach rong");
					break;
				}
				
				CreateRow(X_Add, Y_Add, ContentFlight[0], 27);
				gotoxy(X_Add+10,Y_Add);       	strcpy(fli.idFlight, Input(sizeof(fli.idFlight), ID));
				PNodeFli p = FindFlight(first, fli.idFlight);
				if(CancleFlight(p)){
					Notification("Da huy chuyen");
				}
				else{
					Notification("Chuyen bay khong con hoat dong! Khong the huy chuyen");
				}
				RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
				ShowListFlightOnePage(first, (CurFlightPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 4: //Chuyen trang truoc
			{
				if(CurFlightPage == 1) break;
				else{
					CurFlightPage--;
					ChangeFlightMenuManagerPage(first);
				}
				break;
			}
			case 5:	//Chuyen trang tiep
			{
				if(CurFlightPage >= TotalFlightPage) break;
				else{
					CurFlightPage++;
					ChangeFlightMenuManagerPage(first);
				}
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
    Ticket *pTicket;
    PNodeFli pNodeFli;

    if (!file.is_open())
        return false;
	
	while(!file.eof())
    {
        pNodeFli = new NodeFli;
        file.getline(pNodeFli->data.idFlight, sizeof(pNodeFli->data.idFlight), ';');
        file.getline(pNodeFli->data.arrivalAir, sizeof(pNodeFli->data.arrivalAir), ';');
        file.getline(pNodeFli->data.idAir, sizeof(pNodeFli->data.idAir), ';');
        
        file.getline(str, sizeof(str), ':');
        pNodeFli->data.date.hour = atoi(str);
		file.getline(str, sizeof(str), ';');
        pNodeFli->data.date.minute = atoi(str);
        
        file.getline(str, sizeof(str), '/');
        pNodeFli->data.date.day = atoi(str);
        file.getline(str, sizeof(str), '/');
        pNodeFli->data.date.month = atoi(str);
        file.getline(str, sizeof(str), ';');
        pNodeFli->data.date.year = atoi(str);
        file.getline(str, sizeof(str));
        pNodeFli->data.status = atoi(str);

//        file.getline(str, sizeof(str), ';');
//        pNodeFli->data.listTicket.size_max = atoi(str);
//        file.get(str, sizeof(str), ';');
//        pNodeFli->data.listTicket.size_datve = atoi(str);
       	
        for (int i = 0; i < pNodeFli->data.listTicket.size_max; i++)
        {
            pTicket = new Ticket;

            file.getline(pTicket->idPass, sizeof(pTicket->idPass), ';');
            file.getline(pTicket->seat, sizeof(pTicket->seat), ';');
            if(i <= pNodeFli->data.listTicket.size_max-1){
            	file.getline(str, sizeof(pTicket->statusTicket), ';');
			}else{
				file.getline(str, sizeof(pTicket->statusTicket));
			}
            pTicket->statusTicket = atoi(str);

            pNodeFli->data.listTicket.DSV[i] = *pTicket;
            delete pTicket;
        }
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
