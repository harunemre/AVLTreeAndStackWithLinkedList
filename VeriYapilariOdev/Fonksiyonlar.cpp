#include "stdafx.h"
#include "Fonksiyonlar.h"
Ders VeritabaniYonetimSistemleri = Ders(Sabitler::DERS_ADI_VTYS, Sabitler::DERS_KODU_VTYS, 3, "vtys.txt"); //Dersi Oluþtur, 3.Sýnýf Dersi
Ders VeriYapilariVeAlgoritmalar = Ders(Sabitler::DERS_ADI_VYVA, Sabitler::DERS_KODU_VYVA, 2, "vyva.txt");//Dersi Oluþtur, 2.Sýnýf Dersi
Yigin* yigin = new Yigin(); // Veri Yapilarý ve Algoritmalar Alan öðrencileri Tutacak Liste
AVLAgaci* agac = new AVLAgaci(); //Veritabani Yönetim Sistemleri Dersini alanlarý tutacak aðaç
Liste* eemliler = new Liste(); //eem alan öðrencileri tutacak
Liste* ikiders = new Liste(); //heapaðacýný tutacak

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
Program içinde gerekli yerlerde liste oluþturulacaðý zaman;
öðrencileri metin belgesinden okuyup çeken OgrencileriAl fonksiyonunu kullanarak yýðýn veya aðacý oluþturur.
VeritabaniYonetimSistemleri ve VeriYapilariVeAlgoritmalar deðiþkenleri ders sýnýfýnýn nesnelerini temsil ederken
yýðýn ve agac kavramlarý ise uygulama içinde genel olarak eriþebilir olan ana yýðýn ve aðacý temsil etmektedir.
Diðer Fonksiyonlarýn hepsi bu yýðýn ve agac'ý kullanarak kendi bünyelerinde gerekli iþlemleri yapmaktadýr.
*/
void Fonksiyonlar::ListeOlustur(string kod)
{
	if (kod == Sabitler::DERS_KODU_VYVA)
		yigin = VeriYapilariVeAlgoritmalar.YiginOlustur();
	else
		agac = VeritabaniYonetimSistemleri.AgacOlustur();
}

// TODO: Aciklama düzenlenecek
/*
Bu fonksiyonda 2.sorunun a þýkkýnda istenilen üzerine, Her iki derside alttan alan öðrenciler listelenmiþtir.Ýlk olarak bu iþlem için foknsiyon içinde baðýmsýz bir liste oluþturulmuþtur. Daha sora Bilgisayar Aðlarý Sýnýf Listesini Ýçeren liste'nin en baþýndan baþlanarak, her bir düðümdeki öðrencinin sinifi B.Aðlarý dersinin ders yýlý olan 1.sýnýf ile karþýlaþtýrýlmýþtýr. Eðer öðrenci 1.sýnýftan büyükse bu dersi alttan alýyor demektir, bundan sonra bu öðrenci AVLAgacinda listesi tutulan Bilgisayar Mimarisi Dersinin listesinde aranmýþtýr. Eðer sonuç olumlu ise bu öðrencinin o derside alttan alýp almadýðý ders yili ve öðrencinin sýnýfý kýyaslanarak kontrol edilmiþtir.Eðer sonuç tekrar olumlu çýkarsa bu öðrenci Alttan Alanlar listesine eklenmiþtir. Bu iþlem liste sonuna kadar tüm öðrencilere uygulanacaktýr.En sonuçta ortaya çýkan liste boþ deðilse liste yazdýrýlacak,yoksa liste boþ mesajý dönderilecektir.*/
void Fonksiyonlar::AlttanAlanlar()
{
	Liste* altalan = new Liste();
	//ilk olarak oluþturulmamýþ sinif listesi varsa oluþturuyoruz
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta arýyoruz	
	int i = 0; // listeye eklenme sýrasý
	while (!yigin->BosMu())
	{
		Node* geznode = yigin->Pop(); // listenin baþýndan baþla
		if (
			(geznode->ogr->sinif > VeriYapilariVeAlgoritmalar.yil)& // Ogrencinin sinifi dersin yilindan büyükse alttan alýyor demektir
			(agac->AVLBul(geznode->ogr) != NULL)&// eðer bu öðrenci aðaçta varsa
			(geznode->ogr->sinif > VeritabaniYonetimSistemleri.yil)
			)// BMimarisini alttan alýyorsa
		{
			altalan->NodeEkle(i, geznode->ogr);//listeye ekle
			i++;
		}
	}
	if (altalan->BosMu()) // liste boþþsa bilgilendir
		cout << "\t\t\t\t  ----------> ÝKÝ DERSÝDE AYNI ANDA ALTTAN ALAN ÖÐRENCÝ YOKTUR!<----------" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> ÝKÝ DERSÝDE AYNI ANDA ALTTAN ALANLAR  <----------" << endl;
		altalan->ListeyiYazdir();// yoksa listeyi yazdýr
	}
}

// TODO: Aciklama düzenlenecek
/* AÇIKLAMASI: Bu Fonksiyon için öncelikle yeni bir liste oluþturuyoruz. Bu listede bizim istediðimiz öðrencileri tutacaðýz.Bilgisayar Aðlarý sýnýf listesinin tutulduðu ana listemizin ilk düðümünden baþlýyoruz. Bu düðümdeki öðrenciyi Bilgisayar Mimarisi Listesinin tutulduðu aðaçta arýyoruz. Eðer öðrenci burada yoksa bu öðrenciyi SADECE BÝLGÝSAYAR AÐLARI ALAN Öðrenciler listemize ekliyoruz.Daha sonra listeyi yazdýrýyoruz */
Liste* Fonksiyonlar::VeritabaniYonetimSistemleriAlanlar()
{
	Liste* vtysAlanlar = new Liste();
	//ilk olarak oluþturulmamýþ sinif listesi varsa oluþturuyoruz
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);
	int index = 0;
	// Daha sonra BAglarindaki ogrencinin sinifi > dersyilindan onu agacta arýyoruz
	while (!yigin->BosMu())
	{
		Node* yiginEleman = yigin->Pop();
		if (agac->AVLBul(yiginEleman->ogr) == NULL)// eðer bu öðrenci aðaçta yoksa
			vtysAlanlar->NodeEkle(index++, yiginEleman->ogr);//listeye ekle
	};

	if (vtysAlanlar->BosMu()) // liste boþþsa bilgilendir
		cout << "\t\t\t\t  ! SADECE " << Sabitler::DERS_ADI_VTYS << " ALAN ÖÐRENCÝ YOKTUR !" << endl;
	else
	{
		cout << "\t\t\t\t  ----------> SADECE " << Sabitler::DERS_ADI_VTYS << " DERSÝ ALANLAR  <----------" << endl;
		vtysAlanlar->ListeyiYazdir();// yoksa listeyi yazdýr
	}
	return vtysAlanlar;
}

// TODO: Aciklama düzenlenecek
/*AÇIKLAMASI : Bu fonksiyonda Bilgisayar Aðlarý listesini A ve B grubu olarak parçalamamýz isteniyor. A Grubunda Soyadý A-K arasýnda olanlar, B Grubunda ise soyadý L-Z arasýnda olanlar olacaktýr. 2 adet liste oluþturuyoruz birisi Agrup diðeri ise Bgrup olacak þekilde.Bilgisayar Aðlarý Dersininin Sýnýf Listesini içeren ana listenin ilk elemanýndan baþlýyoruz.Bu Elemanýn içindeki öðrencinin soyadýnýn ÝLK HARFÝ A-K arasýnda ise A grubuna yoksa B grubuna ait listeye ekliyoruz. Bunu ana listenin tüm elemanlarý için uyguluyoruz ve en sonda iki ayrý listemizi yazdýrýyoruz.*/
void Fonksiyonlar::VeritabaniYonetimSistemleriGrupAyir()
{
	ListeKontrol(Sabitler::DERS_KODU_VTYS);

	//Gerekli listeleri oluþtur
	Liste* Agrup = new Liste();
	Liste* Bgrup = new Liste();
	//listede gezmeye baþla	
	VeritabaniYonetimSistemleriGrupEkle(agac->root, Agrup, Bgrup, 0, 0);

	// A Grubunu yazdir
	if (Agrup->BosMu())
		cout << "A Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> " << Sabitler::DERS_ADI_VTYS << " DERSÝ - A GRUBU  <----------" << endl;
		Agrup->ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup->BosMu())
		cout << "B Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> " << Sabitler::DERS_ADI_VTYS << " DERSÝ - B GRUBU  <----------" << endl;
		Bgrup->ListeyiYazdir();
	}

}

// TODO: aciklama düzenlenecek
void Fonksiyonlar::VeriYapilariveAlgoritmalarGrupAyir()
{
	ListeKontrol(Sabitler::DERS_KODU_VYVA);

	//Gerekli listeleri oluþtur
	Liste Agrup, Bgrup = Liste();

	int i = 0, j = 0; // eklerken tutlacak indisler
	while (!yigin->BosMu())
	{
		Node* gezNode = yigin->Pop();
		string soyad = gezNode->ogr->soyad; // soyad karakterini al
		char ch = soyad.at(0); // soyad karakterini chara at
		if (ch >= 'A' && ch <= 'K') // eðer soyadý bu harfler arasýndaysa a grubuna ekle		
			Agrup.NodeEkle(i++, gezNode->ogr);
		else
			Bgrup.NodeEkle(j++, gezNode->ogr); // deðilse B grubuna ekle		
	}
	// A Grubunu yazdir
	if (Agrup.BosMu())
		cout << "A Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t  ----------> "<< Sabitler::DERS_ADI_VYVA <<" DERSÝ - A GRUBU  <----------" << endl;
		Agrup.ListeyiYazdir();
	}

	//B grubunu Yazdir
	if (Bgrup.BosMu())
		cout << "B Grubunda Ögrenci Mevcut Degil";
	else
	{
		cout << "\t\t\t\t ----------> " << Sabitler::DERS_ADI_VYVA << " DERSÝ - B GRUBU  <----------" << endl;
		Bgrup.ListeyiYazdir();
	}

}

/*EEMOgrenciListe AÇIKLAMA : Bilgisayar Aðlarý ve Bilgisayar Mimarisi derslerinin en az birini alan ve elektronik mühendisliði bölümü öðrencisi olan öðrencileri listelemek istiyoruz.Bunun öncelikle ana listemiz gibi baþka fonksiyonlardan eriþilebilecek bir liste oluþturuyoruz.Eemliler adlý bu listeyi dýþarda tutmamýzýn amacý bu listeye aðaçta gezerken ihtiyacýmýz olmasýdýr.Öncelikle Bigisayar Aðlarý Dersinin listesini tutan ana listenin en baþýndaki öðrenciyi alýyoruz, burda öðrencinin öncelikle numarasýnýn ilk harfini tespit ediyoruz.Bu numara eðer 3 ile baþlýyorsa veya Yandalý "Elektrik Elektronik Mühendisliði" ise bu öðrenciyi eemliler listesine ekliyoruz.Bunu liste bitene kadar tekrarlýyoruz.Ondan sonra Agaçta gezme fonksiyonunu çaðýrýp, eriþebilirliði açýk olan eemliler listemizde bu fonksiyon ile deðiþiklik yapýyoruz. En sonda ise bu listeyi yazdýrýyoruz.*/
void Fonksiyonlar::EEMOgrenciListe()
{
	// boþ liste olmasýna karþý kontrol
	ListeKontrol(Sabitler::DERS_KODU_VTYS);
	ListeKontrol(Sabitler::DERS_KODU_VYVA);

	Node* geznode = yigin->head;
	while (geznode != NULL)
	{
		//öðrenci numarasýnýn ilk numarasýný al bölüm belirlemek için
		int digit = geznode->ogr->NumaraTespit(geznode->ogr->ogrNo);
		//eðer elektrik bölümü öðrencisiyse,agactan gelen listede varmý kontrol et
		if (digit == 3 || geznode->ogr->yandal == "Elektrik Elektronik Mühendisligi")
			eemliler->NodeEkle(0, geznode->ogr); // kriteri saðlýyorsa listeye ekle
		geznode = geznode->sonraki; // sonraki düðüme geç
	}
	AgacGez(agac->root);
	cout << "Bilgisayar Aðlarý ve Bilgisayar Mimarisi derslerinin en az birini alan EEMLÝLER";
	eemliler->ListeyiYazdir();
}

// TODO: Aciklama düzenlenecek
void Fonksiyonlar::VeritabaniYonetimSistemleriGrupEkle(AVLNode* kok, Liste* listeA, Liste* listeB, int i, int j)
{
	if (kok == NULL)
		return;
	VeritabaniYonetimSistemleriGrupEkle(kok->sol, listeA, listeB, i, j); //en sola git
	if (TekMi(kok->ogr->ogrNo))//aðacýn elemaný eemlimi		
		listeA->NodeEkle(i++, kok->ogr); // öðrenciyi ekle
	else listeB->NodeEkle(j++, kok->ogr);
	VeritabaniYonetimSistemleriGrupEkle(kok->sag, listeA, listeB, i, j);
}

/*
AVL aðacýnda içkök gezerek aðaç içinde kontrol yapýlýr.
Aðacýn en soluna gidip ordaki öðrencinin numarasýnýn ilk harfininin 3 olup olmadýðýný veya varsa öðrencinin yandalýnýn elektrik elektronik mühendisliði olup olmadýðýný kontrol ediyor.Eðer öðrenci bu kriterleri saðlýyorsa bu öðrenciyi eemliler listesinde arýyor.Eðer bu öðrenci eemliler listesinde mevcut DEÐÝLSE öðrenciyi eemliler listesine ekliyor.Tüm aðaç boyunca içkök kuralýnca bunu yaparak aðacý taramýþ oluyor.
*/
void Fonksiyonlar::AgacGez(AVLNode* kok)
{
	if (kok == NULL)
		return;
	AgacGez(kok->sol); //en sola git
	int digit = kok->ogr->NumaraTespit(kok->ogr->ogrNo); //bölüm bilgisi için
	if (digit == 3 || kok->ogr->yandal == "Elektrik Elektronik Mühendisligi")//aðacýn elemaný eemlimi
		if (eemliler->NodeBul(kok->ogr) == NULL) // eðer öðrenci B.Aðlarýnda yoksa
			eemliler->NodeEkle(0, kok->ogr); // öðrenciyi ekle
	AgacGez(kok->sag);
}

/* Bu fonksiyon yukarýda bahssettiðimiz liste oluþtur fonksiyonlarýný kullanarak. Eðer ANA LÝSTE ve AÐACIMIZ Boþ ise program yürütülemeyeceðinden, bunlarý kontrol edip, boþ ise dolduruyor.*/
void Fonksiyonlar::ListeKontrol(string secim)
{
	// Menü arasý geçiþlerde, Listelerin oluþturulmadýðý durumlar için kontrol
	if (secim == Sabitler::DERS_KODU_VYVA && yigin->BosMu())
		ListeOlustur(Sabitler::DERS_KODU_VYVA);
	else if (secim == Sabitler::DERS_KODU_VTYS && agac->BosMu())
		ListeOlustur(Sabitler::DERS_KODU_VTYS);
}

//Aðacýn bir elemaný alýnýp aðacý baþtan sona gezerken en soldaki elemaný tüm aðaçla karþýlaþtýrýlýr ve en küçük olaný bulunup listeye eklenir
void Fonksiyonlar::SecmeliSirala(AVLNode* kok) // en son buraya dön
{
	if (kok == NULL)
		return;
	SecmeliSirala(kok->sol); //en sola git
	kok->ogr->OgrenciYaz();
	SecmeliSirala(kok->sag);
}

/*Secmeli Sýralanan Aðacý Yazdýrýr*/
void Fonksiyonlar::SecmeliYazdir()
{
	SecmeliSirala(agac->root);
}

/* AÇIKLAMASI : Radiks sýralama kuralý gereði, ilk önce boþ bir liste oluþturuyoruz bu listeye yukarýda daha önceden yapmýþ olduðumuz Sadece Bilgisayar Aðlarý Alanlarýn listesini atýyoruz.Onun haricinde birde elimizde sýraladýktan sonra koyacaðýmýz bir boþ liste oluþturuyoruz.Dolu olan orjinal listemizin içine giriyoruz bütün öðrencileri tarayarak öðrenciye ulaþmamýzý saðlayacak öðrenci bilgisini ve öðrencisini iki boyutlu bir dizi çiftinde tutuyoruz.Bu sýrada her öðrencinin soyadýný eklemeden önce, kaç karakterden oluþtuðunu bir sonraki öðrenci ile karþýlaþtýrarak maxBoy deðiþkeninde tutuyoruz ki, bu bizim radikste gereken elemanlarýn niteliklerini eþitlememiz için kullanacaðýmýz deðiþken.Fonksiyonun devamýnda bütün soyadlarýn son harfini alýp,Soyadýn uzunluðu maxBoy a eþit olana kadar son harfi sürekli ekliyoruz.Bu þekilde bütün soyadlarýn uzunluklarý eþitlenmiþ oluyor. Bundan sonraki kýsýmda en son karakterden baþlayarak soyadlarý birer birer sýralýyoruz taki maxBoy deðeri sýfýra eþit olana kadar.Öncelikle tüm soyadlarýn son karakterini göz önüne alýyoruz, hepsi ayný boyutta olduðu için sorun çýkmýyor. Sonra içinde A varmý diye bakýyoruz varsa o soyada sahip öðrenciyi en baþa alýyoruz ,Daha sonra B ye geçiyoruz. Bu iþlem soyadlarýn hepsi ilk harfine göre yerleþinceye kadar sürekli devam edecek. Tuttuðumuz index deðerinin amacý ise, eðer A-Z arasý harflerden biri bulunursa bu yer deðiþimine sebep olacak buda indexi 1 artýracak, ve index deðeri tüm soyadlarýn toplam sayýsýna(öðrenci sayýsýna) eþit olunca, bu artýk o anki kontrol edilen karakter için sýralanabilecek bir ihtimal kalmadýðý anlamýna gelir ve  bir sonraki karakteri karþýlaþtýrmaya baþlanýr.En sonunda bu tutulan deðerler siralanmis listesine eklenir ve liste ekrana yazdýrýlýr.
Yada Kýsaca:Öðrenci bilgilerinden soyada gidilir. Soyadlarda max boy bulunur. Ýlk öðrencinin soyadýndan baþlanýr max boy olup olmadýðý kontrol edilir son elemana kadar. Max boy olmayanlarý max boy eþitlenir. Ýlk harfini max boy olana kadar ilk harfe tekrarlayarak. Hepsi max boy oldukan sonra her bir soyadýn son harfinden baþlayýp A dan Z ye kontrol edip yazýlýr bu iþlem soyadýn ilk harfine gelene kadar yapýlýr. Sonunda sýralanmýþ þekilde yeni öðrenci düðümüne atanýr ve ekrana yazdýrýlýr.*/
void Fonksiyonlar::RadiksSoyad()
{
	Yigin* orjinal = new Yigin(); // TODO: SadeceVeritabani Yonetim Sistemleri Alanlar
	Liste* siralanmis = new Liste();
	//listedeki soyadlarý vectore ekle
	Node* gezNode = orjinal->head;
	vector<pair<Ogrenci*, string>> soyad; //vector içinde, öðrenci pointeri ve öðrenciye ait soyad çifti tutuldu
	int i = 0, maxBoy = 0;
	//bu kýsýmda öðrencinin pointer ve soyadýný listeden vector çiftimize atýyoruz
	while (gezNode != NULL)
	{
		soyad.push_back({ gezNode->ogr,gezNode->ogr->soyad });//öðrencinin pointeri ve soyadý vectore eklendi
		if (i != 0)
			if (soyad[i - 1].second.size() > soyad[i].second.size()) // soyadlarýn karakter uzunluðu kontrolü
				maxBoy = soyad[i - 1].second.size(); // soyadlardan arasýndan maximum karakter sayýsýný tuttuk
		i++;
		gezNode = gezNode->sonraki;
	}
	//BU KISIM SOYADLARI EÞÝT UZUNLUÐA GETÝREBÝLMEK ÝÇÝN
	for (size_t j = 0; j < soyad.size(); j++) // Her soyadýn sonuna son karakterini ekliyoruz
	{
		while (soyad[j].second.size() != maxBoy)
		{
			soyad[j].second.push_back(soyad[j].second.back()); //soyadýn sonuna maxboy olana kadar son harfi ekle
		}
	}

	//BU KISIM SOYADLARA GÖRE SIRALAMAK ÝÇÝN
	for (int k = maxBoy - 1; k >= 0; k--) //soyadýn maxsimum karakteri kadar sýralama yapýlacak,sýralama sondan baþlayacak
	{
		char kontrol = 'A';//her bir eleman için A harfi varmý kontrol et
		int index = 0; //soyadlarýn her biri yerine yerleþince bu deðer 1 artacak
		while (kontrol != 'Z')
		{
			for (size_t j = 0; j < soyad.size(); j++)//her bir soyadý al
			{
				if (soyad[j].second[k] == kontrol)// eðer soyadda kontrol harfi varsa
				{
					swap(soyad[j], soyad[index]);	//yerlerini deðiþtir
					index++;	//sýrayla baþa eklemek için gerekli index
				}

			}
			if (index == soyad.size() - 1) // eðer elemanlarýn hepsi yerleþtiyse diðer harfe geç
				break;
			kontrol++;//eðer hala yerleþmeyen varsa bir sonraki harfe geç

		}

	}

	//ÞÝMDÝ SIRALANMIÞ VECTORU LÝSTEYE ATIP YAZDIRALIM
	for (size_t p = 0; p < soyad.size(); p++)
	{
		siralanmis->NodeEkle(p, soyad[p].first); //siralanmis öðrencileri yeni listeye ekle
	}

	//Yeni Listeyi Yazdýr
	cout << "\t\t\t\t ------> RADÝKS SIRALANMIÞ LÝSTE (SOYADA GÖRE) <------ " << endl;
	siralanmis->ListeyiYazdir();
}

/*********************************************************************************************************
*			 AÞAÐIDAKÝ BÖLÜM MENÜDE KULLANILMAK ÜZERE EKLEME, SÝLME, BULMA GÝBÝ ÝÞLEMLERÝ ÝÇERMEKTEDÝR   *
*			      ORJÝNAL LÝSTEYÝ ETKÝLEMEZ RAM ÜZERÝNDEKÝ BÝLGÝDE DEÐÝÞÝKLÝK YAPAR                      *
*********************************************************************************************************/

//Menüden çaðrýlmak üzere; klavyeden (kullanýcýlardan) alýnan bilgiye göre yýðýn veya aðaca öðrenci eklemesi yapýlmasýný saðlar
void Fonksiyonlar::KlavyedenEkle(string secim)
{
	string ad, soyad, yandal;
	int no, sinif;
	cout << "\t\t -Lütfen öðrencinin Adýný Giriniz --> ";
	cin >> ad;
	cout << "\t\t -Lütfen öðrencinin Soyadýný Giriniz --> ";
	cin >> soyad;
	cout << "\t\t -Lütfen öðrencinin Numarasýný Giriniz (6 HANELÝ) --> ";
	cin >> no;
	cout << "\t\t -Lütfen öðrencinin Sýnýfýný Giriniz --> ";
	cin >> sinif;
	cout << "\t\t -Lütfen öðrencinin Yandalý varsa Giriniz (Yoksa, Yok yazýnýz...) --> ";
	cin >> yandal;
	Ogrenci* o = new Ogrenci(ad, soyad, no, sinif, yandal);
	if (secim == Sabitler::DERS_KODU_VYVA)
		yigin->Push(o);
	else
		agac->AVLEkle(o);
}

//Menüden çaðrýlmak üzere; istenen listeyi alýp ekrana yazdýrýr. Temel listeler burada tutulduðundan burada yazýldý 
void Fonksiyonlar::Yazdir(string ders) {
	if (ders == Sabitler::DERS_KODU_VYVA)
	{
		cout << "\t\t\t\t ------> " << Sabitler::DERS_ADI_VYVA << " DERSÝ SINIF LÝSTESÝ <------ " << endl;
		yigin->YiginiYazdir();
	}
	else
	{
		cout << "\t\t\t\t ------>" << Sabitler::DERS_ADI_VTYS << " DERSÝ SINIF LÝSTESÝ <------ " << endl;
		agac->AVLYazdir(agac->root, 1);
		cout << "\n" << endl;
	}
}

//Menüden çaðrýlmak üzere; kullanýcý öðrenci silmeyi seçerse, alýnan öðrenci ilgili listeden silinir 
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
		cout << "\t\t -Lütfen Silinecek öðrencinin SOYADINI Giriniz --> ";
		cin >> soyad;
		Ogrenci* o = new Ogrenci();
		o->soyad = soyad;
		kontrol = agac->AVLSil(o);
		if (kontrol)
		{
			cout << "\t\t\t ---> SÝLME ÝSLEMÝ BASARILI!\n" << endl;
			cout << "\t\t--> SÝLÝNEN OGRENCÝNÝN SOYADI : " << o->soyad << endl << endl;
		}
		else
			cout << "\t\t\t ---> SÝLME ÝÞLEMÝ BAÞARISIZ:(\n" << endl;
	}
}

/*Menüden çaðrýlmak üzere; numarasý girilen bir öðrenci istenen listede bulunabilir */
void Fonksiyonlar::KlavyedenBul(string ders)
{
	//Derse göre öðrenciyi bul ve ekrana yazdýr	
	if (ders == Sabitler::DERS_KODU_VYVA)
	{
		yigin->Top();
	}
	else
	{
		string soyad;
		cout << "\t\t -Lütfen Bulunacak öðrencinin SOYADINI Giriniz --> ";
		cin >> soyad;
		Ogrenci* o = new Ogrenci();
		o->soyad = soyad;
		agac->AVLBul(o);
	}
}