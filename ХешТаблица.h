#define _USE_MATH_DEFINES 
#include <windows.h> 
#include <windowsx.h> 
#include <stdio.h> 
#include <conio.h> 
#include <math.h> 
#include <string.h>
#include <iostream>

#include "Фигура.h"



template <class figura>
class table
{
public:
class list
{
public:
	figura *trap;
	list *next;
};
class block
{
public:
	list *head,*helpHead;
	bool empty;
    int kolvo;
	block()
	{
		empty = false;
        kolvo = 0;
	}
};
 	block *A;
	int n;
};
