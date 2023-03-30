#pragma once
#include <cstring>
#include <conio.h>
#include <iostream>
#include <math.h>

#include "KeyValue.h"
#include "Constraint.h"
#include "UserInterface.h"

using namespace std;

typedef struct _Airplane{
    char idAir[16];
    char typeAir[40];
    int col; // so day
    int row; // so hang
}Airplane, *PAirplane;

typedef struct _ListAir{
    int size;
    Airplane *nodes[MAXAIRPLANE+1];
}ListAir, *PListAir;

//Thong tin vi tri hien tai
int CurPosAirplane = 0;
int CurAirplanePage = 1;
int TotalAirplanePage = 0;
extern string ContentAirplane[5];

void InitListAirplane(ListAir &);
bool ListAirIsFull(ListAir &listAir);
bool ListAirIsNull(ListAir &listAir);
PAirplane CreateAirplane(Airplane &Air);
int IndexAirplane(ListAir &, const char*);
bool AirplaneDataIsEmpty(Airplane &);

bool InsertListAir(ListAir &, Airplane &);
void InputAirplane(Airplane &);
void InputListAirplane(ListAir &list);
bool RemoveAirplane(ListAir &, int);
void ShowAirplane(PAirplane, int);
void ShowListAirplaneOnePage(ListAir, int);
void ChangeAirplaneMenuManagerPage(ListAir);
void MenuManageAirplane(ListAir &, Airplane);

void InitListAirplane(ListAir &ListAir){
    ListAir.size = 0;
}

bool ListAirIsFull(ListAir &listAir){
    return listAir.size == MAXAIRPLANE+1;
}

bool ListAirIsNull(ListAir &listAir){
    return listAir.size == 0;
}

PAirplane CreateAirplane(Airplane &Air){
    PAirplane tmp = new Airplane;
    *tmp = Air;
    return tmp;
}

int IndexAirplane(ListAir &List, const char* id){

    for (int i = 0; i < List.size; i++)
        if (stricmp(List.nodes[i]->idAir, id) == 0)
            return i;

    return -1;
}

bool AirplaneDataIsEmpty(Airplane &Air){
    return 
        strlen(Air.idAir)  == 0 || 
        strlen(Air.typeAir)    == 0 ||
        (Air.col * Air.row) == 0;
}

bool InsertListAir(ListAir &ListAir, Airplane &Air){
	if (ListAirIsFull(ListAir))
        return false;
	ListAir.nodes[ListAir.size] = CreateAirplane(Air);
	ListAir.size++;
	return true;
}

void InputAirplane(Airplane &Air){
	ShowCursor(true);
    gotoxy(X_Add+10,Y_Add);       strcpy(Air.idAir, Input(sizeof(Air.idAir), ID));
    gotoxy(X_Add+10,Y_Add+3);     strcpy(Air.typeAir, Input(sizeof(Air.typeAir), ID));
    gotoxy(X_Add+10,Y_Add+6);     std::cin  >> Air.col;
    gotoxy(X_Add+10,Y_Add+9);     std::cin >> Air.row;
}

void InputListAirplane(ListAir &list){
	int size; 
	cout << "So luong may bay: "; cin >> size;
    for(int i = 0; i < size; i++){
    	CreateForm(ContentAirplane, 0, 4, 27);
    	Airplane air;
    	cin.ignore();
    	InputAirplane(air);
    	InsertListAir(list, air);
	}
}

bool RemoveAirplane(ListAir &ListAir, int position)
{
    if (position < 0 || position >= ListAir.size)
        return false;
    int n = ListAir.size;
    delete ListAir.nodes[position];
    for (int i = position; i < n; i++)
    {
        ListAir.nodes[i] = ListAir.nodes[i + 1];
    }
    --ListAir.size;
    return true;
}

void ShowAirplane(PAirplane pAir, int position)
{
	int xKeyDisplay[10] = {20,40,60,80,100,120,130,140,150,160};
	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    printf("%-15s", pAir->idAir);			//dung printtf %s: de ko bi loi dinh dang khi chuyen trang
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    printf("%-15s", pAir->typeAir);
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    printf("%-15d", pAir->col);
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    printf("%-15d", pAir->row);
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position +3);
    printf("%-15d", (pAir->col * pAir->row));
}

void ShowListAirplaneOnePage(ListAir list, int startIndex)
{
	gotoxy(21,3);
	cout << " So luong may bay : " << list.size;
	int i;
	for(i = 0 ; i + startIndex < list.size && i < NumberPerPage; i++)
	{
		ShowAirplane(list.nodes[i+startIndex], i); 
	} 
	RemoveExceedMember(i, 5);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurAirplanePage <<"/"<< TotalAirplanePage; 
}

void ChangeAirplaneMenuManagerPage(ListAir &list)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";

	Display( ContentAirplane,sizeof(ContentAirplane)/sizeof(string) );
	ShowListAirplaneOnePage(list,(CurAirplanePage-1)*NumberPerPage);
}

void MenuManageAirplane(ListAir &list, Airplane air){
//	ShowCursor(false);
//	system("cls");
	CurAirplanePage = 1;
	TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentAirplane, sizeof(ContentAirplane)/sizeof(string));
	ShowListAirplaneOnePage(list, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";
	
	int signal;
	while(true)
	{
		menu:
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentThaoTac);
		switch(signal) {
			case 1: // Insert
			{
				if(list.size == MAXAIRPLANE) 
				{	
					Notification("Danh sach da day, khong the them");
					goto menu;
				}
				gotoxy(X_Add, Y_Add-1);
				InputListAirplane(list);
				Notification("Them thanh cong");
				system("color 0E");
				TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage);
				RemoveForm(0, 4, 27);
				ShowListAirplaneOnePage(list, (CurAirplanePage-1)*NumberPerPage);
				ShowCursor(false);
				goto menu;
			}
			case 2: //Delete
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the xoa");
					goto menu;
				}
				CreateForm(ContentAirplane, 0, 1, 27);
				gotoxy(X_Add+10,Y_Add);       strcpy(air.idAir, Input(sizeof(air.idAir)/sizeof(char), ID));
				if (!RemoveAirplane(list, IndexAirplane(list, air.idAir )))
				{
					Notification("Xoa khong thanh cong");
				}
				else {
					Notification("Xoa thanh cong");
				}
				system("color 0E");
				RemoveForm(0, 4, 27);
				TotalAirplanePage = (int)ceil((double)list.size / NumberPerPage);
				ShowListAirplaneOnePage(list, (CurAirplanePage - 1) * NumberPerPage);
				goto menu;
			}
			case 3: //Edit chua xong
			{
				CreateForm(ContentAirplane,0, 4, 27);
				TotalAirplanePage = (int)ceil((double)list.size / NumberPerPage);
				ShowListAirplaneOnePage(list, (CurAirplanePage - 1) * NumberPerPage);
				goto menu;
			}
			case 4: //Chuyen trang truoc
			{
				if(CurAirplanePage == 1) goto menu;
				else{
					CurAirplanePage --;
					ChangeAirplaneMenuManagerPage(list);
					goto menu;
				}
			}
			case 5:	//Chuyen trang tiep
			{
				if(CurAirplanePage >= TotalAirplanePage) goto menu;
				CurAirplanePage ++;
				ChangeAirplaneMenuManagerPage(list);
				goto menu;
			}
			default: return;
		}
	}
}
