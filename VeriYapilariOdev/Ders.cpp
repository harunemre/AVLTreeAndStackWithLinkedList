#include "stdafx.h"
#include "Ders.h"

/*
	Sýnýf listelerinin oluþturulacaðý derslerin;
	[dersin adi], [kodu], [dersin öðrenim yýlý] ve [dersi alan öðrencilerin aktarýlacaðý dosya yolu] deðiþkenlerin,
	nesneyi oluþtururken belirlenmesini saðlayan constructor method
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
	Öðrenciler iki ayrý metin belgesinde tutulmaktadýr.
	Bu metin belgegelerinden okunup sýnýf listesi oluþturulduðundan burada dosya okuma yazma iþlemleri gerçekleþmektedir.
	Listenin boyutu bilinmediði için c++ daki dinamik dizi görevi gören vectorden, bir öðrenci pointeri tutan vector oluþturuldu.
	Dosya okumak için gerek ifstream ve okunan stringin parçalanmasýna yarayan stringstream sýnýflarýndan türetilen nesneler sayesinde
	metin belgesindeki her bir satýr ":" karakterine göre parçalanýp vektör dizisine atandý.
	Bu vector dizisinin her bir elemaný sýrasýyla ögrencinin bilgilerini içermektedir.
	Bu vektordaki deðerler ListeOlustur ve AgacOlustur Methodu ile sinif listelerini oluþturur.
*/
vector<Ogrenci*> Ders::OgrenciAl()
{
	vector<Ogrenci*> ogr; // öðrencilerin tutulacaðý vectoru oluþtur
	ifstream belge(dosyaYolu, ios::in);// açýlacak metin belgesini belirle
	if (belge.is_open()) //belgeni açýk olmama durumunu kontrol et
	{
		string okunan;
		while (getline(belge, okunan)) //satýr satýr oku, okunana aktar
		{
			vector<string> parca; // parçalarý tutacak string
			string s; // parçalanan parçayý geçici olarak tutacak string
			stringstream sst(okunan);//stringstream e okunan satýrý yolla
			int iparca[2];//ogrencinin numarasý ve sýnýfý için integer deðer tutacak dizi
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
Aðaç ve yýðýn oluþumlarý farklý olduðu için her ikisi de farklý methodlar üzerinde iþleme alýndý.
Her ikisi de yukarýdaki ogrencial methodunu kullanarak öðrencileri tutan vectoru kendi yapýsýna uygun olarak kullanarak aðac veya liste oluþturur.
Vectorun karþýlaþtýrýlmasýnda size_T kullanýldý çünkü vectordaki index bu tipte saðlanmaktadýr.
Fonksiyonlarýn biri Yýðýn diðeri ise AVLAgaci döndürmektedir.
Sonraki kýsýmlarda öðrenci listelerini oluþturulmasý ve üzerinde oynama yapýlmasý için kullanýlacaktýr.
*/
AVLAgaci* Ders::AgacOlustur()
{
	vector<Ogrenci*> ogr = OgrenciAl();
	size_t i; //vectorun size methoduyla, int karþýlaþtýrýlamadýðý için size_t kullanýldým
	AVLAgaci* agac = new AVLAgaci();
	for (i = 0; i < ogr.size(); i++) {
		agac->AVLEkle(ogr[i]);
	}
	return agac;
}

/*
Aðaç ve yýðýn oluþumlarý farklý olduðu için her ikisi de farklý methodlar üzerinde iþleme alýndý.
Her ikisi de yukarýdaki ogrencial methodunu kullanarak öðrencileri tutan vectoru kendi yapýsýna uygun olarak kullanarak aðac veya liste oluþturur.
Vectorun karþýlaþtýrýlmasýnda size_T kullanýldý çünkü vectordaki index bu tipte saðlanmaktadýr.
Fonksiyonlarýn biri Yýðýn diðeri ise AVLAgaci döndürmektedir.
Sonraki kýsýmlarda öðrenci listelerini oluþturulmasý ve üzerinde oynama yapýlmasý için kullanýlacaktýr.
*/
Yigin* Ders::YiginOlustur()
{
	vector<Ogrenci*> ogrenciler = OgrenciAl();
	size_t i; //vectorun size methoduyla, int karþýlaþtýrýlamadýðý için size_t kullanýldýk
	Yigin* list = new Yigin();
	for (i = 0; i < ogrenciler.size(); i++) {
		list->NodeEkle(0, ogrenciler[i]);
	}
	return list;
}
