#include "stdafx.h"
#include "Ogrenci.h"

Ogrenci::Ogrenci() {}

// ��renci bilgilerini al�p ��renci nesnesini olu�turan Constructor
Ogrenci::Ogrenci(string adi, string soyadi, int no, int sinifi, string yandali)
{
	ad = adi;
	soyad = soyadi;
	ogrNo = no;
	sinif = sinifi;
	bolum = BolumTespit(no);
	yandal = yandali;
}

Ogrenci::~Ogrenci(){}

// �grencinin bilgilerini ekrana verilen s�ra nosuyla birlikte yazd�r�r
void Ogrenci::OgrenciYaz(int sira)
{
	cout << sira << ". ��rencinin, ";
	cout << "Ad�: " << ad << endl;
	cout << "Soyad�: " << soyad << endl;
	cout << "Numaras�: " << ogrNo << endl;
	cout << "B�l�m�: " << bolum << endl;
	cout << "S�n�f�: " << sinif << endl;
	cout << "Yandal: " << yandal << endl << endl;
	cout << "***********************************" << endl;
}

// �grencinin bilgilerini ekrana yazd�r�r
void Ogrenci::OgrenciYaz()
{
	cout << "��rencinin, ";
	cout << "Ad�: " << ad << endl;
	cout << "Soyad�: " << soyad << endl;
	cout << "Numaras�: " << ogrNo << endl;
	cout << "B�l�m�: " << bolum << endl;
	cout << "S�n�f�: " << sinif << endl;
	cout << "Yandal: " << yandal << endl << endl;
	cout << "***********************************" << endl;
}

//6 haneli ��renci numarasan�n en ba��ndaki hanesini bulup d�nd�ren fonksiyon, b�l�m tespit etmek i�in kullan�l�r
int Ogrenci::NumaraTespit(int no)
{
	int digit = (int)(no / pow(10, (6 - 1))) % 10;
	return digit;
}

/*
Ald��� ��renci numaras�n�, ��renci olu�turulurken b�l�m�n� tespit etmek i�in kullan�r. 
Numaras�n�n ba� hanesine g�re ��renciye b�l�m atar
*/
string Ogrenci::BolumTespit(int no)
{
	string b = "";
	int digit = NumaraTespit(no);// 6 haneli numaran�n en ba��ndaki numara
	switch (digit)
	{
	case 1:
		b = "�evre M�hendisligi";
		break;
	case 2:
		b = "�n�aat M�hendisligi ";
		break;
	case 3:
		b = "Elektrik Elektronik M�hendisligi";
		break;
	case 4:
		b = "Mekatronik M�hendisligi";
		break;
	case 5:
		b = "Bilgisayar M�hendisligi";
		break;
	case 6:
		b = "End�striyel Tasar�m M�hendisligi";
		break;
	case 7:
		b = "G�da M�hendisligi";
		break;
	case 8:
		b = "Makina M�hendisligi";
		break;
	case 9:
		b = "Tekstil M�hendisligi";
		break;
	default:
		b = "B�l�m Yok";
		break;
	}
	return b;
}