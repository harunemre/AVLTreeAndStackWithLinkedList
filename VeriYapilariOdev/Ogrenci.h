#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ogrenci
{
	string ad, soyad, bolum, yandal;
	int ogrNo, sinif;

public:
	friend class Fonksiyonlar;
	friend class Node;
	friend class Liste;
	friend class AVLNode;
	friend class AVLAgaci;
	Ogrenci();
	Ogrenci(string adi, string soyadi, int no, int sinifi, string yandali = "Yok");
	~Ogrenci();
	void OgrenciYaz(int sira);
	void OgrenciYaz();
	string BolumTespit(int no);
	int NumaraTespit(int no);
};

