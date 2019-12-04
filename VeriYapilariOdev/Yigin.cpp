#include "stdafx.h"
#include "Yigin.h"

// Constructor. Y���nda head varsay�lan olarka bo� olmal�
Yigin::Yigin() {
	head = NULL;
}

// Destructor. Memory leak engellemek ad�na y���ndaki t�m elemanlar gezilerek temizlenir
Yigin::~Yigin() {

	Node* silinecekNode = head, * sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirlenir
		delete silinecekNode; // ge�erli node silinir
		silinecekNode = sonrakiNode;//ge�erli node bir sonraki node olacak �ekilde ayarlan�r
	}
}

// Y���n�n en �st�ndeki eleman� d�nd�r�r, y���nda oynama olmaz
Node* Yigin::Top()
{
	if (BosMu())
	{
		cout << "Y���n bo�..." << endl;
		return NULL;
	}
	else
	{
		cout << "En �stteki ��renci i�in:" << endl;
		head->ogr->OgrenciYaz();

		return head;
	}
}

// Y���n�n en �st�ne LIFO mant���na g�re �ge ekler
bool Yigin::Push(Ogrenci* ogr) {
	return NodeEkle(0, ogr);
}

// Y���n�n en �st�ndeki eleman� LIFO mant���na g�re y���ndan ay�r�p geri d�nd�r�r
Node* Yigin::Pop()
{
	if (BosMu())
	{
		cout << "Y���n bo�..." << endl;
		return NULL;
	}
	else {
		cout << "En �stteki ��kar�lan ��renci i�in:" << endl;
		head->ogr->OgrenciYaz();

		Node* currentNode = head;
		NodeSil(currentNode->ogr);
		return currentNode;
	}
}

// Y���n� ekrana yazd�r�r
void Yigin::YiginiYazdir()
{
	ListeyiYazdir();
}

