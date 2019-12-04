#include "stdafx.h"
#include "AVLAgaci.h"

// Constructor
AVLAgaci::AVLAgaci()
{
	root = NULL;
}

// Destructor
AVLAgaci::~AVLAgaci()
{
}

// iki integer deðerden en büyük olaný bulup döndürür
int AVLAgaci::Max(int a, int b) {
	return (a < b) ? b : a;
}

// En soldaki elemaný bulup döndürür
AVLNode* AVLAgaci::EnKucuk(AVLNode* dugum)
{
	if (dugum != NULL)
		while (dugum->sol != NULL)
			dugum = dugum->sol;
	return dugum;
}

// Aðaçta eleman yoksa kök=NULL ise true deðilse false döndürür
bool AVLAgaci::BosMu()
{
	return root == NULL;
}

/*
AVL Agacinda, parametre olarak verilen öðrenciyi, öðrencinin soyadýna göre arayan fonksiyondur.
Her bir düðüme geldiðinde ögrenci soyadlarýný karþýlaþtýrýr.
Eðer soyad düðümdekinden küçükse sola gider, büyükse saða gider.
Düðümü bulana kadar veya gidebileceði düðüm kalmayana kadar bu iþlem devam eder.
Bulursa düðümün pointerini, bulamazsa da NULL dönderir
*/
AVLNode* AVLAgaci::AVLBul(Ogrenci* o)
{
	bool bulunduMu = false;
	AVLNode* GeziciNode = root;
	if (root == NULL)
		return root; //aðaç boþssa
	else //boþ deðilse
	{
		while (GeziciNode != NULL) // aðacý gezmek için gezicinode oluþturuldu
		{
			if (o->soyad == GeziciNode->ogr->soyad)// öðrenciyi bulursan döngüden çýk	
			{				
				bulunduMu = true;
				break;
			}			
			else if (o->soyad > GeziciNode->ogr->soyad)//girilen öðrenci no,düðümdekinden büyükse sað düðüme git
				GeziciNode = GeziciNode->sag;
			else if (o->soyad < GeziciNode->ogr->soyad)//girilen öðrenci no,düðümdekinden küçükse sol düðüme git
				GeziciNode = GeziciNode->sol;
		}
	}
	if (bulunduMu)
	{
		cout << "\t\tBulunan öðrenci:" << endl;
		GeziciNode->ogr->OgrenciYaz();
	}
	else cout << "\t\t ["<< o->soyad << "] soyadýna sahip bir öðrenci bulunamadý ..." << endl;
	return GeziciNode;
}

/*
Verilen öðrenciyi AVL aðacýna eklemeyi saðlar.
Mantýk AVLBul fonksiyonu ile nerdeyse aynýdýr.
Ýndexleme öðrenci soyadýna göredir.
Eðer aðaçta hiç eleman yoksa kök olarak en baþa öðrenciyi ekler.
Eðer aðaçta eleman varsa ilk düðüme gelir; girilen öðrenci soyadý: düðümdeki ögrenci soyadýndan küçükse sola gider, büyükse saða gider.
NULL yani boþ düðüm bulduðunda oraya yeni düðüm eklenir.
Aðaçta saðda büyük elemanlar solda ise küçükler bulunur.
AVL aðacý olduðu içinse aðacýn denge bozulma ihtimali vardýr.
Bunun için düðüm eklendikten sonra, eklenen düðüm dengekontrol fonksiyonuna gönderilir.
Ekleme baþarýlý ise true döner...
*/
bool AVLAgaci::AVLEkle(Ogrenci* o)
{
	AVLNode* YeniNode = new AVLNode(o);
	if (root == NULL) // aðaç boþsa baþa ekle
	{
		root = YeniNode;
		return true;
	}
	else // deðilse yerini bul
	{
		AVLNode* GeziciNode = root;
		while (GeziciNode != NULL)
		{
			if (o->soyad > (GeziciNode->ogr->soyad))
			{
				if (GeziciNode->sag == NULL)//yeni dugum 'u yaprak olarak ekle
				{
					YeniNode->parent = GeziciNode;// her dugum ebeveyninin pointerini tutacak
					GeziciNode->sag = YeniNode;
					break;
				}
				else
					GeziciNode = GeziciNode->sag;
			}
			else
			{
				if (GeziciNode->sol == NULL)//yeni dugum 'u yaprak olarak ekle
				{
					YeniNode->parent = GeziciNode;// her dugum ebeveyninin pointerini tutacak
					GeziciNode->sol = YeniNode;
					break;
				}

				else
					GeziciNode = GeziciNode->sol;
			}
		}
		DengeKontrol(YeniNode);
		return true;
	}
	return false;
}

/*
Aldýðý düðümün sað ve sol çocuklarýnýn yüksekliðini alýp döndürür.
Mesela bir düðümüm sol yüksekliðine bakmak için dügüm->sol diye parametre yollanýrsa ve düðüm mevcut deðilse -1 dönderir
eðer orda düðüm mevcut ise düðümün sahip olduðu yükseklik deðerini dönderir.
Bu fonksiyon denge iþlemlerinde sýkça kullanýlýr
*/
int AVLAgaci::YukHesap(AVLNode* dugum)
{
	if (dugum == NULL)
		return -1;
	else
		return dugum->yukseklik;
}

/*
AVL Aðacýnýn önemli noktalarýndan denge kontrol fonksiyonun temel fonksiyonudur.
AVL Aðacýný diðer aðaçlardan ayýran solcocuk-saðcocuk yuksekliði -1,0,1 deðerlerinden farklý olursa aðacýn dengesinin bozulmasýdýr.
Her ekleme veya silme yapýldýðýnda her düðüm için bu üç deðerden birinin olmasý saðlanmalýdýr.
Bu fonksiyonda öncelikle kontrol düðümü mevcuttur ve dengeyi bozan düðümdür.
Bu düðümü rotasyon fonksiyonlarýna göndererek dengeleme saðlanmaktadýr.
Bu fonksiyona yollanan düðüm deðeri: [AÐACA EKLENEN DEÐER], [AÐAÇTAN SÝLÝNEN DEÐERÝN PARENTÝ] VEYA [DÖNÜÞ YAPILAN KRÝTÝK DÜÐÜM] olabilir.
Böylece deðiþiklik olan düðümden denge kontrolüne baþlanýlmýþ olur.
Gelen düðüm deðerinden baþlayýp, YUKARI doðru , düðümün sol yüksekliði ve sað yüksekliðinin maxsimumum deðerinin 1 fazlasý
alýnarak o düðümün yuksekliði hesaplanýr.
Denge Faktörü ise bir düðümün sol ve sað düðümünün yükseklikleri farkýdýr.
Bu deðer -1,0,1 den farklý deðer olursa kontrol düðümü, denge faktörü bu deðerlerden farklý olan düðüme eþitlenir.
Sorunlu düðüm tespit edildiði için döngüden çýkýlýr.
Eðer kontrol düðümü tespit edildiyse aðacýn rotasyon ile dengelenmesi gerekir,
bunun için AVLDengele fonksiyonunda gerekli rotasyon tespit edilip uygulanýr.
*/
void AVLAgaci::DengeKontrol(AVLNode* dugum)
{
	AVLNode* kontrol = NULL; // sorunlu düðümü tutacak dugum
	AVLNode* sonraki = NULL;
	while (dugum != NULL)
	{
		dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag)); //o anki düðümün yükseklik hesabý
		dugum->dengeFaktor = (YukHesap(dugum->sol) - YukHesap(dugum->sag)); //o anki düðümün dengefaktörü hesabý
		if (dugum->dengeFaktor > 1 || dugum->dengeFaktor < -1)
		{
			kontrol = dugum; // hatalý düðümü tespit et
			break; // burada döngüden çýkmazsak, kontrol düðümü hatalý bulunabilir
		}


		dugum = dugum->parent; // denge faktörü bozulmadýkça yukarý doðru yükseklik ve denge faktörü hesabý devam eder
	}
	if (kontrol != NULL)
		AVLDengele(kontrol);
}

/*
Bu fonksiyona yukarýda denge faktörü -1,0,1 den farklý olup sorunlu olarak tespit edilen düðüm gelir.
Burada denge faktörünün deðerine göre , sol ve sað yüksekliklere göre rotasyonlar belirlenip uygulanýr.
Aþaðýda kodlarýn yanýnda açýklamasý yapýlmýþtýr.
Sol-Sað yaptýðýmýz için dengefak > 1 sola baskýnlýk vardýr.
dengefak <-1 ise sað tarafta baskýnlýk vardýr.
Ayrýca dönüþler yapýldýktan sonra, dönüþe sebep olan dügüm, rotasyon fonksiyonlarýndan geri döner ve
o dügümden yukarý doðru tekrar denge kontrolü yapýlýr.
*/
void AVLAgaci::AVLDengele(AVLNode* dugum)
{
	if (dugum->dengeFaktor > 1) //Sol taraf uzun, saða tek dönüþ veya Sol sað dönüþ gerekir
		if (YukHesap(dugum->sol->sol) >= YukHesap(dugum->sol->sag)) // solun solun daha büyükse o yapýlýr
			DengeKontrol(SagaTekDonus(dugum));

		else //solun saðý büyükse burasý yapýlýr
			DengeKontrol(SolSagDonus(dugum));

	if (dugum->dengeFaktor < -1) // deðer negatif yani sað taraf daha uzun, sola tek dönüþ veya sað sol dönüþ gereklidir
		if (YukHesap(dugum->sag->sag) >= YukHesap(dugum->sag->sol)) // saðýn saðý uzunsa sola tek dönüþ
			DengeKontrol(SolaTekDonus(dugum));

		else//deðilse sapsol dönüþ yapýlýr
			DengeKontrol(SagSolDonus(dugum));

}

/*
AVLSil fonksiyonundan eðer düðüm tek çocuða sahipse veya hiç çocuðu yoksa buraya yollanýr.
Bulunan düðümün parentine ulaþýlmasý için bu fonksiyon ayrýldý.
Bu fonksiyonda yollanan düðümde eðer tek çocuk varsa çocuðun tarafý tespit edilir,
sonra bu çocuðun atanýn sol koluna mý yoksa sað koluna mý baðlý olduðu tespit edilir.
Çünkü düðümün tek çocuðu olunca çocuðun düðümün atasýna baðlanmasý gerekir.
Kol tespit edildikten sonra çocuk ataya baðlanýr.
Düðümlerin parentleri deðiþtirilir.
Ýstenilen düðüm silinir.
Eðer hiç cocuk yoksa çocuða giden pointerin tespit edilip NULL deðeri atanmasý gerekiyor
aksi takdirde o kýsým hafýzadan silindiði için dengeleme fonksiyonunda sorun yaratýr.
Daha sonra düðüm silinir.
*/
bool AVLAgaci::AVLSilTek(AVLNode* bulunan) //tek çocuk veya hiç çocuk yoksa burasý çalýþýr
{
	AVLNode* ata = bulunan->parent;
	AVLNode* tespit = NULL;
	tespit = (bulunan->sag != NULL) ? bulunan->sag : bulunan->sol; // çocuðun tarafýný tespit et
	if (tespit != NULL) // eðer tek çocuðu varsa
	{
		// çocuk atanýn hangi koluna baðlý
		if (ata->sag == bulunan)
			ata->sag = tespit; // çocuðu ataya baðla

		else if (ata->sol == bulunan) // çocuðu atanýn soluna baðla
			ata->sol = tespit; // çocuðu ataya baðla

		tespit->parent = ata; // parentini deðiþtir
	}
	else //hiç çocuk yok ise
	{
		(ata->sag == bulunan) ? ata->sag = NULL : ata->sol = NULL; //çocuða giden pointere null ata
	}
	delete bulunan;//bulunan nodu sil,
	DengeKontrol(ata);
	return true; // iþlem baþarýlý
}

/*
Düðümün iki çocuðu varsa devreye girer.
Öncelikle silinecek düðüm bulunur.
Daha sonra silinecek düðümün saðýndaki ENKÜÇÜK düðüm bulunur.
Bu en küçük düðümün ogrencisi ile silinecek düðümün ögrencisi deðiþtirilir.
Daha sonra Enkucuk olarak tespit edilen (yani alttaki düðüm) silme fonksiyonuna gönderilir.
Çünkü tek çocuk veya hiç çocuk olmama ihtimali vardýr.
Bu yüzden fonksiyonu ikiye ayrýldý.*/
bool AVLAgaci::AVLSil(Ogrenci* o)
{
	//öncelikle silinecek düðümü bul
	AVLNode* bulunan = AVLBul(o);

	if (bulunan != NULL) // silinecek düðüm mevcutsa
	{
		//iki çocuðu varsa
		if (bulunan->sag != NULL && bulunan->sol != NULL)
		{
			AVLNode* enkucuk = EnKucuk(bulunan->sag);
			bulunan->ogr = enkucuk->ogr;// bulunan ile en kucuk elemanýn deðerlerini yer deðiþtir
			return AVLSilTek(enkucuk);// 1. ve 2. durum var mý diye kontrol et
		}
		else // tek çocuk varsa veya hiç çocuðu yoksa
			return AVLSilTek(bulunan);
	}

	return false; // silinecek dugum bulunamadý
}


/*
Denge fonksiyonun en önemli kýsmý dönüþ fonksiyonlarýdýr.
Öncelikle sola dönüþ yapýlacaðý için sagcocuk isminde bir düðüm oluþturulur ve düðümün saðý atýlýr.
Dönüþten sonra SAÐ ÇOCUÐUN SOLUNA, DÜÐÜMÜN SAÐ KOLU baðlanacaðý için, Sað çocuðun sol deðeri geçici bir düðümde tutulur.
Daha sonra kök deðiþimlerini yapýlýr.
Burada 2 Durum mevcuttur: döndürülecek düðüm kökse veya deðilse
1) Eðer döndürülecek düðüm aðacýn köküne eþitse kök ve sað coçuk yer deðiþtirir.
2) Eðer döndürülecek düðüm aðacýn kökü deðilse ebeveyninin hangi koluna baðlý olduðunun tespit edilmesi gerekir.
Çünkü döndürülecek düðüm, ebeveyninin hangi koluna baðlýysa düðümün sagcocuðu, ebeveyninin o koluna baðlanýr.
Daha sonra dönüþü tamamlamak için sagcocugun soluna dugum baðlanýr ve dugumun sað kolunada baþta tutulan geçici node baðlanýr.
Böylece Dönüþ tamamlanmýþ olur.
Ek olarak aðaçta dengeyi saðlamak için lazým olan parentler deðiþtirilmelidir.
Daha sonra dönen kýsmýn yükseklikleri güncellenir.
Bu fonksiyondan dönen düðüm tekrardan denge kontrole gidecektir.
*/
AVLNode* AVLAgaci::SolaTekDonus(AVLNode* dugum)
{
	AVLNode* sagcocuk = dugum->sag; // cocuðu tut
	AVLNode* gecici = sagcocuk->sol; // sol çocuðun taþýnacak çocuðunu tut
	//**Root Deðiþimi
	if (dugum->parent == NULL) // eðer root döndürülecekse burasý çalýþýr
		root = sagcocuk;
	else // döndürelecek eleman root deðilse
		if (dugum->parent->sag == dugum)//sag kola mý baðlý
			dugum->parent->sag = sagcocuk;
		else // sol kola mý baðlý
			dugum->parent->sol = sagcocuk;
	sagcocuk->sol = dugum;
	dugum->sag = gecici;
	//**Parent deðiþimleri
	if (gecici != NULL)
		gecici->parent = dugum;
	sagcocuk->parent = dugum->parent;
	dugum->parent = sagcocuk;
	//**Yükseklikleri güncelle
	dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag));
	sagcocuk->yukseklik = 1 + Max(YukHesap(sagcocuk->sol), YukHesap(sagcocuk->sag));
	return dugum;
}

//  Yukarida anlatýlan solatek dönüþün tam tersi iþlem
AVLNode* AVLAgaci::SagaTekDonus(AVLNode* dugum)
{
	AVLNode* solcocuk = dugum->sol; // cocuðu tut
	AVLNode* gecici = solcocuk->sag; // sol çocuðun taþýnacak çocuðunu tut
	//**Root Deðiþimi
	if (dugum->parent == NULL) // eðer root döndürülecekse burasý çalýþýr
		root = solcocuk;
	else // döndürelecek eleman root deðilse
		if (dugum->parent->sol == dugum) // sol kola mý baðlý
			dugum->parent->sol = solcocuk;
		else // sað kola mý baðlý
			dugum->parent->sag = solcocuk;

	solcocuk->sag = dugum;
	dugum->sol = gecici;
	//**Parent deðiþimleri 
	if (gecici != NULL)
		gecici->parent = dugum;
	solcocuk->parent = dugum->parent;
	dugum->parent = solcocuk;
	//**Yükseklikleri güncelle
	dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag));
	solcocuk->yukseklik = 1 + Max(YukHesap(solcocuk->sol), YukHesap(solcocuk->sag));
	return dugum;
}

// Sorunlu düðümün önce solundaki düðüme sola tek dönüþ sonra düðümün kendisine saða tek dönüþ uygulanýr.
AVLNode* AVLAgaci::SolSagDonus(AVLNode* dugum)
{
	SolaTekDonus(dugum->sol);
	return SagaTekDonus(dugum);
}

// Sorunlu düðümün saðýndaki düðüme saða tek dönüþ uygulanýr sonra düðümün kendisine sola tek dönüþ uygulanýr.
AVLNode* AVLAgaci::SagSolDonus(AVLNode* dugum)
{
	SagaTekDonus(dugum->sag);
	return SolaTekDonus(dugum);
}

// Recursive yapýda avl aðacý temel özelliði olan içkök gezme iþlemi
void AVLAgaci::Ickok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	Ickok(kok->sol); //en sola git, solu yaz
	cout << kok->ogr->soyad << "  "; //kökü yaz
	Ickok(kok->sag);//saðý yaz
}

/* Recursive yapýda avl aðacý temel özelliði olan sonra gezme iþlemi*/
void AVLAgaci::Sonrakok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	Sonrakok(kok->sol);
	Sonrakok(kok->sag);
	cout << kok->ogr->soyad << "  ";
}

/* Recursive yapýda avl aðacý temel özelliði olan önce gezme iþlemi*/
void AVLAgaci::Oncekok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	cout << kok->ogr->soyad << "  ";
	Oncekok(kok->sol);
	Oncekok(kok->sag);
}

/*
AVL Aðacý stack yapýsýndan farklý olduðu için, aðaçta gezmek stack e göre farklýdýr.
En pratik yolu recursive olarak fonksiyon ile gezmek olduðundan aþaðýda rekürsif fonksiyon kullanýlmýþtýr.
kok->sag gittiði yapýda rekürsif fonksiyonda yaprak kalmayana kadar yani kok=NULL olana kadar en saða gider.
Sonra kalan hepsini toplayarak geriye doðru gelir.
Aynýsý aþaðýdaki sol kýsým içinde geçerlidir.
Bu aðacý gezme iþlemi olurken aðacý yazdýrýlýr
.*/
void AVLAgaci::AVLYazdir(AVLNode* kok, int level)
{	
	if (kok != NULL)
	{
		AVLYazdir(kok->sag, level + 1);
		cout << endl;
		if (kok == root)
			cout << "KÖK -> ";
		for (int i = 0; i < level && kok != root; i++)
			cout << "        ";
		cout << kok->ogr->soyad;
		AVLYazdir(kok->sol, level + 1);
	}
}
