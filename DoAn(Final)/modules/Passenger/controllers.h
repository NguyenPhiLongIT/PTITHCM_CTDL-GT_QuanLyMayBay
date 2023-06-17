#ifndef __PASSENGER__CONTROLLERS__
#define __PASSENGER__CONTROLLERS__

#include <cstring>
#include <conio.h>
#include <math.h>
#include "..\..\data\routers.h"
#include "models.h"

int xKeyDisplayPas[5] = {1,19,44,62,74};

void InputPass(TreePass &rootPass, Passenger &pass, bool Edit = false, bool Check = false);
void ShowPass(Passenger &pass, int position);
void ShowListPassOnePage(TreePass root, int startIndex);
void ChangePassMenuManagerPage(TreePass root);
void MenuManagePassenger(TreePass &rootPass );

//Nhap thong tin hanh khach
void InputPass(TreePass &rootPass, Passenger &pass, bool Edit, bool Check)
{
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int signal;
	char *str;
	TreePass passtmp;	
	if (Edit == false) {
		if(Check){	//Kiem tra CMND chua co o ds hanh khach nen nhap them ho ten gioi tinh
			CreateForm(ContentPass, 0, 4, 27);
			RemoveRow(X_Add,Y_Add,ContentPass[0],27);
			ordinal = 1;
		}	
		else {	
			CreateForm(ContentPass, 0, 4, 27);
		}
	}
	else 
		CreateRow(X_Add, Y_Add, ContentPass[0], 27);
//	else if(Check) //Kiem tra CMND chua co o ds hanh khach nen nhap them ho ten gioi tinh
//	{
//		RemoveRow(X_Add,Y_Add,ContentPass[0],27);
//		ordinal = 1;
//	}
	while(true){
		switch(ordinal){
			case 0:{	//Nhap CMND
				Clean(X_Add+10,Y_Add,X_Add+10+10,Y_Add+1);
				gotoxy(X_Add+10,Y_Add);
				str = Input(SIZE_ID_PASS, Number);
				for(int i= 0; i < SIZE_ID_PASS; i++){
					if(str[i] == ESC){
						Notification("Thoat thao tac!");
						RemoveForm(0, 4, 27);
						return;
					}
				}
				pass.id = atoi(str);
				freeMemmorry(str);
				passtmp = SearchPass(rootPass, pass.id);
				
				if(pass.id < 1){
					Notification("Vui long khong bo trong");
					break;
				}
				else if(passtmp != NULL && Edit == false){
					Notification("CMND da ton tai");
					break;
				}
				else if(passtmp == NULL && Edit == true){
					Notification("CMND khong ton tai");
					break;
				}
				else if(passtmp != NULL && Edit == true){
					CreateForm(ContentPass,0,4,27);
					RemoveRow(X_Add, Y_Add, ContentPass[0], 27);
					ordinal = 1;
					break;
				}
				ordinal++;
				break;
			}
			case 1:{	//Nhap Ho
				gotoxy(X_Add+10,Y_Add+3);      

				str = Input(sizeof(pass.firstName), Text);
				for(int i= 0; i < sizeof(pass.firstName); i++){
					if(str[i] == ESC){
						Notification("Thoat thao tac!");
						RemoveForm(0, 4, 27);
						return;
					}
				}
				strcpy(pass.firstName, str);
				freeMemmorry(str);

				if(strlen(pass.firstName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2:{	//Nhap Ten
				gotoxy(X_Add+10,Y_Add+6);
				str = Input(sizeof(pass.lastName), Text);
				for(int i= 0; i < sizeof(pass.lastName); i++){
					if(str[i] == ESC){
						Notification("Thoat thao tac!");
						RemoveForm(0, 4, 27);
						return;
					}
				}
				strcpy(pass.lastName, str);
				freeMemmorry(str);

				if(strlen(pass.lastName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 3:{	//Nhap gioi tinh
				signal = MenuSelect(X_Add+9,Y_Add+9,2,ContentGender);
				if (signal != -1) pass.gender = --signal;
				else {
					RemoveForm(0, 4, 27);
					RemoveBox(X_Add+9,Y_Add+9,16,4);
					return;
				}
				ordinal++;
				break;
			}
			case 4:{
				if(Edit == false)
					InsertPass(rootPass, pass);
				else {
					if(strlen(pass.firstName) != 0)
						strcpy(passtmp->data.firstName, pass.firstName);					
					if (strlen(pass.lastName) != 0)
						strcpy(passtmp->data.lastName, pass.lastName);
					if (signal == 0 || signal == 1)
						passtmp->data.gender = pass.gender;
						
					Notification("Chinh sua thanh cong");
				}
				RemoveForm(0, 4, 27);
				RemoveBox(X_Add+9,Y_Add+9,16,4);	
				ShowCursor(false);
				return;
			}
		}
	}
}

//Xuat thong tin 1 hanh khach
void ShowPass(Passenger &pass, int position)
{
	char id_str[SIZE_ID_PASS];
	sprintf(id_str, "%.9d", pass.id);
	gotoxy(xKeyDisplayPas[0] + 3, Y_Display + position + 3);
    std::cout << std::left << id_str;
    gotoxy(xKeyDisplayPas[1] + 3, Y_Display + position + 3);
    std::cout << std::left << std::setw(8) << pass.firstName;
    gotoxy(xKeyDisplayPas[2] + 3, Y_Display + position + 3);
    std::cout << std::left << std::setw(8) << pass.lastName;
    gotoxy(xKeyDisplayPas[3] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(5) << (pass.gender ? "Nu" : "Nam");
}

void ShowListPassOnePage(TreePass root, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int position = 0;
	int count = 0;
	
	gotoxy(3,3);
	std::cout << " So luong hanh khach : " << countPass(root);
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	RemoveContent(xKeyDisplayPas, 4);
	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
		if(count < startIndex){
			count++;
			continue;
		}
		ShowPass(*temp, position);
		++position;
		
		if(position >= NumberPerPage){
			break;
		}
	}
	
	SetColor(curColor);
	gotoxy(X_Page,Y_Page);
	std::cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach hanh khach sang trang khac
void ChangePassMenuManagerPage(TreePass root)
{
	Display(xKeyDisplayPas, ContentPass,sizeof(ContentPass)/sizeof(std::string) );
	ShowListPassOnePage(root,(CurPage-1)*NumberPerPage);
}

//Quan ly hanh khach
void MenuManagePassenger(TreePass &rootPass ){
	CurPage = 1;
	TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage); 	//ceil : lam tron 
	
	Display(xKeyDisplayPas, ContentPass, sizeof(ContentPass)/sizeof(std::string));
	if(!EmptyPass(rootPass))
		ShowListPassOnePage(rootPass, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	std::cout << "QUAN LY HANH KHACH";
	
	int signal;
	Passenger pass;
	
	while(true)
	{
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,5,ContentPassSelect);
		switch(signal) {
			case 1: // Them hanh khach
			{
				if(CurPage == 0) CurPage = 1;
				InputPass(rootPass, pass);

				TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage);
				ShowListPassOnePage(rootPass, (CurPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2:	//Chinh sua hanh khach
			{
				if(EmptyPass(rootPass)){
					Notification("Danh sach rong");
					break;
				}
				InputPass(rootPass, pass, true);
				ShowListPassOnePage(rootPass, (CurPage-1)*NumberPerPage);
				break;
			}
			case LEFT:
			case 3: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage--;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case RIGHT:
			case 4:	//Chuyen trang tiep
			{
				if(CurPage >= TotalPage) break;
				else{
					CurPage++;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case 5:
			case -1:
				return;
			default: 
				break;
			
		}
	}
}

#endif
