#include "stdafx.h"
#include "Menu.h"
#include<conio.h>

Fonksiyonlar Fonks; //Fonksiyonlar� men�den kullanabilmek i�in nesne olu�turuldu.

Menu::Menu()
{
}

Menu::~Menu()
{
}

/*
Buradaki fonksiyonlar men� i�lemlerini ger�ekle�tirmek i�indir.
Kullan�c� ��k��� se�ene kadar d�ng�lerle program s�rekli �al��mas� sa�lanm��t�r.
*/
void Menu::MenuListele()
{
	char dersSecim;
	do {
		cout << "___________________________________________________________" << endl;
		cout << "[__/ Alttaki men�den diledi�iniz dersi se�ebilirsiniz  \\__]" << endl;
		cout << "|                                                         |" << endl;
		cout << "\\\t[1] " << Sabitler::DERS_ADI_VYVA << " Dersi ��in      /" << endl;
		cout << "/\t[2] " << Sabitler::DERS_ADI_VTYS << " Dersi ��in      \\" << endl;
		cout << "\\\t[q] �IKI�                                         /" << endl;
		cout << " \\_______________________________________________________/\n" << endl;
		dersSecim = _getch();
		if (dersSecim == 'q')
		{
			cout << "/--------------------------------------------------------------------------------------------\\" << endl;
			cout << "   | Compile'�m� hatas�z, Deployment'�m� �ilesiz, Production'�m� crash's�z eyle yarabbim ! |" << endl;
			cout << "\\--------------------------------------------------------------------------------------------/" << endl;
			break;
		}
		TemelMenu(dersSecim);
	} while (true);

}

void Menu::TemelMenu(char secim)
{
	if (secim == '1') // stack
	{
		Fonks.ListeKontrol(Sabitler::DERS_KODU_VYVA); // listeleri kullan�ma haz�rla
		char Lsecim;//liste se�im
		do {
			cout << "[-] BU MEN� " << Sabitler::DERS_ADI_VYVA << " DERS�(STACK)'N�N TEMEL �ZELL�KLER�N� ��ER�R ~~~~" << endl;
			cout << " [1] Derse �grenci Ekle (Push)" << endl;
			cout << " [2] Derse Kay�tl� Son ��renciyi Bul (Top) " << endl;
			cout << " [3] Derse Kay�tl� Son ��renciyi ��kar (Pop) " << endl;
			cout << " [4] S�n�f Listesini Yazd�r" << endl;
			cout << " [5] Ek Fonksiyonlar & S�ralamalar ��in" << endl;
			cout << " [6] �lk Orjinal S�n�f Listesi" << endl;
			cout << " [0] Ders Se�im Men�s� ��in \n" << endl;
			Lsecim = _getch();
			switch (Lsecim)
			{
			case '1':
				Fonks.KlavyedenEkle(Sabitler::DERS_KODU_VYVA);
				break;
			case '2':
				Fonks.KlavyedenBul(Sabitler::DERS_KODU_VYVA);
				break;
			case '3':
				Fonks.KlavyedenSil(Sabitler::DERS_KODU_VYVA);
				break;
			case '4':
				Fonks.Yazdir(Sabitler::DERS_KODU_VYVA);
				break;
			case '5':
				system("cls");//ekran� temizle
				EkMenu();
				break;
			case '6':
				Fonks.ListeOlustur(Sabitler::DERS_KODU_VYVA);
				Fonks.Yazdir(Sabitler::DERS_KODU_VYVA);
				break;
			case '0':
				system("cls");//ekran� temizle
				break;
			default:cout << "B�yle bir se�enek mevcut degil \n";
				break;
			}
		} while (Lsecim != '0');
	}
	else if (secim == '2') // a�a�
	{
		Fonks.ListeKontrol(Sabitler::DERS_KODU_VTYS); // listeleri kullan�ma haz�rla
		char Lsecim;//liste se�im
		do {
			cout << "[-] BU MEN� " << Sabitler::DERS_ADI_VTYS << " DERS�(AGAC)'N�N TEMEL �ZELL�KLER�N� ��ER�R ~~~" << endl;
			cout << " [1] Derse �grenci Ekle" << endl;
			cout << " [2] Derse Kay�tl� Bir ��renciyi Bul" << endl;
			cout << " [3] Dersten Bir �grenciyi Sil" << endl;
			cout << " [4] S�n�f Listesini Yazd�r" << endl;
			cout << " [5] Ek Fonksiyonlar & S�ralamalar ��in" << endl;
			cout << " [6] �lk Orjinal S�n�f Listesi" << endl;
			cout << " [0] Ders Se�im Men�s� ��in \n" << endl;
			Lsecim = _getch();
			switch (Lsecim)
			{
			case '1':
				Fonks.KlavyedenEkle(Sabitler::DERS_KODU_VTYS);
				break;
			case '2':
				Fonks.KlavyedenBul(Sabitler::DERS_KODU_VTYS);
				break;
			case '3':
				Fonks.KlavyedenSil(Sabitler::DERS_KODU_VTYS);
				break;
			case '4':
				Fonks.Yazdir(Sabitler::DERS_KODU_VTYS);
				break;
			case '5':
				system("cls");//ekran� temizle
				EkMenu();
				break;
			case '6':
				Fonks.ListeOlustur(Sabitler::DERS_KODU_VTYS);
				Fonks.Yazdir(Sabitler::DERS_KODU_VTYS);
				break;
			case '0':system("cls");//ekran� temizle
				break;
			default:cout << "B�yle bir se�enek mevcut degil\n";
				break;
			}
		} while (Lsecim != '0');
	}
	else
		cout << "\n****B�yle bir se�enek Mevcut De�il!****\n" << endl;

}

void Menu::EkMenu()
{
	char secim; //ek men� secimi
	do {
		cout << " [1] EK FONKS�YONLAR ���N " << endl;
		cout << " [2] SIRALAMALAR ���N " << endl;
		cout << " [0] B�R �ST MEN� ���N \n" << endl;
		secim = _getch();
		if (secim == '1')
		{
			char Fsecim;//fonksiyon se�imi
			do {
				cout << "[-] BU MEN� EK FONKS�YONLARI ��ER�R ~~~" << endl;
				cout << " [1] HER �K� DERS� DE 1 den Fazla Alan ��renciler" << endl;
				cout << " [2] Sadece " << Sabitler::DERS_ADI_VTYS << " Dersini Alan �grenciler" << endl;
				cout << " [3] Her 2 Dersi De A ve B Grubu Olarak Ay�r" << endl;
				cout << " [4] Her 2 Dersi De Alan Ve Ba�ka B�l�m ��rencileri Olanlar� Listele" << endl;
				cout << " [0] �ST MEN� ���N \n" << endl;
				Fsecim = _getch();
				switch (Fsecim)
				{
				case '1':
					Fonks.AlttanAlanlar();
					break;
				case '2':
					Fonks.VeritabaniYonetimSistemleriAlanlar();
					break;
				case '3':
					Fonks.VeritabaniYonetimSistemleriGrupAyir();
					Fonks.VeriYapilariveAlgoritmalarGrupAyir();
					break;
				case '4':
					Fonks.EEMOgrenciListe();
					break;
				case '0':
					system("cls"); // ekran� temizle
					break;
				default:cout << "B�yle bir se�enek mevcut degil";
					break;
				}
			} while (Fsecim != '0');
		}
		else if (secim == '2')
		{
			char Ssecim;//SIRALAMA SE��M
			do {
				cout << "[-] BU MEN� SINIF L�STELER�N� SIRALAMAK ���ND�R ~~~" << endl;
				cout << " [1] RAD�KS SIRALAMA �le Her 2 Dersi De Alan ��rencileri SOYADLARINA G�re S�rala" << endl;
				cout << " [2] SE�MEL� SIRALAMA ile SADECE " << Sabitler::DERS_ADI_VTYS << " S�n�f�n�, ADLARINA G�re " << endl;
				cout << " [3] HIZLI SIRALAMA �le " << Sabitler::DERS_ADI_VYVA << " S�n�f�n� NUMARAYA G�re S�rala" << endl;
				cout << " [0] �ST MEN� ���N \n" << endl;
				Ssecim = _getch();
				switch (Ssecim)
				{
				case '1':
					Fonks.RadiksSoyad();  //Radiks S�ralama Fonksiyonunu �a��r
					break;
				case '2':
					Fonks.SecmeliYazdir();//Se�meli S�ralama Fonksiyonunu �a��r
					break;
				case '3':
					Fonks.SecmeliYazdir();//
					break;
				case '0':
					system("cls");
					break;
				default:cout << "B�yle bir se�enek mevcut degil";
					break;
				}
			} while (Ssecim != '0');
		}
		else
			cout << "****B�yle bir se�enek Mevcut De�il!****" << endl;
	} while (secim != '0');
}