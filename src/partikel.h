#ifndef __PARTIKEL_H_
#define __PARTIKEL_H_

#include <iostream>

struct partikel{
	double masse = 1.0;
	double ort[3] = {0.0, 0.0, 0.0};
	double kraft[3] = {0.0, 0.0, 0.0};
	double geschwindigkeit[3] = {0.0, 0.0, 0.0};
	double radius = 1.0;
};

void Wechselwirkung(partikel &p1, partikel &p2, double graviKonst);
void Bewegen(double deltaT, partikel &p);
void Nullen(partikel &p);

#endif //__PARTIKEL_H_