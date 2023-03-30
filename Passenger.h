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

void ShowPass(const Passenger &pass)
{
	cout << pass.id << endl;
	cout << pass.firstName << endl;
	cout << pass.lastName << endl;
	cout << (pass.gender ? "Nam" : "Nu") << endl;
}

void ShowListPass(TreePass root)
{
	
}
