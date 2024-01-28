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
		p1.kraft[i] += (p2.ort[i] - p1.ort[i]) * p1.masse * p2.masse * graviKonst / pow(entfernungsFkt, 2.0);
		p2.kraft[i] -= p1.kraft[i];
	}
	return;
}

void Bewegen(double deltaT, partikel &p)
{
	for(int i = 0; i < 3; i++)
	{
		p.geschwindigkeit[i] += deltaT * p.kraft[i] / p.masse + p.deltaGeschw[i];
		p.ort[i] += p.geschwindigkeit[i] * deltaT;
	}
	Nullen(p);
	return;
}

void Nullen(partikel &p)
{
	p.kraft[0] = p.kraft[1] = p.kraft[2] = 0.0;
	p.deltaGeschw[0] = p.deltaGeschw[1] = p.deltaGeschw[2] = 0.0; 
	return;
}

void Aufprall(partikel &p1, partikel &p2)
{
	//return;
	double abstand = 0.0;
	for(int i = 0; i < 3; i++)
	{
		abstand += (p1.ort[i] - p2.ort[i]) * (p1.ort[i] - p2.ort[i]);
	}
	abstand = sqrt(abstand);
	
	double richtung[3];
	for(int i = 0; i < 3; i++)
	{
		richtung[i] = (p1.ort[i] - p2.ort[i]) / abstand;
	}

	double lambda1 = 0.0;
	double lambda2 = 0.0;
	for(int i = 0; i < 3; i++)
	{
		lambda1 += richtung[i] * p1.geschwindigkeit[i];
		lambda2 += richtung[i] * p2.geschwindigkeit[i];
	}
	if(lambda1 > 0)lambda1 = 0;
	if(lambda2 < 0)lambda2 = 0;
	for(int i = 0; i < 3; i++)
	{
		p1.deltaGeschw[i] -= 2 * (lambda1 - lambda2) * richtung[i] * p2.masse / (p1.masse + p2.masse);
		p2.deltaGeschw[i] -= 2 * (lambda2 - lambda1) * richtung[i] * p1.masse / (p1.masse + p2.masse);
	}

	return;
}