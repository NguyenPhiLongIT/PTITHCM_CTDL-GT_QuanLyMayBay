#include <iostream>
#include <string.h>
#include "Date.h"
#include "Mylibrary.h"
#include "Constraint.h"
#include "Ticket.h"
#include "Airplane.h"
#include "Flight.h"
#include "UserInterface.h"
#include "Passenger.h"
#include "KeyValue.h"

using namespace std;

void CreateForm(string content[], int StartIndex, int nContent, int length);

void menu_xuli();

// void Duyet(TreePass root){
//     if(root != NULL){
//         ShowPass(root->data);
//         Duyet(root->pLeft);
//         Duyet(root->pRight);
//     }
// }

int main(){
        
    // ShowCursor(false); // ?n con tr?(false)/ hi?n(true);
    // SetConsoleOutputCP(65001); //Set b?ng mã kí t? d? in ra ti?ng vi?t ...
    // SetConsoleCP(65001); //Set nh?p vào ti?ng vi?t ...
    // SetConsoleTitleW(L"Qu?n lí máy bay"); //Set Title for console
    // cout << "Xin chào m?i ngu?i mình tên là Chó Thùy" << endl;
    // clreol({0,0});
    // cout << "Xin chào m?i ngu?i mình tên là Chó Thùy" << endl;
    // wchar_t ch;
    // wcin >> ch;
    // cout << ch << endl;

    // TreePass treePass;
    // InitTreePass(treePass);
    // Passenger pass[] = {
    //     {"12345", "Nguyen Tan", "Nguyen", 1},
    //     {"53232", "Vo Bich", "Thi", 0},
    //     {"63323", "Phan Thi My", "Duyen", 0}
    // };
    // InsertPass(treePass, pass[0]);
    // InsertPass(treePass, pass[1]);
    // InsertPass(treePass, pass[2]);
    // Duyet(treePass);
//     char r[100] = {};
//     strcpy(r,Input(100, ID));
//     cout << endl << r << endl;
    
//     _getch();
    
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
