#pragma once
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

typedef struct _Passenger
{
	char id[13];
	char firstName[31];
	char lastName[11];
	bool gender; // 1 la nam , 0 la nu
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
void InputPass(Passenger &pass);
void InsertPass(TreePass &rootPass, Passenger &pass);
PPassNode SearchPass(TreePass rootPass, char *idPass);

void ShowPass(const Passenger &pass);
void ShowListPass(TreePass root);

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

void InputPass(Passenger &pass)
{
	cout << "CCCD: ";
	cin >> pass.id;
	cout << "Ho: ";
	gets(pass.firstName);
	cout << "Ten: ";
	gets(pass.lastName);
	cout << "Phai(0:Nu - 1:Nam): ";
	cin >> pass.gender;
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

void ShowPass(const Passenger &pass, int position)
{
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.id;
    gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
    cout << left << setw(3) << pass.firstName;
    gotoxy(xKeyDisplay[2] + 3, Y_Display + position + 3);
    cout << left << setw(8) << pass.lastName;
    gotoxy(xKeyDisplay[3] + 3, Y_Display + position + 3);
	cout << left << setw(8) << (pass.gender ? "Nam" : "Nu");
}

void ShowListPassOnePage(TreePass root, int startdex)
{
	gotoxy(3,3);
	cout << " So luong khach hang : ";
	
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); //cac phan tu hien trong bang se co chu mau trang
	int count = -1;

	
	
	SetColor(curColor);
	gotoxy(X_Page,Y_Page);
	cout <<" Trang " << CurPassPage <<"/"<< TotalPassPage; 
}

void ChangeFlightMenuManagerPage(TreePass root)
{
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY CHUYEN BAY";

	Display( ContentPass,sizeof(ContentPass)/sizeof(string) );
	ShowListPassOnePage(root,(CurPassPage-1)*NumberPerPage);
}

void MenuManagePassenger(TreePass root){
//	ShowCursor(false);
	CurPassPage = 1;
	//TotalPassPage = (int)ceil((double)size(root)/NumberPassPage); 	//ceil : lam tron 
	
	Display(ContentPass, sizeof(ContentPass)/sizeof(string));
	ShowListPassOnePage(root, 0);
	
	gotoxy(X_TitlePage,Y_TitlePage);
	cout << "QUAN LY HANH KHACH";
	
	Passenger pass;
	int signal;
	while(true)
	{
		menu:
		signal = menu_dong(X_ThaoTac,Y_ThaoTac,6,ContentPass_ThaoTac);
		switch(signal) {
			case 1: // Insert
			{
				break;
			}
			edit: case 2: //Edit date time
			{
				
				break;		
			}
			case 3: //Cancle flight
			{
				
				break;
			}
			case 4: //Chuyen trang truoc
			{
				if(CurFlightPage == 1) break;
				else{
					CurFlightPage--;
					ChangeFlightMenuManagerPage(root);
				}
				break;
			}
			case 5:	//Chuyen trang tiep
			{
				if(CurFlightPage >= TotalFlightPage) break;
				else{
					CurFlightPage++;
					ChangeFlightMenuManagerPage(root);
				}
				break;
			}
			default: return;
			
		}
	}
}
