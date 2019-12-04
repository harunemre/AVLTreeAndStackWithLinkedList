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

// iki integer de�erden en b�y�k olan� bulup d�nd�r�r
int AVLAgaci::Max(int a, int b) {
	return (a < b) ? b : a;
}

// En soldaki eleman� bulup d�nd�r�r
AVLNode* AVLAgaci::EnKucuk(AVLNode* dugum)
{
	if (dugum != NULL)
		while (dugum->sol != NULL)
			dugum = dugum->sol;
	return dugum;
}

// A�a�ta eleman yoksa k�k=NULL ise true de�ilse false d�nd�r�r
bool AVLAgaci::BosMu()
{
	return root == NULL;
}

/*
AVL Agacinda, parametre olarak verilen ��renciyi, ��rencinin soyad�na g�re arayan fonksiyondur.
Her bir d���me geldi�inde �grenci soyadlar�n� kar��la�t�r�r.
E�er soyad d���mdekinden k���kse sola gider, b�y�kse sa�a gider.
D���m� bulana kadar veya gidebilece�i d���m kalmayana kadar bu i�lem devam eder.
Bulursa d���m�n pointerini, bulamazsa da NULL d�nderir
*/
AVLNode* AVLAgaci::AVLBul(Ogrenci* o)
{
	bool bulunduMu = false;
	AVLNode* GeziciNode = root;
	if (root == NULL)
		return root; //a�a� bo�ssa
	else //bo� de�ilse
	{
		while (GeziciNode != NULL) // a�ac� gezmek i�in gezicinode olu�turuldu
		{
			if (o->soyad == GeziciNode->ogr->soyad)// ��renciyi bulursan d�ng�den ��k	
			{				
				bulunduMu = true;
				break;
			}			
			else if (o->soyad > GeziciNode->ogr->soyad)//girilen ��renci no,d���mdekinden b�y�kse sa� d���me git
				GeziciNode = GeziciNode->sag;
			else if (o->soyad < GeziciNode->ogr->soyad)//girilen ��renci no,d���mdekinden k���kse sol d���me git
				GeziciNode = GeziciNode->sol;
		}
	}
	if (bulunduMu)
	{
		cout << "\t\tBulunan ��renci:" << endl;
		GeziciNode->ogr->OgrenciYaz();
	}
	else cout << "\t\t ["<< o->soyad << "] soyad�na sahip bir ��renci bulunamad� ..." << endl;
	return GeziciNode;
}

/*
Verilen ��renciyi AVL a�ac�na eklemeyi sa�lar.
Mant�k AVLBul fonksiyonu ile nerdeyse ayn�d�r.
�ndexleme ��renci soyad�na g�redir.
E�er a�a�ta hi� eleman yoksa k�k olarak en ba�a ��renciyi ekler.
E�er a�a�ta eleman varsa ilk d���me gelir; girilen ��renci soyad�: d���mdeki �grenci soyad�ndan k���kse sola gider, b�y�kse sa�a gider.
NULL yani bo� d���m buldu�unda oraya yeni d���m eklenir.
A�a�ta sa�da b�y�k elemanlar solda ise k���kler bulunur.
AVL a�ac� oldu�u i�inse a�ac�n denge bozulma ihtimali vard�r.
Bunun i�in d���m eklendikten sonra, eklenen d���m dengekontrol fonksiyonuna g�nderilir.
Ekleme ba�ar�l� ise true d�ner...
*/
bool AVLAgaci::AVLEkle(Ogrenci* o)
{
	AVLNode* YeniNode = new AVLNode(o);
	if (root == NULL) // a�a� bo�sa ba�a ekle
	{
		root = YeniNode;
		return true;
	}
	else // de�ilse yerini bul
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
Ald��� d���m�n sa� ve sol �ocuklar�n�n y�ksekli�ini al�p d�nd�r�r.
Mesela bir d���m�m sol y�ksekli�ine bakmak i�in d�g�m->sol diye parametre yollan�rsa ve d���m mevcut de�ilse -1 d�nderir
e�er orda d���m mevcut ise d���m�n sahip oldu�u y�kseklik de�erini d�nderir.
Bu fonksiyon denge i�lemlerinde s�k�a kullan�l�r
*/
int AVLAgaci::YukHesap(AVLNode* dugum)
{
	if (dugum == NULL)
		return -1;
	else
		return dugum->yukseklik;
}

/*
AVL A�ac�n�n �nemli noktalar�ndan denge kontrol fonksiyonun temel fonksiyonudur.
AVL A�ac�n� di�er a�a�lardan ay�ran solcocuk-sa�cocuk yuksekli�i -1,0,1 de�erlerinden farkl� olursa a�ac�n dengesinin bozulmas�d�r.
Her ekleme veya silme yap�ld���nda her d���m i�in bu �� de�erden birinin olmas� sa�lanmal�d�r.
Bu fonksiyonda �ncelikle kontrol d���m� mevcuttur ve dengeyi bozan d���md�r.
Bu d���m� rotasyon fonksiyonlar�na g�ndererek dengeleme sa�lanmaktad�r.
Bu fonksiyona yollanan d���m de�eri: [A�ACA EKLENEN DE�ER], [A�A�TAN S�L�NEN DE�ER�N PARENT�] VEYA [D�N�� YAPILAN KR�T�K D���M] olabilir.
B�ylece de�i�iklik olan d���mden denge kontrol�ne ba�lan�lm�� olur.
Gelen d���m de�erinden ba�lay�p, YUKARI do�ru , d���m�n sol y�ksekli�i ve sa� y�ksekli�inin maxsimumum de�erinin 1 fazlas�
al�narak o d���m�n yuksekli�i hesaplan�r.
Denge Fakt�r� ise bir d���m�n sol ve sa� d���m�n�n y�kseklikleri fark�d�r.
Bu de�er -1,0,1 den farkl� de�er olursa kontrol d���m�, denge fakt�r� bu de�erlerden farkl� olan d���me e�itlenir.
Sorunlu d���m tespit edildi�i i�in d�ng�den ��k�l�r.
E�er kontrol d���m� tespit edildiyse a�ac�n rotasyon ile dengelenmesi gerekir,
bunun i�in AVLDengele fonksiyonunda gerekli rotasyon tespit edilip uygulan�r.
*/
void AVLAgaci::DengeKontrol(AVLNode* dugum)
{
	AVLNode* kontrol = NULL; // sorunlu d���m� tutacak dugum
	AVLNode* sonraki = NULL;
	while (dugum != NULL)
	{
		dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag)); //o anki d���m�n y�kseklik hesab�
		dugum->dengeFaktor = (YukHesap(dugum->sol) - YukHesap(dugum->sag)); //o anki d���m�n dengefakt�r� hesab�
		if (dugum->dengeFaktor > 1 || dugum->dengeFaktor < -1)
		{
			kontrol = dugum; // hatal� d���m� tespit et
			break; // burada d�ng�den ��kmazsak, kontrol d���m� hatal� bulunabilir
		}


		dugum = dugum->parent; // denge fakt�r� bozulmad�k�a yukar� do�ru y�kseklik ve denge fakt�r� hesab� devam eder
	}
	if (kontrol != NULL)
		AVLDengele(kontrol);
}

/*
Bu fonksiyona yukar�da denge fakt�r� -1,0,1 den farkl� olup sorunlu olarak tespit edilen d���m gelir.
Burada denge fakt�r�n�n de�erine g�re , sol ve sa� y�ksekliklere g�re rotasyonlar belirlenip uygulan�r.
A�a��da kodlar�n yan�nda a��klamas� yap�lm��t�r.
Sol-Sa� yapt���m�z i�in dengefak > 1 sola bask�nl�k vard�r.
dengefak <-1 ise sa� tarafta bask�nl�k vard�r.
Ayr�ca d�n��ler yap�ld�ktan sonra, d�n��e sebep olan d�g�m, rotasyon fonksiyonlar�ndan geri d�ner ve
o d�g�mden yukar� do�ru tekrar denge kontrol� yap�l�r.
*/
void AVLAgaci::AVLDengele(AVLNode* dugum)
{
	if (dugum->dengeFaktor > 1) //Sol taraf uzun, sa�a tek d�n�� veya Sol sa� d�n�� gerekir
		if (YukHesap(dugum->sol->sol) >= YukHesap(dugum->sol->sag)) // solun solun daha b�y�kse o yap�l�r
			DengeKontrol(SagaTekDonus(dugum));

		else //solun sa�� b�y�kse buras� yap�l�r
			DengeKontrol(SolSagDonus(dugum));

	if (dugum->dengeFaktor < -1) // de�er negatif yani sa� taraf daha uzun, sola tek d�n�� veya sa� sol d�n�� gereklidir
		if (YukHesap(dugum->sag->sag) >= YukHesap(dugum->sag->sol)) // sa��n sa�� uzunsa sola tek d�n��
			DengeKontrol(SolaTekDonus(dugum));

		else//de�ilse sapsol d�n�� yap�l�r
			DengeKontrol(SagSolDonus(dugum));

}

/*
AVLSil fonksiyonundan e�er d���m tek �ocu�a sahipse veya hi� �ocu�u yoksa buraya yollan�r.
Bulunan d���m�n parentine ula��lmas� i�in bu fonksiyon ayr�ld�.
Bu fonksiyonda yollanan d���mde e�er tek �ocuk varsa �ocu�un taraf� tespit edilir,
sonra bu �ocu�un atan�n sol koluna m� yoksa sa� koluna m� ba�l� oldu�u tespit edilir.
��nk� d���m�n tek �ocu�u olunca �ocu�un d���m�n atas�na ba�lanmas� gerekir.
Kol tespit edildikten sonra �ocuk ataya ba�lan�r.
D���mlerin parentleri de�i�tirilir.
�stenilen d���m silinir.
E�er hi� cocuk yoksa �ocu�a giden pointerin tespit edilip NULL de�eri atanmas� gerekiyor
aksi takdirde o k�s�m haf�zadan silindi�i i�in dengeleme fonksiyonunda sorun yarat�r.
Daha sonra d���m silinir.
*/
bool AVLAgaci::AVLSilTek(AVLNode* bulunan) //tek �ocuk veya hi� �ocuk yoksa buras� �al���r
{
	AVLNode* ata = bulunan->parent;
	AVLNode* tespit = NULL;
	tespit = (bulunan->sag != NULL) ? bulunan->sag : bulunan->sol; // �ocu�un taraf�n� tespit et
	if (tespit != NULL) // e�er tek �ocu�u varsa
	{
		// �ocuk atan�n hangi koluna ba�l�
		if (ata->sag == bulunan)
			ata->sag = tespit; // �ocu�u ataya ba�la

		else if (ata->sol == bulunan) // �ocu�u atan�n soluna ba�la
			ata->sol = tespit; // �ocu�u ataya ba�la

		tespit->parent = ata; // parentini de�i�tir
	}
	else //hi� �ocuk yok ise
	{
		(ata->sag == bulunan) ? ata->sag = NULL : ata->sol = NULL; //�ocu�a giden pointere null ata
	}
	delete bulunan;//bulunan nodu sil,
	DengeKontrol(ata);
	return true; // i�lem ba�ar�l�
}

/*
D���m�n iki �ocu�u varsa devreye girer.
�ncelikle silinecek d���m bulunur.
Daha sonra silinecek d���m�n sa��ndaki ENK���K d���m bulunur.
Bu en k���k d���m�n ogrencisi ile silinecek d���m�n �grencisi de�i�tirilir.
Daha sonra Enkucuk olarak tespit edilen (yani alttaki d���m) silme fonksiyonuna g�nderilir.
��nk� tek �ocuk veya hi� �ocuk olmama ihtimali vard�r.
Bu y�zden fonksiyonu ikiye ayr�ld�.*/
bool AVLAgaci::AVLSil(Ogrenci* o)
{
	//�ncelikle silinecek d���m� bul
	AVLNode* bulunan = AVLBul(o);

	if (bulunan != NULL) // silinecek d���m mevcutsa
	{
		//iki �ocu�u varsa
		if (bulunan->sag != NULL && bulunan->sol != NULL)
		{
			AVLNode* enkucuk = EnKucuk(bulunan->sag);
			bulunan->ogr = enkucuk->ogr;// bulunan ile en kucuk eleman�n de�erlerini yer de�i�tir
			return AVLSilTek(enkucuk);// 1. ve 2. durum var m� diye kontrol et
		}
		else // tek �ocuk varsa veya hi� �ocu�u yoksa
			return AVLSilTek(bulunan);
	}

	return false; // silinecek dugum bulunamad�
}


/*
Denge fonksiyonun en �nemli k�sm� d�n�� fonksiyonlar�d�r.
�ncelikle sola d�n�� yap�laca�� i�in sagcocuk isminde bir d���m olu�turulur ve d���m�n sa�� at�l�r.
D�n��ten sonra SA� �OCU�UN SOLUNA, D���M�N SA� KOLU ba�lanaca�� i�in, Sa� �ocu�un sol de�eri ge�ici bir d���mde tutulur.
Daha sonra k�k de�i�imlerini yap�l�r.
Burada 2 Durum mevcuttur: d�nd�r�lecek d���m k�kse veya de�ilse
1) E�er d�nd�r�lecek d���m a�ac�n k�k�ne e�itse k�k ve sa� co�uk yer de�i�tirir.
2) E�er d�nd�r�lecek d���m a�ac�n k�k� de�ilse ebeveyninin hangi koluna ba�l� oldu�unun tespit edilmesi gerekir.
��nk� d�nd�r�lecek d���m, ebeveyninin hangi koluna ba�l�ysa d���m�n sagcocu�u, ebeveyninin o koluna ba�lan�r.
Daha sonra d�n��� tamamlamak i�in sagcocugun soluna dugum ba�lan�r ve dugumun sa� kolunada ba�ta tutulan ge�ici node ba�lan�r.
B�ylece D�n�� tamamlanm�� olur.
Ek olarak a�a�ta dengeyi sa�lamak i�in laz�m olan parentler de�i�tirilmelidir.
Daha sonra d�nen k�sm�n y�kseklikleri g�ncellenir.
Bu fonksiyondan d�nen d���m tekrardan denge kontrole gidecektir.
*/
AVLNode* AVLAgaci::SolaTekDonus(AVLNode* dugum)
{
	AVLNode* sagcocuk = dugum->sag; // cocu�u tut
	AVLNode* gecici = sagcocuk->sol; // sol �ocu�un ta��nacak �ocu�unu tut
	//**Root De�i�imi
	if (dugum->parent == NULL) // e�er root d�nd�r�lecekse buras� �al���r
		root = sagcocuk;
	else // d�nd�relecek eleman root de�ilse
		if (dugum->parent->sag == dugum)//sag kola m� ba�l�
			dugum->parent->sag = sagcocuk;
		else // sol kola m� ba�l�
			dugum->parent->sol = sagcocuk;
	sagcocuk->sol = dugum;
	dugum->sag = gecici;
	//**Parent de�i�imleri
	if (gecici != NULL)
		gecici->parent = dugum;
	sagcocuk->parent = dugum->parent;
	dugum->parent = sagcocuk;
	//**Y�kseklikleri g�ncelle
	dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag));
	sagcocuk->yukseklik = 1 + Max(YukHesap(sagcocuk->sol), YukHesap(sagcocuk->sag));
	return dugum;
}

//  Yukarida anlat�lan solatek d�n���n tam tersi i�lem
AVLNode* AVLAgaci::SagaTekDonus(AVLNode* dugum)
{
	AVLNode* solcocuk = dugum->sol; // cocu�u tut
	AVLNode* gecici = solcocuk->sag; // sol �ocu�un ta��nacak �ocu�unu tut
	//**Root De�i�imi
	if (dugum->parent == NULL) // e�er root d�nd�r�lecekse buras� �al���r
		root = solcocuk;
	else // d�nd�relecek eleman root de�ilse
		if (dugum->parent->sol == dugum) // sol kola m� ba�l�
			dugum->parent->sol = solcocuk;
		else // sa� kola m� ba�l�
			dugum->parent->sag = solcocuk;

	solcocuk->sag = dugum;
	dugum->sol = gecici;
	//**Parent de�i�imleri 
	if (gecici != NULL)
		gecici->parent = dugum;
	solcocuk->parent = dugum->parent;
	dugum->parent = solcocuk;
	//**Y�kseklikleri g�ncelle
	dugum->yukseklik = 1 + Max(YukHesap(dugum->sol), YukHesap(dugum->sag));
	solcocuk->yukseklik = 1 + Max(YukHesap(solcocuk->sol), YukHesap(solcocuk->sag));
	return dugum;
}

// Sorunlu d���m�n �nce solundaki d���me sola tek d�n�� sonra d���m�n kendisine sa�a tek d�n�� uygulan�r.
AVLNode* AVLAgaci::SolSagDonus(AVLNode* dugum)
{
	SolaTekDonus(dugum->sol);
	return SagaTekDonus(dugum);
}

// Sorunlu d���m�n sa��ndaki d���me sa�a tek d�n�� uygulan�r sonra d���m�n kendisine sola tek d�n�� uygulan�r.
AVLNode* AVLAgaci::SagSolDonus(AVLNode* dugum)
{
	SagaTekDonus(dugum->sag);
	return SolaTekDonus(dugum);
}

// Recursive yap�da avl a�ac� temel �zelli�i olan i�k�k gezme i�lemi
void AVLAgaci::Ickok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	Ickok(kok->sol); //en sola git, solu yaz
	cout << kok->ogr->soyad << "  "; //k�k� yaz
	Ickok(kok->sag);//sa�� yaz
}

/* Recursive yap�da avl a�ac� temel �zelli�i olan sonra gezme i�lemi*/
void AVLAgaci::Sonrakok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	Sonrakok(kok->sol);
	Sonrakok(kok->sag);
	cout << kok->ogr->soyad << "  ";
}

/* Recursive yap�da avl a�ac� temel �zelli�i olan �nce gezme i�lemi*/
void AVLAgaci::Oncekok(AVLNode* kok)
{
	if (kok == NULL)
		return;
	cout << kok->ogr->soyad << "  ";
	Oncekok(kok->sol);
	Oncekok(kok->sag);
}

/*
AVL A�ac� stack yap�s�ndan farkl� oldu�u i�in, a�a�ta gezmek stack e g�re farkl�d�r.
En pratik yolu recursive olarak fonksiyon ile gezmek oldu�undan a�a��da rek�rsif fonksiyon kullan�lm��t�r.
kok->sag gitti�i yap�da rek�rsif fonksiyonda yaprak kalmayana kadar yani kok=NULL olana kadar en sa�a gider.
Sonra kalan hepsini toplayarak geriye do�ru gelir.
Ayn�s� a�a��daki sol k�s�m i�inde ge�erlidir.
Bu a�ac� gezme i�lemi olurken a�ac� yazd�r�l�r
.*/
void AVLAgaci::AVLYazdir(AVLNode* kok, int level)
{	
	if (kok != NULL)
	{
		AVLYazdir(kok->sag, level + 1);
		cout << endl;
		if (kok == root)
			cout << "K�K -> ";
		for (int i = 0; i < level && kok != root; i++)
			cout << "        ";
		cout << kok->ogr->soyad;
		AVLYazdir(kok->sol, level + 1);
	}
}
