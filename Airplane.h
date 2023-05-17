#pragma once
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

//#include "Flight.h"
#include "KeyValue.h"
#include "Constraint.h"
#include "UserInterface.h"

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

void InitListAirplane(ListAir &listAir);
bool ListAirIsFull(ListAir &listAir);
bool ListAirIsNull(ListAir &listAir);
PAirplane CreateAirplane(Airplane &air);
int IndexAirplane(ListAir &list, const char* id);

bool InsertListAir(ListAir &listAir, Airplane &air);
void InputAirplane(ListAir &list, Airplane &air, bool Edit, bool Delete);
bool RemoveAirplane(ListAir &listAir, int position);
void ShowAirplane(PAirplane pAir, int position);
void ShowListAirplaneOnePage(ListAir list, int startIndex);
void ChangeAirplaneMenuManagerPage(ListAir list);
void MenuManageAirplane(ListAir &list);

bool SaveAirplane(ListAir &listAir);
bool LoadAirplane(ListAir &listAir);

//Khoi tao danh sach may bay
void InitListAirplane(ListAir &listAir){
    listAir.size = 0;
}

//Kiem tra danh sach da day
bool ListAirIsFull(ListAir &listAir){
    return listAir.size == MAXAIRPLANE+1;
}

//Kiem tra danh sach chua co may bay
bool ListAirIsNull(ListAir &listAir){
    return listAir.size == 0;
}

//Tao may bay moi
PAirplane CreateAirplane(Airplane &air){
    PAirplane tmp = new Airplane;
    *tmp = air;
    return tmp;
}

//Vi tri may bay
int IndexAirplane(ListAir &list, const char* id){

    for (int i = 0; i < list.size; i++)
        if (stricmp(list.nodes[i]->idAir, id) == 0)
            return i;

    return -1;
}

//Them may bay vao danh sach
bool InsertListAir(ListAir &listAir, Airplane &air){
	if (ListAirIsFull(listAir))
        return false;
	listAir.nodes[listAir.size] = CreateAirplane(air);
	listAir.size++;
	return true;
}

//Xoa may bay
bool RemoveAirplane(ListAir &listAir, int position)
{
    if (position < 0 || position >= listAir.size)
        return false;
    int n = listAir.size;
    delete listAir.nodes[position];
    for (int i = position; i < n; i++)
    {
        listAir.nodes[i] = listAir.nodes[i + 1];
    }
    --listAir.size;
    return true;
}

//Nhap thong tin may bay
void InputAirplane(ListAir &list, Airplane &air, bool Edit = false, bool Delete = false){
	int ordinal = 0;	// thu tu nhap	
	int position = -1;	// vi tri may bay
	if(Edit == false && Delete == false) CreateForm(ContentAirplaneInput,0,3,27);
	while(true){
		ShowCursor(true);
		switch(ordinal){
			case 0:{	//Nhap so hieu may bay			
				do{
					CreateRow(X_Add, Y_Add, ContentAirplane[0], 27);
					gotoxy(X_Add+10,Y_Add);       	strcpy(air.idAir, Input(sizeof(air.idAir), ID));
					position = IndexAirplane(list, air.idAir);
					if(strlen(air.idAir) == 0) {
						Notification("Vui long khong bo trong");
					}			
					if(position > -1 && Edit == false && Delete == false) {
						Notification("ID da ton tai");	
					}
					if(position < 0 && (Edit == true || Delete == true) && (strlen(air.idAir) != 0)){
						Notification("ID khong ton tai");
					}
					if(position > -1 && Delete == true){
						ShowCursor(false);
//						if(IndexAirplane(list, fli.idAir) < 0){
							Box(X_Notification,Y_Notification, 27, 3, "Ban co chac muon xoa khong? ");
							gotoxy(X_Notification+1,Y_Notification+2); cout << "ESC: Huy - ENTER: Xoa";
						
							char c = _getch();
							RemoveRow(X_Add, Y_Add, ContentAirplane[0], 27);
							RemoveBox(X_Notification,Y_Notification, 27, 3);
						
							if (c == ESC) Notification("Xoa that bai!");
							else if (c == ENTER) {
								RemoveAirplane(list, position);
								if(SaveAirplane(list)) Notification("Xoa thanh cong!");
							}		
//						}else Notification("May bay da thuc hien chuyen bay");
										
						return;
					}
					if(
						(position > -1 && Edit == true) ||
						(position < 0 && Edit == false && Delete ==  false && (strlen(air.idAir) != 0)) 
					)break;
				}while(true);
				
				while (Edit == true) {
					CreateForm(ContentAirplaneInput,0,3,27);
					Box(X_Add-3,Y_Add-4, 44, 2, "Phan nao khong muon chinh sua. Hay bo trong!");
					gotoxy(X_Add+10,Y_Add);	strcpy(air.idAir, Input(sizeof(air.idAir), ID));
					if (IndexAirplane(list, air.idAir) > -1) {
						Notification("ID da ton tai");
					} else {
						break;
					}
				}
				ordinal++;
				break;
			}
			case 1:{	//Nhap loai may bay
				gotoxy(X_Add+11,Y_Add+3);     	strcpy(air.typeAir, Input(sizeof(air.typeAir), Text));
				if(strlen(air.typeAir) == 0 && Edit == false){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2: { //Nhap so cot va so hang
				gotoxy(X_Add+15,Y_Add+6); cout << "    x    ";
				gotoxy(X_Add+15,Y_Add+6); 		char c[3]; strcpy(c, Input(sizeof(c), Number)); air.col = atoi(c);
				gotoxy(X_Add+15+7,Y_Add+6);     	char r[3]; strcpy(r, Input(sizeof(r), Number)); air.row = atoi(r);
				if((air.col < 1 || air.row < 1) && Edit == false) {
					Notification("Vui long khong bo trong");
					break;
				}	
				if((air.col >= 0 || air.row >= 0) && (air.col*air.row < MINSEAT)) {
					Notification("So cho phai >= 20");	
					break;
				}
				ordinal++;
				break;
			}
			case 3:{
				//Chinh sua
				if(Edit) {
					if(strlen(air.idAir) != 0) strcpy(list.nodes[position]->idAir, air.idAir);					
					if (strlen(air.typeAir) != 0) strcpy(list.nodes[position]->typeAir, air.typeAir);
					if (air.col >= 1) list.nodes[position]->col = air.col;
					if (air.row >= 1) list.nodes[position]->row = air.row;
					if(SaveAirplane(list)) Notification("Chinh sua thanh cong");
				}
				//Them moi
				else 
				{
					InsertListAir(list, air);
					if(SaveAirplane(list)) Notification("Them thanh cong");
				}
				RemoveForm(0, 3, 27);
				RemoveBox(X_Add-3,Y_Add-4, 44, 2);
			}
			return;
		}
	}	
	ShowCursor(false);
}

//Xuat thong tin 1 may bay
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

//Xuat danh sach may bay trong 1 trang
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
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach may bay qua trang khac
void ChangeAirplaneMenuManagerPage(ListAir list)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";

	Display( ContentAirplane,sizeof(ContentAirplane)/sizeof(string) );
	ShowListAirplaneOnePage(list,(CurPage-1)*NumberPerPage);
}

//Quan ly may bay
void MenuManageAirplane(ListAir &list){
	ShowCursor(false);
	CurPage = 1;
	TotalPage = (int)ceil((double)list.size/NumberPerPage); 	//ceil : lam tron 
	
	Display(ContentAirplane, sizeof(ContentAirplane)/sizeof(string));
	ShowListAirplaneOnePage(list, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY MAY BAY";
	
	int signal;
	Airplane air;

	while(true)
	{
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,6,ContentAirSelect);
		switch(signal) {
			case 1: // Them may bay
			{
				if(CurPage == 0) CurPage = 1;
				if(list.size == MAXAIRPLANE) 
				{	
					Notification("Danh sach da day, khong the them");
					return;
				}
				InputAirplane(list, air);
				
				TotalPage = (int)ceil((double)list.size/NumberPerPage);
				ShowListAirplaneOnePage(list, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2: //Xoa may bay
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the xoa");
					break;
				}
				
				InputAirplane(list, air, false, true);
				
				TotalPage = (int)ceil((double)list.size / NumberPerPage);
				if (ListAirIsNull(list))  { //neu nhu danh sach khong co phan tu, trang 0/0
					CurPage = 0;
					ShowListAirplaneOnePage(list, 0);
				} else {
					if (CurPage > TotalPage) CurPage--;
					ShowListAirplaneOnePage(list, (CurPage-1) * NumberPerPage);
				}
				break;
			}
			case 3: //Chinh sua
			{
				if(list.size == 0)
				{
					Notification("Danh sach rong, khong the chinh sua");
					break;
				}
								
				InputAirplane(list, air, true, false);
				
				TotalPage = (int)ceil((double)list.size/NumberPerPage);
				ShowListAirplaneOnePage(list, (CurPage-1)*NumberPerPage);
				break;
			}
			case 4: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage --;
					ChangeAirplaneMenuManagerPage(list);
					break;
				}
			}
			case 5:	//Chuyen trang sau
			{
				if(CurPage >= TotalPage) break;
				CurPage ++;
				ChangeAirplaneMenuManagerPage(list);
				break;
			}
			default: return;
			
		}
	}
}

//Load file danh sach may bay
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

//Luu file danh sach may bay
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
