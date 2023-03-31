//test
#pragma once
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <iomanip>

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

bool SaveAirplane(ListAir &listAir);
bool LoadAirplane(ListAir &listAir);

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
    gotoxy(X_Add+10,Y_Add+3);     strcpy(Air.typeAir, Input(sizeof(Air.typeAir), Text));
    gotoxy(X_Add+10,Y_Add+6);     char col[2]; std::sprintf(col, "%d", Air.col); strcpy(col, Input(sizeof(col), Number));
    gotoxy(X_Add+10,Y_Add+9);     char row[2]; std::sprintf(row, "%d", Air.row); strcpy(row, Input(sizeof(row), Number));
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
    cout << left << setw(15) << pAir->idAir;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(15) << pAir->typeAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(15) << pAir->col;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    cout << left << setw(15) << pAir->row;
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position +3);
    cout << left << setw(15) << (pAir->col * pAir->row);
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

void ChangeAirplaneMenuManagerPage(ListAir list)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";

	Display( ContentAirplane,sizeof(ContentAirplane)/sizeof(string) );
	ShowListAirplaneOnePage(list,(CurAirplanePage-1)*NumberPerPage);
}

void MenuManageAirplane(ListAir &list, Airplane air){
//	ShowCursor(false);
//	system("cls");
	CurAirplanePage = !ListAirIsNull(list);
	TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentAirplane, sizeof(ContentAirplane)/sizeof(string));
	ShowListAirplaneOnePage(list, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";
	
	int signal;
	while(true)
	{
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentThaoTac);
		switch(signal) {
			case 1: // Insert
			{
				if(CurAirplanePage == 0) CurAirplanePage = 1;
				if(list.size == MAXAIRPLANE) 
				{	
					Notification("Danh sach da day, khong the them");
					break;
				}
				gotoxy(X_Add, Y_Add-1);
				InputListAirplane(list);
				
				if(SaveAirplane(list)){
					Notification("Them thanh cong");
				}
				
				system("color 0E");
				TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage);
				RemoveForm(0, 4, 27);
				ShowListAirplaneOnePage(list, (CurAirplanePage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2: //Delete
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the xoa");
					break;
				}
				CreateForm(ContentAirplane, 0, 1, 27);
				gotoxy(X_Add+10,Y_Add);       strcpy(air.idAir, Input(sizeof(air.idAir), ID));
				if (!RemoveAirplane(list, IndexAirplane(list, air.idAir )))
				{
					Notification("Xoa khong thanh cong");
				}
				else {
					if(SaveAirplane(list)){
					Notification("Xoa thanh cong");
				}
				}
				system("color 0E");
				RemoveForm(0, 4, 27);
				TotalAirplanePage = (int)ceil((double)list.size / NumberPerPage);
				if (ListAirIsNull(list))  {
					CurAirplanePage = 0;
					ShowListAirplaneOnePage(list, 0);
				} else {
					if (CurAirplanePage > TotalAirplanePage) CurAirplanePage--;
					ShowListAirplaneOnePage(list, (CurAirplanePage-1) * NumberPerPage);
				}
				break;
			}
			edit: case 3: //Edit chua xong
			{
				ShowListAirplaneOnePage(list, (CurAirplanePage-1) * NumberPerPage);
				int i = (CurAirplanePage-1)*20;
				int j = i; 
				int xp = 22, yp = Y_Display+2;
				int xcu = xp, ycu = yp; //luu vi tri dong gan nhat
				char c;
				bool kt = true; //kiem tra co nhap phim chua
				while (true) {
					if (kt == true) {
						gotoxy(xcu,ycu);
						thanh_sang(xcu,ycu,18,2,BLACK,(string)list.nodes[j]->idAir);
						j = i;
						xcu = xp; ycu = yp;
						thanh_sang(xp,yp,18,2,BLUE_LIGHT,(string)list.nodes[i]->idAir);
						kt = false;
					}
					if (_kbhit()) {
						char c = _getch();
						if (c == -32) {
							kt = true;
							c = _getch();
							int max;
							if (CurAirplanePage < TotalAirplanePage) max = Y_Display+2 + (NumberPerPage-1);
							else max = Y_Display+2 + (list.size%20-1);
							if (c == UP) {
								if (yp != Y_Display+2) {
									yp--;
									i--;
								} else if (yp == Y_Display+2 && CurAirplanePage > 1) {
									CurAirplanePage--;
									ChangeAirplaneMenuManagerPage(list);
									goto edit;
								}
							} else if (c == DOWN) {
								if (yp != max) {
									yp++;
									i++;
								} else if (yp == max && CurAirplanePage < TotalAirplanePage) {
									CurAirplanePage ++;
									ChangeAirplaneMenuManagerPage(list);
									goto edit;
								}	
							}
						} else if (c == ENTER) {
							Notification("Ban muon thay doi phan nao?");
							thanh_sang(xp,yp,18,2,BLACK,(string)list.nodes[i]->idAir);
							break;
						} else if (c == ESC) {
							thanh_sang(xp,yp,18,2,BLACK,(string)list.nodes[i]->idAir);
							break;
						} 
					}
				}
				break;
			}
			prepage: case 4: //Chuyen trang truoc
			{
				if(CurAirplanePage == 1) break;
				else{
					CurAirplanePage --;
					ChangeAirplaneMenuManagerPage(list);
					break;
				}
			}
			nextpage: case 5:	//Chuyen trang tiep
			{
				if(CurAirplanePage >= TotalAirplanePage) break;
				CurAirplanePage ++;
				ChangeAirplaneMenuManagerPage(list);
				break;
			}
			default: return;
			
		}
	}
}


bool LoadAirplane(ListAir &listAir)
{
    ifstream filein("DSMB.TXT", ios_base::in);
    char str[1000];
    PAirplane pAir;

    if (!filein.is_open())
        return false;

    filein.getline(str, sizeof(str));
    listAir.size = atoi(str);
    for(int i = 0; i < listAir.size; i++)
    {
        pAir = new Airplane;
        filein.getline(pAir->idAir, sizeof(pAir->idAir), ';');
        filein.getline(pAir->typeAir, sizeof(pAir->typeAir), ';');
        filein.getline(str, sizeof(str), ';');
        pAir->col = atoi(str);
        filein.getline(str, sizeof(str));
        pAir->row = atoi(str);

        listAir.nodes[i] = pAir;
    }
    
    filein.close();
    return true;
}

bool SaveAirplane(ListAir &listAir)
{
    ofstream file("DSMB.TXT", ios_base::out);

    if (!file.is_open())
        return false;

    file << listAir.size << endl;
    for (int i = 0; i < listAir.size; i++)
    {
        file << listAir.nodes[i]->idAir << ";"
             << listAir.nodes[i]->typeAir << ";"
             << listAir.nodes[i]->col << ";"
             << listAir.nodes[i]->row << endl;
    }
    file.close();
    return true;
}
