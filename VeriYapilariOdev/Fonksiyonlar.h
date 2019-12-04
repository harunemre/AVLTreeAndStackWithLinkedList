#pragma once
#include <utility>
#include "Ders.h"
#include "Sabitler.h"
class Fonksiyonlar
{
public:
	void ListeKontrol(string secim);
	void ListeOlustur(string kod);
	void AlttanAlanlar();
	Liste* VeritabaniYonetimSistemleriAlanlar();
	void VeritabaniYonetimSistemleriGrupAyir();
	void VeriYapilariveAlgoritmalarGrupAyir();
	void EEMOgrenciListe();
	void AgacGez(AVLNode* kok);
	void VeritabaniYonetimSistemleriGrupEkle(AVLNode* kok, Liste* listeA, Liste* listeB, int i, int j);
	void HizliSirala(AVLNode* kok);
	void SecmeliSirala(AVLNode* kok);
	void SecmeliYazdir();
	void RadiksSoyad();
	/*AÞAÐIDAKÝ FONKSÝYONLAR MENÜDEKÝ ÝÞLEVSEL ÝÞLEMLER ÝÇÝNDÝR*/
	void KlavyedenEkle(string secim);
	void Yazdir(string ders);
	void KlavyedenBul(string ders);
	void KlavyedenSil(string ders);
	bool TekMi(int no);
	Fonksiyonlar();
	~Fonksiyonlar();
};

