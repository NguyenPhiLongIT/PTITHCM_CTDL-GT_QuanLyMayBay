#pragma once
#include <iostream>
#include <string.h>
#include <conio.h>
#include "KeyValue.h"
#include "Mylibrary.h"

bool Space(char &);
bool Underscore(char &);
bool Dash(char &);
bool Number(char &);
bool NormalText(char &);
bool CapitalText(char &);
bool Text(char &);
bool All(char &);
bool ID(char &);
bool Special(char &);
char *Input(int, bool (*)(char &));

bool Space(char &res)
{
    return res == ' ';
}

bool Underscore(char &res)
{
    return res == '_';
}

bool Dash(char &res)
{
    return res == '-';
}

bool Number(char &res)
{
    return '0' <= res && res <= '9';
}

bool NormalText(char &res)
{
    return 'a' <= res && res <= 'z';
}

bool CapitalText(char &res)
{
    return 'A' <= res && res <= 'Z';
}

bool Text(char &res)
{
    return CapitalText(res) ||
           NormalText(res) ||
           Space(res);
}

bool AutoCapitalText(char &res)
{	
    if (NormalText(res))
    {
        res -= 32;
    }
    return CapitalText(res);
}

bool All(char &res)
{
    return 1;
}

bool ID(char &res)
{
    if (NormalText(res))
    {
        res -= 32;
    }
    return CapitalText(res) ||
           Number(res) ||
           Dash(res) ||
           Underscore(res);
}

bool Special(char &res)
{
    return !(Number(res) && Text(res));
}

bool Gender(char &res)
{
    return 
        res == '0'||
        res == '1';
}

char *Input(int size, bool (*constraint)(char &) = All)
{
    char *res = new char[size];
    char signal;
    int cursize = 0;
    do
    {
        signal = getch();
        // Xu li nhan phim mui ten
        if (signal == -32 || signal == 0 || signal == 224)
        {
            getch();
            continue;
        }

        if (constraint(signal) && cursize < size && signal != BACKSPACE)
        {
            res[cursize++] = signal;
            std::cout << signal;
        }
        if (
            (cursize == 1 && (Space(signal) || Dash(signal) || Underscore(signal))) ||
            (cursize > 1 && Space(signal) && Space(res[cursize - 2])) ||
            (cursize > 0 && signal == BACKSPACE))
        {
            std::cout << "\b \b";
            res[cursize--] = '\0';
        }
    } while (
        (signal != ENTER) &&
        (signal != TAB)
    );

    res[cursize] = '\0';
    return res;
}
