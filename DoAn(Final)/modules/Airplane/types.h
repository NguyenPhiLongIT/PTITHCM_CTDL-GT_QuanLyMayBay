#ifndef __AIRPLANE__TYPES__
#define __AIRPLANE__TYPES__

#include "../../types/KeyValue.h"

typedef struct _Airplane{
    char idAir[SIZE_ID_AIRPLANE];
    char typeAir[40];
    int col; // so day
    int row; // so hang
    int amount; //so luong chuyen bay cua may bay
}Airplane, *PAirplane;

typedef struct _ListAir{
    int size;
    Airplane *nodes[MAXAIRPLANE];
}ListAir, *PListAir;

#endif
