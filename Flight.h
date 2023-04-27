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

void InputFlight(PNodeFli &, Flight &, ListAir , bool );
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
		memset(flight.listTicket.DSV[i].idPas,0,sizeof(flight.listTicket.DSV[i].idPas));
		memset(flight.listTicket.DSV[i].seat,0,sizeof(flight.listTicket.DSV[i].seat));
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
	for (PNodeFli p = first; p!= NULL; p=p->pNext)
		count++;
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

	PNodeFli p, t, s;		//t la nut truoc, s la nut sau
	p = CreateFlight(flight);
	for(s = first; s != NULL && strcmp(s->data.idFlight,flight.idFlight) < 0; t=s, s = s->pNext);
	//for(s = first; s != NULL && s->data.idFlight > flight.idFlight; t=s, s = s->pNext);
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
			p->data.status = 3;
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
void InputFlight(PNodeFli &first, Flight &flight, ListAir dsmb, bool Edit = false){
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri chuyen bay
	if(Edit == false) CreateForm(ContentFlight, 0, 4, 32);
	while(true){
		switch(ordinal){
			case 0:{	//Nhap idFlight
				do{
					CreateRow(X_Add, Y_Add, ContentFlight[0], 27);
					gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
					position = FindIndexFlight(first, flight.idFlight);
					if(strlen(flight.idFlight) == 0){
						Notification("Vui long khong bo trong");
					}
					if(position > -1 && Edit == false){
						Notification("ID chuyen bay da ton tai");
					}
					if(position < 0 && Edit == true && strlen(flight.idFlight) != 0){
						Notification("ID chuyen bay khong ton tai");
					}
					if(
						(position > -1 && Edit == true) 
						||
						(position < 0 && Edit == false && (strlen(flight.idFlight) != 0))
					) break;
				}
				while(true);
				
				while (Edit == true) {
					PNodeFli p = FindFlight(first, flight.idFlight);
					if(p->data.status == CONVE || p->data.status == HETVE){
						CreateRow(X_Add, Y_Add, ContentFlight[3], 32);
						gotoxy(X_Add+13,Y_Add);		InputDate(&flight.date);
						RemoveRow(X_Add, Y_Add, ContentFlight[3], 44); 
						if(EditDateTime(p, flight.date)){
							if(SaveFlight(first)){
								Notification("Chinh sua thanh cong");
								return;
							}
						}
					}
					else {
						Notification("Khong the hieu chinh ngay gio");
						RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
						return;
					}
				}
				  
				ordinal++;
				break;
			}
			case 1:{	//Nhap arrivalAir
				gotoxy(X_Add+11,Y_Add+3);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), Text));
				if(strlen(flight.arrivalAir) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2:{	//Nhap idAir
				gotoxy(X_Add+10,Y_Add+6); cout << "			";
				gotoxy(X_Add+10,Y_Add+6);     	strcpy(flight.idAir, Input(sizeof(flight.idAir), ID));
				position = IndexAirplane(dsmb, flight.idAir);
				if(strlen(flight.idAir) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				if(position < 0){
					Notification("ID may bay khong ton tai");
					break;
				}
				ordinal++;
				break;
			}
			case 3:{	//Nhap DateTime
				gotoxy(X_Add+13,Y_Add+9);		InputDate(&flight.date); 
				ordinal++;
				break;
			}
			case 4:{
				InitFlight(flight,dsmb);
				ordinal++;
				break;
			}
			case 5:{
				if(Edit == false){
					InsertListFlight(first, flight);
					if(SaveFlight(first)){
						Notification("Them thanh cong");
					}
				}
				RemoveForm(0, 4, 32);
			}
			return;
		}
	}
	ShowCursor(false);
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
	SetColor(curColor);
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
				InputFlight(first, fli, dsmb);

				TotalFlightPage = (int)ceil((double)size(first)/NumberPerPage);
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
				InputFlight(first, fli, dsmb, true);
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



//Menu thao tac voi danh sach ve
void MenuManageListTicket(ListAir dsmb, PNodeFli dscb) {
	Flight cb_tmp;
	Airplane mb_tmp;
	PNodeFli pcb_tmp;
	
	if(dscb == NULL) {
		Notification("Danh sach chua co chuyen bay nao!");
		return;
	}
	
	
	
	//Tao khung nhap va kiem tra dieu kien
	do {
		CreateRow(X_Add, Y_Add, ContentFlight[0], 32);
		gotoxy(X_Add+10,Y_Add);       	strcpy(cb_tmp.idFlight, Input(sizeof(cb_tmp.idFlight), ID));
		pcb_tmp = FindFlight(dscb,cb_tmp.idFlight);
		if (pcb_tmp == NULL) Notification("Chuyen bay khong ton tai");
		else if (pcb_tmp->data.status == HETVE) Notification("Chuyen bay da het ve");
		else if (pcb_tmp->data.status == HUYCHUYEN) Notification("Chuyen bay da bi huy");
		else if (pcb_tmp->data.status == HOANTAT) Notification("Chuyen bay da hoan tat");
		else break;
	} while (true);
	
	RemoveRow(X_Add, Y_Add, ContentFlight[0], 32);
	
	//Luu vi tri may bay cua chuyen bay do
	int result = IndexAirplane(dsmb,pcb_tmp->data.idAir);
	mb_tmp = *dsmb.nodes[result];
	
	//Thuc hien thao tac voi danh sach ve
	gotoxy(X_TitlePage-10,Y_TitlePage);
	cout << "MA CHUYEN BAY: " << pcb_tmp->data.idFlight << " - DIA DIEM: " << pcb_tmp->data.arrivalAir << " - THOI GiAN: "; PrintDate(&pcb_tmp->data.date);
	MenuManageTicket(mb_tmp, pcb_tmp->data.listTicket);
	if(!SaveFlight(dscb)) Notification("Da luu");
}

bool LoadFlight(PNodeFli &First)
{
    ifstream file("DSCB.TXT", ios_base::in);
    string str;
    PNodeFli pNodeFli = NULL;

    if (!file.is_open())
        return false;
	
	while(!file.eof())
    {
        pNodeFli = new NodeFli;
        getline(file, str, ';');	strcpy(pNodeFli->data.idFlight, str.c_str());
        getline(file, str, ';');	strcpy(pNodeFli->data.arrivalAir, str.c_str());
        getline(file, str, ';');	strcpy(pNodeFli->data.idAir, str.c_str());
        
        getline(file, str, ':');	pNodeFli->data.date.hour = atoi(str.c_str());
		getline(file, str, ';');    pNodeFli->data.date.minute = atoi(str.c_str());
        
        getline(file, str, '/');    pNodeFli->data.date.day = atoi(str.c_str());
        getline(file, str, '/');    pNodeFli->data.date.month = atoi(str.c_str());
        getline(file, str, ';');    pNodeFli->data.date.year = atoi(str.c_str());
        getline(file, str, ';');	pNodeFli->data.status = atoi(str.c_str());

        getline(file, str, ';');	pNodeFli->data.listTicket.size_max = atoi(str.c_str());
        getline(file, str, ';');    pNodeFli->data.listTicket.size_datve = atoi(str.c_str());
       	
        for (int i = 0; i < pNodeFli->data.listTicket.size_max; i++)
        {
            getline(file, str, ';');	strcpy(pNodeFli->data.listTicket.DSV[i].idPas, str.c_str());
            getline(file, str, ';');	strcpy(pNodeFli->data.listTicket.DSV[i].seat, str.c_str());
            if(i != pNodeFli->data.listTicket.size_max-1){
            	getline(file, str, ';');
			}else{
				getline(file, str);
			}
            pNodeFli->data.listTicket.DSV[i].statusTicket = atoi(str.c_str());
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
             << First->data.date.hour << ":"
             << First->data.date.minute << ";"
             << First->data.date.day << "/"
             << First->data.date.month << "/"
             << First->data.date.year << ";"
             << First->data.status << ";"
             << First->data.listTicket.size_max << ";"
             << First->data.listTicket.size_datve << ";";
        for (int i = 0; i < First->data.listTicket.size_max; i++)
        {
            file << First->data.listTicket.DSV[i].idPas << ";"
                 << First->data.listTicket.DSV[i].seat << ";"
                 << First->data.listTicket.DSV[i].statusTicket;
            if (i == First->data.listTicket.size_max - 1 && First->pNext != NULL)
            {
                file << endl;
            }
            else
            {
                file << ";";
            }
        }
        First = First->pNext;
    }

    file.close();
    return true;
}
