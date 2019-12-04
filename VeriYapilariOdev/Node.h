#pragma once
#include "Ogrenci.h"
class Node
{
public:
	Ogrenci* ogr = new Ogrenci();
	Node* sonraki;

public:	
	Node(Ogrenci* o);
	~Node();
};

