// Program ana giri� yeri

#include "stdafx.h"
#include <iostream>
#include "Fonksiyonlar.h"
#include "Menu.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");//Utf-8 karakter sorunu i�in
	Menu menu; //Men� nesnesinin olu�turulmas�
	menu.MenuListele(); // Men�y� �izecek olan fonksiyonun �a��r�lmas�
	
	system("pause");
	return 0;
}

