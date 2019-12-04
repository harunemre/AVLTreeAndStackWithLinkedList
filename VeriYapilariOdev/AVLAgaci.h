#pragma once
#include "AVLNode.h"
class AVLAgaci
{
public:AVLNode* root;
public:
	int Max(int a, int b);
	bool BosMu();
	AVLNode* EnKucuk(AVLNode* dugum);
	bool AVLEkle(Ogrenci* o);
	AVLNode* AVLBul(Ogrenci* o);
	bool AVLSil(Ogrenci* o);
	bool AVLSilTek(AVLNode* bulunan);
	int YukHesap(AVLNode* dugum);
	void DengeKontrol(AVLNode* dugum);
	void AVLDengele(AVLNode* denge);
	void AVLYazdir(AVLNode* ptr, int level);
	void Oncekok(AVLNode* kok);
	void Sonrakok(AVLNode* kok);
	void Ickok(AVLNode* kok);
	AVLNode* SolaTekDonus(AVLNode* dugum);
	AVLNode* SagaTekDonus(AVLNode* dugum);
	AVLNode* SolSagDonus(AVLNode* dugum);
	AVLNode* SagSolDonus(AVLNode* dugum);
	AVLAgaci();
	~AVLAgaci();
};

