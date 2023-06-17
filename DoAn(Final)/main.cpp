#include <iostream>
#include <string.h>

#include "data/routers.h"
#include "./modules/Date/controllers.h"
#include "./modules/Ticket/controllers.h"
#include "./modules/Airplane/controllers.h"
#include "./modules/Flight/controllers.h"
#include "./modules/Passenger/controllers.h"
#include "./utils/Mylibrary.h"
#include "./utils/UserInterface.h"
#include "./types/KeyValue.h"
#include "Introduction.h"

using namespace std;

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
    int tt;
    
    if(!LoadFlight(listFlight));
	if(!LoadAirplane(listAir));
	if(!LoadTreePass(rootPass));
    while (true) {
    	WORD cur;
    	GetColor(cur);
    	tt = 0;
    	Clear();
	    if(tt == 0)
	    	Introduction();
	    SetColor(cur);
        tt = MenuSelect(X_Menu, Y_Menu,7, ContentMenu);
        Clear();
        switch(tt) {
            case 1: //Home
            	Introduction();
                break;
            case 2: //Airplane
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
                MenuManageAirplane(listAir, listFlight);
                break;
            }
            case 3: // Flight
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
            	MenuManageFlight(listFlight,listAir,rootPass);
                break;	
			}
            case 4: // Passenger
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
            	MenuManagePassenger(rootPass);
                break;	
			}
            case 5: // Ticket
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
				MenuManageListTicket(listAir,listFlight,rootPass);
				break;
            }
            case 6: // List
            {
            	RemoveBox(X_Menu, Y_Menu, 20, 15);
            	ListAirplaneFly(listFlight,listAir);
            	break;
			}
			case -1:
            case 7: //Exit
			{
				Box(X_Notification,Y_Notification, 29, 3, "Ban co luu khong? ");
				gotoxy(X_Notification+1,Y_Notification+2); cout << "ESC: Khong - ENTER: Co";
				char c = _getch();
				RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
				RemoveBox(X_Notification,Y_Notification, 29, 3);
						
				if(c == ESC){
					return;
				}
				if (c == ENTER) {
					if(SaveAirplane(listAir) && SaveFlight(listFlight) && SaveTreePass(rootPass)) Notification("Luu thanh cong");
					else Notification("Luu that bai");
				}	
				DeleteAllListFlight(listFlight);
				RemoveListAir(listAir);
				DeleteAllTreePass(rootPass);
				return;
			}
			default:
				break;
        }
        SetColor(cur);
    }
}
