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
#include "Sort.h"

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

void InitFlight(Flight &flight, ListAir listAir);
int Size(PNodeFli &pNodeFli);
int SizeTicketAvailable(PNodeFli &first);
int SizeDateDes(PNodeFli &first, Date date, const char* arrival);

bool LessAmount(Airplane *&a, Airplane *&b);
PNodeFli CreateFlight(Flight &flight);
void InsertListFlight(PNodeFli &first, Flight flight);
bool CancleFlight(PNodeFli pNodeFli);

PNodeFli FindFlight(PNodeFli &first, const char *idFli);
PNodeFli FindFlightByIdPlane(PNodeFli &first, const char *idAir);
int FindIndexFlight(PNodeFli first, const char *idFli);
int FindDestination(PNodeFli first, const char *arrivalAir);

void AutoUpdateFlightStatus(PNodeFli &pNodeFli);
int EditDateTime(PNodeFli &pNodeFli, Date date);
bool CheckDate(PNodeFli first, PDate date);

void InputFlight(PNodeFli &first, Flight &flight, ListAir dsmb, bool Edit, bool Cancle);
void ShowFlight(Flight &flight, int position);
void ShowListFlightOnePage(PNodeFli first, int startIndex);
void ChangeFlightMenuManagerPage(PNodeFli first);
void MenuManageFlight(PNodeFli &first, ListAir listAir);

void ListFlightDateAndDes(PNodeFli first, Date date, const char* arrival, int startIndex, bool ticketAvailable);
void ChangeListFlightDateAndDesPage(PNodeFli first, Date date, const char* arrival, bool ticketAvailable);

void MenuManageListTicket(ListAir &listAir, PNodeFli &listFlight, TreePass &rootPass);

bool LoadFlight(PNodeFli &first);
bool SaveFlight(PNodeFli first);


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
		return 1;
	}
	return 0;
}

/*
	PNodeFli temp[26] = {0}; 
	while(first != NULL){
		if(temp[first->data.idFli[0]-'A'] == NULL){
			temp[first->data.idFli[0]-'A'] = first->data;
		}
	}
	for(... it
*/
//Tim chuyen bay
PNodeFli FindFlight(PNodeFli &first, const char *id)
{
	if (first == NULL) return NULL;
	PNodeFli p;
	for (p = first; p != NULL; p = p->pNext)
		if (strcmp(p->data.idFlight, id) == 0)
			return p;
	return NULL;

//	if (first == NULL) return NULL;
//	PNodeFli left = first;
//	PNodeFli right = first;
//	while(left->pNext != NULL)
//		right = right->pNext;
//	PNodeFli p;
//	while(strcmp(left->data.idFlight, right->data.idFlight) <= 0){
//		p = (left + right)/2;
//		if(strcmp(p->data.idFlight, id) == )
//	}
}

//Tra ve chuyen bay theo ma may bay
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

bool FindDate(PNodeFli first, Flight fli){
	for(PNodeFli p = first; p != NULL; p = p->pNext)
	{
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
	return true;
}

//Kiem tra ngay thang nam
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
			p->data.status = 3;
		}
		else if(p->data.listTicket.sizeBooked == p->data.listTicket.sizeTotal){
			p->data.status = 2;
		}			
	}
}

//Chinh sua ngay
int EditDateTime(PNodeFli &first, Date date){
	if(IsValidDate(&date)){
		first->data.date = date;
		return 1;
	}
	return 0;
}

//Nhap thong tin chuyen bay
void InputFlight(PNodeFli &first, Flight &flight, ListAir listAir, bool Edit = false, bool Cancle = false){
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri chuyen bay
	if(Edit == false && Cancle == false) CreateForm(ContentFlight, 0, 4, 32);
	while(true){
		switch(ordinal){
			case 0:{	//Nhap idFlight
				do{
					CreateRow(X_Add, Y_Add, ContentFlight[0], 27);
					gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
					//Mang con tro
					//Duyet DSLK
					position = FindIndexFlight(first, flight.idFlight);
					if(strlen(flight.idFlight) == 0){
						Notification("Vui long khong bo trong");
					}
					if(position > -1 && Edit == false && Cancle == false){
						Notification("ID chuyen bay da ton tai");
					}
					if(position < 0 && (Edit == true || Cancle == true) && strlen(flight.idFlight) != 0){
						Notification("ID chuyen bay khong ton tai");
					}
					if(position >-1 && Edit == true) {
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
							Notification("Chuyen bay khong con hoat dong! Khong the hieu chinh ngay gio");
							RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
							return;
						}
					}
					if(position > -1 && Cancle == true){
						ShowCursor(false);
						PNodeFli p = FindFlight(first, flight.idFlight);
						if(p->data.status == HUYCHUYEN || p->data.status == HOANTAT){
							Notification("Chuyen bay khong con hoat dong! Khong the huy chuyen");
						}
						else{
							Box(X_Notification,Y_Notification, 29, 3, "Ban co chac muon huy chuyen? ");
							gotoxy(X_Notification+1,Y_Notification+2); cout << "ESC: Thoat - ENTER: Huy";
							char c = _getch();
							RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
							RemoveBox(X_Notification,Y_Notification, 29, 3);
						
							if(c == ESC){
								Notification("Huy that bai!");
								return;
							}
							if (c == ENTER) {
								if(CancleFlight(p)){
									if(SaveFlight(first)) {
										Notification("Huy thanh cong!");
									}	
								}
							}
							return;					
						}
						
					}
					if(
						(position > -1 && Edit == true) 
						||
						(position < 0 && Edit == false && Cancle == false && (strlen(flight.idFlight) != 0))
					) break;
				}
				while(true);
				  
				ordinal++;
				break;
			}
			case 1:{	//Nhap arrivalAir
				gotoxy(X_Add+11,Y_Add+3);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), AutoCapitalText));
				if(strlen(flight.arrivalAir) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}		
			case 2:{	//Nhap idAir
				char signal;
				char strFind[1000] = "";
				int cursize = 0;
				int index;
				RemoveTable(ContentFlight, 6);
				gotoxy(X_Add+10,Y_Add+6); cout << "			";
				do{
					if(cursize == 0){
						Display( ContentAirplane,sizeof(ContentAirplane)/sizeof(string) );
						ShowListAirplaneOnePage(listAir,0);
					}
					index = 0;
					gotoxy(X_Add+10+cursize,Y_Add+6);
					signal = getch();
					Clean(xKeyDisplay[0]+1,Y_Display+3,xKeyDisplay[1]-1, Y_Display + 24);    
					Clean(xKeyDisplay[1]+1,Y_Display+3,xKeyDisplay[2]-1, Y_Display + 24);    
					Clean(xKeyDisplay[2]+1,Y_Display+3,xKeyDisplay[3]-1, Y_Display + 24);    
					Clean(xKeyDisplay[3]+1,Y_Display+3,xKeyDisplay[4]-1, Y_Display + 24);    
					Clean(xKeyDisplay[4]+1,Y_Display+3,xKeyDisplay[5]-1, Y_Display + 24);    
					if (signal == -32 || signal == 0 || signal == 224)
					{
						getch();
						continue;
					}
					if(ID(signal) && cursize < 1000 && signal != BACKSPACE){
						strFind[cursize++] = signal;
            			std::cout << signal;
					}
					if (
						(cursize == 1 && (Space(signal) || Dash(signal) || Underscore(signal))) ||
						(cursize > 1 && Space(signal) && Space(strFind[cursize - 2])) ||
						(cursize > 0 && signal == BACKSPACE))
					{
						std::cout << "\b \b";
						strFind[cursize--] = '\0';
					}
					for(int i = 0; i + index < listAir.size; i++){
						if(index == 20) break;
						if(strstr(listAir.nodes[i]->idAir, strFind) != NULL){
							ShowAirplane(listAir.nodes[i], index);
							index++;
						}
					}
				}while (
					(signal != ENTER) &&
					(signal != TAB)
				);
				strcpy(flight.idAir, strFind);
				position = IndexAirplane(listAir, flight.idAir);
				if(strlen(flight.idAir) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				if(position < 0){
					Notification("ID may bay khong ton tai");
					break;
				}
				ordinal++;
				listAir.nodes[position]->amount++;
				break;
			}
			case 3:{	//Nhap DateTime		
				do {
					gotoxy(X_Add+13,Y_Add+9);
					cout << "          ";
					gotoxy(X_Add+13,Y_Add+9);
					InputDate(&flight.date);
					if(!FindDate(first, flight)) {
						Notification("Thoi gian khong hop le! Vui long nhap thoi gian cach 2 tieng");
					}
					else break;
				} while(true);
				ordinal++;
				break;
			}
			case 4:{
				InitFlight(flight,listAir);
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
void ShowFlight(Flight &fli, int position)
{	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idFlight;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(12) << fli.arrivalAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(10) << fli.idAir;
    gotoxy(xKeyDisplay[3] + 2, Y_Display + position +3);
    PrintDate(&fli.date);
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position + 3);
    cout << fli.listTicket.sizeBooked << "/" << left << setw(10) <<  fli.listTicket.sizeTotal;
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

//Hien thi danh sach chuyen bay trong 1 trang
void ShowListFlightOnePage(PNodeFli first, int startIndex)
{
	gotoxy(3,3); cout << " So luong chuyen bay : " << Size(first);
	
	if(first == NULL) return;
	
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int count = -1;
	AutoUpdateFlightStatus(first);
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
	gotoxy(3,3);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach chuyen bay khi qua trang
void ChangeFlightMenuManagerPage(PNodeFli first)
{
	Display( ContentFlight,sizeof(ContentFlight)/sizeof(string) );
	ShowListFlightOnePage(first,(CurPage-1)*NumberPerPage);
}

//Quan ly chuyen bay
void MenuManageFlight(PNodeFli &first, ListAir listAir){
	CurPage = 1;
	TotalPage = (int)ceil((double)Size(first)/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentFlight, sizeof(ContentFlight)/sizeof(string));
	ShowListFlightOnePage(first, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";
	
	Flight fli;
	int signal;
	while(true)
	{
		menu:
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,6,ContentFlightSelect);
		switch(signal) {
			case 1: // Them chuyen bay
			{
				if(CurPage == 0) CurPage = 1;
				InputFlight(first, fli, listAir);

				TotalPage = (int)ceil((double)Size(first)/NumberPerPage);
//				ShowListFlightOnePage(first, (CurPage-1)*NumberPerPage);
				ChangeFlightMenuManagerPage(first);
				ShowCursor(false);
				break;
			}
			edit: case 2: //Chinh sua ngay thang nam
			{
				ShowCursor(true);
				if(first == NULL) {
					Notification("Danh sach rong");
					break;
				}
				InputFlight(first, fli, listAir, true, false);
				ShowListFlightOnePage(first, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;		
			}
			case 3: //Huy chuyen bay
			{
				ShowCursor(true);
				if(first == NULL) {
					Notification("Danh sach rong");
					break;
				}			
				InputFlight(first, fli, listAir, false, true);
				ShowListFlightOnePage(first, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case LEFT:
			case 4: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage--;
					ChangeFlightMenuManagerPage(first);
				}
				break;
			}
			case RIGHT:
			case 5:	//Chuyen trang tiep
			{
				if(CurPage >= TotalPage) break;
				else{
					CurPage++;
					ChangeFlightMenuManagerPage(first);
				}
				break;
			}
			default: return;
			
		}
	}
}

//Xuat danh sach chuyen bay theo ngay va dia diem trong 1 trang
void ListFlightDateAndDes(PNodeFli first, Date date, const char* arrival, int startIndex, bool ticketAvailable = false){
	Display( ContentFlight,sizeof(ContentFlight)/sizeof(string) );
	if(first == NULL) return;
	
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int count = -1;
	AutoUpdateFlightStatus(first);
	
	int x = 60;
	int y = 62;

	for(PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (p->data.status == CONVE)	count++;
		if(count == startIndex){
			int i = -1;
			while(p != NULL && i < NumberPerPage - 1){
				if(CheckDate(p, &date) && strcmp(p->data.arrivalAir, arrival) == 0 && p->data.status == CONVE && !ticketAvailable){
					ShowFlight(p->data, ++i);
				}
				else if(p->data.status == CONVE && ticketAvailable){
					ShowFlight(p->data, ++i);
				}
				p = p->pNext;
			}
			RemoveExceedMember(i+1, 6);
			break;
		}
	}
	gotoxy(3,3); 
	if(ticketAvailable) cout << " So luong chuyen bay : " << SizeTicketAvailable(first);
	else cout << " So luong chuyen bay : " << SizeDateDes(first,date,arrival);
	SetColor(curColor);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}


PNodeFli *ListFlightInDate(PNodeFli first, PDate date){
	int n = Size(first);
	int index = 0;
	PNodeFli *list = new PNodeFli[n];
	for(PNodeFli temp = first; temp != NULL; temp = temp->pNext){
		if(
			temp->data.date.year == date->year 		&&
			temp->data.date.month == date->month 	&&
			temp->data.date.day == date->day
		){
			list[index++] = temp;
		}
	}
	return list;
}

//Thay doi danh sach chuyen bay theo ngay va dia diem sang trang khac
void ChangeListFlightDateAndDesPage(PNodeFli first, Date date, const char* arrival, bool ticketAvailable) {
	ListFlightDateAndDes(first, date, arrival, (CurPage-1)*NumberPerPage, ticketAvailable);
}

//Quan ly danh sach ve
void MenuManageListTicket(ListAir &listAir, PNodeFli &listFlight, TreePass &rootPass) {
	Flight flight;
	Airplane air;
	PNodeFli pFlight;
	Date date;
	bool ticketAvailable = true;
	int signal;
	
	CurPage = 1;
	TotalPage = (int)ceil((double)SizeTicketAvailable(listFlight)/NumberPerPage); 	//ceil : lam tron
	Display(ContentFlight,sizeof(ContentFlight)/sizeof(string));
	ListFlightDateAndDes(listFlight, date, flight.arrivalAir, 0, ticketAvailable);
	gotoxy(X_TitlePage-4,Y_TitlePage);
	cout << "DANH SACH CAC CHUYEN BAY CON VE";
	
	if(listFlight == NULL) {
		Notification("Danh sach chua co chuyen bay nao!");
		return;
	}
	
	while (true) {
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,5,ContentTicketSelect1);
		switch(signal) {
			case 1: //Chon chuyen bay muon dat
            {
            	do {
					CreateRow(X_Add, Y_Add, ContentFlight[0], 32);
					gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
					pFlight = FindFlight(listFlight,flight.idFlight);
					if (pFlight == NULL) Notification("Chuyen bay khong ton tai");
					else if (pFlight->data.status == HETVE) Notification("Chuyen bay da het ve");
					else if (pFlight->data.status == HUYCHUYEN) Notification("Chuyen bay da bi huy");
					else if (pFlight->data.status == HOANTAT) Notification("Chuyen bay da hoan tat");
					else break;
				} while (true);
				
				RemoveRow(X_Add, Y_Add, ContentFlight[0], 32);
				RemoveTable(ContentFlight,sizeof(ContentFlight)/sizeof(string));
	
				//Luu vi tri may bay cua chuyen bay do
				int result = IndexAirplane(listAir,pFlight->data.idAir);
				air = *listAir.nodes[result];
	
				//Thuc hien thao tac voi danh sach ve
				gotoxy(X_TitlePage-10,Y_TitlePage);
				cout << "MA CHUYEN BAY: " << pFlight->data.idFlight << " - DIA DIEM: " << pFlight->data.arrivalAir << " - THOI GiAN: "; PrintDate(&pFlight->data.date);
				if(rootPass == NULL){
					system("pause");
				}
				MenuManageTicket(air, pFlight->data.listTicket,rootPass);
				if(SaveFlight(listFlight));
				if(SaveTreePass(rootPass));
                return;
            }
            case 2: //Loc chuyen bay theo ngay va dia diem
            {
				CreateRow(X_Add, Y_Add, ContentFlight[1], 32); 
				CreateRow(X_Add, Y_Add+3, ContentFlight[3], 32);
				gotoxy(X_Add+12,Y_Add);     	strcpy(flight.arrivalAir, Input(sizeof(flight.arrivalAir), AutoCapitalText));	
				gotoxy(X_Add+14,Y_Add+3); 		InputDate(&date, true);
					
				RemoveRow(X_Add, Y_Add, ContentFlight[1], 32);
				RemoveRow(X_Add, Y_Add+3, ContentFlight[3], 46);
//				PNodeFli *listInDate = ListFlightInDate(listFlight, &date);
//				ShowListFlightOnePage(listInDate, 0);
				 
				RemoveTable(ContentFlight,sizeof(ContentFlight)/sizeof(string));
				CurPage = 1;
				TotalPage = (int)ceil((double)SizeDateDes(listFlight,date,flight.arrivalAir)/NumberPerPage);
				ListFlightDateAndDes(listFlight, date, flight.arrivalAir,0);
				ticketAvailable = true;
                break;
            }
            case LEFT:
            case 3: //Trang truoc
            {
            	if(CurPage == 1) break;
				else{
					CurPage --;
					ChangeListFlightDateAndDesPage(listFlight, date, flight.arrivalAir, ticketAvailable);
					break;
				}
            }
            case RIGHT:
            case 4: //Trang sau
            {
            	if(CurPage >= TotalPage) break;
				CurPage ++;
				ChangeListFlightDateAndDesPage(listFlight, date, flight.arrivalAir, ticketAvailable);
                break;
            }
            default: return;
        }
	}
}

//Xuat thong tin 1 may bay
void ShowAirplaneFly(PAirplane pAir, int position)
{	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(8) << pAir->idAir;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(4) << (pAir->amount);
}

//Xuat danh sach may bay trong 1 trang
void ShowListAirplaneFlyOnePage(ListAir list, int startIndex)
{
	gotoxy(3,3);
	cout << " So luong may bay : " << list.size;
	int i;
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	for(i = 0 ; i + startIndex < list.size && i < NumberPerPage; i++)
	{
		ShowAirplaneFly(list.nodes[i+startIndex], i); 
	} 
	SetColor(curColor);
	RemoveExceedMember(i, 2);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach may bay qua trang khac
void ChangeAirplaneFlyMenuManagerPage(ListAir list)
{
	Display( ContentListAir,sizeof(ContentListAir)/sizeof(string) );
	ShowListAirplaneFlyOnePage(list,(CurPage-1)*NumberPerPage);
}

//Thong ke so luot thuc hien chuyen bay cua may bay
void ListAirplaneFly(PNodeFli first, ListAir listAir){
	PNodeFli p;
//	for (int i = 0; i < listAir.size; i++){
//		 for (p = first; p != NULL; p = p->pNext){
//			if(strcmp(p->data.idAir, listAir.nodes[i]->idAir) == 0) listAir.nodes[i]->amount++;
//		}
//	}
//	if(!SaveAirplane(listAir)){
//		Notification("Luu file that bai!");
//	}
	ShowCursor(false);
	CurPage = 1;
	TotalPage = (int)ceil((double)listAir.size/NumberPerPage);
	
	Display(ContentAirplane, sizeof(ContentListAir)/sizeof(string));
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "DANH SACH THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA MAY BAY";
	Quicksort<Airplane*>(listAir.nodes,0, listAir.size-1, LessAmount);
	ShowListAirplaneFlyOnePage(listAir, 0);
	
	while(true)
	{
		char c = _getch();
		if (c == -32) {
			c = _getch();
			if (c == LEFT && CurPage != 1) {
				CurPage --;
				ChangeAirplaneFlyMenuManagerPage(listAir);
			} else if (c == RIGHT && CurPage < TotalPage) {
				CurPage ++;
				ChangeAirplaneFlyMenuManagerPage(listAir);
			}
		} else if (c == ESC) {
			return;
		}
	}
}

//So luong hanh khach theo chuyen bay
int CountPassOfFlight(PNodeFli fli){
	int count = 0;
	if(fli == NULL){
		return count;
	}
	
	for (int i = 0; i < fli->data.listTicket.sizeTotal; i++) {
		if (fli->data.listTicket.DSV[i].statusTicket == 1) count ++;
	}
	return count;
}

//Xuat thong tin hanh khach theo chuyen bay
void ShowPassFli(Passenger &pass, PNodeFli fli, int position)
{
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
	cout << left << setw(8) << position+1;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
    cout << left << setw(8) << fli->data.listTicket.DSV[position].seat;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.id;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.firstName << " " << pass.lastName;
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position + 3);
	cout << left << setw(8) << (pass.gender ? "Nu" : "Nam");
}

//Xuat danh sach hanh khach theo chuyen bay trong 1 trang
void ShowListPassFliOnePage(TreePass root, PNodeFli fli, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int position = startIndex;
	int count = 0;
	
//	gotoxy(3,3);
//	cout << " So luong hanh khach : " << position;
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		
		for (int i = 0; i < fli->data.listTicket.sizeTotal; i++) {
			if (fli->data.listTicket.DSV[i].statusTicket == 1 &&  strcmp(fli->data.listTicket.DSV[i].idPas, temp->id) == 0) {
				count ++;
				ShowPassFli(*temp, fli, position);
				++position;
				break;
			} 	
		}
		
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
		if(position >= NumberPerPage){
			break;
		}
	}
	
	SetColor(curColor);
	gotoxy(X_Display, Y_Display-1);
	cout << "So luong hanh khach: "<< count;
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach hanh khach sang trang khac
void ChangePassFliMenuManagerPage(TreePass root, PNodeFli fli)
{
	Display(ContentListPass,sizeof(ContentListPass)/sizeof(string) );
	ShowListPassFliOnePage(root,fli,(CurPage-1)*NumberPerPage);
}

//Danh sach hanh khach thuoc chuyen bay X
void ListPassOfFlight(PNodeFli listFlight, TreePass rootPass){
	ShowCursor(false);
	CurPage = 1;
	
	Flight flight;
	PNodeFli pFlight;
	do {
		CreateRow(X_Add, Y_Add, ContentFlight[0], 32);
		gotoxy(X_Add+10,Y_Add);       	strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
		pFlight = FindFlight(listFlight,flight.idFlight);
		if (pFlight == NULL) Notification("Chuyen bay khong ton tai");
		else if (pFlight->data.status == HETVE) Notification("Chuyen bay da het ve");
		else if (pFlight->data.status == HUYCHUYEN) Notification("Chuyen bay da bi huy");
		else if (pFlight->data.status == HOANTAT) Notification("Chuyen bay da hoan tat");
		else break;
	} while (true);
				
	RemoveRow(X_Add, Y_Add, ContentFlight[0], 32);	
	TotalPage = (int)ceil((double)CountPassOfFlight(pFlight)/NumberPerPage);
	Display(ContentListPass, sizeof(ContentListPass)/sizeof(string));
	
	gotoxy(X_TitlePage-10,Y_TitlePage);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << pFlight->data.idFlight;
	gotoxy(X_TitlePage-20, Y_TitlePage+1); cout << "Ngay gio khoi hanh: "; PrintDate(&pFlight->data.date); 
	gotoxy(X_TitlePage+25, Y_TitlePage+1); cout << "Noi den: " << pFlight->data.arrivalAir;
	
	ShowListPassFliOnePage(rootPass, pFlight, 0);
	
	while(true)
	{
		char c = _getch();
		if (c == -32) {
			c = _getch();
			if (c == LEFT && CurPage != 1) {
				CurPage --;
				ChangePassFliMenuManagerPage(rootPass, listFlight);
			} else if (c == RIGHT && CurPage < TotalPage) {
				CurPage ++;
				ChangePassFliMenuManagerPage(rootPass, listFlight);
			}
		} else if (c == ESC) {
			return;
		}
	}
}

//Load file danh sach chuyen bay
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

        getline(file, str, ';');	pNodeFli->data.listTicket.sizeTotal = atoi(str.c_str());
        getline(file, str, ';');    pNodeFli->data.listTicket.sizeBooked = atoi(str.c_str());
       	
       	pNodeFli->data.listTicket.DSV = new Ticket[pNodeFli->data.listTicket.sizeTotal];
        for (int i = 0; i < pNodeFli->data.listTicket.sizeTotal; i++)
        {
            getline(file, str, ';');	strcpy(pNodeFli->data.listTicket.DSV[i].idPas, str.c_str());
            getline(file, str, ';');	strcpy(pNodeFli->data.listTicket.DSV[i].seat, str.c_str());
            if(i != pNodeFli->data.listTicket.sizeTotal-1){
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

//Luu file danh sach chuyen bay
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
             << First->data.listTicket.sizeTotal << ";"
             << First->data.listTicket.sizeBooked << ";";
        
        for (int i = 0; i < First->data.listTicket.sizeTotal; i++)
        {
            file << First->data.listTicket.DSV[i].idPas << ";"
                 << First->data.listTicket.DSV[i].seat << ";"
                 << First->data.listTicket.DSV[i].statusTicket;
            if (i == First->data.listTicket.sizeTotal - 1 && First->pNext != NULL)
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
