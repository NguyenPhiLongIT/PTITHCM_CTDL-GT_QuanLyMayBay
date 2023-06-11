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
#include "Passenger.h"

typedef struct _Ticket {
//    char idPas[13];
	int idPas;
    char seat[5];
    int statusTicket; // 0: ve trong, 1: ve da duoc dat, 2: ve da huy
} Ticket, PTicket;

typedef struct _ListTicket {
    int sizeBooked; //so luong ve da dat
    int sizeTotal; // tong so luong ve cua 1 may bay
    Ticket *DSV;
} ListTicket, PListTicket;

int xKeyDisplayTicket[4] = {1,13,25,43};

void InitSeats(ListTicket &listTicket, Airplane air);
void InitListTicket(ListTicket &listTicket,Airplane air);
bool ListTicketIsFull(ListTicket listTicket);
bool ListTicketIsNull(ListTicket listTicket);
void InputTicket(Ticket &ticket);
int ConvertMSVtoNumber(const char msv[3], int column);
bool CancelTicket(Airplane air, ListTicket &listTicket, Ticket ticket);
int CheckSeat(Airplane air, ListTicket listTicket, Ticket ticket);
bool CheckCMND(ListTicket listTicket, Ticket ticket);
bool InsertListTicket(Airplane air, ListTicket &listTicket, Ticket ticket);
void ShowTicket(Ticket ticket, int position);
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket);
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket);
void MenuManageTicket(Airplane air, ListTicket &listTicket, TreePass &rootPass, bool emptyTicket);

//----------------------------------------------------------------//

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
		listTicket.DSV[i].statusTicket = 0;
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

//Nhap thong tin ve
void InputTicket(Ticket &ticket) {
    ShowCursor(true);
    CreateForm(ContentTicketInput,0,2,27);
    gotoxy(X_Add+12,Y_Add); char c[9]; strcpy(c, Input(sizeof(c), Number)); ticket.idPas = atoi(c);
    gotoxy(X_Add+12,Y_Add+3); strcpy(ticket.seat, Input(sizeof(ticket.seat), ID)); 
}

//Chuan hoa MSV
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
    listTicket.DSV[vitri].statusTicket  = 1;
    listTicket.sizeBooked++;
    return true;
}

//Huy ve
bool CancelTicket(Airplane air, ListTicket &listTicket, Ticket ticket) {
    if (ListTicketIsNull(listTicket)) return false;
    int vitri = ConvertMSVtoNumber(ticket.seat,air.col);
    listTicket.DSV[vitri].statusTicket = 2;
    return true;
}

//Kiem tra ghe hop le
int CheckSeat(Airplane air, ListTicket listTicket, Ticket ticket) {
    int position = ConvertMSVtoNumber(ticket.seat, air.col);
    if (position >= listTicket.sizeTotal || position < 0) return -1;
    else {
        if (listTicket.DSV[position].statusTicket == 1) return 0;
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

//Xuat thong tin 1 ve
void ShowTicket(Ticket ticket, int position) {
        gotoxy(xKeyDisplayTicket[0] + 3, Y_Display + position + 3);
        cout << left << setw(8) << ticket.seat;
        gotoxy(xKeyDisplayTicket[1] + 3, Y_Display + position + 3);
        if(ticket.statusTicket == 1) cout << left << setw(3) << "Da dat";
        else if (ticket.statusTicket == 0) cout << left << setw(3) << "Con ve";
        else cout << left << setw(3) << "Da huy";
    	gotoxy(xKeyDisplayTicket[2] + 3, Y_Display + position + 3);
    	cout << left << setw(8) << ticket.idPas;
}

//Xuat thong tin danh sach ve trong 1 trang
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket = false) {

    
    WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
    

    
    RemoveContent(xKeyDisplayTicket,3);
    
//    for(i = 0 ; i + startIndex < listTicket.sizeTotal && position < NumberPerPage; i++)
//	{
//		if(!emptyTicket){
//			ShowTicket(listTicket.DSV[i+startIndex],position);
//			position++;
//		} 
//		else if(emptyTicket && listTicket.DSV[i+startIndex].statusTicket == 0){
//			ShowTicket(listTicket.DSV[i+startIndex],position);
//			position++;
//		}
//	} 

	if(!emptyTicket){
		gotoxy(3,3);
    	cout << "Ve: " << listTicket.sizeBooked << "/" << listTicket.sizeTotal;
		for(int i = startIndex ; i < listTicket.sizeTotal && i < startIndex + NumberPerPage; i++)
			ShowTicket(listTicket.DSV[i],i - startIndex);
	}else{
		gotoxy(3,3);
    	cout << "Ve trong: " << listTicket.sizeTotal - listTicket.sizeBooked ;
		int position = 0;
		int count = 0;
		for(int i = 0; i < listTicket.sizeTotal && position < NumberPerPage; i++){
			if(listTicket.DSV[i].statusTicket == 0){
				if(count < startIndex){
					++count;
					continue;
				}
				ShowTicket(listTicket.DSV[i],position++);
			}
		}
	}
	
	SetColor(curColor);

    gotoxy(X_Page,Y_Page);
    cout << "Trang " << CurPage << "/" << TotalPage;
}

//Thay doi danh sach ve thanh trang khac
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket)
{
	DisplayTest(xKeyDisplayTicket, ContentTicketOutput,sizeof(ContentTicketOutput)/sizeof(string) );
	ShowListTicketOnePage(listTicket,(CurPage-1)*NumberPerPage, emptyTicket);
}

//Quan ly ve
void MenuManageTicket(Airplane air, ListTicket &listTicket, TreePass &rootPass, bool emptyTicket = false) {
    ShowCursor(false);
	CurPage = 1;
	
	gotoxy(20,3);
	if (!emptyTicket) {
		cout << "_DANH SACH VE_";
		TotalPage = (int)ceil((double)listTicket.sizeTotal/NumberPerPage); 	//ceil : lam tron 
	} else {
		cout << "_DANH SACH CAC VE CON TRONG_";
		TotalPage = (int)ceil((double)listTicket.sizeTotal-listTicket.sizeBooked/NumberPerPage); 	//ceil : lam tron 
	}
	DisplayTest(xKeyDisplayTicket, ContentTicketOutput, sizeof(ContentTicketOutput)/sizeof(string));
	ShowListTicketOnePage(listTicket, 0);	
	
	Ticket ticket_tmp;
	Passenger pass_tmp;
	int signal;

    while (true) {
        signal = MenuSelect(X_ThaoTac,Y_ThaoTac,6,ContentTicketSelect2);
        switch(signal) {
            case 1: //Dat ve
            {
                if (ListTicketIsFull(listTicket)) {
                    Notification("Da het ve");
                    break;
                }
                InputTicket(ticket_tmp);
                RemoveForm(0,4,27);
                int vitri = ConvertMSVtoNumber(ticket_tmp.seat,air.col);
                
                
                
                if (listTicket.DSV[vitri].statusTicket == 2) { // ve huy
                	Notification("Ve da huy. Khong the dat!");
                	break;
				}
                
                if (CheckSeat(air,listTicket,ticket_tmp) == -1) { // khong ton tai
                    Notification("Vi tri nay khong ton tai");
            		break;
                } else if (CheckSeat(air,listTicket,ticket_tmp) == 0) { // da dat
                	Notification("Vi tri nay da co nguoi dat");
                	break;
				} else { // ve trong
					if (CheckCMND(listTicket,ticket_tmp)) {
					Notification("Ban da dat ve tren chuyen bay nay");
					}
                	else {
                		if (SearchPass(rootPass,ticket_tmp.idPas) == NULL) {
							pass_tmp.id = ticket_tmp.idPas;
                			InputPass(rootPass,pass_tmp,true);
                			
						}
                    	InsertListTicket(air,listTicket,ticket_tmp);
                    	Notification("Them thanh cong");
                	} 
				}
                ShowListTicketOnePage(listTicket, (CurPage-1)*NumberPerPage);
                ShowCursor(false);
                break;
            }
            case 2: //Huy ve
            {
                if (ListTicketIsNull(listTicket)) {
                    Notification("Khong con ve de xoa");
                    break;
                }
                //gotoxy(X_Add,Y_Add-1);
                InputTicket(ticket_tmp);
                RemoveForm(0,4,27);
                if (CheckSeat(air,listTicket,ticket_tmp) == -1) {
                    Notification("Vi tri nay khong ton tai");
                    break;
                } else if (CheckSeat(air,listTicket,ticket_tmp) == 1) {
                    Notification("Vi tri nay chua duoc dat");
                    break;
                } else {
                    CancelTicket(air,listTicket,ticket_tmp);
                    Notification("Huy ve thanh cong");
                }
                ShowListTicketOnePage(listTicket,(CurPage - 1)/NumberPerPage);
                break;
            }
            case 3:	//Chuyen che do xem full ve va cac ve con trong
			{
				int signal = MenuSelect(X_ThaoTac+16,Y_ThaoTac+3,2,ContentTicketEmpty);
				if(signal == 1){
					emptyTicket = false;
					gotoxy(20,3);
					cout << "                                     ";
					gotoxy(20,3);
					cout << "_DANH SACH VE_";
					ChangeTicketMenuManagerPage(listTicket, emptyTicket);
				}
				else {
					emptyTicket = true;
					gotoxy(20,3);
					cout << "                                       ";
					gotoxy(20,3);
					cout << "_DANH SACH CAC VE CON TRONG_";
					ChangeTicketMenuManagerPage(listTicket, emptyTicket);
				}
			} 
            case LEFT:
            case 4: //Trang truoc
            {
            	if(CurPage == 1) break;
				CurPage --;
				ChangeTicketMenuManagerPage(listTicket, emptyTicket);
				break;
            }
            case RIGHT:
            case 5: //Trang sau
            {
            	if(CurPage >= TotalPage) break;
				CurPage ++;
				ChangeTicketMenuManagerPage(listTicket, emptyTicket);
				break;
            }
            default: return;
        }
    }
}
