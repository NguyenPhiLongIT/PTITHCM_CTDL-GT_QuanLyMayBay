#include <iostream>
#include <string.h>

using namespace std;
#include "Date.h"
#include "Mylibrary.h"
#include "Constraint.h"
#include "Ticket.h"
#include "Airplane.h"
#include "Flight.h"
#include "UserInterface.h"
#include "Passenger.h"
#include "KeyValue.h"


void CreateForm(string content[], int StartIndex, int nContent, int length);

void menu_xuli();

int main(){

    fullScreen();
    menu_xuli();
    return 0;
}

void menu_xuli() {
    ListAir list;
    InitListAirplane(list);
    Airplane air;
    TicketList ticketlist;
    InitTicketList(ticketlist);
    Ticket ticket;
    InputListAirplane(list);
	
    system("cls");
    while (true) {
        menuchinh:
        gotoxy(X_TitlePage-1,Y_TitlePage-1);
	    cout << "HANG HANG KHONG PTITHCM";
        int tt = menu_dong(X_Menu, Y_Menu,6, ContentMenu);
        switch(tt) {
            case 1: //Home
                break;
            case 2: //Airplane
            {
                MenuManageAirplane(list, air);
                system("cls");
                goto menuchinh;
            }
            case 3: // Flight
                break;
            case 4: // Passenger
                break;
            case 5: // Ticket
            {
//                MenuManagaTicket(ticketlist,ticket);
//                system("cls");
//                goto menuchinh;
					break;
            }
            default: //Exit
                return;
        }
    }
}
