#pragma once
#include <iostream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <windows.h>

using namespace std;

#include "Mylibrary.h"
#include "KeyValue.h"

// Xuat bang thong tin
int xKeyDisplay[8] = {1,19,37,55,75,93,111,127};
int CurPage = 1;
int TotalPage = 0;

//May bay
string ContentAirplane[5] = { "Plane ID", "Plane Type", "Column", "Row", "Seat"};
string ContentAirSelect[6] = {"Insert", "Delete", "Edit", "Previous Page", "Next Page", "Back"};
string ContentAirplaneInput[3] = {"Plane ID", "Plane Type", "Column & Row"};

//Chuyen bay
string ContentFlight[6] = { "Flight ID", "Destination", "Plane ID", "Date and Time", "Number Tickets", "Status"};
string ContentFlightSelect[6] = {"Insert", "Edit DateTime", "Cancle Flight", "Previous Page", "Next Page", "Back"};

//Ve
string ContentTicketInput[2] = {"PassengerID","Seat"};
string ContentTicketOutput[3] = {"Seat", "Status", "PassengerID"};
string ContentTicketSelect2[5] = {"Book Seat", "Cancel Seat", "Previous Page", "Next Page", "Back"};
string ContentTicketSelect1[5] = {"Book Ticket", "Filter", "Previous Page", "Next Page", "Back"};

//Hanh khach
string ContentPass[4] = {"ID", "FirstName", "LastName", "Gender"};
string ContentPassSelect[4] = {"Insert", "Previous Page", "Next Page", "Back"};
string ContentGender[2] = {"Nam", "Nu"};

//Menu
string ContentMenu[7] = {"Home", "Plane", "Flight", "Passenger", "Ticket", "List", "Exit"};

//Ve 1 hop thoai
void Box(int x, int y, int w, int h, string nd) {
	WORD curColor;
	GetColor(curColor);
	SetBGColor(BLACK);
	for (int iy = y + 1; iy < y+h; iy++) {
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoxy(ix,iy);
			cout << " ";
		}
	}//========= noi dung
	SetColor(WHITE);
	gotoxy(x+1,y+1);
	cout << nd;
	// ============= ve vien ============
	SetColor(YELLOW);
	//========= ve vien ngang
	for (int ix = x; ix <= x + w; ix++) {
		gotoxy(ix,y);
		cout << char(196);
		gotoxy(ix,y + h);
		cout << char(196);
	}
	//=========== ve vien doc
	for (int iy = y; iy <= y + h; iy++) {
		gotoxy(x, iy);
		cout << char(179);
		gotoxy(x+w, iy);
		cout << char(179);
	}
	//========== bo goc
	gotoxy(x,y); cout << char(218);
	gotoxy(x+w,y); cout << char(191);
	gotoxy(x,y+h); cout << char(192);
	gotoxy(x+w,y+h); cout << char(217);
	SetColor(curColor);
}

//Xoa 1 hop thoai
void RemoveBox(int x, int y, int w, int h) {
	for (int iy = y; iy <= y+h; iy++) {
		for (int ix = x; ix <= x + w; ix++) {
			gotoxy(ix,iy);
			cout << " ";
		}
	}
}

//Thong bao
void Notification(string s) {
	ShowCursor(false);
	int n = s.length();
	int x = wherex(), y = wherey();
	Box(X_Notification,Y_Notification+1,n+1,2,s);
	Sleep(1700);
	while(_kbhit()) _getch(); //khong nhan phim trong thoi gian ngu
	RemoveBox(X_Notification,Y_Notification+1,n+1,2);
	ShowCursor(true);
}

//Tao nhieu hop thoai
void MultiBox(int x, int y, int soluong, string noidung[]) {
	WORD curColor;
	GetColor(curColor);
	for (int i = 0; i < soluong; i++) {
		SetColor(YELLOW);
		Box(x, y + i*Box_Height, Box_Width, Box_Height, noidung[i]);
		if (i != 0) {
			gotoxy(x, y + i*Box_Height);
			cout << char(195);
			gotoxy(x + Box_Width,y + i*Box_Height);
			cout << char(180);
		}
	}
	SetColor(curColor);
}

//Thanh sang
void Highlight(int x, int y, int w, int h, int b_color, string nd) {
	WORD curColor;
	GetColor(curColor);
	ShowCursor(false);
	SetBGColor(b_color);
	for (int iy = y + 1; iy < y + h; iy++) {
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoxy(ix,iy);
			cout << " ";
		}
	}
	SetColor(WHITE);
	gotoxy(x+1,y+1);
	cout << nd;
	SetBGColor(BLACK);
	SetColor(curColor);
}

int MenuSelect(int x, int y, int sl, string nd[]) {
	MultiBox(x,y,sl,nd);
	int xtmp = x, ytmp = y;
	int xOld = xtmp, yOld = ytmp;
	int i = 0;
	int j = i; //luu vi tri box gan nhat
	bool kt = true; //kiem tra co nhap phim khong
	while (true) {
		gotoxy(xOld,yOld);
		Highlight(xOld,yOld,Box_Width,Box_Height,BLACK,nd[j]);
		j = i; xOld = xtmp; yOld = ytmp;
		Highlight(xtmp,ytmp,Box_Width,Box_Height,BLUE_LIGHT,nd[i]);
		kt = false;
		char c = _getch();
		if (c == -32) {
			kt = true;
			c = _getch();
			if (c == UP && ytmp != y) {
				ytmp -= Box_Height;
				i--;
			} else if (c == DOWN && ytmp != y + Box_Height*(sl-1)) {
				ytmp += Box_Height;
				i++;
			}
			if (c == LEFT || c == RIGHT)	return c;
		} else if (c == ENTER) {
			if (ytmp == y + Box_Height*(sl-1)) Highlight(xtmp,ytmp,Box_Width,Box_Height,BLACK,nd[i]);
			return i+1;
		} else if (c == ESC) {
			Highlight(xtmp,ytmp,Box_Width,Box_Height,BLACK,nd[i]);
			return -1;
		}
	}
}

//Ve bang
void Display(string content[], int nContent) 
{
	SetColor(11);
	SetBGColor(0);
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 3, Y_Display+1);
		cout << content[i];
	}

	//ve cac duong thang de phan chia cac cot - kich thuoc toi da la 28 ve chieu dai
	for (int j = Y_Display ; j <= Y_Display + 24; j++)
	{
		for (int i = 0; i < nContent+1; i++)
		{
			gotoxy(xKeyDisplay[i], j);
			cout << char(186);
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display);
		cout << char(186);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << char(186);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 25);
		cout << char(205);
	}
}

//Loai bo nhung phan tu da hien thi o Page truoc 
void RemoveExceedMember(int count,int nContent)	
{
	if (count < NumberPerPage)
	{
		for (int i = count; i < NumberPerPage; i++)
		{
			for (int y = 0; y < nContent; y++)
			{
				gotoxy(xKeyDisplay[y] + 2, Y_Display + 3 + i); printf("%-16s"," ");
			}
		}
	}
}

//Tao 1 hang
void CreateRow(int x, int y, string content, int length)
{
	gotoxy(x - 2, y - 1);
	cout << char(254) << setw(length) << setfill(char(254)) << char(254) << char(254);

	gotoxy(x - 2, y);
	cout << char(186) << content << setw(length - content.length() + 1) << setfill(' ') << char(186);
}

//Xoa 1 hang
void RemoveRow(int x, int y, string content, int length) {
	gotoxy(x - 2, y - 1);
	cout << " " << setw(length) << setfill(' ') << " " << " ";

	gotoxy(x - 2, y);
	cout << " " << " " << setw(length - content.length() + 1) << setfill(' ') << " ";
}

//Tao 1 bang nhap thong tin
void CreateForm(string content[],int StartIndex,int nContent,int length)
{
	int yAdd = Y_Add;
	for (int i = StartIndex; i < nContent; i++)
	{
		CreateRow(X_Add, yAdd,content[i],length);
		yAdd += 3;
	}
}

//Xoa bang nhap thong tin
void RemoveForm(int StartIndex,int nContent,int length) {
	int yAdd = Y_Add;
	for (int i = StartIndex; i < nContent; i++)
	{
		RemoveRow(X_Add, yAdd," ",length);
		yAdd += 3;
	}
}

//Xoa bang hien thi
void RemoveTable(string content[], int nContent){
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 3, Y_Display+1);
		printf("%-16s"," ");
	}

	//xoa cac duong thang de phan chia cac cot - kich thuoc toi da la 28 ve chieu dai
	for (int j = Y_Display ; j <= Y_Display + 24; j++)
	{
		for (int i = 0; i < nContent+1; i++)
		{
			gotoxy(xKeyDisplay[i], j);	
			printf("%-20s"," ");
		}
	}
	//xoa thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//xoa thanh ngang ben tren so 1
		gotoxy(i, Y_Display-1);
		cout << " ";

		//xoa thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << " ";

		//xoa thanh ngang ben duoi
		gotoxy(i, Y_Display + 25);
		cout << " ";
	}
	gotoxy(X_Page,Y_Page);
	cout << "                    ";
}
