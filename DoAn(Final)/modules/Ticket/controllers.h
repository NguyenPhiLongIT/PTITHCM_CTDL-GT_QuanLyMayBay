#ifndef __TICKET__CONTROLLERS__
#define __TICKET__CONTROLLERS__

#include <cmath>
#include "models.h"
#include "../Passenger/controllers.h"
#include "../Flight/models.h"
#include "../../types/KeyValue.h"

int xKeyDisplayTicket[4] = {1, 13, 25, 43};

void ShowTicket(Ticket ticket, int position);
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket = false);
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket);
void MenuManageTicket(Airplane air, PNodeFli listFli, PNodeFli fli, TreePass &rootPass, bool emptyTicket = false);

// Nhap thong tin ve
void InputTicket(Ticket &ticket) {
    int ordinal = 0;	// thu tu nhap	
	int position = -1;	// vi tri ve
	char *str;
	CreateForm(ContentTicketInput,0,2,27);
	while(true){
		ShowCursor(true);
		switch(ordinal){
			case 0:{	//nhap CMND
				gotoxy(X_Add+12,Y_Add); 
				str = Input(SIZE_ID_PASS, Number); ticket.idPas = atoi(str);
				freeMemmorry(str);
				if(ticket.idPas < 1) {
					Notification("Vui long khong bo trong");
					break;
				}
				ordinal++;
				break;
			}
			case 1:{	//nhap so cho ngoi
				gotoxy(X_Add+12,Y_Add+3); 
				str = Input(sizeof(ticket.seat), ID); strcpy(ticket.seat, str);
				freeMemmorry(str);
				if(strlen(ticket.seat) == 0){
					Notification("Vui long khong bo trong");
					break;
				}
				return;
			}
		}	
	}
}

// Xuat thong tin 1 ve
void ShowTicket(Ticket ticket, int position)
{
	gotoxy(xKeyDisplayTicket[0] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << ticket.seat;
	gotoxy(xKeyDisplayTicket[1] + 3, Y_Display + position + 3);
	if (ticket.statusTicket == 1)
		std::cout << std::left << std::setw(3) << "Da dat";
	else if (ticket.statusTicket == 0)
		std::cout << std::left << std::setw(3) << "Con ve";
	else
		std::cout << std::left << std::setw(3) << "Da huy";
	gotoxy(xKeyDisplayTicket[2] + 3, Y_Display + position + 3);
	if(ticket.idPas > -1){
		char id_str[SIZE_ID_PASS];
		sprintf(id_str, "%.9d", ticket.idPas);
		std::cout << std::left << std::setw(8) << id_str;
	}
    else std::cout << std::left << std::setw(8) << "";
}

// Xuat thong tin danh sach ve trong 1 trang
void ShowListTicketOnePage(ListTicket listTicket, int startIndex, bool emptyTicket)
{

	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang

	RemoveContent(xKeyDisplayTicket, 3);
	gotoxy(3,3); std::cout << "             ";

	if (!emptyTicket)
	{
		gotoxy(3, 3);
		std::cout << "Ve: " << listTicket.sizeBooked << "/" << listTicket.sizeTotal;
		for (int i = startIndex; i < listTicket.sizeTotal && i < startIndex + NumberPerPage; i++)
			ShowTicket(listTicket.DSV[i], i - startIndex);
	}
	else
	{
		gotoxy(3, 3);
		std::cout << "Ve trong: " << listTicket.sizeTotal - listTicket.sizeBooked;
		int position = 0;
		int count = 0;
		for (int i = 0; i < listTicket.sizeTotal && position < NumberPerPage; i++)
		{
			if (listTicket.DSV[i].statusTicket == 0)
			{
				if (count < startIndex)
				{
					++count;
					continue;
				}
				ShowTicket(listTicket.DSV[i], position++);
			}
		}
	}

	SetColor(curColor);

	gotoxy(X_Page, Y_Page);
	std::cout << "Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach ve thanh trang khac
void ChangeTicketMenuManagerPage(ListTicket listTicket, bool emptyTicket)
{
	Display(xKeyDisplayTicket, ContentTicketOutput, sizeof(ContentTicketOutput) / sizeof(std::string));
	ShowListTicketOnePage(listTicket, (CurPage - 1) * NumberPerPage, emptyTicket);
}

void MenuManageTicket(Airplane air, PNodeFli listFli, PNodeFli fli, TreePass &rootPass, bool emptyTicket)
{
	ShowCursor(false);
	CurPage = 1;

	gotoxy(20, 3);
	if (!emptyTicket)
	{
		std::cout << "_DANH SACH VE_";
		TotalPage = (int)ceil((double)fli->data.listTicket.sizeTotal / NumberPerPage); // ceil : lam tron
	}
	else
	{
		std::cout << "_DANH SACH CAC VE CON TRONG_";
		TotalPage = (int)ceil((double)(fli->data.listTicket.sizeTotal - fli->data.listTicket.sizeBooked) / NumberPerPage); // ceil : lam tron
	}
	Display(xKeyDisplayTicket, ContentTicketOutput, sizeof(ContentTicketOutput) / sizeof(std::string));
	ShowListTicketOnePage(fli->data.listTicket, 0);

	Ticket ticket_tmp;
	Passenger pass_tmp;
	int signal;

	while (true)
	{
		signal = MenuSelect(X_ThaoTac, Y_ThaoTac, 6, ContentTicketSelect2);
		switch (signal)
		{
		case 1: // Dat ve
		{
			if (ListTicketIsFull(fli->data.listTicket))
			{
				Notification("Da het ve");
				break;
			}
			InputTicket(ticket_tmp);
			RemoveForm(0, 4, 27);
			int vitri = ConvertMSVtoNumber(ticket_tmp.seat, air.col);

			if (fli->data.listTicket.DSV[vitri].statusTicket == VEHUY)
			{ // ve huy
				Notification("Ve da huy. Khong the dat!");
				break;
			}

			if (CheckSeat(air, fli->data.listTicket, ticket_tmp) == -1)
			{ // khong ton tai
				Notification("Vi tri nay khong ton tai");
				break;
			}
			else if (CheckSeat(air, fli->data.listTicket, ticket_tmp) == 0)
			{ // da dat
				Notification("Vi tri nay da co nguoi dat");
				break;
			}
			else
			{ // ve trong
				if (CheckCMND(fli->data.listTicket, ticket_tmp))
				{
					Notification("Ban da dat ve tren chuyen bay nay");
				}
				else
				{	PPassNode tmp = SearchPass(rootPass, ticket_tmp.idPas);
					if (tmp == NULL)	
					{
						pass_tmp.id = ticket_tmp.idPas;
						InputPass(rootPass, pass_tmp, false,true);
					}
					else {
						ShowCursor(false);
						CreateForm(ContentPass,0,4,27);
						char id_str[SIZE_ID_PASS];
						sprintf(id_str, "%.9d", tmp->data.id);
						gotoxy(X_Add+15,Y_Add);
						std::cout << id_str;
						gotoxy(X_Add+15,Y_Add + 3);
						std::cout << tmp->data.firstName;
						gotoxy(X_Add+15,Y_Add+6);
						std::cout << tmp->data.lastName;
						gotoxy(X_Add+15,Y_Add+9);
						std::cout << (tmp->data.gender ? "Nu" : "Nam");
						_getch();
						RemoveForm(0,4,27);
					}
					if(!checkCMNDInFli(listFli, fli, ticket_tmp.idPas)){
						Notification("Vui long chon chuyen bay cach nhau 12 tieng");
						break;
					}
					InsertListTicket(air, fli->data.listTicket, ticket_tmp);
					Notification("Them thanh cong");
				}
			}
			ShowListTicketOnePage(fli->data.listTicket, (CurPage - 1) * NumberPerPage);
			ShowCursor(false);
			break;
		}
		case 2: // Huy ve
		{
			if (ListTicketIsNull(fli->data.listTicket))
			{
				Notification("Danh sach ve rong");
				break;
			}
			InputTicket(ticket_tmp);
			RemoveForm(0, 4, 27);
			if (CheckSeat(air, fli->data.listTicket, ticket_tmp) == -1)
			{
				Notification("Vi tri nay khong ton tai");
				break;
			}
			else if (CheckSeat(air, fli->data.listTicket, ticket_tmp) == 1)
			{
				Notification("Vi tri nay chua duoc dat");
				break;
			}
			else
			{
				CancelTicket(air, fli->data.listTicket, ticket_tmp);
				Notification("Huy ve thanh cong");
			}
			ShowListTicketOnePage(fli->data.listTicket, (CurPage - 1) / NumberPerPage);
			break;
		}
		case 3: // Chuyen che do xem full ve va cac ve con trong
		{
			int signal = MenuSelect(X_ThaoTac + 16, Y_ThaoTac + 3, 2, ContentTicketEmpty);
			if (signal == 1)
			{
				emptyTicket = false;
				Clean(20, 3, 20+38, 3);
				gotoxy(20, 3);
				std::cout << "_DANH SACH VE_";
				ChangeTicketMenuManagerPage(fli->data.listTicket, emptyTicket);
			}
			else
			{
				emptyTicket = true;
				Clean(20, 3, 20+40, 3);
				gotoxy(20, 3);
				std::cout << "_DANH SACH CAC VE CON TRONG_";
				ChangeTicketMenuManagerPage(fli->data.listTicket, emptyTicket);
			}
			Clean(X_ThaoTac+16,Y_ThaoTac+3,X_ThaoTac+16+20,Y_ThaoTac+3+5);
		}
		case LEFT:
		case 4: // Trang truoc
		{
			if (CurPage == 1)
				break;
			CurPage--;
			ChangeTicketMenuManagerPage(fli->data.listTicket, emptyTicket);
			break;
		}
		case RIGHT:
		case 5: // Trang sau
		{
			if (CurPage >= TotalPage)
				break;
			CurPage++;
			ChangeTicketMenuManagerPage(fli->data.listTicket, emptyTicket);
			break;
		}
		case 6:
		case -1:{
			Clean(X_ThaoTac, Y_ThaoTac,X_ThaoTac+12, Y_ThaoTac+14);
			RemoveTable(ContentTicketOutput,3);
			return;
		}
		default:
			break;
		}
	}
}

#endif
