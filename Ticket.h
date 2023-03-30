#pragma once
#include "KeyValue.h"
#include "Constraint.h"
#include "UI.h"
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct _Ticket
{
    char *idPass;          // string *id(luu dia chi id cua khach hang);
    int col;           // so day
    int row;           // so dong
    bool statusTicket; // false: huy; true: da dat
} Ticket, *PTicket;

typedef struct _TicketList
{
    int size;
    Ticket *DSV[MAXVE + 1];
}TicketList, *PTicketList;

//Thong tin vi tri hien tai
int CurPosTicket = 0;
int CurTicketPage = 1;
int TotalTicketPage = 0;

//-------------------------------------------------------------//
void InitTicketList(TicketList &ticketList);
bool EmptyList(TicketList);
bool FullList(TicketList);
PTicket CreateTicket(Ticket &ticket);
bool InsertTicketList(TicketList &ticketList, Ticket &ticket);
void InputTicket(Ticket &ticket);
void InputTicketList(TicketList &tickeList);
void CancelTicket(TicketList &ticketList, char *id);
void ShowTicket(PTicket pTicket, int position);
void ShowListTicketOnePage(TicketList ticketList, int startIndex);
void ChangeTicketMenuManagerPage(TicketList ticketList);
void MenuManagaTicket(TicketList ticketList, Ticket ticket);

//----------------------------------------------------------------//

void InitTicketList(TicketList &ticketList)
{
    ticketList.size = 0;
}

PTicket CreateTicket(Ticket &ticket)
{
    PTicket tmp = new Ticket;
    *tmp = ticket;
    // tmp->id = id;
    // tmp->col = col;
    // tmp->row = row;
    // tmp->statusTicket = false;
    return tmp;
}

bool EmptyList(TicketList ticketList)
{
    return ticketList.size == 0;
}

bool FullList(TicketList ticketList)
{
    return ticketList.size == MAXVE + 1;
}

bool InsertTicketList(TicketList &ticketList, Ticket &ticket)
{
    if (FullList(ticketList)) return false;
    ticketList.DSV[ticketList.size] = CreateTicket(ticket);
    ticketList.DSV[ticketList.size]->statusTicket = true;
    ticketList.size++;
    return true;
}

void InputTicket(Ticket &ticket)
{
    gotoxy(X_Add+10,Y_Add);       strcpy(ticket.idPass, Input(sizeof(ticket.idPass), ID));
    gotoxy(X_Add+10,Y_Add+3);     std::cin  >> ticket.col;
    gotoxy(X_Add+10,Y_Add+6);     std::cin >> ticket.row;
}

void InputTicketList(TicketList &tickeList)
{
    int size;
    cout << "So luong ve can dat: "; cin >> size;
    for (int i = 0; i < size; i++) {
        CreateForm(ContentTicket, 0, 4, 27);
    	Ticket ticket;
    	cin.ignore();
    	InputTicket(ticket);
    	InsertTicketList(tickeList, ticket);
    }
}

void CancelTicket(TicketList &ticketList, const char *id)
{
    for (int i = 0; i < ticketList.size; i++) {
        if (strcmp(id,ticketList.DSV[ticketList.size]->idPass) == 0) ticketList.DSV[i]->statusTicket = false;
    }
}

void ShowTicket(PTicket pTicket, int position) {
    int xKeyDisplay[10] = {20,40,60,80,100,120,130,140,150,160};

    gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    printf("%-15s", pTicket->idPass);			//dung printtf %s: de ko bi loi dinh dang khi chuyen trang
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    printf("%-15d", pTicket->col);
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    printf("%-15d", pTicket->row);
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    printf("%-15d", pTicket->statusTicket);
}

void ShowListTicketOnePage(TicketList ticketList, int startIndex)
{
	gotoxy(21,3);
	cout << " So luong ve : " << ticketList.size;
	int i;
	for(i = 0 ; i + startIndex < ticketList.size && i < NumberPerPage; i++)
	{
        ShowTicket(ticketList.DSV[i+startIndex],i);
	} 
	RemoveExceedMember(i, 5);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurTicketPage <<"/"<< TotalTicketPage; 
}

void ChangeTicketMenuManagerPage(TicketList ticketList)
{
    gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY VE";

    Display(ContentTicket, sizeof(ContentTicket)/sizeof(string));
    ShowListTicketOnePage(ticketList,(CurTicketPage-1)*NumberPerPage);
}

void MenuManagaTicket(TicketList ticketList, Ticket ticket)
{
    CurTicketPage = 1;
    TotalTicketPage = (int)ceil((double)ticketList.size/NumberPerPage);
    
    Display(ContentTicket,sizeof(ContentTicket)/sizeof(string));
    ShowListTicketOnePage(ticketList,0);

    gotoxy(X_TitlePage, Y_TitlePage);
    cout << "QUAN LY VE";

    int signal;
    while (true)
    {
        menu:
        signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentThaoTac);
        switch(signal) {
            case 1: //Insert
            {
                if(FullList(ticketList))
                {
                    Notification("Da het ve, khong the them");
                    goto menu;
                }
                gotoxy(X_Add,Y_Add-1);
                InputTicketList(ticketList);
                Notification("Dat ve thanh cong");
                system("color 0E");
                TotalTicketPage = (int)ceil((double)ticketList.size/NumberPerPage);
                RemoveForm(0, 4, 27);
                ShowListTicketOnePage(ticketList,(CurTicketPage-1)*NumberPerPage);
            }
            default: return;
        }
    }
}
