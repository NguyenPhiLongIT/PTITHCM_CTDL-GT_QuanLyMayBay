#ifndef __DATA__
#define __DATA__

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstring>

#include "../modules/Airplane/models.h"
#include "../modules/Flight/models.h"
#include "../modules/Date/models.h"
#include "../modules/Passenger/models.h"
#include "../utils/Stack_Queue.h"

//Load file danh sach may bay
bool LoadAirplane(ListAir &listAir)
{
    std::ifstream filein("./data/DSMB.TXT", std::ios_base::in);
    char str[1000];
    PAirplane pAir;

    if (!filein.is_open())
        return false;

    filein.getline(str, sizeof(str));
    listAir.size = atoi(str);
    for(int i = 0; i < listAir.size; i++)
    {
        pAir = new Airplane;
        filein.getline(pAir->idAir, sizeof(pAir->idAir), ';');
        filein.getline(pAir->typeAir, sizeof(pAir->typeAir), ';');
        filein.getline(str, sizeof(str), ';');
        pAir->col = atoi(str);
        filein.getline(str, sizeof(str), ';');
        pAir->row = atoi(str);
        filein.getline(str, sizeof(str));
        pAir->amount = atoi(str);

        listAir.nodes[i] = pAir;
    }
    
    filein.close();
    return true;
}

//Luu file danh sach may bay
bool SaveAirplane(ListAir &listAir)
{
    std::ofstream file("./data/DSMB.TXT", std::ios_base::out);

    if (!file.is_open())
        return false;

    file << listAir.size << std::endl;
    for (int i = 0; i < listAir.size; i++)
    {
        file << listAir.nodes[i]->idAir << ";"
             << listAir.nodes[i]->typeAir << ";"
             << listAir.nodes[i]->col << ";"
             << listAir.nodes[i]->row << ";"
			 << listAir.nodes[i]->amount << std::endl;
    }
    file.close();
    return true;
}

//Load file danh sach chuyen bay
bool LoadFlight(PNodeFli &First)
{
    std::ifstream file("./data/DSCB.TXT", std::ios_base::in);
    std::string str;
    PNodeFli pNodeFli = NULL;

    if (!file.is_open())
        return false;
	
	while(!file.eof())
    {
        pNodeFli = new NodeFli;
        std::getline(file, str, ';');	strcpy(pNodeFli->data.idFlight, str.c_str());
        if(strcmp(pNodeFli->data.idFlight, "") == 0)
        	continue;
        std::getline(file, str, ';');	strcpy(pNodeFli->data.arrivalAir, str.c_str());
        std::getline(file, str, ';');	strcpy(pNodeFli->data.idAir, str.c_str());
        
        std::getline(file, str, ':');	pNodeFli->data.date.hour = atoi(str.c_str());
		std::getline(file, str, ';');    pNodeFli->data.date.minute = atoi(str.c_str());
        
        std::getline(file, str, '/');    pNodeFli->data.date.day = atoi(str.c_str());
        std::getline(file, str, '/');    pNodeFli->data.date.month = atoi(str.c_str());
        std::getline(file, str, ';');    pNodeFli->data.date.year = atoi(str.c_str());
        std::getline(file, str, ';');	pNodeFli->data.status = atoi(str.c_str());

        std::getline(file, str, ';');	pNodeFli->data.listTicket.sizeTotal = atoi(str.c_str());
        std::getline(file, str, ';');    pNodeFli->data.listTicket.sizeBooked = atoi(str.c_str());
       	
       	pNodeFli->data.listTicket.DSV = new Ticket[pNodeFli->data.listTicket.sizeTotal];
        for (int i = 0; i < pNodeFli->data.listTicket.sizeTotal; i++)
        {
            std::getline(file, str, ';');	pNodeFli->data.listTicket.DSV[i].idPas = atoi(str.c_str());
            std::getline(file, str, ';');	strcpy(pNodeFli->data.listTicket.DSV[i].seat, str.c_str());
            if(i != pNodeFli->data.listTicket.sizeTotal-1){
            	std::getline(file, str, ';');
			}else{
				std::getline(file, str);
			}
            pNodeFli->data.listTicket.DSV[i].statusTicket = atoi(str.c_str());
        }
        InsertListFlight(First, pNodeFli->data);
    }
    file.close();
    return true;
}

//Luu file danh sach chuyen bay
bool SaveFlight(PNodeFli First)
{
    std::ofstream file("./data/DSCB.TXT", std::ios_base::out);

    if (!file.is_open())
        return false;

    while (First != NULL)
    {
        file << First->data.idFlight << ";"
             << First->data.arrivalAir << ";"
             << First->data.idAir << ";"
             << First->data.date.hour << ":"
             << First->data.date.minute << ";"
             << First->data.date.day << "/"
             << First->data.date.month << "/"
             << First->data.date.year << ";"
             << First->data.status << ";"
             << First->data.listTicket.sizeTotal << ";"
             << First->data.listTicket.sizeBooked << ";";
        
        for (int i = 0; i < First->data.listTicket.sizeTotal; i++)
        {
            file << First->data.listTicket.DSV[i].idPas << ";"
                 << First->data.listTicket.DSV[i].seat << ";"
                 << First->data.listTicket.DSV[i].statusTicket;
            if (i == First->data.listTicket.sizeTotal - 1 && First->pNext != NULL)
            {
                file << std::endl;
            }
            else
            {
                file << ";";
            }
        }
        First = First->pNext;
    }

    file.close();
    return true;
}

//Load file danh sach hanh khach
bool LoadTreePass(TreePass &root)
{
	std::ifstream file("./data/DSHK.TXT", std::ios_base::in);
	std::string str;
	Passenger pass;

	if(!file.is_open())
		return false;
	
	while(std::getline(file, str))
	{
		std::stringstream ss(str);

		std::getline(ss, str, ';');	
		if(strlen(str.c_str()) == 0)
			continue;
		pass.id = atoi(str.c_str());
		std::getline(ss, str, ';');	strcpy(pass.firstName, str.c_str());
		std::getline(ss, str, ';');	strcpy(pass.lastName, str.c_str());
		std::getline(ss, str, ';');	pass.gender = atoi(str.c_str());
		InsertPass(root, pass);
	}

	file.close();
	return true;
}

//Luu file danh sach hanh khach
bool SaveTreePass(TreePass root)
{
	std::ofstream file("./data/DSHK.TXT", std::ios_base::out);

	if(!file.is_open())
		return false;
	
	PPassenger temp;
	PPassNode node;
	Queue<Passenger> queue;
	InitQueue(queue);
	pushQueue(queue, root->data);

	while (!emptyQueue(queue))
	{
		temp = frontQueue(queue);
		popQueue(queue);
		
		file << temp->id << ";"
			 << temp->firstName << ";"
			 << temp->lastName << ";"	
			 << temp->gender << std::endl;
		node = (PPassNode)(temp);
		if(node->pLeft != NULL){
			pushQueue(queue, node->pLeft->data);
		}
		if(node->pRight != NULL){
			pushQueue(queue, node->pRight->data);
		}
	}
	

	file.close();
	return true;
}

#endif