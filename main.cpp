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
    PNodeFli dscb = NULL;
    Flight cb_tmp;
    
    if(!LoadFlight(dscb));
	if(!LoadAirplane(list));
	
    while (true) {
    	Clear();
        gotoxy(X_TitlePage-1,Y_TitlePage-1);
	    cout << "HANG HANG KHONG PTITHCM";
        int tt = menu_dong(X_Menu, Y_Menu,6, ContentMenu);
        switch(tt) {
            case 1: //Home
                break;
            case 2: //Airplane
            {
            	remove_box(X_Menu, Y_Menu, 20, 12);
                MenuManageAirplane(list, air);
                break;
            }
            case 3: // Flight
            	remove_box(X_Menu, Y_Menu, 20, 12);
            	MenuManageFlight(dscb,list);
                break;
            case 4: // Passenger
                break;
            case 5: // Ticket
            {
	           	remove_box(X_Menu, Y_Menu, 20, 12);  	
				MenuManageListTicket(list,dscb);
				break;
            }
            default: //Exit
                return;
        }
    }
}
