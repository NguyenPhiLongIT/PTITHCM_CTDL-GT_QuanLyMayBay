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
//Airplane
string ContentAirplane[5] = { "Plane ID", "Plane Type", "Column", "Row", "Seat"};
string ContentThaoTac[6] = {"Insert", "Delete", "Edit", "Previous Page", "Next Page", "Back"};
string ContentAirplane_Input[3] = {"Plane ID", "Plane Type", "Column & Row"};
//Flight
string ContentFlight[6] = { "Flight ID", "Destination", "Plane ID", "Date and Time", "Number Tickets", "Status"};
string ContentFlight_ThaoTac[6] = {"Insert", "Edit DateTime", "Cancle Flight", "Previous Page", "Next Page", "Back"};
//Ticket
string ContentTicket_Input[2] = {"PassengerID","Seat"};
string ContentTicket_Output[3] = {"Seat", "Status", "PassengerID"};
string ContentTicket_ThaoTac[5] = {"Order", "Cancel", "Previous Page", "Next Page", "Back"};
//Passenger
string ContentPass[4] = {"ID", "FirstName", "LastName", "Gender"};
string ContentPass_ThaoTac[6] = {"Insert", "Delete", "Edit", "Previous Page", "Next Page", "Back"};
//Menu
string ContentMenu[6] = {"Home", "Plane", "Flight", "Passenger", "Ticket", "Exit"};





void box(int x, int y, int w, int h, string nd) {
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

void remove_box(int x, int y, int w, int h) {
	for (int iy = y; iy <= y+h; iy++) {
		for (int ix = x; ix <= x + w; ix++) {
			gotoxy(ix,iy);
			cout << " ";
		}
	}
}

void Notification(string s) {
	ShowCursor(false);
	int n = s.length();
	int x = wherex(), y = wherey();
	box(X_Notification,Y_Notification+1,n+1,2,s);
	Sleep(1200);
	while(_kbhit()) _getch(); //khong nhan phim trong thoi gian ngu
	remove_box(X_Notification,Y_Notification+1,n+1,2);
	ShowCursor(true);
}

void n_box(int x, int y, int soluong, string noidung[]) {
	WORD curColor;
	GetColor(curColor);
	for (int i = 0; i < soluong; i++) {
		SetColor(YELLOW);
		box(x, y + i*Box_Height, Box_Width, Box_Height, noidung[i]);
		if (i != 0) {
			gotoxy(x, y + i*Box_Height);
			cout << char(195);
			gotoxy(x + Box_Width,y + i*Box_Height);
			cout << char(180);
		}
	}
	SetColor(curColor);
}

void thanh_sang(int x, int y, int w, int h, int b_color, string nd) {
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

int menu_dong(int x, int y, int sl, string nd[]) {
	n_box(x,y,sl,nd);
	int xp = x, yp = y;
	int xcu = xp, ycu = yp;
	int i = 0;
	int j = i; //luu vi tri box gan nhat
	bool kt = true; //kiem tra co nhap phim khong
	while (true) {
		if (kt == true) {
			gotoxy(xcu,ycu);
			thanh_sang(xcu,ycu,Box_Width,Box_Height,BLACK,nd[j]);
			j = i; xcu = xp; ycu = yp;
			thanh_sang(xp,yp,Box_Width,Box_Height,BLUE_LIGHT,nd[i]);
			kt = false;
		}
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				kt = true;
				c = _getch();
				if (c == UP && yp != y) {
					yp -= Box_Height;
					i--;
				} else if (c == DOWN && yp != y + Box_Height*(sl-1)) {
					yp += Box_Height;
					i++;
				} 
			} else if (c == ENTER) {
				if (yp == y + Box_Height*(sl-1)) thanh_sang(xp,yp,Box_Width,Box_Height,BLACK,nd[i]);
				return i+1;
			} else if (c == ESC) {
				thanh_sang(xp,yp,Box_Width,Box_Height,BLACK,nd[i]);
				return -1;
			}
		}
	}
}

void Display(string content[], int nContent) 	// ve bang
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

	//ve cac duong thang de phan chia cac cot - kich thuoc toi da la 28 ve chieu dai
	for (int j = Y_Display ; j <= Y_Display + 24; j++)
	{
		for (int i = 0; i < nContent+1; i++)
		{
			gotoxy(xKeyDisplay[i], j);	
			printf("%-20s"," ");
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display-1);
		cout << " ";

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		cout << " ";

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 25);
		cout << " ";
	}
	gotoxy(X_Page,Y_Page);
	cout << "                    ";
}
