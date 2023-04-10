#pragma once
#include <fstream>
#include <string>


using namespace std;

#include "Airplane.h"
#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"





bool LoadPass(TreePass &treePass)
{
    ofstream file("DSHK.TXT", ios_base::out);

    if (!file.is_open())
        return false;

    file.close();
    return true;
}

bool SavePass(TreePass treePass)
{
    ofstream file("DSHK.TXT", ios_base::out);

    if (!file.is_open())
        return false;

    file.close();
    return true;
}
