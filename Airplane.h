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
void InputAirplane(ListAir &, Airplane &, bool);
void InputListAirplane(ListAir &list);
bool RemoveAirplane(ListAir &, int);
void ShowAirplane(PAirplane, int);
void ShowListAirplaneOnePage(ListAir, int);
void ChangeAirplaneMenuManagerPage(ListAir);
void EditAirplane(string , ListAir , Airplane , int , int , int , int );
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

void InputAirplane(ListAir &list, Airplane &air, bool Edit = false){
	int ordinal = 0;	// thu tu nhap	
	int position = -1;
	if(Edit == false) CreateForm(ContentAirplane,0,4,27);
	while(true){
		ShowCursor(true);
		switch(ordinal){
			case 0:{	//Nhap idAir
			
				do{
					CreateRow(X_Add, Y_Add, ContentAirplane[0], 27);
					gotoxy(X_Add+10,Y_Add);       	strcpy(air.idAir, Input(sizeof(air.idAir), ID));
					if(strlen(air.idAir) == 0) {
						Notification("Vui long khong bo trong");
					}
					position = IndexAirplane(list, air.idAir);
					if(position > -1 && Edit == false ) {
						Notification("ID da ton tai");	
					}
					if(position < 0 && Edit == true){
						Notification("ID khong ton tai");
					}
					if(
						(position > -1 && Edit == true) ||
						(position < 0 && Edit == false)
					) break;
				}while(true);
				
				while (Edit == true) {
					CreateForm(ContentAirplane,0,4,27);
					gotoxy(X_Add+10,Y_Add);
					strcpy(air.idAir, Input(sizeof(air.idAir), ID));
					if (IndexAirplane(list, air.idAir) > -1 ) {
						Notification("ID da ton tai");
					} else {
						break;
					}
				}
				ordinal++;
				break;
			}
			case 1:{	//Nhap typeAir
				gotoxy(X_Add+10,Y_Add+3);     	strcpy(air.typeAir, Input(sizeof(air.typeAir), Text));
				if(strlen(air.typeAir) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2:{	//Nhap col
				gotoxy(X_Add+10,Y_Add+6); 		char c[3]; strcpy(c, Input(sizeof(c), Number)); air.col = atoi(c);
				if(air.col < 1){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;	
			}
			case 3:{	//Nhap row
				gotoxy(X_Add+10,Y_Add+9);     	char r[3]; strcpy(r, Input(sizeof(r), Number)); air.row = atoi(r);
				if(air.row < 1){
					Notification("Vui long khong bo trong");
					break;
				}
				if(air.col*air.row < MINSEAT){
					Notification("So cho phai >= 20");
					ordinal = 2;
					break;
				}
				ordinal++;
				break;
			}
			case 4:{	
				//Them moi
				if(Edit == false) {
					InsertListAir(list, air);
				}	
				
				//Chinh sua
				else 
				{
					strcpy(list.nodes[position]->idAir, air.idAir);
					strcpy(list.nodes[position]->typeAir, air.typeAir);
					list.nodes[position]->col = air.col;
					list.nodes[position]->row = air.row;
				}
				RemoveForm(0, 4, 27);
			}
			return;
		}
	}	
	ShowCursor(false);
}

void ShowAirplane(PAirplane pAir, int position)
{	
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position +3);
    cout << left << setw(8) << pAir->idAir;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position +3);
    cout << left << setw(14) << pAir->typeAir;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position +3);
    cout << left << setw(4) << pAir->col;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position +3);
    cout << left << setw(4) << pAir->row;
    gotoxy(xKeyDisplay[4] + 3, Y_Display + position +3);
    cout << left << setw(4) << (pAir->col * pAir->row);
}

void ShowListAirplaneOnePage(ListAir list, int startIndex)
{
	gotoxy(3,3);
	cout << " So luong may bay : " << list.size;
	int i;
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	for(i = 0 ; i + startIndex < list.size && i < NumberPerPage; i++)
	{
		ShowAirplane(list.nodes[i+startIndex], i); 
	} 
	SetColor(curColor);
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
	ShowCursor(false);
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
					return;
				}
				InputAirplane(list, air);
				if(SaveAirplane(list)) Notification("Them thanh cong");
				TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage);
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
				CreateRow(X_Add, Y_Add, ContentAirplane[0], 27);
				gotoxy(X_Add+10,Y_Add); strcpy(air.idAir, Input(sizeof(air.idAir), ID));
				if (!RemoveAirplane(list, IndexAirplane(list, air.idAir ))) Notification("ID khong ton tai");
				else {
					if(SaveAirplane(list)) Notification("Xoa thanh cong");
				}
				RemoveRow(X_Add, Y_Add, ContentAirplane[0], 27);
				TotalAirplanePage = (int)ceil((double)list.size / NumberPerPage);
				if (ListAirIsNull(list))  { //neu nhu danh sach khong co phan tu, trang 0/0
					CurAirplanePage = 0;
					ShowListAirplaneOnePage(list, 0);
				} else {
					if (CurAirplanePage > TotalAirplanePage) CurAirplanePage--;
					ShowListAirplaneOnePage(list, (CurAirplanePage-1) * NumberPerPage);
				}
				break;
			}
			case 3: //Edit 
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the chinh sua");
					break;
				}
								
				InputAirplane(list, air, true);
				if(SaveAirplane(list)) Notification("Chinh sua thanh cong");
				TotalAirplanePage = (int)ceil((double)list.size/NumberPerPage);
				ShowListAirplaneOnePage(list, (CurAirplanePage-1)*NumberPerPage);
				break;
			}
			case 4: //Chuyen trang truoc
			{
				if(CurAirplanePage == 1) break;
				else{
					CurAirplanePage --;
					ChangeAirplaneMenuManagerPage(list);
					break;
				}
			}
			case 5:	//Chuyen trang tiep
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
