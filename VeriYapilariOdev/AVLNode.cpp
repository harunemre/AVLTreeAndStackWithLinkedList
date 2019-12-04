#include "stdafx.h"
#include "AVLNode.h"

AVLNode::AVLNode() {
	sol = sag = parent = NULL;
	yukseklik = 0;
	dengeFaktor = 0;
}

AVLNode::AVLNode(Ogrenci* o)
{
	sol = sag = parent = NULL;
	ogr = o;
	yukseklik = 0;
	dengeFaktor = 0;
}


AVLNode::~AVLNode()
{

}
