#pragma once
#include <iostream>
#include <string.h>
#include <fstream>

#include "KeyValue.h"
#include "Constraint.h"
#include "UserInterface.h"
#include "Stack_Queue.h"

using namespace std;

typedef struct _Passenger
{
	char id[13];
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

int CurPosPass = 0;
int CurPassPage = 1;
int TotalPassPage = 0;
extern string ContentFlight[6];

void InitTreePass(TreePass &rootPass);
bool EmptyPass(TreePass &rootPass);
PPassNode NewPassNode(Passenger &data);
void PreOrder(TreePass &rootPass, int &position);
int countPass(TreePass &rootPass);

void InputPass(TreePass &rootPass, Passenger &pass);
void InsertPass(TreePass &rootPass, Passenger &pass);
PPassNode SearchPass(TreePass rootPass, char *idPass);


void ShowPass(Passenger &pass, int position);
void ShowListPass(TreePass root);

bool LoadTreePass(TreePass &pass);
bool SaveTreePass(TreePass pass);

void InitTreePass(TreePass &rootPass)
{
	rootPass = NULL;
}

bool EmptyPass(TreePass &rootPass)
{
	return rootPass == NULL;
}

PPassNode NewPassNode(Passenger &data)
{
	PPassNode passNode = new PassNode;
	passNode->data = data;
	passNode->pLeft = passNode->pRight = NULL;
	return passNode;
}

int countPass(TreePass &rootPass)
{
	if(rootPass == NULL)	return 0;

	return 1 + countPass(rootPass->pLeft) + countPass(rootPass->pRight);
}

void PreOrder(TreePass &rootPass, int &position){
	if(rootPass == NULL) return;
	ShowPass(rootPass->data, position);
	++position;
	PreOrder(rootPass->pLeft, position);
	PreOrder(rootPass->pRight, position);
}

void ChooseGender(bool &gender){
	int signal = menu_dong(X_Add+14,Y_Add+9,2,ContentGender);
	gender = --signal;	
}

void InputPass(TreePass &rootPass, Passenger &pass)
{
	ShowCursor(true);
	int ordinal = 0;	//thu tu nhap
	int position = -1;	//vi tri hanh khach
	CreateForm(ContentPass, 0, 4, 27);
	while(true){
		switch(ordinal){
			case 0:{	//Nhap CCCD
				gotoxy(X_Add+10,Y_Add);       	strcpy(pass.id, Input(sizeof(pass.id), ID));
				
				if(strlen(pass.id) == 0){
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
				gotoxy(X_Add+13,Y_Add+9);
				ChooseGender(pass.gender);
				ordinal++;
				break;
			}
			case 4:{
				InsertPass(rootPass, pass);
				RemoveForm(0, 4, 27);
			}
			return;
		}
		ShowCursor(false);
	}
}

void InsertPass(TreePass &rootPass, Passenger &pass)
{
	if (EmptyPass(rootPass))
	{
		rootPass = NewPassNode(pass);
		return;
	}
	PPassNode p = rootPass;
	while (true)
	{
		if (atoi(rootPass->data.id) > atoi(pass.id))
		{
			if (p->pRight == NULL)
			{
				p->pRight = NewPassNode(pass);
				return;
			}
			else
			{
				p = p->pRight;
			}
		}
		else
		{
			if (p->pLeft == NULL)
			{
				p->pLeft = NewPassNode(pass);
				return;
			}
			else
			{
				p = p->pLeft;
			}
		}
	}
}

PPassNode SearchPass(TreePass rootPass, char *idPass)
{
	while (!EmptyPass(rootPass))
	{
		if (0 == strcmp(rootPass->data.id, idPass))
			return rootPass;
		else if (strcmp(rootPass->data.id, idPass) < 0)
			rootPass = rootPass->pLeft;
		else
			rootPass = rootPass->pRight;
	}
	return NULL;
}

void ShowPass(Passenger &pass, int position)
{
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.id;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.firstName;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.lastName;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position + 3);
	cout << left << setw(8) << (pass.gender ? "Nu" : "Nam");
}

void ShowListPassOnePage(TreePass root, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int position = startIndex;
	
	
	gotoxy(3,3);
	cout << " So luong hanh khach : " << position;
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		
		ShowPass(*temp, position);
		++position;
		
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
		if(position >= NumberPerPage){
			break;
		}
	}
	
	SetColor(curColor);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPassPage <<"/"<< TotalPassPage; 
}

void ChangePassMenuManagerPage(TreePass root)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY HANH KHACH";

	Display( ContentPass,sizeof(ContentPass)/sizeof(string) );
	ShowListPassOnePage(root,(CurPassPage-1)*NumberPerPage);
}

void MenuManagePassenger(TreePass &rootPass, Passenger pass){
	CurPassPage = 1;
//	TotalPassPage = (int)ceil((double)countPass(rootPass)/NumberPassPage); 	//ceil : lam tron 
	
	Display(ContentPass, sizeof(ContentPass)/sizeof(string));
	ShowListPassOnePage(rootPass, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY HANH KHACH";
	
	int signal;
	while(true)
	{
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,3,ContentPass_ThaoTac);
		gotoxy(50,50); cout << "HAHAHAHA";
		switch(signal) {
			case 1: // Insert
			{
				if(CurPassPage == 0) CurPassPage = 1;
				InputPass(rootPass, pass);

//				TotalPassPage = (int)ceil((double)size(first)/NumberPerPage);
				ShowListPassOnePage(rootPass, (CurPassPage-1)*NumberPerPage);
				ShowCursor(false);
				break;
			}
			case 2: //Chuyen trang truoc
			{
				if(CurPassPage == 1) break;
				else{
					CurPassPage--;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			case 3:	//Chuyen trang tiep
			{
				if(CurPassPage >= TotalPassPage) break;
				else{
					CurPassPage++;
					ChangePassMenuManagerPage(rootPass);
				}
				break;
			}
			default: return;
			
		}
	}
}

bool LoadTreePass(TreePass &root)
{
	ifstream file("DSHK.TXT", ios_base::in);
	char str[10];
	Passenger pass;

	if(!file.is_open())
		return false;
	
	while(!file.eof())
	{
		
		file.getline(pass.id, sizeof(pass.id), ';');
		if(strcmp(pass.id, "") != 0)
		{
			file.getline(pass.firstName, sizeof(pass.firstName), ';');
			file.getline(pass.lastName, sizeof(pass.lastName), ';');
//			file >> pass.gender;
//			file.ignore();
			file.getline(str,sizeof(str));
			pass.gender = atoi(str);
			InsertPass(root, pass);
		}
	}

	file.close();
	return true;
}

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
