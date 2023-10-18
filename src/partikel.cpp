#include "partikel.h"
#include <cmath>

void Wechselwirkung(partikel &p1, partikel &p2, double graviKonst)
{
	double entfernungsFkt = 0.0;
	for(int i = 0; i < 3; i++)
	{
		entfernungsFkt += (p1.ort[i] - p2.ort[i]) * (p1.ort[i] - p2.ort[i]);
	}
	if(!entfernungsFkt)
	{
		std::cout<<"entfernungsFkt = 0!\n";
		return;
	}
	entfernungsFkt = sqrt(entfernungsFkt);
	if(entfernungsFkt <= (p1.radius + p2.radius))
	{
		Aufprall(p1, p2);
		return;
	}
	for(int i = 0; i < 3; i++)
	{
		p1.kraft[i] += (p2.ort[i] - p1.ort[i]) * p1.masse * p2.masse * graviKonst / pow(entfernungsFkt, 3.0);
		p2.kraft[i] -= p1.kraft[i];
	}
	return;
}

void Bewegen(double deltaT, partikel &p)
{
	for(int i = 0; i < 3; i++)
	{
		p.geschwindigkeit[i] += deltaT * p.kraft[i] / p.masse;
		p.ort[i] += p.geschwindigkeit[i] * deltaT;
	}
	Nullen(p);
	return;
}

void Nullen(partikel &p)
{
	p.kraft[0] = p.kraft[1] = p.kraft[2] = 0.0;
	return;
}

void Aufprall(partikel &p1, partikel &p2)
{
	return;
	double EModul = 1000.0;
	
	double abstand = 0.0;
	for(int i = 0; i < 3; i++)
	{
		abstand += (p1.ort[i] - p2.ort[i]) * (p1.ort[i] - p2.ort[i]);
	}
	abstand = sqrt(abstand);
	double delta1 = 1.0 - (abstand - p2.radius) / p1.radius;
	double delta2 = 1.0 - (abstand - p1.radius) / p2.radius;
	
	if(!abstand)return;
	for(int i = 0; i < 3; i++)
	{
		p1.kraft[i] += (p1.ort[i]-p2.ort[i]) * delta1 * EModul / abstand;
		p2.kraft[i] += (p2.ort[i]-p1.ort[i]) * delta2 * EModul / abstand;
	}
	
	return;
}