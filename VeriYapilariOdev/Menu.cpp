#include "stdafx.h"
#include "Menu.h"
#include<conio.h>

Fonksiyonlar Fonks; //Fonksiyonlarý menüden kullanabilmek için nesne oluþturuldu.

Menu::Menu()
{
}

Menu::~Menu()
{
}

/*
Buradaki fonksiyonlar menü iþlemlerini gerçekleþtirmek içindir.
Kullanýcý çýkýþý seçene kadar döngülerle program sürekli çalýþmasý saðlanmýþtýr.
*/
void Menu::MenuListele()
{
	char dersSecim;
	do {
		cout << "___________________________________________________________" << endl;
		cout << "[__/ Alttaki menüden dilediðiniz dersi seçebilirsiniz  \\__]" << endl;
		cout << "|                                                         |" << endl;
		cout << "\\\t[1] " << Sabitler::DERS_ADI_VYVA << " Dersi Ýçin      /" << endl;
		cout << "/\t[2] " << Sabitler::DERS_ADI_VTYS << " Dersi Ýçin      \\" << endl;
		cout << "\\\t[q] ÇIKIÞ                                         /" << endl;
		cout << " \\_______________________________________________________/\n" << endl;
		dersSecim = _getch();
		if (dersSecim == 'q')
		{
			cout << "/--------------------------------------------------------------------------------------------\\" << endl;
			cout << "   | Compile'ýmý hatasýz, Deployment'ýmý çilesiz, Production'ýmý crash'sýz eyle yarabbim ! |" << endl;
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
		Fonks.ListeKontrol(Sabitler::DERS_KODU_VYVA); // listeleri kullanýma hazýrla
		char Lsecim;//liste seçim
		do {
			cout << "[-] BU MENÜ " << Sabitler::DERS_ADI_VYVA << " DERSÝ(STACK)'NÝN TEMEL ÖZELLÝKLERÝNÝ ÝÇERÝR ~~~~" << endl;
			cout << " [1] Derse Ögrenci Ekle (Push)" << endl;
			cout << " [2] Derse Kayýtlý Son Öðrenciyi Bul (Top) " << endl;
			cout << " [3] Derse Kayýtlý Son Öðrenciyi Çýkar (Pop) " << endl;
			cout << " [4] Sýnýf Listesini Yazdýr" << endl;
			cout << " [5] Ek Fonksiyonlar & Sýralamalar Ýçin" << endl;
			cout << " [6] Ýlk Orjinal Sýnýf Listesi" << endl;
			cout << " [0] Ders Seçim Menüsü Ýçin \n" << endl;
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
				system("cls");//ekraný temizle
				EkMenu();
				break;
			case '6':
				Fonks.ListeOlustur(Sabitler::DERS_KODU_VYVA);
				Fonks.Yazdir(Sabitler::DERS_KODU_VYVA);
				break;
			case '0':
				system("cls");//ekraný temizle
				break;
			default:cout << "Böyle bir seçenek mevcut degil \n";
				break;
			}
		} while (Lsecim != '0');
	}
	else if (secim == '2') // aðaç
	{
		Fonks.ListeKontrol(Sabitler::DERS_KODU_VTYS); // listeleri kullanýma hazýrla
		char Lsecim;//liste seçim
		do {
			cout << "[-] BU MENÜ " << Sabitler::DERS_ADI_VTYS << " DERSÝ(AGAC)'NÝN TEMEL ÖZELLÝKLERÝNÝ ÝÇERÝR ~~~" << endl;
			cout << " [1] Derse Ögrenci Ekle" << endl;
			cout << " [2] Derse Kayýtlý Bir Öðrenciyi Bul" << endl;
			cout << " [3] Dersten Bir Ögrenciyi Sil" << endl;
			cout << " [4] Sýnýf Listesini Yazdýr" << endl;
			cout << " [5] Ek Fonksiyonlar & Sýralamalar Ýçin" << endl;
			cout << " [6] Ýlk Orjinal Sýnýf Listesi" << endl;
			cout << " [0] Ders Seçim Menüsü Ýçin \n" << endl;
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
				system("cls");//ekraný temizle
				EkMenu();
				break;
			case '6':
				Fonks.ListeOlustur(Sabitler::DERS_KODU_VTYS);
				Fonks.Yazdir(Sabitler::DERS_KODU_VTYS);
				break;
			case '0':system("cls");//ekraný temizle
				break;
			default:cout << "Böyle bir seçenek mevcut degil\n";
				break;
			}
		} while (Lsecim != '0');
	}
	else
		cout << "\n****Böyle bir seçenek Mevcut Deðil!****\n" << endl;

}

void Menu::EkMenu()
{
	char secim; //ek menü secimi
	do {
		cout << " [1] EK FONKSÝYONLAR ÝÇÝN " << endl;
		cout << " [2] SIRALAMALAR ÝÇÝN " << endl;
		cout << " [0] BÝR ÜST MENÜ ÝÇÝN \n" << endl;
		secim = _getch();
		if (secim == '1')
		{
			char Fsecim;//fonksiyon seçimi
			do {
				cout << "[-] BU MENÜ EK FONKSÝYONLARI ÝÇERÝR ~~~" << endl;
				cout << " [1] HER ÝKÝ DERSÝ DE 1 den Fazla Alan Öðrenciler" << endl;
				cout << " [2] Sadece " << Sabitler::DERS_ADI_VTYS << " Dersini Alan Ögrenciler" << endl;
				cout << " [3] Her 2 Dersi De A ve B Grubu Olarak Ayýr" << endl;
				cout << " [4] Her 2 Dersi De Alan Ve Baþka Bölüm Öðrencileri Olanlarý Listele" << endl;
				cout << " [0] ÜST MENÜ ÝÇÝN \n" << endl;
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
					system("cls"); // ekraný temizle
					break;
				default:cout << "Böyle bir seçenek mevcut degil";
					break;
				}
			} while (Fsecim != '0');
		}
		else if (secim == '2')
		{
			char Ssecim;//SIRALAMA SEÇÝM
			do {
				cout << "[-] BU MENÜ SINIF LÝSTELERÝNÝ SIRALAMAK ÝÇÝNDÝR ~~~" << endl;
				cout << " [1] RADÝKS SIRALAMA Ýle Her 2 Dersi De Alan Öðrencileri SOYADLARINA Göre Sýrala" << endl;
				cout << " [2] SEÇMELÝ SIRALAMA ile SADECE " << Sabitler::DERS_ADI_VTYS << " Sýnýfýný, ADLARINA Göre " << endl;
				cout << " [3] HIZLI SIRALAMA Ýle " << Sabitler::DERS_ADI_VYVA << " Sýnýfýný NUMARAYA Göre Sýrala" << endl;
				cout << " [0] ÜST MENÜ ÝÇÝN \n" << endl;
				Ssecim = _getch();
				switch (Ssecim)
				{
				case '1':
					Fonks.RadiksSoyad();  //Radiks Sýralama Fonksiyonunu Çaðýr
					break;
				case '2':
					Fonks.SecmeliYazdir();//Seçmeli Sýralama Fonksiyonunu Çaðýr
					break;
				case '3':
					Fonks.SecmeliYazdir();//
					break;
				case '0':
					system("cls");
					break;
				default:cout << "Böyle bir seçenek mevcut degil";
					break;
				}
			} while (Ssecim != '0');
		}
		else
			cout << "****Böyle bir seçenek Mevcut Deðil!****" << endl;
	} while (secim != '0');
}