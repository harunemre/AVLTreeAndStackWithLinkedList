#include "stdafx.h"
#include "Liste.h"

//Bo� stack i�in head=NULL olur. Constructor.
Liste::Liste()
{
	head = NULL;
}

//Memory Leak engellemek i�in liste nesnesi silindi�inde haf�zadan listenin i�ini bo�alt�r
Liste::~Liste()
{

	Node* silinecekNode = head, * sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirleyip, o anki nodu siliyoruz
		delete silinecekNode;
		silinecekNode = sonrakiNode;//�uanki nodu tekrar at�yoruz..
	}
}

//Liste bo�sa true , de�ilse false d�nderir
bool Liste::BosMu()
{
	return head == NULL; // bo�sa true yoksa false d�nder
}

/*
Olu�turulan bir listenin belirli bir indexine, Ogrenci eklemesi yapar.
2 �zel durumu vard�r. Ba�a ekleme ve ortaya / sona ekleme.
Listenin i�inde belirtilen index e�er s�f�rsa direkt ba�a ekler, currIndex=1 olur ve 1.s�raya ekler,
di�er durumlarda indexi currIndex olana kadar liste i�inde gezinerek indexin denk geldi�i node'u tespit eder.
Tespit edilen node'un hemen sonras�na yeni node eklenir.
*/
Node* Liste::NodeEkle(int index, Ogrenci* o)
{
	if (index < 0) return NULL; // index kontrol�
	int currIndex = 1; //istenilen indexteki eleman� bulmak i�in kullan�l�r.As�l index 0.indexten ba�layarak ilerler.
	Node* currNode = head;
	while (currNode && index > currIndex) {//istenin index'ten bir �nceki eleman�n� bulup, onu currNode de�erine at�yoruz.
		currNode = currNode->sonraki;
		currIndex++;
	}

	if (index > 0 && currNode == NULL) return NULL;

	Node* NewNode = new Node(o);

	if (index == 0) { //e�er eleman ba�a eklenecekse
		NewNode->sonraki = head;
		head = NewNode;
	}

	else { //ortaya veya sona eklenecekse
		NewNode->sonraki = currNode->sonraki;
		currNode->sonraki = NewNode;
	}
	return NewNode;
}

//Verilen �grenci numaras�na g�re ��renci varsa varolan node 'u d�nd�r�r yoksa NULL d�nd�r�r
Node* Liste::NodeBul(Ogrenci* o) {
	Node* currNode = head;
	while (currNode && currNode->ogr->soyad != o->soyad) { //istenilen d���m� buluyor
		currNode = currNode->sonraki;//soyad uyu�muyorsa di�er d���me ge�
	}
	return currNode;
}

//Verilen indexe kar��l�k gelen node'u bulur ve pointerini d�nderir.
Node* Liste::IndextenNodeBul(int index)
{
	Node* gecici = head;
	for (int i = 0; i < index; i++) {
		gecici = gecici->sonraki;
	}
	return gecici; // bulunan node'u d�nder
}

/*NodeEkle fonksiyonunda oldu�u gibi burada da
�grenci numaras�na g�re listede gezerek istenen index bulunur,
bulunan indexten �nceki node ge�ici bir node'a at�l�r.
Gecici node un sonraki de�eri, bulunan node'un sonraki de�erine e�itlenir ve bulunan node silinir.
E�er gecici node NULL ise bu listenin ba��ndaki node'un bulundu�unu g�sterir.
*/
int Liste::NodeSil(Ogrenci* o) {

	Node* arananNode = head;
	int ArananIndex = 1;
	while (arananNode && arananNode->ogr->soyad != o->soyad) {
		arananNode = arananNode->sonraki;
		ArananIndex++;
	}

	if (arananNode) {
		head = arananNode->sonraki;
		delete arananNode;

		return ArananIndex;
	}
	return 0;
}

/*Listenin ba��ndan ba�layarak
t�m ��rencileri yazd�r�r,
her bir yazd�rmas�na sirayi bir artt�r�r,
bu s�ra de�i�keni ka��nc� ��rencinin yazd�r�ld���n� g�steren de�erdir*/
void Liste::ListeyiYazdir()
{
	int sira = 1;
	Node* yazilanNode = head;
	while (yazilanNode != NULL)
	{
		yazilanNode->ogr->OgrenciYaz(sira);
		yazilanNode = yazilanNode->sonraki;
		sira++;
	}
}
