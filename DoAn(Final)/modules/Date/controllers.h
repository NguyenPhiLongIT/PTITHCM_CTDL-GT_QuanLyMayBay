#ifndef __DATE__CONTROLLERS__
#define __DATE__CONTROLLERS__

#include <iostream>
#include <string.h>

#include "models.h"
#include "../../utils/String.h"
#include "../../utils/UserInterface.h"
#include "../../utils/Mylibrary.h"

void InputDate(PDate pDate, bool filter = false)
{
    int x = wherex();
    int y = wherey();
    bool isValidDate = false;
    char *str;

    while(!isValidDate)
    {
        ShowCursor(true);
        gotoxy(x,y);    
        if(filter == false) {
        	std::cout <<"  :   -   /  /    .";

        	gotoxy(x, y);
            str = Input(2, Number);
            pDate->hour = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+3,y);
            str = Input(2, Number);
            pDate->minute = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+8,y);
            str = Input(2, Number);
            pDate->day = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+11,y);
            str = Input(2, Number);
            pDate->month = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+14,y);
            str = Input(4, Number);
            pDate->year = atoi(str);
            freeMemmorry(str);
		}
		else {
			std::cout <<"   /  /    .";

			gotoxy(x+1,y);
            str = Input(2, Number);
            pDate->day = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+4,y);
            str = Input(2, Number);
            pDate->month = atoi(str);
            freeMemmorry(str);

        	gotoxy(x+7,y);
            str = Input(4, Number);
            pDate->year = atoi(str);
            freeMemmorry(str);
		}

        isValidDate = IsValidDate(pDate);
        if(isValidDate == false)
            Notification("Thoi gian khong hop le!");
    }
}

#endif
