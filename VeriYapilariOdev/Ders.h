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
	int yil; // dersin kaçýncý sýnýfa ait olduðu
public:
	friend class Fonksiyonlar;
	Ders(string ad, string kod, int yil, string _dosyaYolu);
	~Ders();
	Yigin* YiginOlustur(); //Orjinal yýðýna dokunmadan pointerýný dönderiyoruz
	AVLAgaci* AgacOlustur();
	vector<Ogrenci*> OgrenciAl();
};



