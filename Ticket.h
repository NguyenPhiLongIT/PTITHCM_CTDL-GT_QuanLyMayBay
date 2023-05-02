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
    char idPas[13];
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
extern string ContentTicket_Output[3];
extern string ContentTicket_ThaoTac[5];

void InitSeats(ListTicket &listTicket, Airplane Air);
void InitListTicket(ListTicket &listTicket,Airplane Air);
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

void InitSeats(ListTicket &listTicket, Airplane Air) {
	for (int i = 0; i < Air.col; i++) {
		for (int j = 0; j < Air.row; j++) {
			sprintf(listTicket.DSV[Air.col*j+i].seat,"%c%.2d",i+'A',j+1);
		}
	}
}

void InitListTicket(ListTicket &listTicket,Airplane Air){
    for (int i = 0; i < listTicket.size_max; i++) {
		listTicket.DSV[i].statusTicket = 0;
		memset(listTicket.DSV[i].idPas,0,sizeof(listTicket.DSV[i].idPas));
		InitSeats(listTicket,Air);
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
    gotoxy(X_Add+12,Y_Add); strcpy(Ticket.idPas, Input(10,Number));
    gotoxy(X_Add+12,Y_Add+3); strcpy(Ticket.seat, Input(sizeof(Ticket.seat), ID));
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
        gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
        cout << left << setw(8) << Ticket.seat;
        gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
        if(Ticket.statusTicket == 1) cout << left << setw(3) << "Da dat";
        else if (Ticket.statusTicket == 0) cout << left << setw(3) << "Con ve";
        else cout << left << setw(3) << "Da huy";
    	gotoxy(xKeyDisplay[2] + 3, Y_Display + position + 3);
    	cout << left << setw(8) << Ticket.idPas;
}

void ShowListTicketOnePage(ListTicket ListTicket, int startIndex) {
    gotoxy(3,3);
    cout << "Ve: " << ListTicket.size_datve << "/" << ListTicket.size_max;
    
    WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
    
    int i; int j = 0;
    
    for(i = 0 ; i + startIndex < ListTicket.size_max && i < NumberPerPage; i++)
	{
		ShowTicket(ListTicket.DSV[i+startIndex],i); 
	} 
	SetColor(curColor);
	RemoveExceedMember(i, 5);
    gotoxy(X_Page,Y_Page);
    cout << "Trang " << CurPage << "/" << TotalPage;
}

void ChangeTicketMenuManagerPage(ListTicket listTicket)
{
	Display( ContentTicket_Output,sizeof(ContentTicket_Output)/sizeof(string) );
	ShowListTicketOnePage(listTicket,(CurPage-1)*NumberPerPage);
}

void MenuManageTicket(Airplane Air, ListTicket &ListTicket) {
    ShowCursor(false);
	CurPage = 1;
	TotalPage = (int)ceil((double)ListTicket.size_max/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentTicket_Output, sizeof(ContentTicket_Output)/sizeof(string));
	ShowListTicketOnePage(ListTicket, 0);	
	
	Ticket ticket_tmp;
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
                //gotoxy(X_Add, Y_Add-1);
                InputTicket(ticket_tmp);
                RemoveForm(0,4,27);
                int vitri = ConvertMSVtoNumber(ticket_tmp.seat,Air.col);
                
                if (ListTicket.DSV[vitri].statusTicket == 2) {
                	Notification("Ve da huy. Khong the dat!");
                	break;
				}
                
                if (CheckSeat(Air,ListTicket,ticket_tmp) == -1) {
                    Notification("Vi tri nay khong ton tai");
            		break;
                } else if (CheckSeat(Air,ListTicket,ticket_tmp) == 0) {
                	Notification("Vi tri nay da co nguoi dat");
                	break;
				}
                else {
                    InsertListTicket(Air,ListTicket,ticket_tmp);
                    Notification("Them thanh cong");
                } 
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
                //gotoxy(X_Add,Y_Add-1);
                InputTicket(ticket_tmp);
                RemoveForm(0,4,27);
                if (CheckSeat(Air,ListTicket,ticket_tmp) == -1) {
                    Notification("Vi tri nay khong ton tai");
                    break;
                } else if (CheckSeat(Air,ListTicket,ticket_tmp) == 1) {
                    Notification("Vi tri nay chua duoc dat");
                    break;
                } else {
                    CancelTicket(Air,ListTicket,ticket_tmp);
                    Notification("Huy ve thanh cong");
                }
                ShowListTicketOnePage(ListTicket,(CurPage - 1)/NumberPerPage);
                break;
            }
            case 3: //Previous Page
            {
            	if(CurPage == 1) break;
				else{
					CurPage --;
					ChangeTicketMenuManagerPage(ListTicket);
					break;
				}
            }
            case 4: //Next Page
            {
            	if(CurPage >= TotalPage) break;
				CurPage ++;
				ChangeTicketMenuManagerPage(ListTicket);
                break;
            }
            default: return;
        }
    }
}
