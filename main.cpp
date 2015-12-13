#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <string.h> 
#include <conio.h> 
#include "ХешТаблица.h"
#include <locale.h>

int _NUMBER_OF_ELEMENTS = 100;
FILE *f = fopen("input.txt", "r");

/*------------------------------------------------------------------------------------------------------------------------------------
	4,8,6,5,7,9 - Управление фигурой
	E - Вывод всех фигур в списке
	R - Выбор фигуры в списке для контроля над ней
	--------------------------------------------------------------------------------------------------------------------------------------*/

int hash(int key)
{
	return (_NUMBER_OF_ELEMENTS / (key + 1));
}

template <class Ta>
void addInTable(table<Ta> *T, int indentificator, HWND consol, HDC hdc, RECT rt1)
{
	  
	if (!T->A[hash(indentificator)].empty)
	{
		T->A[hash(indentificator)].head = new table<Ta>::list;
		T->A[hash(indentificator)].head->trap = new Ta(f, rt1, hdc, consol);
		T->A[hash(indentificator)].helpHead = T->A[hash(indentificator)].head;
		T->A[hash(indentificator)].helpHead->next = NULL;
		T->A[hash(indentificator)].empty = true;
		T->A[hash(indentificator)].kolvo++;
	}
	else
	{
		T->A[hash(indentificator)].helpHead->next = new table<Ta>::list;
		T->A[hash(indentificator)].helpHead = T->A[hash(indentificator)].helpHead->next;
		T->A[hash(indentificator)].helpHead->trap = new Ta(f, rt1, hdc, consol);
		T->A[hash(indentificator)].helpHead->next = NULL;
		T->A[hash(indentificator)].kolvo++;
	}

}

template <class TRAPEZE>
table<TRAPEZE>::list *choosedFiguraInlist(table<TRAPEZE> *T, int nomerVspiske, int ind)
{
	T->A[hash(ind)].helpHead = T->A[hash(ind)].head;

	for (int i = 1; i < nomerVspiske; i++)
	{
		if (T->A[hash(ind)].helpHead->next != NULL)
			T->A[hash(ind)].helpHead = T->A[hash(ind)].helpHead->next;
	}
	return T->A[hash(ind)].helpHead;
}

template <class TRAPEZE>
table<TRAPEZE>::list *DelFiguraFromSpisok(table<TRAPEZE> *T, int nomerVspiske, int ind)//Фиктивное звено
{
	table<D>::list *x = choosedFiguraInlist(T, nomerVspiske, ind);
	    if(T->A[hash(ind)].empty != false)
        {
		T->A[hash(ind)].helpHead = T->A[hash(ind)].head;
		while (T->A[hash(ind)].helpHead->next != x)
		{
			T->A[hash(ind)].helpHead = T->A[hash(ind)].helpHead->next;
		}
		T->A[hash(ind)].helpHead->next = T->A[hash(ind)].helpHead->next->next;
		delete x;
		T->A[hash(ind)].kolvo--;
	    return T->A[hash(ind)].head;
        }
}

template <class T>
void Interface(char j, T *T, int *ind, int *chooseFigura)
{
	switch (j)
	{
	case 'E':                  //Выбор фигуры в списке
		printf_s("\nВведите номер фигуры в списке для контроля над ней__");
		scanf_s("%d", chooseFigura);
		T->A[hash(*ind)].helpHead = choosedFiguraInlist(T, *chooseFigura, *ind);
		break;
	 case 'D':   
		 int d;//Выбор фигуры в списке
		printf_s("\nВведите номер фигуры в списке для контроля над ней__");
		scanf_s("%d", &d);
		T->A[hash(*ind)].helpHead = DelFiguraFromSpisok(T, d, *ind);
		printf_s("Количество элементов в таблице %d", T->A[hash(*ind)].kolvo);
		break;
	}
	T->A[hash(*ind)].helpHead = choosedFiguraInlist(T, *chooseFigura, *ind);
	T->A[hash(*ind)].helpHead->trap->move(j);
}

void main()
{
	setlocale(LC_CTYPE, "Russian");
	HWND consol = GetConsoleWindow();
	HDC hdc = GetDC(consol);
	RECT rt1;
	HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(60, 200, 160));
	HPEN hOldPen = SelectPen(hdc, hRedPen);
	SetBkColor(hdc, RGB(255, 255, 255));
	SetTextColor(hdc, RGB(0, 0, 0));
	GetClientRect(consol, &rt1);
	printf_s("Что бы закрыть инструкцию нажмите любую клавишу");
	printf_s("\n 4,8,6,5,7,9 - Управление фигурой");
	printf_s("\n e + Shift - Вывод всех фигур в списке ");
	printf_s("\n r + Shift - Выбор фигуры в списке для контроля над ней");
	_getch();
	system("cls");
	table<trapeze> *T = new table<trapeze>; 
	T->A = new table<trapeze>::block[10];

	int ind = 0;
	while (ind != -1)
	{
		printf_s("Введите числовой индентификатор фигуры 0 - 99\n");
		scanf_s("%d", &ind);
		if (ind != -1)
			addInTable(T, ind, consol, hdc, rt1);
	}
	system("cls");
	//Выбор ветки, которую отрисовываем
	printf_s("\n Введите номер списка");
	scanf_s("%d", &ind);
	if (!T->A[hash(ind)].empty)
	{
		printf_s("Ошибка, этот список пуст");
	}
	else
	{
		system("cls");
		printf_s("\n Количество элементов в выбранном списке : %d", T->A[hash(ind)].kolvo);
		int choosedFigura;
		T->A[hash(ind)].helpHead = T->A[hash(ind)].head;

		if (T->A[hash(ind)].head->trap->Check())
			do{
			T->A[hash(ind)].helpHead = T->A[hash(ind)].head;
			T->A[hash(ind)].head->trap->clear();
			T->A[hash(ind)].helpHead->trap->Draw();
			while (T->A[hash(ind)].helpHead != NULL)
			{
				T->A[hash(ind)].helpHead->trap->Draw();
				T->A[hash(ind)].helpHead = T->A[hash(ind)].helpHead->next;
			}
			Interface(_getch(), T, &ind, &choosedFigura);
			T->A[hash(ind)].helpHead = T->A[hash(ind)].head;

			} while (_getch() != VK_ESCAPE);

		else
			printf_s("Error");
	}
	SelectPen(hdc, hOldPen);
	DeletePen(hRedPen);
	ReleaseDC(consol, hdc);

	_getch();
}
