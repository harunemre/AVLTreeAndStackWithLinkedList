#include "stdafx.h"
#include "Ders.h"

/*
	S�n�f listelerinin olu�turulaca�� derslerin;
	[dersin adi], [kodu], [dersin ��renim y�l�] ve [dersi alan ��rencilerin aktar�laca�� dosya yolu] de�i�kenlerin,
	nesneyi olu�tururken belirlenmesini sa�layan constructor method
*/
Ders::Ders(string ad, string kod, int yili, string _dosyaYolu)
{
	dersAdi = ad;
	dersKodu = kod;
	yil = yili;
	dosyaYolu = _dosyaYolu;
}

// Destructor
Ders::~Ders()
{
}

/*
	��renciler iki ayr� metin belgesinde tutulmaktad�r.
	Bu metin belgegelerinden okunup s�n�f listesi olu�turuldu�undan burada dosya okuma yazma i�lemleri ger�ekle�mektedir.
	Listenin boyutu bilinmedi�i i�in c++ daki dinamik dizi g�revi g�ren vectorden, bir ��renci pointeri tutan vector olu�turuldu.
	Dosya okumak i�in gerek ifstream ve okunan stringin par�alanmas�na yarayan stringstream s�n�flar�ndan t�retilen nesneler sayesinde
	metin belgesindeki her bir sat�r ":" karakterine g�re par�alan�p vekt�r dizisine atand�.
	Bu vector dizisinin her bir eleman� s�ras�yla �grencinin bilgilerini i�ermektedir.
	Bu vektordaki de�erler ListeOlustur ve AgacOlustur Methodu ile sinif listelerini olu�turur.
*/
vector<Ogrenci*> Ders::OgrenciAl()
{
	vector<Ogrenci*> ogr; // ��rencilerin tutulaca�� vectoru olu�tur
	ifstream belge(dosyaYolu, ios::in);// a��lacak metin belgesini belirle
	if (belge.is_open()) //belgeni a��k olmama durumunu kontrol et
	{
		string okunan;
		while (getline(belge, okunan)) //sat�r sat�r oku, okunana aktar
		{
			vector<string> parca; // par�alar� tutacak string
			string s; // par�alanan par�ay� ge�ici olarak tutacak string
			stringstream sst(okunan);//stringstream e okunan sat�r� yolla
			int iparca[2];//ogrencinin numaras� ve s�n�f� i�in integer de�er tutacak dizi
			while (getline(sst, s, ':')) {
				parca.push_back(s);
			}
			istringstream(parca[2]) >> iparca[0];
			istringstream(parca[3]) >> iparca[1];
			Ogrenci* o = new Ogrenci(parca[0], parca[1], iparca[0], iparca[1], parca[4]);
			ogr.push_back(o);
		}
	}
	else
		cout << "Ogrencilerin bulundugu dosya acilamadi!";
	return ogr;
}
/*
A�a� ve y���n olu�umlar� farkl� oldu�u i�in her ikisi de farkl� methodlar �zerinde i�leme al�nd�.
Her ikisi de yukar�daki ogrencial methodunu kullanarak ��rencileri tutan vectoru kendi yap�s�na uygun olarak kullanarak a�ac veya liste olu�turur.
Vectorun kar��la�t�r�lmas�nda size_T kullan�ld� ��nk� vectordaki index bu tipte sa�lanmaktad�r.
Fonksiyonlar�n biri Y���n di�eri ise AVLAgaci d�nd�rmektedir.
Sonraki k�s�mlarda ��renci listelerini olu�turulmas� ve �zerinde oynama yap�lmas� i�in kullan�lacakt�r.
*/
AVLAgaci* Ders::AgacOlustur()
{
	vector<Ogrenci*> ogr = OgrenciAl();
	size_t i; //vectorun size methoduyla, int kar��la�t�r�lamad��� i�in size_t kullan�ld�m
	AVLAgaci* agac = new AVLAgaci();
	for (i = 0; i < ogr.size(); i++) {
		agac->AVLEkle(ogr[i]);
	}
	return agac;
}

/*
A�a� ve y���n olu�umlar� farkl� oldu�u i�in her ikisi de farkl� methodlar �zerinde i�leme al�nd�.
Her ikisi de yukar�daki ogrencial methodunu kullanarak ��rencileri tutan vectoru kendi yap�s�na uygun olarak kullanarak a�ac veya liste olu�turur.
Vectorun kar��la�t�r�lmas�nda size_T kullan�ld� ��nk� vectordaki index bu tipte sa�lanmaktad�r.
Fonksiyonlar�n biri Y���n di�eri ise AVLAgaci d�nd�rmektedir.
Sonraki k�s�mlarda ��renci listelerini olu�turulmas� ve �zerinde oynama yap�lmas� i�in kullan�lacakt�r.
*/
Yigin* Ders::YiginOlustur()
{
	vector<Ogrenci*> ogrenciler = OgrenciAl();
	size_t i; //vectorun size methoduyla, int kar��la�t�r�lamad��� i�in size_t kullan�ld�k
	Yigin* list = new Yigin();
	for (i = 0; i < ogrenciler.size(); i++) {
		list->NodeEkle(0, ogrenciler[i]);
	}
	return list;
}
