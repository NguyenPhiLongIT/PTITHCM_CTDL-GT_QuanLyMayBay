#include <fstream>
#include <cstring>
#include <sstream>
#include "./utils/Mylibrary.h"
#include "./types/KeyValue.h"

void Introduction()
{
	WORD cur;
	GetColor(cur);
	ShowCursor(false);
	SetColor(BLUE_LIGHT);
	std::string temp;
	std::ifstream filein("Introduction.TXT", std::ios_base::in);
	int y = 0;
	if (filein.good())
	{
		while ( filein.eof() == false )
		{
			std::getline(filein,temp);
			gotoxy(45,y++);
			std::cout << temp;
		}
	}
	SetColor(cur);
	return;
}
