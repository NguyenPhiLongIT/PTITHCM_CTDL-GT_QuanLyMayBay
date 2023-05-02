#pragma once
#include <iostream>
#include <ctime>
#include <string.h>

#include "Mylibrary.h"
#include "Constraint.h"
#include "UserInterface.h"

typedef struct _Date{
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
}Date, *PDate;

Date GetCurTime();
char *DateToString(PDate pDate);
bool IsLeapYear(PDate pDate);
int CompareDate(PDate date1, PDate date2);
void InputDate(PDate pDate);
void PrintDate(PDate date);

Date GetCurTime(){
    Date Date;
    time_t Time_cur = time(NULL);
    tm* pTime = localtime(&Time_cur);

    Date.second    = pTime->tm_sec         ;
    Date.minute    = pTime->tm_min         ;
    Date.hour      = pTime->tm_hour        ;
    Date.day       = pTime->tm_mday        ;
    Date.month     = pTime->tm_mon   + 1   ;
    Date.year      = pTime->tm_year  + 1900;

    return Date;
}

char *DateToString(PDate pDate){
    char *result = new char[20];
    sprintf(result, "%.2d:%.2d %.2d/%.2d/%.4d", pDate->hour, pDate->minute, pDate->day, pDate->month, pDate->year);
    return result;
}

bool IsRightDate(PDate date){
	int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if(
        date->year < 0 ||
        date->month < 0 || date->month > 12 ||
        date->day < 0 || date->day > 31
    ){
        return false;
    }else{
        if(IsLeapYear(date))
            dayOfMonth[1] = 29;
    }
    return date->day < dayOfMonth[date->month-1];
}

bool IsValidDate(PDate date){
	if(!IsRightDate(date)) return false;
	
	Date dateNow = GetCurTime();
    if(date->year < dateNow.year) return false;
    if ((date->year == dateNow.year) && (date->month < dateNow.month))  return false;
    if (date->year == dateNow.year && date->month == dateNow.month && date->day < dateNow.day) return false;
	if (date->year == dateNow.year && date->month == dateNow.month && date->day == dateNow.day 
	 	&& date->hour < dateNow.hour) return false;
	if (date->year == dateNow.year && date->month == dateNow.month && date->day == dateNow.day && date->hour == dateNow.hour 
	 	&& date->minute < dateNow.minute) return false;
	return true;
//    return (CompareDate(date, &dateNow) > 0);
}

bool IsLeapYear(PDate pDate){
    return (pDate->year%400 == 0) 
        || (pDate->year%4 == 0 && pDate->year%100 != 0);
}
/*
So sÃ¡nh 2 ngÃ y nháº­p vÃ o chÃ­nh xÃ¡c theo giÃ¢y
Náº¿u khÃ´ng cÃ³ tham sá»‘ thá»© 2 thÃ¬ so sÃ¡nh ngÃ y nháº­p vÃ o vá»›i ngÃ y hiá»‡n táº¡i cá»§a há»‡ thá»‘ng
*/
int CompareDate(PDate date1, PDate date2){
    int SumSecond1 = date1->hour*3600+date1->minute*60+date1->second;
    int SumSecond2 = date2->hour*3600+date2->minute*60+date2->second;
    return SumSecond1 - SumSecond2;
}

void PrintDate(PDate date){
	char *DateString = DateToString(date);
    	cout << DateString;
    	delete DateString;
}

void InputDate(PDate pDate)
{
    char hour[2], minute[2];
    char day[2], month[2], year[4]; 
    int x = wherex();
    int y = wherey();
    bool isValidDate = false;

    while(!isValidDate)
    {
        ShowCursor(true);
        gotoxy(x,y);    
        std::cout <<"  :   -   /  /    .";

        gotoxy(x, y);    strcpy(hour, Input(sizeof(hour), Number));      pDate->hour = atoi(hour);
        gotoxy(x+3,y);   strcpy(minute, Input(sizeof(minute), Number));  pDate->minute = atoi(minute);
        gotoxy(x+8,y);   strcpy(day, Input(sizeof(day), Number));        pDate->day = atoi(day); 
        gotoxy(x+11,y);  strcpy(month, Input(sizeof(month), Number));    pDate->month = atoi(month);
        gotoxy(x+14,y);  strcpy(year, Input(sizeof(year), Number));      pDate->year = atoi(year);

        isValidDate = IsValidDate(pDate);
        if(isValidDate == false)
        {
            Notification("Thoi gian khong hop le!");
            // gotoxy(X_Notification,Y_Notification);
            // std::cout << "Thoi gian khong hop le!" << std::endl;
        }
    }
}
