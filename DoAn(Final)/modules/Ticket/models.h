#ifndef __TICKET__UTILS__
#define __TICKET__UTILS__

#include <iostream>
#include <string.h>
#include "types.h"
#include "../Airplane/types.h"
#include "../Flight/types.h"
#include "../Date/models.h"
#include "../../utils/UserInterface.h"
#include "../../utils/String.h"

//Khoi tao cho ngoi
void InitSeats(ListTicket &listTicket, Airplane air) {
	for (int i = 0; i < air.col; i++) {
		for (int j = 0; j < air.row; j++) {
			sprintf(listTicket.DSV[air.col*j+i].seat,"%c%.2d",i+'A',j+1);
		}
	}
}

//Khoi tao danh sach ve
void InitListTicket(ListTicket &listTicket,Airplane air){
	listTicket.DSV = new Ticket[listTicket.sizeTotal];
    for (int i = 0; i < listTicket.sizeTotal; i++) {
		listTicket.DSV[i].statusTicket = VETRONG;
		listTicket.DSV[i].idPas = -1;
		InitSeats(listTicket,air);
	}
}

//Kiem tra danh sach day
bool ListTicketIsFull(ListTicket listTicket) {
    return listTicket.sizeBooked == listTicket.sizeTotal;
}

//Kiem tra danh sach rong
bool ListTicketIsNull(ListTicket listTicket) {
    return listTicket.sizeBooked == 0;
}

//Chuan hoa ma so ve
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

//Them 1 ve
bool InsertListTicket(Airplane air, ListTicket &listTicket, Ticket ticket) {
    if (ListTicketIsFull(listTicket)) return false;
    int vitri = ConvertMSVtoNumber(ticket.seat,air.col);
    listTicket.DSV[vitri] = ticket;
    listTicket.DSV[vitri].statusTicket = VEDAT;
    listTicket.sizeBooked++;
    return true;
}

//Huy ve
bool CancelTicket(Airplane air, ListTicket &listTicket, Ticket ticket) {
    if (ListTicketIsNull(listTicket)) return false;
    int vitri = ConvertMSVtoNumber(ticket.seat,air.col);
    listTicket.DSV[vitri].statusTicket = VEHUY;
    return true;
}

//Kiem tra ghe hop le
int CheckSeat(Airplane air, ListTicket listTicket, Ticket ticket) {
    int position = ConvertMSVtoNumber(ticket.seat, air.col);
    if (position >= listTicket.sizeTotal || position < 0) return -1;
    else {
        if (listTicket.DSV[position].statusTicket == VEDAT) return 0;
        else return 1;
    }
}

//Kiem tra CMND
bool CheckCMND(ListTicket listTicket, Ticket ticket) {
	for (int i = 0; i < listTicket.sizeTotal; i++) {
		if (listTicket.DSV[i].idPas == ticket.idPas) return true;
	}
	return false;
}

// Kiem tra 1 CMND trong nhieu chuyen bay
bool checkCMNDInFli(PNodeFli listFlight, PNodeFli fli, int idPas){
	PNodeFli p = listFlight;
	while (p != NULL) {
		if (strcmp(p->data.idFlight, fli->data.idFlight) != 0 && p->data.status == CONVE) {
			for (int i = 0; i < p->data.listTicket.sizeTotal ; i++) {
				if (p->data.listTicket.DSV[i].statusTicket != VEDAT) continue; 
				if (p->data.listTicket.DSV[i].idPas == idPas && !Check12Hours(&p->data.date, &fli->data.date) ) {
					return false;
				}
			}
		}
		p = p->pNext;
	}
	return true;
}

#endif
