#pragma once
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <iostream>

#define Enter 13

// char* Pwd();
// int CheckPwd();
void gotoxy(short x, short y);
int wherex();
int wherey();
void clreol();
void SetColor(WORD color);
void SetBGColor(WORD color);
void Clear();
void ShowCursor(bool CursorVisibility);
void DisableSelection();
void SizeConsole(SHORT width, SHORT height);
void fullScreen();

// const int WHITE=15;
//  #define PASSWORD "abcdef"
// const int WHITE=15;

// char* Pwd () {
//     char S[40]; int i=0;
//     while((S[i]= getch()) != Enter ){
//         printf ("%c", '*') ; i++ ;
//     }
//     S[i]='\0';
//     return S;
// }

// int CheckPwd(){
//     for (int count = 1 ; count <=3 ; count++){
//         printf( "Password :");
//         if(strcmp(Pwd(),PASSWORD) == 0)   return 1;
//         else printf ( "\nPassword sai. Hay nhap lai\n")  ;
//     }
//     return 0;
// }

void gotoxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

int wherex()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
// Sá»­ dá»¥ng Ä‘á»ƒ xÃ³a dÃ²ng tá»« vá»‹ trÃ­ coord Ä‘áº¿n con trá» hiá»‡n táº¡i trÃªn Console
void clreol(COORD coord)
{
    // COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // coord.X = info.dwCursorPosition.X;
    // coord.Y = info.dwCursorPosition.Y;
    FillConsoleOutputCharacter(
        GetStdHandle(STD_OUTPUT_HANDLE),
        ' ',
        info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y,
        coord,
        &written
    );
    gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void GetColor(WORD &color)
{
	HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    
    color = screen_buffer_info.wAttributes;
}

void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//XÃ³a toÃ n bá»™ mÃ n hÃ¬nh console
void Clear()
{
	SetBGColor(0);
    DWORD written;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = 0;
    coord.Y = 0;
    FillConsoleOutputCharacter(
        GetStdHandle(STD_OUTPUT_HANDLE),
        ' ',
        info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y,
        coord,
        &written
    );
}

//Hien thi con tro hoac khong
void ShowCursor(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 10;
    cursor.bVisible = CursorVisibility;
    SetConsoleCursorInfo(handle, &cursor);
}

void SizeConsole(SHORT width, SHORT height)
{
	SMALL_RECT SizeW = { 0,0,width - 1,height - 1 };
	COORD sizebuff = { width,height };
	BOOL BSize = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &SizeW);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), sizebuff);
	if (!BSize) SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &SizeW);
}

void fullScreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
