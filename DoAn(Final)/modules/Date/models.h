#ifndef __DATE__UTILS__
#define __DATE__UTILS__

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <math.h>
#include "types.h"

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

PDate StringToDate(char *str){
    PDate pDate = new Date;
    sscanf(str, "%d:%d %d/%d/%d", &pDate->hour, &pDate->minute, &pDate->day, &pDate->month, &pDate->year);
    return pDate;
}

bool IsLeapYear(PDate pDate){
    return (pDate->year%400 == 0) 
        || (pDate->year%4 == 0 && pDate->year%100 != 0);
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
    return date->day <= dayOfMonth[date->month-1];
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
}

bool Check12Hours(PDate date1, PDate date2){
	int SumMinute1 = date1->hour*60+date1->minute;
   	int SumMinute2 = date2->hour*60+date2->minute;
	if(date1->day == date2->day && date1->month == date2->month && date1->year == date2->year){
		if (abs(SumMinute1 - SumMinute2) < 720) return false;
	}
	else if(abs(date1->day - date2->day) == 1 && date1->month == date2->month && date1->year == date2->year){
		if (abs(SumMinute1 - SumMinute2) > 720) return false;
	}
	return true;
}

int CompareDate(PDate date1, PDate date2){
	int result, SumMinute1, SumMinute2;
	SumMinute1 = date1->hour*60+date1->minute;
   	SumMinute2 = date2->hour*60+date2->minute;
   	result = abs(SumMinute1 - SumMinute2);
	if(abs(date1->day - date2->day) == 1 || abs(date1->day - date2->day) == 30 ||
		abs(date1->day - date2->day) == 29 || abs(date1->day - date2->day) == 27){
		result = abs(abs(SumMinute1 - SumMinute2) - 24*60);
	}
	return result;
}

void PrintDate(PDate date){
	char *DateString = DateToString(date);
    	std::cout << DateString;
    	delete DateString;
}

#endif
