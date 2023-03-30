#pragma once

#include <cstring>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;
#include "KeyValue.h"
#include "Constraint.h"
#include "KeyValue.h"
#include "Constraint.h"
//#include "UserInterface.h"

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
//extern string ContentTicket[4];


void InitTicketList(TicketList &ticketList);
bool EmptyList(TicketList);
bool FullList(TicketList);
PTicket CreateTicket(Ticket &ticket);
bool InsertTicketList(TicketList &ticketList, Ticket &ticket);
void InputTicket(Ticket &ticket);
void InputTicketList(TicketList &tickeList);
void CancelTicket(TicketList &ticketList, char *idPass);
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
    // tmp->idPass = idPass;
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

void CancelTicket(TicketList &ticketList, const char *idPass)
{
    for (int i = 0; i < ticketList.size; i++) {
        if (strcmp(idPass,ticketList.DSV[ticketList.size]->idPass) == 0) ticketList.DSV[i]->statusTicket = false;
    }
}
