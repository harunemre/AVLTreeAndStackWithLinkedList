#include "stdafx.h"
#include "Fonksiyonlar.h"
Ders VeritabaniYonetimSistemleri = Ders(Sabitler::DERS_ADI_VTYS, Sabitler::DERS_KODU_VTYS, 3, "vtys.txt"); //Dersi Olu�tur, 3.S�n�f Dersi
Ders VeriYapilariVeAlgoritmalar = Ders(Sabitler::DERS_ADI_VYVA, Sabitler::DERS_KODU_VYVA, 2, "vyva.txt");//Dersi Olu�tur, 2.S�n�f Dersi
Yigin* yigin = new Yigin(); // Veri Yapilar� ve Algoritmalar Alan ��rencileri Tutacak Liste
AVLAgaci* agac = new AVLAgaci(); //Veritabani Y�netim Sistemleri Dersini alanlar� tutacak a�a�
Liste* eemliler = new Liste(); //eem alan ��rencileri tutacak
Liste* ikiders = new Liste(); //heapa�ac�n� tutacak

Fonksiyonlar::Fonksiyonlar()
{

}

Fonksiyonlar::~Fonksiyonlar()
{

}

bool Fonksiyonlar::TekMi(int no) {
	return no % 2 == 1;
}

/*
Program i�inde gerekli yerlerde liste olu�turulaca�� zaman;
��rencileri metin belgesinden okuyup �eken OgrencileriAl fonksiyonunu kullanarak y���n veya a�ac� olu�turur.
VeritabaniYonetimSistemleri ve VeriYapilariVeAlgoritmalar de�i�kenleri ders s�n�f�n�n nesnelerini temsil ederken
y���n ve agac kavramlar� ise uygulama i�inde genel olarak eri�ebilir olan ana y���n ve a�ac� temsil etmektedir.
Di�er Fonksiyonlar�n hepsi bu y���n ve agac'� kullanarak kendi b�nyelerinde gerekli i�lemleri yapmaktad�r.
*/
void Fonksiyonlar::ListeOlustur(string kod)
{
	if (kod == Sabitler::DERS_KODU_VYVA)
		yigin = VeriYapilariVeAlgoritmalar.YiginOlustur();
	else
		agac = VeritabaniYonetimSistemleri.AgacOlustur();
}

// TODO: Aciklama d�zenlenecek
/*
Bu fonksiyonda 2.sorunun a ��kk�nda istenilen �zerine, Her iki derside alttan alan ��renciler listelenmi�tir.�lk olarak bu i�lem i�in foknsiyon i�inde ba��ms�z bir liste olu�turulmu�tur. Daha sora Bilgisayar A�lar� S�n�f Listesini ��eren liste'nin en ba��ndan ba�lanarak, her bir d���mdeki ��rencinin sinifi B.A�lar� dersinin ders y�l� olan 1.s�n�f ile kar��la�t�r�lm��t�r. E�er ��renci 1.s�n�ftan b�y�kse bu dersi alttan al�yor demektir, bundan sonra bu ��renci AVLAgacinda listesi tutulan Bilgisayar Mimarisi Dersinin listesinde aranm��t�r. E�er sonu� olumlu ise bu ��rencinin o derside alttan al�p almad��� ders yili ve ��rencinin s�n�f� k�yaslanarak kontrol edilmi�tir.E�er sonu� tekrar olumlu ��karsa bu ��renci Alttan Alanlar listesine eklenmi�tir. Bu i�lem liste sonuna kadar t�m ��rencilere uygulanacakt�r.En sonu�ta ortaya ��kan liste bo� de�ilse liste yazd�r�lacak,yoksa liste bo� mesaj� d�nderilecektir.*/
void Fonksiyonlar::AlttanAlanlar()
{
	Liste* altalan = new Liste();
	//ilk olarak olu�turulmam�� sinif listesi varsa olu�turuyoruz
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta ar�yoruz	
	int i = 0; // listeye eklenme s�ras�
	while (!yigin->BosMu())
	{
		Node* geznode = yigin->Pop(); // listenin ba��ndan ba�la
		if (
			(geznode->ogr->sinif > VeriYapilariVeAlgoritmalar.yil)& // Ogrencinin sinifi dersin yilindan b�y�kse alttan al�yor demektir
			(agac->AVLBul(geznode->ogr) != NULL)&// e�er bu ��renci a�a�ta varsa
			(geznode->ogr->sinif > VeritabaniYonetimSistemleri.yil)
			)// BMimarisini alttan al�yorsa
		{
			altalan->NodeEkle(i, geznode->ogr);//listeye ekle
			i++;
		}
	}
	if (altalan->BosMu()) // liste bo��sa bilgilendir
		cout << "\t\t\t\t  ----------> �K� DERS�DE AYNI ANDA ALTTAN ALAN ��RENC� YOKTUR!<----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> �K� DERS�DE AYNI ANDA ALTTAN ALANLAR  <----------" << endl;
		altalan->ListeyiYazdir();// yoksa listeyi yazd�r
	}
}

// TODO: Aciklama d�zenlenecek
/* A�IKLAMASI: Bu Fonksiyon i�in �ncelikle yeni bir liste olu�turuyoruz. Bu listede bizim istedi�imiz ��rencileri tutaca��z.Bilgisayar A�lar� s�n�f listesinin tutuldu�u ana listemizin ilk d���m�nden ba�l�yoruz. Bu d���mdeki ��renciyi Bilgisayar Mimarisi Listesinin tutuldu�u a�a�ta ar�yoruz. E�er ��renci burada yoksa bu ��renciyi SADECE B�LG�SAYAR A�LARI ALAN ��renciler listemize ekliyoruz.Daha sonra listeyi yazd�r�yoruz */
Liste* Fonksiyonlar::VeritabaniYonetimSistemleriAlanlar()
{
	Liste* vtysAlanlar = new Liste();
	//ilk olarak olu�turulmam�� sinif listesi varsa olu�turuyoruz
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);
	int index = 0;
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta ar�yoruz
	while (!yigin->BosMu())
	{
		Node* yiginEleman = yigin->Pop();
		if (agac->AVLBul(yiginEleman->ogr) == NULL)// e�er bu ��renci a�a�ta yoksa
			vtysAlanlar->NodeEkle(index++, yiginEleman->ogr);//listeye ekle
	};

	if (vtysAlanlar->BosMu()) // liste bo��sa bilgilendir
		cout << "\t\t\t\t  ! SADECE " << Sabitler::DERS_ADI_VTYS << " ALAN ��RENC� YOKTUR !" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> SADECE " << Sabitler::DERS_ADI_VTYS << " DERS� ALANLAR  <----------" << endl;
		vtysAlanlar->ListeyiYazdir();// yoksa listeyi yazd�r
	}
	return vtysAlanlar;
}

// TODO: Aciklama d�zenlenecek
/*A�IKLAMASI : Bu fonksiyonda Bilgisayar A�lar� listesini A ve B grubu olarak par�alamam�z isteniyor. A Grubunda Soyad� A-K aras�nda olanlar, B Grubunda ise soyad� L-Z aras�nda olanlar olacakt�r. 2 adet liste olu�turuyoruz birisi Agrup di�eri ise Bgrup olacak �ekilde.Bilgisayar A�lar� Dersininin S�n�f Listesini i�eren ana listenin ilk eleman�ndan ba�l�yoruz.Bu Eleman�n i�indeki ��rencinin soyad�n�n �LK HARF� A-K aras�nda ise A grubuna yoksa B grubuna ait listeye ekliyoruz. Bunu ana listenin t�m elemanlar� i�in uyguluyoruz ve en sonda iki ayr� listemizi yazd�r�yoruz.*/
void Fonksiyonlar::VeritabaniYonetimSistemleriGrupAyir()
{
	ListeKontrol(Sabitler::DERS_KODU_VTYS);

	//Gerekli listeleri olu�tur
	Liste* Agrup = new Liste();
	Liste* Bgrup = new Liste();
	//listede gezmeye ba�la	
	VeritabaniYonetimSistemleriGrupEkle(agac->root, Agrup, Bgrup, 0, 0);

	// A Grubunu yazdir
	if (Agrup->BosMu())
		cout << "A Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> " << Sabitler::DERS_ADI_VTYS << " DERS� - A GRUBU  <----------" << endl;
		Agrup->ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup->BosMu())
		cout << "B Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> " << Sabitler::DERS_ADI_VTYS << " DERS� - B GRUBU  <----------" << endl;
		Bgrup->ListeyiYazdir();
	}

}

// TODO: aciklama d�zenlenecek
void Fonksiyonlar::VeriYapilariveAlgoritmalarGrupAyir()
{
	ListeKontrol(Sabitler::DERS_KODU_VYVA);

	//Gerekli listeleri olu�tur
	Liste Agrup, Bgrup = Liste();

	int i = 0, j = 0; // eklerken tutlacak indisler
	while (!yigin->BosMu())
	{
		Node* gezNode = yigin->Pop();
		string soyad = gezNode->ogr->soyad; // soyad karakterini al
		char ch = soyad.at(0); // soyad karakterini chara at
		if (ch >= 'A' && ch <= 'K') // e�er soyad� bu harfler aras�ndaysa a grubuna ekle		
			Agrup.NodeEkle(i++, gezNode->ogr);
		else
			Bgrup.NodeEkle(j++, gezNode->ogr); // de�ilse B grubuna ekle		
	}
	// A Grubunu yazdir
	if (Agrup.BosMu())
		cout << "A Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> "<< Sabitler::DERS_ADI_VYVA <<" DERS� - A GRUBU  <----------" << endl;
		Agrup.ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup.BosMu())
		cout << "B Grubunda �grenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> " << Sabitler::DERS_ADI_VYVA << " DERS� - B GRUBU  <----------" << endl;
		Bgrup.ListeyiYazdir();
	}

}

/*EEMOgrenciListe A�IKLAMA : Bilgisayar A�lar� ve Bilgisayar Mimarisi derslerinin en az birini alan ve elektronik m�hendisli�i b�l�m� ��rencisi olan ��rencileri listelemek istiyoruz.Bunun �ncelikle ana listemiz gibi ba�ka fonksiyonlardan eri�ilebilecek bir liste olu�turuyoruz.Eemliler adl� bu listeyi d��arda tutmam�z�n amac� bu listeye a�a�ta gezerken ihtiyac�m�z olmas�d�r.�ncelikle Bigisayar A�lar� Dersinin listesini tutan ana listenin en ba��ndaki ��renciyi al�yoruz, burda ��rencinin �ncelikle numaras�n�n ilk harfini tespit ediyoruz.Bu numara e�er 3 ile ba�l�yorsa veya Yandal� "Elektrik Elektronik M�hendisli�i" ise bu ��renciyi eemliler listesine ekliyoruz.Bunu liste bitene kadar tekrarl�yoruz.Ondan sonra Aga�ta gezme fonksiyonunu �a��r�p, eri�ebilirli�i a��k olan eemliler listemizde bu fonksiyon ile de�i�iklik yap�yoruz. En sonda ise bu listeyi yazd�r�yoruz.*/
void Fonksiyonlar::EEMOgrenciListe()
{
	// bo� liste olmas�na kar�� kontrol
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);

	Node* geznode = yigin->head;
	while (geznode != NULL)
	{
		//��renci numaras�n�n ilk numaras�n� al b�l�m belirlemek i�in
		int digit = geznode->ogr->NumaraTespit(geznode->ogr->ogrNo);
		//e�er elektrik b�l�m� ��rencisiyse,agactan gelen listede varm� kontrol et
		if (digit == 3 || geznode->ogr->yandal == "Elektrik Elektronik M�hendisligi")
			eemliler->NodeEkle(0, geznode->ogr); // kriteri sa�l�yorsa listeye ekle
		geznode = geznode->sonraki; // sonraki d���me ge�
	}
	AgacGez(agac->root);
	cout << "Bilgisayar A�lar� ve Bilgisayar Mimarisi derslerinin en az birini alan EEML�LER";
	eemliler->ListeyiYazdir();
}

// TODO: Aciklama d�zenlenecek
void Fonksiyonlar::VeritabaniYonetimSistemleriGrupEkle(AVLNode* kok, Liste* listeA, Liste* listeB, int i, int j)
{
	if (kok == NULL)
		return;
	VeritabaniYonetimSistemleriGrupEkle(kok->sol, listeA, listeB, i, j); //en sola git
	if (TekMi(kok->ogr->ogrNo))//a�ac�n eleman� eemlimi		
		listeA->NodeEkle(i++, kok->ogr); // ��renciyi ekle
	else listeB->NodeEkle(j++, kok->ogr);
	VeritabaniYonetimSistemleriGrupEkle(kok->sag, listeA, listeB, i, j);
}

/*
AVL a�ac�nda i�k�k gezerek a�a� i�inde kontrol yap�l�r.
A�ac�n en soluna gidip ordaki ��rencinin numaras�n�n ilk harfininin 3 olup olmad���n� veya varsa ��rencinin yandal�n�n elektrik elektronik m�hendisli�i olup olmad���n� kontrol ediyor.E�er ��renci bu kriterleri sa�l�yorsa bu ��renciyi eemliler listesinde ar�yor.E�er bu ��renci eemliler listesinde mevcut DE��LSE ��renciyi eemliler listesine ekliyor.T�m a�a� boyunca i�k�k kural�nca bunu yaparak a�ac� taram�� oluyor.
*/
void Fonksiyonlar::AgacGez(AVLNode* kok)
{
	if (kok == NULL)
		return;
	AgacGez(kok->sol); //en sola git
	int digit = kok->ogr->NumaraTespit(kok->ogr->ogrNo); //b�l�m bilgisi i�in
	if (digit == 3 || kok->ogr->yandal == "Elektrik Elektronik M�hendisligi")//a�ac�n eleman� eemlimi
		if (eemliler->NodeBul(kok->ogr) == NULL) // e�er ��renci B.A�lar�nda yoksa
			eemliler->NodeEkle(0, kok->ogr); // ��renciyi ekle
	AgacGez(kok->sag);
}

/* Bu fonksiyon yukar�da bahssetti�imiz liste olu�tur fonksiyonlar�n� kullanarak. E�er ANA L�STE ve A�ACIMIZ Bo� ise program y�r�t�lemeyece�inden, bunlar� kontrol edip, bo� ise dolduruyor.*/
void Fonksiyonlar::ListeKontrol(string secim)
{
	// Men� aras� ge�i�lerde, Listelerin olu�turulmad��� durumlar i�in kontrol
	if (secim == Sabitler::DERS_KODU_VYVA && yigin->BosMu())
		ListeOlustur(Sabitler::DERS_KODU_VYVA);
	else if (secim == Sabitler::DERS_KODU_VTYS && agac->BosMu())
		ListeOlustur(Sabitler::DERS_KODU_VTYS);
}

//A�ac�n bir eleman� al�n�p a�ac� ba�tan sona gezerken en soldaki eleman� t�m a�a�la kar��la�t�r�l�r ve en k���k olan� bulunup listeye eklenir
void Fonksiyonlar::SecmeliSirala(AVLNode* kok) // en son buraya d�n
{
	if (kok == NULL)
		return;
	SecmeliSirala(kok->sol); //en sola git
	kok->ogr->OgrenciYaz();
	SecmeliSirala(kok->sag);
}

/*Secmeli S�ralanan A�ac� Yazd�r�r*/
void Fonksiyonlar::SecmeliYazdir()
{
	SecmeliSirala(agac->root);
}

/* A�IKLAMASI : Radiks s�ralama kural� gere�i, ilk �nce bo� bir liste olu�turuyoruz bu listeye yukar�da daha �nceden yapm�� oldu�umuz Sadece Bilgisayar A�lar� Alanlar�n listesini at�yoruz.Onun haricinde birde elimizde s�ralad�ktan sonra koyaca��m�z bir bo� liste olu�turuyoruz.Dolu olan orjinal listemizin i�ine giriyoruz b�t�n ��rencileri tarayarak ��renciye ula�mam�z� sa�layacak ��renci bilgisini ve ��rencisini iki boyutlu bir dizi �iftinde tutuyoruz.Bu s�rada her ��rencinin soyad�n� eklemeden �nce, ka� karakterden olu�tu�unu bir sonraki ��renci ile kar��la�t�rarak maxBoy de�i�keninde tutuyoruz ki, bu bizim radikste gereken elemanlar�n niteliklerini e�itlememiz i�in kullanaca��m�z de�i�ken.Fonksiyonun devam�nda b�t�n soyadlar�n son harfini al�p,Soyad�n uzunlu�u maxBoy a e�it olana kadar son harfi s�rekli ekliyoruz.Bu �ekilde b�t�n soyadlar�n uzunluklar� e�itlenmi� oluyor. Bundan sonraki k�s�mda en son karakterden ba�layarak soyadlar� birer birer s�ral�yoruz taki maxBoy de�eri s�f�ra e�it olana kadar.�ncelikle t�m soyadlar�n son karakterini g�z �n�ne al�yoruz, hepsi ayn� boyutta oldu�u i�in sorun ��km�yor. Sonra i�inde A varm� diye bak�yoruz varsa o soyada sahip ��renciyi en ba�a al�yoruz ,Daha sonra B ye ge�iyoruz. Bu i�lem soyadlar�n hepsi ilk harfine g�re yerle�inceye kadar s�rekli devam edecek. Tuttu�umuz index de�erinin amac� ise, e�er A-Z aras� harflerden biri bulunursa bu yer de�i�imine sebep olacak buda indexi 1 art�racak, ve index de�eri t�m soyadlar�n toplam say�s�na(��renci say�s�na) e�it olunca, bu art�k o anki kontrol edilen karakter i�in s�ralanabilecek bir ihtimal kalmad��� anlam�na gelir ve  bir sonraki karakteri kar��la�t�rmaya ba�lan�r.En sonunda bu tutulan de�erler siralanmis listesine eklenir ve liste ekrana yazd�r�l�r.
Yada K�saca:��renci bilgilerinden soyada gidilir. Soyadlarda max boy bulunur. �lk ��rencinin soyad�ndan ba�lan�r max boy olup olmad��� kontrol edilir son elemana kadar. Max boy olmayanlar� max boy e�itlenir. �lk harfini max boy olana kadar ilk harfe tekrarlayarak. Hepsi max boy oldukan sonra her bir soyad�n son harfinden ba�lay�p A dan Z ye kontrol edip yaz�l�r bu i�lem soyad�n ilk harfine gelene kadar yap�l�r. Sonunda s�ralanm�� �ekilde yeni ��renci d���m�ne atan�r ve ekrana yazd�r�l�r.*/
void Fonksiyonlar::RadiksSoyad()
{
	Yigin* orjinal = new Yigin(); // TODO: SadeceVeritabani Yonetim Sistemleri Alanlar
	Liste* siralanmis = new Liste();
	//listedeki soyadlar� vectore ekle
	Node* gezNode = orjinal->head;
	vector<pair<Ogrenci*, string>> soyad; //vector i�inde, ��renci pointeri ve ��renciye ait soyad �ifti tutuldu
	int i = 0, maxBoy = 0;
	//bu k�s�mda ��rencinin pointer ve soyad�n� listeden vector �iftimize at�yoruz
	while (gezNode != NULL)
	{
		soyad.push_back({ gezNode->ogr,gezNode->ogr->soyad });//��rencinin pointeri ve soyad� vectore eklendi
		if (i != 0)
			if (soyad[i - 1].second.size() > soyad[i].second.size()) // soyadlar�n karakter uzunlu�u kontrol�
				maxBoy = soyad[i - 1].second.size(); // soyadlardan aras�ndan maximum karakter say�s�n� tuttuk
		i++;
		gezNode = gezNode->sonraki;
	}
	//BU KISIM SOYADLARI E��T UZUNLU�A GET�REB�LMEK ���N
	for (size_t j = 0; j < soyad.size(); j++) // Her soyad�n sonuna son karakterini ekliyoruz
	{
		while (soyad[j].second.size() != maxBoy)
		{
			soyad[j].second.push_back(soyad[j].second.back()); //soyad�n sonuna maxboy olana kadar son harfi ekle
		}
	}

	//BU KISIM SOYADLARA G�RE SIRALAMAK ���N
	for (int k = maxBoy - 1; k >= 0; k--) //soyad�n maxsimum karakteri kadar s�ralama yap�lacak,s�ralama sondan ba�layacak
	{
		char kontrol = 'A';//her bir eleman i�in A harfi varm� kontrol et
		int index = 0; //soyadlar�n her biri yerine yerle�ince bu de�er 1 artacak
		while (kontrol != 'Z')
		{
			for (size_t j = 0; j < soyad.size(); j++)//her bir soyad� al
			{
				if (soyad[j].second[k] == kontrol)// e�er soyadda kontrol harfi varsa
				{
					swap(soyad[j], soyad[index]);	//yerlerini de�i�tir
					index++;	//s�rayla ba�a eklemek i�in gerekli index
				}

			}
			if (index == soyad.size() - 1) // e�er elemanlar�n hepsi yerle�tiyse di�er harfe ge�
				break;
			kontrol++;//e�er hala yerle�meyen varsa bir sonraki harfe ge�

		}

	}

	//��MD� SIRALANMI� VECTORU L�STEYE ATIP YAZDIRALIM
	for (size_t p = 0; p < soyad.size(); p++)
	{
		siralanmis->NodeEkle(p, soyad[p].first); //siralanmis ��rencileri yeni listeye ekle
	}

	//Yeni Listeyi Yazd�r
	cout << "\t\t\t\t ------> RAD�KS SIRALANMI� L�STE (SOYADA G�RE) <------ " << endl;
	siralanmis->ListeyiYazdir();
}

/*********************************************************************************************************
*			 A�A�IDAK� B�L�M MEN�DE KULLANILMAK �ZERE EKLEME, S�LME, BULMA G�B� ��LEMLER� ��ERMEKTED�R   *
*			      ORJ�NAL L�STEY� ETK�LEMEZ RAM �ZER�NDEK� B�LG�DE DE����KL�K YAPAR                      *
*********************************************************************************************************/

//Men�den �a�r�lmak �zere; klavyeden (kullan�c�lardan) al�nan bilgiye g�re y���n veya a�aca ��renci eklemesi yap�lmas�n� sa�lar
void Fonksiyonlar::KlavyedenEkle(string secim)
{
	string ad, soyad, yandal;
	int no, sinif;
	cout << "\t\t -L�tfen ��rencinin Ad�n� Giriniz --> ";
	cin >> ad;
	cout << "\t\t -L�tfen ��rencinin Soyad�n� Giriniz --> ";
	cin >> soyad;
	cout << "\t\t -L�tfen ��rencinin Numaras�n� Giriniz (6 HANEL�) --> ";
	cin >> no;
	cout << "\t\t -L�tfen ��rencinin S�n�f�n� Giriniz --> ";
	cin >> sinif;
	cout << "\t\t -L�tfen ��rencinin Yandal� varsa Giriniz (Yoksa, Yok yaz�n�z...) --> ";
	cin >> yandal;
	Ogrenci* o = new Ogrenci(ad, soyad, no, sinif, yandal);
	if (secim == Sabitler::DERS_KODU_VYVA)
		yigin->Push(o);
	else
		agac->AVLEkle(o);
}

//Men�den �a�r�lmak �zere; istenen listeyi al�p ekrana yazd�r�r. Temel listeler burada tutuldu�undan burada yaz�ld� 
void Fonksiyonlar::Yazdir(string ders) {
	if (ders == Sabitler::DERS_KODU_VYVA)
	{
		cout << "\t\t\t\t ------> " << Sabitler::DERS_ADI_VYVA << " DERS� SINIF L�STES� <------ " << endl;
		yigin->YiginiYazdir();
	}
	else
	{
		cout << "\t\t\t\t ------>" << Sabitler::DERS_ADI_VTYS << " DERS� SINIF L�STES� <------ " << endl;
		agac->AVLYazdir(agac->root, 1);
		cout << "\n" << endl;
	}
}

//Men�den �a�r�lmak �zere; kullan�c� ��renci silmeyi se�erse, al�nan ��renci ilgili listeden silinir 
void Fonksiyonlar::KlavyedenSil(string ders)
{
	if (ders == Sabitler::DERS_KODU_VYVA)
	{
		yigin->Pop();
	}
	else
	{
		bool kontrol = false;
		string soyad;
		cout << "\t\t -L�tfen Silinecek ��rencinin SOYADINI Giriniz --> ";
		cin >> soyad;
		Ogrenci* o = new Ogrenci();
		o->soyad = soyad;
		kontrol = agac->AVLSil(o);
		if (kontrol)
		{
			cout << "\t\t\t ---> S�LME �SLEM� BASARILI!\n" << endl;
			cout << "\t\t--> S�L�NEN OGRENC�N�N SOYADI : " << o->soyad << endl << endl;
		}
		else
			cout << "\t\t\t ---> S�LME ��LEM� BA�ARISIZ:(\n" << endl;
	}
}

/*Men�den �a�r�lmak �zere; numaras� girilen bir ��renci istenen listede bulunabilir */
void Fonksiyonlar::KlavyedenBul(string ders)
{
	//Derse g�re ��renciyi bul ve ekrana yazd�r	
	if (ders == Sabitler::DERS_KODU_VYVA)
	{
		yigin->Top();
	}
	else
	{
		string soyad;
		cout << "\t\t -L�tfen Bulunacak ��rencinin SOYADINI Giriniz --> ";
		cin >> soyad;
		Ogrenci* o = new Ogrenci();
		o->soyad = soyad;
		agac->AVLBul(o);
	}
}