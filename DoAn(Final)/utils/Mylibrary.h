#ifndef __MYLIBRARY__UTILS__
#define __MYLIBRARY__UTILS__

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <iostream>

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
// Sử dụng để xóa dòng từ vị trí coord đến con trỏ hiện tại trên Console
void Clean(int left, int top, int right, int bottom)
{
    HANDLE hConsoleOutput;
    COORD coord;
    DWORD written, dwCells;
    CONSOLE_SCREEN_BUFFER_INFO info;

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    if(GetConsoleScreenBufferInfo(hConsoleOutput, &info)){
        coord.X = left;
        coord.Y = top;

        dwCells = right - left + 1;
        while(coord.Y <= bottom){
            FillConsoleOutputCharacter(
                hConsoleOutput,
                ' ',
                dwCells,
                coord,
                &written
            );
            FillConsoleOutputAttribute(
                hConsoleOutput,
                // (info.wAttributes & 0xff00) | 0x0007,
                info.wAttributes,
                dwCells,
                coord,
                &written
            );
            ++coord.Y;
        }
        SetConsoleCursorPosition(hConsoleOutput, info.dwCursorPosition);
    }
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
//Xóa toàn bộ màn hình console
void Clear()
{
	SetBGColor(0);
    HANDLE hConsoleOutput;
    DWORD written;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO info;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 0;
    coord.Y = 0;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    FillConsoleOutputCharacter(
        GetStdHandle(STD_OUTPUT_HANDLE),
        ' ',
        info.dwSize.X * info.dwSize.Y,
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

#endif