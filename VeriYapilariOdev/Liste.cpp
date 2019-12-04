#include "stdafx.h"
#include "Liste.h"

//Boþ stack için head=NULL olur. Constructor.
Liste::Liste()
{
	head = NULL;
}

//Memory Leak engellemek için liste nesnesi silindiðinde hafýzadan listenin içini boþaltýr
Liste::~Liste()
{

	Node* silinecekNode = head, * sonrakiNode = NULL;
	while (silinecekNode->sonraki != NULL) {
		sonrakiNode = silinecekNode->sonraki;// bir sonraki nodu belirleyip, o anki nodu siliyoruz
		delete silinecekNode;
		silinecekNode = sonrakiNode;//þuanki nodu tekrar atýyoruz..
	}
}

//Liste boþsa true , deðilse false dönderir
bool Liste::BosMu()
{
	return head == NULL; // boþsa true yoksa false dönder
}

/*
Oluþturulan bir listenin belirli bir indexine, Ogrenci eklemesi yapar.
2 özel durumu vardýr. Baþa ekleme ve ortaya / sona ekleme.
Listenin içinde belirtilen index eðer sýfýrsa direkt baþa ekler, currIndex=1 olur ve 1.sýraya ekler,
diðer durumlarda indexi currIndex olana kadar liste içinde gezinerek indexin denk geldiði node'u tespit eder.
Tespit edilen node'un hemen sonrasýna yeni node eklenir.
*/
Node* Liste::NodeEkle(int index, Ogrenci* o)
{
	if (index < 0) return NULL; // index kontrolü
	int currIndex = 1; //istenilen indexteki elemaný bulmak için kullanýlýr.Asýl index 0.indexten baþlayarak ilerler.
	Node* currNode = head;
	while (currNode && index > currIndex) {//istenin index'ten bir önceki elemanýný bulup, onu currNode deðerine atýyoruz.
		currNode = currNode->sonraki;
		currIndex++;
	}

	if (index > 0 && currNode == NULL) return NULL;

	Node* NewNode = new Node(o);

	if (index == 0) { //eðer eleman baþa eklenecekse
		NewNode->sonraki = head;
		head = NewNode;
	}

	else { //ortaya veya sona eklenecekse
		NewNode->sonraki = currNode->sonraki;
		currNode->sonraki = NewNode;
	}
	return NewNode;
}

//Verilen ögrenci numarasýna göre öðrenci varsa varolan node 'u döndürür yoksa NULL döndürür
Node* Liste::NodeBul(Ogrenci* o) {
	Node* currNode = head;
	while (currNode && currNode->ogr->soyad != o->soyad) { //istenilen düðümü buluyor
		currNode = currNode->sonraki;//soyad uyuþmuyorsa diðer düðüme geç
	}
	return currNode;
}

//Verilen indexe karþýlýk gelen node'u bulur ve pointerini dönderir.
Node* Liste::IndextenNodeBul(int index)
{
	Node* gecici = head;
	for (int i = 0; i < index; i++) {
		gecici = gecici->sonraki;
	}
	return gecici; // bulunan node'u dönder
}

/*NodeEkle fonksiyonunda olduðu gibi burada da
ögrenci numarasýna göre listede gezerek istenen index bulunur,
bulunan indexten önceki node geçici bir node'a atýlýr.
Gecici node un sonraki deðeri, bulunan node'un sonraki deðerine eþitlenir ve bulunan node silinir.
Eðer gecici node NULL ise bu listenin baþýndaki node'un bulunduðunu gösterir.
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

/*Listenin baþýndan baþlayarak
tüm öðrencileri yazdýrýr,
her bir yazdýrmasýna sirayi bir arttýrýr,
bu sýra deðiþkeni kaçýncý öðrencinin yazdýrýldýðýný gösteren deðerdir*/
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
