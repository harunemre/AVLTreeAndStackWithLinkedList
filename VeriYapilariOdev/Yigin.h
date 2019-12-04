#pragma once
#include "Liste.h"
class Yigin : public Liste {
public:
	Yigin();
	~Yigin();
	Node* Top();
	bool Push(Ogrenci* o);
	Node* Pop();
	void YiginiYazdir();
};


