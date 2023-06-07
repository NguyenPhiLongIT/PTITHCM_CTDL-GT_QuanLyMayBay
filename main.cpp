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


void MainMenu();

int main(){
    fullScreen();
    MainMenu();
    return 0;
}

void MainMenu() {
    ListAir listAir;
    InitListAirplane(listAir); 
    PNodeFli listFlight = NULL;
    TreePass rootPass = NULL;
    
    if(!LoadFlight(listFlight));
	if(!LoadAirplane(listAir));
	if(!LoadTreePass(rootPass));
	
    while (true) {
    	Clear();
        gotoxy(X_TitlePage-1,Y_TitlePage-1);
	    cout << "HANG HANG KHONG PTITHCM";
        int tt = MenuSelect(X_Menu, Y_Menu, 7, ContentMenu);
        switch(tt) {
            case 1: //Home
                break;
            case 2: //Airplane
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
                MenuManageAirplane(listAir);
                break;
            }
            case 3: // Flight
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
            	MenuManageFlight(listFlight,listAir);
                break;
            case 4: // Passenger
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
            	MenuManagePassenger(rootPass);
                break;
            case 5: // Ticket
            {
	           	RemoveBox(X_Menu, Y_Menu, 20, 15);  	
				MenuManageListTicket(listAir,listFlight,rootPass);
				break;
            }
            //EXIT
            case 7:
            case -1:
                return;
            
            default: //Thong bao loi khong co chuc nang nay
                break;
        }
    }
}
