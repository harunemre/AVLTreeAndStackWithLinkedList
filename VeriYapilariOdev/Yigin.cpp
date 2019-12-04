#include "stdafx.h"
#include "Yigin.h"

// Constructor. Yýðýnda head varsayýlan olarka boþ olmalý
Yigin::Yigin() {
	head = NULL;
}

// Destructor. Memory leak engellemek adýna yýðýndaki tüm elemanlar gezilerek temizlenir
Yigin::~Yigin() {

	Node* silinecekNode = head, * sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirlenir
		delete silinecekNode; // geçerli node silinir
		silinecekNode = sonrakiNode;//geçerli node bir sonraki node olacak þekilde ayarlanýr
	}
}

// Yýðýnýn en üstündeki elemaný döndürür, yýðýnda oynama olmaz
Node* Yigin::Top()
{
	if (BosMu())
	{
		cout << "Yýðýn boþ..." << endl;
		return NULL;
	}
	else
	{
		cout << "En üstteki öðrenci için:" << endl;
		head->ogr->OgrenciYaz();

		return head;
	}
}

// Yýðýnýn en üstüne LIFO mantýðýna göre öge ekler
bool Yigin::Push(Ogrenci* ogr) {
	return NodeEkle(0, ogr);
}

// Yýðýnýn en üstündeki elemaný LIFO mantýðýna göre yýðýndan ayýrýp geri döndürür
Node* Yigin::Pop()
{
	if (BosMu())
	{
		cout << "Yýðýn boþ..." << endl;
		return NULL;
	}
	else {
		cout << "En üstteki çýkarýlan öðrenci için:" << endl;
		head->ogr->OgrenciYaz();

		Node* currentNode = head;
		NodeSil(currentNode->ogr);
		return currentNode;
	}
}

// Yýðýný ekrana yazdýrýr
void Yigin::YiginiYazdir()
{
	ListeyiYazdir();
}

