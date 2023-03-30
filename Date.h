#pragma once
#include <iostream>
#include <ctime>
#include <string.h>

typedef struct _Date{
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
}Date, *PDate;

PDate GetCurTime();
bool IsLeapYear(PDate);
int CompareDate(PDate, PDate);

PDate GetCurTime(){
    PDate pDate = new Date;
    time_t Time_cur = time(NULL);
    tm* pTime = localtime(&Time_cur);

    pDate->second    = pTime->tm_sec         ;
    pDate->minute    = pTime->tm_min         ;
    pDate->hour      = pTime->tm_hour        ;
    pDate->day       = pTime->tm_mday        ;
    pDate->month     = pTime->tm_mon   + 1   ;
    pDate->year      = pTime->tm_year  + 1900;

    return pDate;
}

bool IsValidDate(PDate date){
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

bool IsLeapYear(PDate date){
    return (date->year%400 == 0) 
        || (date->year%4 == 0 && date->year%100 != 0);
}
/*
So sánh 2 ngày nhập vào chính xác theo giây
Nếu không có tham số thứ 2 thì so sánh ngày nhập vào với ngày hiện tại của hệ thống
*/
int CompareDate(PDate date1, PDate date2 = GetCurTime()){
    int SumSecond1 = date1->hour*3600+date1->minute*60+date1->second;
    int SumSecond2 = date2->hour*3600+date2->minute*60+date2->second;
    return SumSecond1 - SumSecond2;
}

void FormatDate(PDate pDate){
    
}

void PrintDate(PDate date){
    std :: cout << date->day << "/" << date->month << "/" << date->year
        << " " << date->second << ":" << date->minute << ":" << date->hour;
}