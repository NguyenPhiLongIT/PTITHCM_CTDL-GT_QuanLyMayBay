#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "KeyValue.h"
#include "Constraint.h"
#include "UserInterface.h"
#include "Stack_Queue.h"

using namespace std;

typedef struct _Passenger
{
//	char id[13];
	int id;
	char firstName[31];
	char lastName[11];
	bool gender; // 0 la nam , 1 la nu
} Passenger, *PPassenger;

typedef struct _PassNode
{
	Passenger data;
	struct _PassNode *pLeft;
	struct _PassNode *pRight;
} PassNode, *PPassNode, *TreePass;

int xKeyDisplayPas[5] = {1,19,44,62,74};


void InitTreePass(TreePass &rootPass);
bool EmptyPass(TreePass &rootPass);
PPassNode NewPassNode(Passenger &data);
void PreOrder(TreePass &rootPass, int &position);
int countPass(TreePass &rootPass);

void InputPass(TreePass &rootPass, Passenger &pass, bool Check);
void InsertPass(TreePass &rootPass, Passenger &pass);
PPassNode SearchPass(TreePass rootPass, int idPass);


void ShowPass(Passenger &pass, int position);
void ShowListPass(TreePass root);

bool LoadTreePass(TreePass &pass);
bool SaveTreePass(TreePass pass);

//Khoi tao danh sach hanh khach
void InitTreePass(TreePass &rootPass)
{
	rootPass = NULL;
}

//Kiem tra danh sach trong
bool EmptyPass(TreePass &rootPass)
{
	return rootPass == NULL;
}

//Tao 1 hanh khach moi
PPassNode NewPassNode(Passenger &data)
{
	PPassNode passNode = new PassNode;
	passNode->data = data;
	passNode->pLeft = passNode->pRight = NULL;
	return passNode;
}

//So luong hanh khach
int countPass(TreePass &rootPass)
{
	if(rootPass == NULL)	return 0;

	return 1 + countPass(rootPass->pLeft) + countPass(rootPass->pRight);
}


void PreOrder(TreePass &rootPass, int &position){
	if(rootPass == NULL) return;
	ShowPass(rootPass->data, position);
	position++;
	system("pause");
	PreOrder(rootPass->pLeft, position);
	PreOrder(rootPass->pRight, position);
}

//Nhap thong tin hanh khach
void InputPass(TreePass &rootPass, Passenger &pass, bool Check = false)
{
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri hanh khach
	CreateForm(ContentPass, 0, 4, 27);
	if(Check) 
	{
		RemoveRow(X_Add,Y_Add,ContentPass[0],27);
		ordinal = 1;
	}
	while(true){
		switch(ordinal){
			case 0:{	//Nhap CMND
				gotoxy(X_Add+10,Y_Add);       	char c[9]; strcpy(c, Input(sizeof(c), Number)); pass.id = atoi(c);		
				if(pass.id < 1){
					Notification("Vui long khong bo trong");
					break;
				}
				if(SearchPass(rootPass, pass.id)){
					Notification("CMND da ton tai");
					break;
				}
				ordinal++;
				break;
			}
			case 1:{	//Nhap Ho
				gotoxy(X_Add+10,Y_Add+3);       strcpy(pass.firstName, Input(sizeof(pass.firstName), Text));
				if(strlen(pass.firstName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 2:{	//Nhap Ten
				gotoxy(X_Add+10,Y_Add+6);     	strcpy(pass.lastName, Input(sizeof(pass.lastName), Text));
				if(strlen(pass.lastName) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 3:{	//Nhap gioi tinh
				int signal = MenuSelect(X_Add+9,Y_Add+9,2,ContentGender);
				pass.gender = --signal;
				ordinal++;
				break;
			}
			case 4:{
				InsertPass(rootPass, pass);
				if(SaveTreePass(rootPass));
				RemoveForm(0, 4, 27);
				RemoveBox(X_Add+9,Y_Add+9,16,4);
				
			}
			return;
		}
		ShowCursor(false);
	}
}

//Them hanh khach vao danh sach
void InsertPass(TreePass &rootPass, Passenger &pass)
{
	if (EmptyPass(rootPass))
	{
		rootPass = NewPassNode(pass);
		return;
	}

	if (pass.id > rootPass->data.id)
        InsertPass(rootPass->pRight, pass);
    else InsertPass(rootPass->pLeft, pass);
}

//Tim kiem hanh khach
PPassNode SearchPass(TreePass rootPass, int idPass)
{
	if(rootPass == NULL || idPass == rootPass->data.id)
		return rootPass;
	if (idPass > rootPass->data.id)
        return SearchPass(rootPass->pRight, idPass);
    return SearchPass(rootPass->pLeft, idPass);
}

//Xuat thong tin 1 hanh khach
void ShowPass(Passenger &pass, int position)
{
	gotoxy(xKeyDisplayPas[0] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.id;
    gotoxy(xKeyDisplayPas[1] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.firstName;
    gotoxy(xKeyDisplayPas[2] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.lastName;
    gotoxy(xKeyDisplayPas[3] + 3, Y_Display + position + 3);
	cout << left << setw(5) << (pass.gender ? "Nu" : "Nam");
}

//Xuat danh sach hanh khach trong 1 trang
//void ShowListPassOnePage(TreePass root, int startIndex)
//{
//	WORD curColor;
//	GetColor(curColor);
//	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
//
//	int position = 0;
//	int count = 0;
//	
//	PPassenger temp;
//	PPassNode node;
//	Queue<Passenger> queue;
//	InitQueue(queue);
//	pushQueue(queue, root->data);
//	RemoveContent(xKeyDisplayPas,4);
//	PreOrder(root, position);
//	
//	SetColor(curColor);
//	gotoxy(3,3);
//	cout << " So luong hanh khach : " << countPass(root);
//	gotoxy(X_Page,Y_Page);
//	cout <<" Trang " << CurPage <<"/"<< TotalPage;
//}

void ShowListPassOnePage(TreePass root, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int position = 0;
	int count = 0;
	
	gotoxy(3,3);
	cout << " So luong hanh khach : " << countPass(root);
	
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
	cout <<" Trang " << CurPage <<"/"<< TotalPage; 
}

//Thay doi danh sach hanh khach sang trang khac
void ChangePassMenuManagerPage(TreePass root)
{
	DisplayTest(xKeyDisplayPas, ContentPass,sizeof(ContentPass)/sizeof(string) );
	ShowListPassOnePage(root,(CurPage-1)*NumberPerPage);
}

//Quan ly hanh khach
void MenuManagePassenger(TreePass &rootPass ){
	CurPage = 1;
	TotalPage = (int)ceil((double)countPass(rootPass)/NumberPerPage); 	//ceil : lam tron 
	
	DisplayTest(xKeyDisplayPas, ContentPass, sizeof(ContentPass)/sizeof(string));
	ShowListPassOnePage(rootPass, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY HANH KHACH";
	
	int signal;
	Passenger pass;

	while(true)
	{
		signal = MenuSelect(X_ThaoTac,Y_ThaoTac,4,ContentPassSelect);
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
			case LEFT:
			case 2: //Chuyen trang truoc
			{
				if(CurPage == 1) break;
				else{
					CurPage--;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case RIGHT:
			case 3:	//Chuyen trang tiep
			{
				if(CurPage >= TotalPage) break;
				else{
					CurPage++;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			default: return;
			
		}
	}
}

//Load file danh sach hanh khach
bool LoadTreePass(TreePass &root)
{
	ifstream file("DSHK.TXT", ios_base::in);
	string str;
	Passenger pass;

	if(!file.is_open())
		return false;
	
	while(getline(file, str))
	{
		stringstream ss(str);

		getline(ss, str, ';');	
		if(strlen(str.c_str()) == 0)
			continue;
		pass.id = atoi(str.c_str());
		getline(ss, str, ';');	strcpy(pass.firstName, str.c_str());
		getline(ss, str, ';');	strcpy(pass.lastName, str.c_str());
		getline(ss, str, ';');	pass.gender = atoi(str.c_str());
		InsertPass(root, pass);
	}

	file.close();
	return true;
}

//Luu file danh sach hanh khach
bool SaveTreePass(TreePass root)
{
	ofstream file("DSHK.TXT", ios_base::out);

	if(!file.is_open())
		return false;
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		
		file << temp->id << ";"
			 << temp->firstName << ";"
			 << temp->lastName << ";"	
			 << temp->gender << endl;
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
	}
	

	file.close();
	return true;
}
