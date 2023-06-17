#ifndef __USERINTERFACE__
#define __USERINTERFACE__

#include <iostream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

#include "Mylibrary.h"
#include "../types/KeyValue.h"

int xKeyDisplay[8] = {1,19,37,55,80,92,104,140};
int CurPage = 1;
int TotalPage = 0;

//May bay
std::string ContentAirplane[5] = { "Plane ID", "Plane Type", "Column", "Row", "Seat"};
std::string ContentAirSelect[6] = {"Insert", "Delete", "Edit", "Previous Page", "Next Page", "Back"};
std::string ContentAirplaneInput[3] = {"Plane ID", "Plane Type", "Column & Row"};

//Chuyen bay
std::string ContentFlight[6] = { "Flight ID", "Destination", "Plane ID", "Date and Time", "Number Tickets", "Status"};
std::string ContentFlightSelect[7] = {"Insert", "Edit DateTime", "Cancle Flight", "PassOfFlight", "Previous Page", "Next Page", "Back"};

//Ve
std::string ContentTicketInput[2] = {"PassengerID","Seat"};
std::string ContentTicketOutput[3] = {"Seat", "Status", "PassengerID"};
std::string ContentTicketSelect1[5] = {"Book Ticket", "Filter", "Previous Page", "Next Page", "Back"};
std::string ContentTicketSelect2[6] = {"Book Seat", "Cancel Seat", "Change Display", "Previous Page", "Next Page", "Back"};
std::string ContentTicketEmpty[2] = {"Full Ticket", "Empty Ticket"};

//Hanh khach
std::string ContentPass[4] = {"ID", "FirstName", "LastName", "Gender"};
std::string ContentPassSelect[5] = {"Insert", "Edit", "Previous Page", "Next Page", "Back"};
std::string ContentGender[2] = {"Nam", "Nu"};

//Menu
std::string ContentMenu[7] = {"Home", "Plane", "Flight", "Passenger", "Ticket", "List", "Exit"};

//List
std::string ContentListAir[2] = {"Plane ID", "NumOfFlying"};
std::string ContentListPass[6] = {"STT", "Ticket", "ID Pass", "FirstName", "LastName", "Gender"};

//Ve 1 hop thoai
void Box(int x, int y, int w, int h, std::string nd) {
	WORD curColor;
	GetColor(curColor);
	SetBGColor(BLACK);
	for (int iy = y + 1; iy < y+h; iy++) {
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoxy(ix,iy);
			std::cout << " ";
		}
	}
	//========= noi dung
	SetColor(WHITE);
	gotoxy(x+1,y+1);
	std::cout << nd;
	// ============= ve vien ============
	SetColor(YELLOW);
	//========= ve vien ngang
	for (int ix = x; ix <= x + w; ix++) {
		gotoxy(ix,y);
		std::cout << char(196);
		gotoxy(ix,y + h);
		std::cout << char(196);
	}
	//=========== ve vien doc
	for (int iy = y; iy <= y + h; iy++) {
		gotoxy(x, iy);
		std::cout << char(179);
		gotoxy(x+w, iy);
		std::cout << char(179);
	}
	//========== bo goc
	gotoxy(x,y); std::cout << char(218);
	gotoxy(x+w,y); std::cout << char(191);
	gotoxy(x,y+h); std::cout << char(192);
	gotoxy(x+w,y+h); std::cout << char(217);
	SetColor(curColor);
}

//Xoa 1 hop thoai
void RemoveBox(int x, int y, int w, int h) {
	// Clean(x, y, x + w, y + h);
	for (int iy = y; iy <= y+h; iy++) {
		for (int ix = x; ix <= x + w; ix++) {
			gotoxy(ix,iy);
			std::cout << " ";
		}
	}
}

//Thong bao
void Notification(std::string s) {
	ShowCursor(false);
	int n = s.length();
	int x = wherex(), y = wherey();
	Box(X_Notification,Y_Notification+1,n+1,2,s);
	Sleep(1700);
	while(_kbhit()) _getch(); //khong nhan phim trong thoi gian ngu
	RemoveBox(X_Notification,Y_Notification+1,n+1,2);
	gotoxy(x, y);
	ShowCursor(true);
}

//Tao nhieu hop thoai
void MultiBox(int x, int y, int soluong, std::string noidung[]) {
	WORD curColor;
	GetColor(curColor);
	for (int i = 0; i < soluong; i++) {
		SetColor(YELLOW);
		Box(x, y + i*Box_Height, Box_Width, Box_Height, noidung[i]);
		if (i != 0) {
			gotoxy(x, y + i*Box_Height);
			std::cout << char(195);
			gotoxy(x + Box_Width,y + i*Box_Height);
			std::cout << char(180);
		}
	}
	SetColor(curColor);
}

//Thanh sang
void Highlight(int x, int y, int w, int h, int b_color, std::string nd) {
	WORD curColor;
	GetColor(curColor);
	ShowCursor(false);
	SetBGColor(b_color);
	for (int iy = y + 1; iy < y + h; iy++) {
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoxy(ix,iy);
			std::cout << " ";
		}
	}
	SetColor(WHITE);
	gotoxy(x+1,y+1);
	std::cout << nd;
	SetBGColor(BLACK);
	SetColor(curColor);
}

int MenuSelect(int x, int y, int sl, std::string nd[]) {
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
			if (c == LEFT || c == RIGHT)
				return c;
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
void Display(int *xKey, std::string content[], int nContent) 
{
	SetColor(11);
	SetBGColor(0);
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKey[i] + 3, Y_Display+1);
		std::cout << content[i];
	}

	//ve cac duong thang de phan chia cac cot - kich thuoc toi da la 28 ve chieu dai
	for (int j = Y_Display ; j <= Y_Display + 24; j++)
	{
		for (int i = 0; i < nContent+1; i++)
		{
			gotoxy(xKey[i], j);
			std::cout << char(186);
		}
	}
	//ve thanh ngang ben tren va duoi
	for (int i = xKey[0]; i <= xKey[nContent]; i++)
	{
		//ve thanh ngang ben tren so 1
		gotoxy(i, Y_Display);
		std::cout << char(186);

		// ve thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		std::cout << char(186);

		//ve thanh ngang ben duoi
		gotoxy(i, Y_Display + 25);
		std::cout << char(205);
	}
	//ve khung huong dan phim tat
	gotoxy(X_Shortcuts, Y_Shortcuts); std::cout << "----Phim Tat----" << std::endl;
	std::cout << " ESC : Thoat hoac Tro Lai Thao Tac Truoc" << "    " 
		<< "-> : Chuyen Trang Sau" << "    " << "<- : Chuyen Trang Truoc";
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
				gotoxy(xKeyDisplay[y] + 2, Y_Display + 3 + i);
				printf("%-16s"," ");
			}
		}
	}
}

void RemoveContent(int *xKey,int nContent) {
	for (int i = 0; i < nContent; i++) {
		Clean(xKey[i]+1,Y_Display+3,xKey[i+1]-1, Y_Display + 24);
	}
}

//Tao 1 hang
void CreateRow(int x, int y, std::string content, int length)
{
	gotoxy(x - 2, y - 1);
	std::cout << char(254) << std::setw(length) << std::setfill(char(254)) << char(254) << char(254);

	gotoxy(x - 2, y);
	std::cout << char(186) << content << std::setw(length - content.length() + 1) << std::setfill(' ') << char(186);
}

//Xoa 1 hang
void RemoveRow(int x, int y, std::string content, int length) {
	gotoxy(x - 2, y - 1);
	std::cout << " " << std::setw(length) << std::setfill(' ') << " " << " ";

	gotoxy(x - 2, y);
	std::cout << " " << " " << std::setw(length - content.length() + 1) << std::setfill(' ') << " ";
}

//Tao 1 bang nhap thong tin
void CreateForm(std::string content[],int StartIndex,int nContent,int length)
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
void RemoveTable(std::string content[], int nContent){
	//xoa content cua cac cot
	for (int i = 0; i < nContent; i++)
	{
		gotoxy(xKeyDisplay[i] + 2, Y_Display);
		printf("%-30s"," ");
		gotoxy(xKeyDisplay[i] + 2, Y_Display+1);
		printf("%-30s"," "); 
		Clean(xKeyDisplay[i]+1,Y_Display+3,xKeyDisplay[i+1]-1, Y_Display + 24);   
	}

	//xoa cac duong thang de phan chia cac cot - kich thuoc toi da la 28 ve chieu dai
	for (int j = Y_Display ; j <= Y_Display + 24; j++)
	{
		for (int i = 0; i < nContent+1; i++)
		{
			gotoxy(xKeyDisplay[i], j);	
			std::cout << "            ";
		}
	}
	
	//xoa thanh ngang ben tren va duoi
	for (int i = xKeyDisplay[0]; i <= xKeyDisplay[nContent]; i++)
	{
		//xoa thanh ngang ben tren so 1
		gotoxy(i, Y_Display-1);
		std::cout << " ";

		//xoa thanh ngang ben tren so 2
		gotoxy(i, Y_Display + 2);
		std::cout << "       ";

		//xoa thanh ngang ben duoi
		gotoxy(i, Y_Display + 25);
		std::cout << "             ";
	}
	
	//xoa bang chuc nang
	for (int i = 111; i <= 130; i++)
	{
		for(int j = 4; j <= 20; j++)
		{
			gotoxy(i, j);
			std::cout << " ";
		}
	}
	gotoxy(X_Page,Y_Page);
	std::cout << "                    ";
}

#endif
