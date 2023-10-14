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
		p1.kraft[i] += (p2.ort[i] - p1.ort[i]) * p1.masse * p2.masse * graviKonst * entfernungsFkt;
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
	double dP[3];
	double richtAnteil = 0.0;
	double abstandQuad = 0.0;
	for(int i = 0; i < 3; i++)
	{
		richtAnteil += p1.geschwindigkeit[i] * (p2.ort[i] - p1.ort[i]);
		dP[i] = (p2.ort[i] - p1.ort[i]);
		abstandQuad +=  dP[i] * dP[i];
	}
	if(!abstandQuad)return;
	richtAnteil /= abstandQuad;
	
	for(int i = 0; i < 3; i++)
	{
		p1.geschwindigkeit[i] -= richtAnteil * dP[i] * 0.9 * p2.masse / (p1.masse + p2.masse);
		p2.geschwindigkeit[i] += richtAnteil * dP[i] * 0.9 * p1.masse / (p1.masse + p2.masse);
	}
	return;
}