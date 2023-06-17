#ifndef __FLIGHT__CONTROLLERS__
#define __FLIGHT__CONTROLLERS__

#include "../../types/KeyValue.h"
#include "../../data/routers.h"
#include "../../utils/String.h"
#include "../../utils/Sort.h"
#include "../Date/controllers.h"
#include <string>
#include "models.h"

int xKeyDisplayFli[8] = {1, 19, 37, 55, 78, 96, 114, 130};
int xKeyDisplayPassFli[8] = {1, 10, 22, 40, 65, 78, 88, 130};

void InputFlight(PNodeFli &first, Flight &flight, ListAir listAir, bool Edit, bool Cancle);
void ShowFlight(Flight &fli, int position);
void ShowListFlightOnePage(PNodeFli first, int startIndex);
void ChangeFlightMenuManagerPage(PNodeFli first);
void MenuManageFlight(PNodeFli &first, ListAir listAir, TreePass rootPass);
void ListFlightDateAndDes(PNodeFli first, Date date, const char *arrival, int startIndex, bool ticketAvailable = false);
void ChangeListFlightDateAndDesPage(PNodeFli first, Date date, const char *arrival, bool ticketAvailable);
void MenuManageListTicket(ListAir &listAir, PNodeFli &listFlight, TreePass &rootPass);
void ShowAirplaneFly(PAirplane pAir, int position);
void ShowAirplaneFly(PAirplane pAir, int position);
void ShowListAirplaneFlyOnePage(ListAir list, int startIndex);
void ChangeAirplaneFlyMenuManagerPage(ListAir list);
void ListAirplaneFly(PNodeFli first, ListAir listAir);
int CountPassOfFlight(PNodeFli fli);
void ShowPassFli(Passenger &pass, Ticket &ticket, int position);
void ShowListPassFliOnePage(TreePass root, PNodeFli fli, int startIndex);
void ChangePassFliMenuManagerPage(TreePass root, PNodeFli fli);
void ListPassOfFlight(PNodeFli listFlight, TreePass rootPass);

// Nhap thong tin chuyen bay
void InputFlight(PNodeFli &first, Flight &flight, ListAir listAir, bool Edit = false, bool Cancle = false)
{
	ShowCursor(true);
	int ordinal = 0;   // thu tu nhap
	int position = -1; // vi tri chuyen bay
	char *str;
	if (Edit == false && Cancle == false)
		CreateForm(ContentFlight, 0, 4, 32);
	else CreateRow(X_Add, Y_Add, ContentFlight[0], 27);
	while (true)
	{
		switch (ordinal)
		{
		case 0:
		{ // Nhap idFlight
			do
			{
				Clean(X_Add + 10, Y_Add,X_Add + 22, Y_Add);
				gotoxy(X_Add + 10, Y_Add);
				str = Input(sizeof(flight.idFlight), ID);
				for(int i= 0; i < sizeof(flight.idFlight); i++){
					if(str[i] == ESC){
						Notification("Thoat thao tac!");
						RemoveForm(0, 4, 32);
						return;
					}
				}
				strcpy(flight.idFlight, str);
				freeMemmorry(str);
				position = FindIndexFlight(first, flight.idFlight);
				if (strlen(flight.idFlight) == 0)
				{
					Notification("Vui long khong bo trong");
				}
				else if (position > -1 && Edit == false && Cancle == false)
				{
					Notification("ID chuyen bay da ton tai");
				}
				else if (position < 0 && (Edit == true || Cancle == true))
				{
					Notification("ID chuyen bay khong ton tai");
				}
				else if (position > -1 && Edit == true)
				{
					PNodeFli p = FindFlight(first, flight.idFlight);
					Date tmp = p->data.date;
					if (p->data.status == CONVE || p->data.status == HETVE)
					{
						CreateRow(X_Add, Y_Add, ContentFlight[3], 32);
						gotoxy(X_Add + 13, Y_Add);
						InputDate(&p->data.date);
						RemoveRow(X_Add, Y_Add, ContentFlight[3], 44);
							if(!FindDate(first, p->data)) {
								Notification("Thoi gian khong hop le! Vui long nhap thoi gian cach 2 tieng");
								p->data.date = tmp;
								return;
							}
							else {
								Notification("Chinh sua thanh cong");
								return;
							}
					}
					else
					{
						Notification("Chuyen bay khong con hoat dong! Khong the hieu chinh ngay gio");
						RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
						return;
					}
				}
				else if (position > -1 && Cancle == true)
				{
					ShowCursor(false);
					PNodeFli p = FindFlight(first, flight.idFlight);
					if (p->data.status == HUYCHUYEN || p->data.status == HOANTAT)
					{
						Notification("Chuyen bay khong con hoat dong! Khong the huy chuyen");
					}
					else
					{
						Box(X_Notification, Y_Notification, 29, 3, "Ban co chac muon huy chuyen? ");
						gotoxy(X_Notification + 1, Y_Notification + 2);
						std::cout << "ESC: Khong - ENTER: Co";
						char c = _getch();
						RemoveRow(X_Add, Y_Add, ContentFlight[0], 27);
						RemoveBox(X_Notification, Y_Notification, 29, 3);

						if (c == ESC)
						{
							Notification("Huy that bai!");
							return;
						}
						if (c == ENTER)
						{
							if (CancleFlight(p))
							{
								Notification("Huy thanh cong!");
							}
						}
						return;
					}
				}
				else break;
			} while (true);

			ordinal++;
			break;
		}
		case 1:
		{ // Nhap arrivalAir
			gotoxy(X_Add + 11, Y_Add + 3);
			str = Input(sizeof(flight.arrivalAir), AutoCapitalText);
			for(int i= 0; i < sizeof(flight.arrivalAir); i++){
				if(str[i] == ESC){
					Notification("Thoat thao tac!");
					RemoveForm(0, 4, 32);
					return;
				}
			}
			strcpy(flight.arrivalAir, str);
			freeMemmorry(str);
			if (strlen(flight.arrivalAir) == 0)
			{
				Notification("Vui long khong bo trong");
				break;
			}
			ordinal++;
			break;
		}
		case 2:
		{ // Nhap idAir
			char signal;
			char strFind[SIZE_ID_AIRPLANE] = "";
			int cursize = 0;
			int index;
			RemoveTable(ContentFlight, 6);
			Clean(X_Add + 10, Y_Add + 6, X_Add + 10 + 4, Y_Add + 6);
			do
			{
				if (cursize == 0)
				{
					Display(xKeyDisplayAir, ContentAirplane, sizeof(ContentAirplane) / sizeof(std::string));
					ShowListAirplaneOnePage(listAir, 0);
				}
				index = 0;
				gotoxy(X_Add + 10 + cursize, Y_Add + 6);
				signal = getch();
				RemoveContent(xKeyDisplayAir, 5);
				if (signal == -32 || signal == 0 || signal == 224)
				{
					getch();
					continue;
				}
				if (ID(signal) && cursize < 1000 && signal != BACKSPACE)
				{
					strFind[cursize++] = signal;
					std::cout << signal;
				}
				if (
					(cursize == 1 && (Space(signal) || Dash(signal) || Underscore(signal))) ||
					(cursize > 1 && Space(signal) && Space(strFind[cursize - 2])) ||
					(cursize > 0 && signal == BACKSPACE))
				{
					std::cout << "\b \b";
					strFind[cursize--] = '\0';
				}
				for (int i = 0; i < listAir.size; i++)
				{
					if (index == 20)
						break;
					if (strstr(listAir.nodes[i]->idAir, strFind) != NULL)
					{
						ShowAirplane(listAir.nodes[i], index);
						index++;
					}
				}
			} while (
				(signal != ENTER) &&
				(signal != TAB));
			strcpy(flight.idAir, strFind);
			position = IndexAirplane(listAir, flight.idAir);
			if (strlen(flight.idAir) == 0)
			{
				Notification("Vui long khong bo trong");
				break;
			}
			if (position < 0)
			{
				Notification("ID may bay khong ton tai");
				break;
			}
			ordinal++;
			listAir.nodes[position]->amount++;
			RemoveTable(ContentAirplane,5);
			ChangeFlightMenuManagerPage(first);
			break;
		}
		case 3:
		{ // Nhap DateTime
			do
			{
				Clean(X_Add + 13, Y_Add + 9, X_Add + 24, Y_Add + 1);
				gotoxy(X_Add + 13, Y_Add + 9);
				InputDate(&flight.date);
				if (!FindDate(first, flight))
				{
					Notification("Thoi gian khong hop le! Vui long nhap thoi gian cach 2 tieng");
				}
				else
					break;
			} while (true);
			ordinal++;
			break;
		}
		case 4:
		{
			InitFlight(flight, listAir);
			ordinal++;
			break;
		}
		case 5:
		{
			if (Edit == false)
			{
				InsertListFlight(first, flight);
				Notification("Them thanh cong");
			}
			RemoveForm(0, 4, 32);
		}
			return;
		}
	}
	ShowCursor(false);
}

// Hien thi thong tin 1 chuyen bay
void ShowFlight(Flight &fli, int position)
{
	gotoxy(xKeyDisplayFli[0] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(10) << fli.idFlight;
	gotoxy(xKeyDisplayFli[1] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(12) << fli.arrivalAir;
	gotoxy(xKeyDisplayFli[2] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(10) << fli.idAir;
	gotoxy(xKeyDisplayFli[3] + 3, Y_Display + position + 3);
	PrintDate(&fli.date);
	gotoxy(xKeyDisplayFli[4] + 3, Y_Display + position + 3);
	std::cout << fli.listTicket.sizeBooked << "/" << std::left << std::setw(10) << fli.listTicket.sizeTotal;
	gotoxy(xKeyDisplayFli[5] + 3, Y_Display + position + 3);
	switch (fli.status)
	{
	case 0:
		std::cout << "Huy	  ";
		break;
	case 1:
		std::cout << "Con ve   ";
		break;
	case 2:
		std::cout << "Het ve   ";
		break;
	case 3:
		std::cout << "Hoan tat ";
		break;
	default:
		break;
	}
}

// Hien thi danh sach chuyen bay trong 1 trang
void ShowListFlightOnePage(PNodeFli first, int startIndex)
{
	gotoxy(3, 3);
	std::cout << " So luong chuyen bay : " << Size(first);

	if (first == NULL)
		return;

	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang
	int count = -1;
	AutoUpdateFlightStatus(first);
	RemoveContent(xKeyDisplayFli, 6);
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		count++;
		if (count == startIndex)
		{
			int i = -1;
			while (p != NULL && i < NumberPerPage - 1)
			{
				ShowFlight(p->data, ++i);
				p = p->pNext;
			}
			break;
		}
	}
	SetColor(curColor);
	gotoxy(3, 3);
	gotoxy(X_Page, Y_Page);
	std::cout << " Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach chuyen bay khi qua trang
void ChangeFlightMenuManagerPage(PNodeFli first)
{
	Display(xKeyDisplayFli, ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
	ShowListFlightOnePage(first, (CurPage - 1) * NumberPerPage);
}

// Quan ly chuyen bay
void MenuManageFlight(PNodeFli &first, ListAir listAir, TreePass rootPass)
{
	CurPage = 1;
	TotalPage = (int)ceil((double)Size(first) / NumberPerPage); // ceil : lam tron

	Display(xKeyDisplayFli, ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
	ShowListFlightOnePage(first, 0);

	gotoxy(X_TitlePage, Y_TitlePage);
	std::cout << "QUAN LY CHUYEN BAY";

	Flight fli;
	int signal;
	while (true)
	{
	menu:
		signal = MenuSelect(X_ThaoTac, Y_ThaoTac, 7, ContentFlightSelect);
		switch (signal)
		{
		case 1: // Them chuyen bay
		{
			if (CurPage == 0)
				CurPage = 1;
			InputFlight(first, fli, listAir);

			TotalPage = (int)ceil((double)Size(first) / NumberPerPage);
			ChangeFlightMenuManagerPage(first);
			ShowCursor(false);
			break;
		}
		case 2: // Chinh sua ngay thang nam
		{
			ShowCursor(true);
			if (first == NULL)
			{
				Notification("Danh sach rong");
				break;
			}
			InputFlight(first, fli, listAir, true, false);
			ShowListFlightOnePage(first, (CurPage - 1) * NumberPerPage);
			ShowCursor(false);
			break;
		}
		case 3: // Huy chuyen bay
		{
			ShowCursor(true);
			if (first == NULL)
			{
				Notification("Danh sach rong");
				break;
			}
			InputFlight(first, fli, listAir, false, true);
			ShowListFlightOnePage(first, (CurPage - 1) * NumberPerPage);
			ShowCursor(false);
			break;
		}
		case 4: // Danh sach hanh khach thuoc chuyen bay
		{
			ListPassOfFlight(first, rootPass);
			RemoveTable(ContentListPass,6);
			return;
		}
		case LEFT:
		case 5: // Chuyen trang truoc
		{
			if (CurPage == 1)
				break;
			else
			{
				CurPage--;
				ChangeFlightMenuManagerPage(first);
			}
			break;
		}
		case RIGHT:
		case 6: // Chuyen trang tiep
		{
			if (CurPage >= TotalPage)
				break;
			else
			{
				CurPage++;
				ChangeFlightMenuManagerPage(first);
			}
			break;
		}
		case 7:
		case -1:
			return;
		default:
			break;
		}
	}
}

// Xuat danh sach chuyen bay theo ngay va dia diem trong 1 trang
void ListFlightDateAndDes(PNodeFli first, Date date, const char *arrival, int startIndex, bool ticketAvailable)
{
	Display(xKeyDisplayFli, ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
	if (first == NULL)
		return;

	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang
	int count = -1;
	AutoUpdateFlightStatus(first);

	RemoveContent(xKeyDisplayFli, 6);
	for (PNodeFli p = first; p != NULL; p = p->pNext)
	{
		if (p->data.status == CONVE)
			count++;
		if (count == startIndex)
		{
			int i = -1;
			while (p != NULL && i < NumberPerPage - 1)
			{
				if (CheckDate(p, &date) && strcmp(p->data.arrivalAir, arrival) == 0 && p->data.status == CONVE && !ticketAvailable)
				{
					ShowFlight(p->data, ++i);
				}
				else if (p->data.status == CONVE && ticketAvailable)
				{
					ShowFlight(p->data, ++i);
				}
				p = p->pNext;
			}
			break;
		}
	}
	SetColor(curColor);
	gotoxy(3, 3);
	if (ticketAvailable)
		std::cout << " So luong chuyen bay : " << SizeTicketAvailable(first);
	else
		std::cout << " So luong chuyen bay : " << SizeDateDes(first, date, arrival);

	gotoxy(X_Page, Y_Page);
	std::cout << " Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach chuyen bay theo ngay va dia diem sang trang khac
void ChangeListFlightDateAndDesPage(PNodeFli first, Date date, const char *arrival, bool ticketAvailable)
{
	ListFlightDateAndDes(first, date, arrival, (CurPage - 1) * NumberPerPage, ticketAvailable);
}

// Quan ly danh sach ve
void MenuManageListTicket(ListAir &listAir, PNodeFli &listFlight, TreePass &rootPass)
{
	Flight flight;
	Airplane air;
	PNodeFli pFlight;
	Date date;
	bool ticketAvailable = true;
	int signal;

	CurPage = 1;
	TotalPage = (int)ceil((double)SizeTicketAvailable(listFlight) / NumberPerPage); // ceil : lam tron
	Display(xKeyDisplayFli, ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
	ListFlightDateAndDes(listFlight, date, flight.arrivalAir, 0, ticketAvailable);
	gotoxy(X_TitlePage - 4, Y_TitlePage);
	std::cout << "DANH SACH CAC CHUYEN BAY CON VE";

	if (listFlight == NULL)
	{
		Notification("Danh sach chua co chuyen bay nao!");
		return;
	}

	while (true)
	{
		signal = MenuSelect(X_ThaoTac, Y_ThaoTac, 5, ContentTicketSelect1);
		switch (signal)
		{
		case 1: // Chon chuyen bay muon dat
		{
			do
			{
				CreateRow(X_Add, Y_Add, ContentFlight[0], 32);
				gotoxy(X_Add + 10, Y_Add);

				char *str = Input(sizeof(flight.idFlight), ID);
				strcpy(flight.idFlight, str);
				freeMemmorry(str);

				pFlight = FindFlight(listFlight, flight.idFlight);
				if (pFlight == NULL)
					Notification("Chuyen bay khong ton tai");
				else if (pFlight->data.status == HETVE)
					Notification("Chuyen bay da het ve");
				else if (pFlight->data.status == HUYCHUYEN)
					Notification("Chuyen bay da bi huy");
				else if (pFlight->data.status == HOANTAT)
					Notification("Chuyen bay da hoan tat");
				else
					break;
			} while (true);

			RemoveRow(X_Add, Y_Add, ContentFlight[0], 32);
			RemoveTable(ContentFlight, sizeof(ContentFlight) / sizeof(std::string));

			// Luu vi tri may bay cua chuyen bay do
			int result = IndexAirplane(listAir, pFlight->data.idAir);
			air = *listAir.nodes[result];

			// Thuc hien thao tac voi danh sach ve
			gotoxy(X_TitlePage - 10, Y_TitlePage);
			std::cout << "MA CHUYEN BAY: " << pFlight->data.idFlight << " - DIA DIEM: " << pFlight->data.arrivalAir << " - THOI GiAN: ";
			PrintDate(&pFlight->data.date);
			MenuManageTicket(air, listFlight ,pFlight, rootPass);
			CurPage = 1;
			TotalPage = (int)ceil((double)SizeTicketAvailable(listFlight) / NumberPerPage); // ceil : lam tron
			ListFlightDateAndDes(listFlight, date, flight.arrivalAir, 0, ticketAvailable);
			break;
		}
		filter: case 2: // Loc chuyen bay theo ngay va dia diem
		{
			ShowCursor(true);
			CreateRow(X_Add, Y_Add, ContentFlight[1], 32);
			CreateRow(X_Add, Y_Add + 3, ContentFlight[3], 32);
			gotoxy(X_Add + 12, Y_Add);
			char *str = Input(sizeof(flight.arrivalAir), AutoCapitalText);
			strcpy(flight.arrivalAir, str);
			freeMemmorry(str);
			if(strlen(flight.arrivalAir) == 0){
				Notification("Vui long khong bo trong");
				goto filter;
			}

			gotoxy(X_Add + 14, Y_Add + 3);
			InputDate(&date, true);

			RemoveRow(X_Add, Y_Add, ContentFlight[1], 32);
			RemoveRow(X_Add, Y_Add + 3, ContentFlight[3], 46);

			RemoveTable(ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
			if(SizeDateDes(listFlight, date, flight.arrivalAir) == 0) CurPage = 0;
			else CurPage = 1;
			TotalPage = (int)ceil((double)SizeDateDes(listFlight, date, flight.arrivalAir) / NumberPerPage);
			ListFlightDateAndDes(listFlight, date, flight.arrivalAir, 0);
			ticketAvailable = true;
			break;
		}
		case LEFT:
		case 3: // Trang truoc
		{
			if (CurPage == 1)
				break;
			else
			{
				CurPage--;
				ChangeListFlightDateAndDesPage(listFlight, date, flight.arrivalAir, ticketAvailable);
				break;
			}
		}
		case RIGHT:
		case 4: // Trang sau
		{
			if (CurPage >= TotalPage)
				break;
			CurPage++;
			ChangeListFlightDateAndDesPage(listFlight, date, flight.arrivalAir, ticketAvailable);
			break;
		}
		case 5:
		case -1:
			return;
		default:
			break;
		}
	}
}

// Xuat thong tin 1 may bay
void ShowAirplaneFly(PAirplane pAir, int position)
{
	gotoxy(xKeyDisplay[0] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << pAir->idAir;
	gotoxy(xKeyDisplay[1] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(4) << pAir->amount;
}

// Xuat danh sach may bay trong 1 trang
void ShowListAirplaneFlyOnePage(ListAir list, int startIndex)
{
	gotoxy(3, 3);
	std::cout << " So luong may bay : " << list.size;
	int i;
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang

	RemoveContent(xKeyDisplay, 2);

	for (i = 0; i + startIndex < list.size && i < NumberPerPage; i++)
	{
		ShowAirplaneFly(list.nodes[i + startIndex], i);
	}
	SetColor(curColor);

	gotoxy(X_Page, Y_Page);
	std::cout << " Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach may bay qua trang khac
void ChangeAirplaneFlyMenuManagerPage(ListAir list)
{
	Display(xKeyDisplay, ContentListAir, sizeof(ContentListAir) / sizeof(std::string));
	ShowListAirplaneFlyOnePage(list, (CurPage - 1) * NumberPerPage);
}

// Thong ke so luot thuc hien chuyen bay cua may bay
void ListAirplaneFly(PNodeFli first, ListAir listAir)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE);
	PNodeFli p;
	ShowCursor(false);
	if(first == NULL){
		Notification("Danh sach rong");
		return;
	}
	CurPage = 1;
	TotalPage = (int)ceil((double)listAir.size / NumberPerPage);

	SetColor(curColor);
	Display(xKeyDisplayFli, ContentListAir, sizeof(ContentListAir) / sizeof(std::string));

	gotoxy(X_TitlePage, Y_TitlePage);
	std::cout << "DANH SACH THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA MAY BAY";
	Quicksort<PAirplane>(listAir.nodes, 0, listAir.size - 1, LessAmount);
	ShowListAirplaneFlyOnePage(listAir, 0);
	
	while (true)
	{
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			if (c == LEFT && CurPage != 1)
			{
				CurPage--;
				ChangeAirplaneFlyMenuManagerPage(listAir);
			}
			else if (c == RIGHT && CurPage < TotalPage)
			{
				CurPage++;
				ChangeAirplaneFlyMenuManagerPage(listAir);
			}
		}
		else if (c == ESC)
		{
			return;
		}
	}
}

// Xuat thong tin hanh khach theo chuyen bay
void ShowPassFli(Passenger &pass, Ticket &ticket, int position)
{
	gotoxy(xKeyDisplayPassFli[1] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << ticket.seat;
	gotoxy(xKeyDisplayPassFli[2] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(SIZE_ID_PASS) << pass.id;
	gotoxy(xKeyDisplayPassFli[3] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << pass.firstName;
	gotoxy(xKeyDisplayPassFli[4] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(8) << pass.lastName;
	gotoxy(xKeyDisplayPassFli[5] + 3, Y_Display + position + 3);
	std::cout << std::left << std::setw(5) << (pass.gender ? "Nu" : "Nam");
}

// Xuat danh sach hanh khach theo chuyen bay trong 1 trang
void ShowListPassFliOnePage(TreePass root, PNodeFli fli, int startIndex)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang
	int position = 0;
	int count = 0;
	RemoveContent(xKeyDisplayPassFli, 6);
	for (int i = 0; i < fli->data.listTicket.sizeTotal; i++)
	{
		if (fli->data.listTicket.DSV[i].statusTicket == 1 && position < NumberPerPage)
		{
			if (count < startIndex)
			{
				count++;
				continue;
			}
			PPassNode temp = SearchPass(root, fli->data.listTicket.DSV[i].idPas);
			gotoxy(xKeyDisplayPassFli[0] + 3, Y_Display + position + 3);
			std::cout << std::left << std::setw(5) << position + startIndex + 1;
			ShowPassFli(temp->data, fli->data.listTicket.DSV[i], position);
			++position;
		}
	}

	SetColor(curColor);
	gotoxy(3,3);
	std::cout << "So luong hanh khach: " << fli->data.listTicket.sizeBooked;
	gotoxy(X_Page, Y_Page);
	std::cout << " Trang " << CurPage << "/" << TotalPage;
}

// Thay doi danh sach hanh khach sang trang khac
void ChangePassFliMenuManagerPage(TreePass root, PNodeFli fli)
{
	Display(xKeyDisplayPassFli, ContentListPass, sizeof(ContentListPass) / sizeof(std::string));
	ShowListPassFliOnePage(root, fli, (CurPage - 1) * NumberPerPage);
}

// Danh sach hanh khach thuoc chuyen bay X
void ListPassOfFlight(PNodeFli listFlight, TreePass rootPass)
{
	WORD curColor;
	GetColor(curColor);
	SetColor(WHITE); // cac phan tu hien trong bang se co chu mau trang
	ShowCursor(true);

	Flight flight;
	PNodeFli pFlight;
	
	do
	{
		CreateRow(X_Add, Y_Add, ContentFlight[0], 32);
		gotoxy(X_Add + 10, Y_Add);
		strcpy(flight.idFlight, Input(sizeof(flight.idFlight), ID));
		pFlight = FindFlight(listFlight, flight.idFlight);
		if (pFlight == NULL)
			Notification("Chuyen bay khong ton tai");
		else if (pFlight->data.status == HETVE)
			Notification("Chuyen bay da het ve");
		else if (pFlight->data.status == HUYCHUYEN)
			Notification("Chuyen bay da bi huy");
		else if (pFlight->data.status == HOANTAT)
			Notification("Chuyen bay da hoan tat");
		else
			break;
	} while (true);

	RemoveRow(X_Add, Y_Add, ContentFlight[0], 46);
	RemoveTable(ContentFlight, sizeof(ContentFlight) / sizeof(std::string));
	if(pFlight->data.listTicket.sizeBooked == 0) CurPage = 0;
	else CurPage = 1;
	TotalPage = (int)ceil((double)pFlight->data.listTicket.sizeBooked/NumberPerPage); 	//ceil : lam tron 
	SetColor(curColor);
	gotoxy(X_TitlePage - 10, Y_TitlePage);
	std::cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << pFlight->data.idFlight;
	gotoxy(X_TitlePage - 20, Y_TitlePage + 1);
	std::cout << "Ngay gio khoi hanh: ";
	PrintDate(&pFlight->data.date);
	gotoxy(X_TitlePage + 25, Y_TitlePage + 1);
	std::cout << "Noi den: " << pFlight->data.arrivalAir;
	Display(xKeyDisplayPassFli, ContentListPass, sizeof(ContentListPass) / sizeof(std::string));
	ShowListPassFliOnePage(rootPass, pFlight, 0);
	ShowCursor(false);
	while (true)
	{
		char c = _getch();
		if (c == -32)
		{
			c = _getch();
			if (c == LEFT && CurPage > 1)
			{
				CurPage--;
				ChangePassFliMenuManagerPage(rootPass, pFlight);
			}
			else if (c == RIGHT && CurPage < TotalPage)
			{
				CurPage++;
				ChangePassFliMenuManagerPage(rootPass, pFlight);
			}
		}
		else if (c == ESC)
		{
			return;
		}
	}
}

#endif
