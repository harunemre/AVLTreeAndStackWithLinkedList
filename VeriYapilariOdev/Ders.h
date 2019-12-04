#pragma once
#include "AVLAgaci.h"
#include "Yigin.h"
#include <vector>
#include <fstream>
#include <sstream>
class Ders
{
	string dersAdi;
	string dersKodu;
	string dosyaYolu;
	int yil; // dersin ka��nc� s�n�fa ait oldu�u
public:
	friend class Fonksiyonlar;
	Ders(string ad, string kod, int yil, string _dosyaYolu);
	~Ders();
	Yigin* YiginOlustur(); //Orjinal y���na dokunmadan pointer�n� d�nderiyoruz
	AVLAgaci* AgacOlustur();
	vector<Ogrenci*> OgrenciAl();
};



