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
//#include "Process.h"


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
    ListTicket listticket;
    Ticket ticket;
    Flight fli;
    PNodeFli first;
    InitListFlight(first);
//    InitFlight(fli);
//    InputListFlight(first);
//	InputFlight(fli);
//	InsertFlight(first, fli);
//    InputListAirplane(list);
	if(!LoadAirplane(list));
//	if(!LoadFlight(first));

    system("cls");
    while (true) {
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
                break;
            }
            case 3: // Flight
//            	MenuManageFlight(first, fli);
				ChangeFlightMenuManagerPage(first);
            	system("cls");
                break;
            case 4: // Passenger
                break;
            case 5: // Ticket
            {
            	air = *list.nodes[2]; //lay may bay thu 3 de test
            	InitListTicket(listticket,air); //khoi tao danh sach ve cho may bay
                MenuManageTicket(air, listticket, ticket);
                system("cls");
		break;
            }
            default: //Exit
                return;
        }
    }
}
