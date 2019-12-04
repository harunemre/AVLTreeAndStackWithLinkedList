#pragma once
#include "Node.h"
class Liste
{
public:
	Liste();
	~Liste();
	friend class Fonksiyonlar;
	bool BosMu();
	Node* NodeEkle(int index, Ogrenci* o);
	Node* NodeBul(Ogrenci* o);
	Node* IndextenNodeBul(int index);
	int NodeSil(Ogrenci* node);
	void ListeyiYazdir();

private:
	Node* head;
	friend class Yigin;
};

