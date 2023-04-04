#pragma once

#include <cstring>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;
#include "Airplane.h" 
#include "KeyValue.h"
#include "Constraint.h"
#include "KeyValue.h"
#include "Constraint.h"
#include "UserInterface.h"

typedef struct _Ticket {
    char idPas[16];
    char seat[5];
    int statusTicket; // 0: ve trong, 1: ve da duoc dat, 2: ve da huy
} Ticket, PTicket;

typedef struct _ListTicket {
    int size_datve; //so luong ve da dat
    int size_max; // tong so luong ve cua 1 may bay
    Ticket DSV[MAXVE+1];
} ListTicket, PListTicket;

int CurPage, TotalPage;
extern string ContentTicket_Input[2];
extern string ContentTicket_Output[4];
extern string ContentTicket_ThaoTac[5];

void InitListTicket(ListTicket &ListTicket, Airplane Air);
bool ListTicketIsFull(ListTicket ListTicket);
bool ListTicketIsNull(ListTicket ListTicket);
void InputTicket(Ticket &Ticket);
int ConvertMSVtoNumber(const char msv[3], int column);
int CheckSeat(Airplane Air, ListTicket ListTicket, Ticket Ticket);
bool InsertListTicket(Airplane Air, ListTicket &ListTicket, Ticket Ticket);
void ShowTicket(Ticket Ticket, int position);
void ShowListTicketOnePage(ListTicket ListTicket, int startIndex);
void MenuManageTicket(Airplane Air, ListTicket &ListTicket, Ticket Ticket);

//----------------------------------------------------------------//

void InitListTicket(ListTicket &ListTicket, Airplane Air) {
    ListTicket.size_max = Air.col*Air.row;
    ListTicket.size_datve = 0;
    for (int i = 0; i < ListTicket.size_max; i++) {
        ListTicket.DSV[i].statusTicket = 0;
    }
}

bool ListTicketIsFull(ListTicket ListTicket) {
    return ListTicket.size_datve == ListTicket.size_max;
}

bool ListTicketIsNull(ListTicket ListTicket) {
    return ListTicket.size_datve == 0;
}

void InputTicket(Ticket &Ticket) {
    ShowCursor(true);
    CreateForm(ContentTicket_Input,0,2,27);
    gotoxy(X_Add+10,Y_Add); strcpy(Ticket.idPas, Input(10,ID));
    gotoxy(X_Add+10,Y_Add+3); strcpy(Ticket.seat, Input(sizeof(Ticket.seat), ID));
}

int ConvertMSVtoNumber(const char msv[3], int column) {
    int col = (msv[0]-64);
    int row;
    if (msv[2] == '\0') row = msv[1]-48;
    else row = ((msv[1]-48)*10)+(msv[2]-48);
    if (col < 1 || col > 26 || row == 0) {
        return -1;
    }
    return (col-1)+(row-1)*column;
}

bool InsertListTicket(Airplane Air, ListTicket &ListTicket, Ticket Ticket) {
    if (ListTicketIsFull(ListTicket)) return false;
    int vitri = ConvertMSVtoNumber(Ticket.seat,Air.col);
    ListTicket.DSV[vitri] = Ticket;
    ListTicket.DSV[vitri].statusTicket  = 1;
    ListTicket.size_datve++;
    return true;
}

bool CancelTicket(Airplane Air, ListTicket &ListTicket, Ticket Ticket) {
    if (ListTicketIsNull(ListTicket)) return false;
    int vitri = ConvertMSVtoNumber(Ticket.seat,Air.col);
    ListTicket.DSV[vitri].statusTicket = 2;
    return true;
}

int CheckSeat(Airplane Air, ListTicket ListTicket, Ticket Ticket) {
    int vitri = ConvertMSVtoNumber(Ticket.seat, Air.col);
    if (vitri >= ListTicket.size_max || vitri < 0) return -1;
    else {
        if (ListTicket.DSV[vitri].statusTicket == 1) return 0;
        else return 1;
    }
}

bool CheckCMND() {
}

void ShowTicket(Ticket Ticket, int position) {
    int xKeyDisplay[10] = {20,35,55,70,85,100,115,130,145,160};
    if (Ticket.statusTicket != 0) {
    	gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
    	cout << left << setw(8) << "";
    	gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
    	cout << left << setw(8) << "";
        gotoxy(xKeyDisplay[2] + 3, Y_Display + position + 3);
        cout << left << setw(8) << Ticket.seat;
        gotoxy(xKeyDisplay[3] + 3, Y_Display + position + 3);
        if(Ticket.statusTicket == 1) cout << left << setw(3) << "Da dat";
        else cout << left << setw(3) << "Da huy";
    }
}

void ShowListTicketOnePage(ListTicket ListTicket, int startIndex) {
    gotoxy(21,3);
    cout << "Ve: " << ListTicket.size_datve << "/" << ListTicket.size_max;
    int i; int j = 0;
    for (i = 0; i + startIndex < ListTicket.size_max; i++) {
        if (ListTicket.DSV[i+startIndex].statusTicket != 0) {
            ShowTicket(ListTicket.DSV[i+startIndex],j);
            j++;
            cout << endl;
        }
    }
    RemoveExceedMember(i,5);
    gotoxy(X_Page,Y_Page);
    cout << "Trang " << CurPage << "/" << TotalPage;
}

void MenuManageTicket(Airplane Air, ListTicket &ListTicket, Ticket Ticket) {
    ShowCursor(false);
	CurPage = !ListTicketIsNull(ListTicket);
	TotalPage = (int)ceil((double)ListTicket.size_max/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentTicket_Output, sizeof(ContentTicket_Output)/sizeof(string));
	ShowListTicketOnePage(ListTicket, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY VE";
	
	int signal;

    while (true) {
        signal = menu_dong(X_ThaoTac,Y_ThaoTac,5,ContentTicket_ThaoTac);
        switch(signal) {
            case 1: //Order
            {
                if (CurPage == 0) CurPage = 1;
                if (ListTicketIsFull(ListTicket)) {
                    Notification("Da het ve");
                    break;
                }
                gotoxy(X_Add, Y_Add-1);
                InputTicket(Ticket);
                RemoveForm(0,4,27);
                if (CheckSeat(Air,ListTicket,Ticket) == -1) {
                    Notification("Vi tri nay khong ton tai");
            		break;
                } else if (CheckSeat(Air,ListTicket,Ticket) == 0) {
                	Notification("Vi tri nay da co nguoi dat");
                	break;
				}
                else {
                    InsertListTicket(Air,ListTicket,Ticket);
                    Notification("Them thanh cong");
                } 
                system("color 0E");
                ShowListTicketOnePage(ListTicket, (CurPage-1)*NumberPerPage);
                ShowCursor(false);
                break;
            }
            case 2: //Cancel
            {
                if (ListTicketIsNull(ListTicket)) {
                    Notification("Khong con ve de xoa");
                    break;
                }
                gotoxy(X_Add,Y_Add-1);
                InputTicket(Ticket);
                RemoveForm(0,4,27);
                if (CheckSeat(Air,ListTicket,Ticket) == -1) {
                    Notification("Vi tri nay khong ton tai");
                    break;
                } else if (CheckSeat(Air,ListTicket,Ticket) == 1) {
                    Notification("Vi tri nay chua duoc dat");
                    break;
                } else {
                    CancelTicket(Air,ListTicket,Ticket);
                    Notification("Huy ve thanh cong");
                }
                system("color 0E");
                ShowListTicketOnePage(ListTicket,(CurPage - 1)/NumberPerPage);
                break;
            }
            case 3: //Edit
            {
                break;
            }
            case 4: //Previous Page
            {
                break;
            }
            case 5: //Next Page 
            {
                break;
            }
            default: return;
        }
    }
}
