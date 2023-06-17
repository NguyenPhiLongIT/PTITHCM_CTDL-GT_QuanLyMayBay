#ifndef __TICKET__TYPES__
#define __TICKET__TYPES__


#include "../../types/KeyValue.h"

typedef struct _Ticket {
	int idPas;
    char seat[5];
    int statusTicket; // 0: ve trong, 1: ve da duoc dat, 2: ve da huy
} Ticket, PTicket;

typedef struct _ListTicket {
    int sizeBooked; //so luong ve da dat
    int sizeTotal; // tong so luong ve cua 1 may bay
    Ticket *DSV;
} ListTicket, PListTicket;

#endif
