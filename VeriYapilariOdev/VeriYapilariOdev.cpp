// Program ana giriþ yeri

#include "stdafx.h"
#include <iostream>
#include "Fonksiyonlar.h"
#include "Menu.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");//Utf-8 karakter sorunu için
	Menu menu; //Menü nesnesinin oluþturulmasý
	menu.MenuListele(); // Menüyü çizecek olan fonksiyonun çaðýrýlmasý
	
	system("pause");
	return 0;
}

