#include "Kamera_3D.h"
#include "..\Matrix\Matrix.h"
#include "..\Vektor\Vektor.h"
#include <iostream>

Kamera::Kamera(Vektor& v_Standpunkt, double v_hoehenwinkel, double v_seitenwinkel, double v_FOV, double v_lwBreite)
{
    sPkt = v_Standpunkt; /*Standpunkt*/

    w_Hoehe = v_hoehenwinkel;
    w_Seite = v_seitenwinkel;

    double cos_a, cos_b, sin_a, sin_b;
    cos_a = cos(w_Hoehe);
    sin_a = sin(w_Hoehe);
    cos_b = cos(w_Seite);
    sin_b = sin(w_Seite);

    n0.SetKoordinaten(cos_a*cos_b, cos_a*sin_b, sin_a);
    h0.SetKoordinaten(-sin_a*cos_b, -sin_a*sin_b, cos_a);
    r0.SetKoordinaten(sin_b, -cos_b, 0.0);

    _FOV = v_FOV*PI/180;
    lwBreite = v_lwBreite;/*Breite der Leinwand / sichtbare Breite*/
	SichtBreiteBerechnen();
}

Kamera::~Kamera()
{

}

void Kamera::FOV(double v_FOV)
{
    _FOV = v_FOV*PI/180;
	SichtBreiteBerechnen();
    return;
}

void Kamera::Verschieben(double rechts, double vorne, double oben) /*negative werte verschieben nach links, hinten oder unten*/
{
    sPkt = sPkt + (r0 * rechts + n0 * vorne + h0 * oben);
    return;
}

void Kamera::Drehen(double delta_alpha, double delta_beta) /*Hoehenwinkel, Seitenwinkel*/
{
    w_Hoehe += delta_alpha;
    w_Seite += delta_beta;

    double cos_a, cos_b, sin_a, sin_b;
    cos_a = cos(w_Hoehe);
    sin_a = sin(w_Hoehe);
    cos_b = cos(w_Seite);
    sin_b = sin(w_Seite);

    n0.SetKoordinaten(cos_a*cos_b, cos_a*sin_b, sin_a);
    h0.SetKoordinaten(-sin_a*cos_b, -sin_a*sin_b, cos_a);
    r0.SetKoordinaten(sin_b, -cos_b, 0.0);

    return;
}

Vektor Kamera::Aufnahme(const Vektor& realPkt)
{
    Vektor sehStrahl = sPkt;
    sehStrahl = sehStrahl - realPkt;
    double xRueck, yRueck, zRueck;

    gDet = r0.x() * h0.y() * sehStrahl.z() - sehStrahl.x() * h0.y() * r0.z()
            + h0.x() * sehStrahl.y() * r0.z() - r0.x() * sehStrahl.y() * h0.z()
            + sehStrahl.x() * r0.y() * h0.z() - h0.x() * r0.y() * sehStrahl.z();

    if(gDet == 0)return Vektor(0, 0, -1);

    detax = h0.y() * sehStrahl.z() - sehStrahl.y() * h0.z();
    detay = h0.z() * sehStrahl.x() - sehStrahl.z() * h0.x();
    detaz = h0.x() * sehStrahl.y() - sehStrahl.x() * h0.y();

    detbx = sehStrahl.y() * r0.z() - r0.y() * sehStrahl.z();
    detby = sehStrahl.z() * r0.x() - r0.z() * sehStrahl.x();
    detbz = sehStrahl.x() * r0.y() - r0.x() * sehStrahl.y();

    detcx = r0.y() * h0.z() - h0.y() * r0.z();
    detcy = r0.z() * h0.x() - h0.z() * r0.x();
    detcz = r0.x() * h0.y() - h0.x() * r0.y();

    xRueck = -sichtFkt * (n0.x() * detax + n0.y() * detay + n0.z() * detaz);
    yRueck = -sichtFkt * (n0.x() * detbx + n0.y() * detby + n0.z() * detbz);
    zRueck = -sichtFkt * (n0.x() * detcx + n0.y() * detcy + n0.z() * detcz);

    return(Vektor(xRueck/gDet, yRueck/gDet, zRueck/gDet));
}

const Vektor Kamera::HoleOrt(void)
{
    return(sPkt);
}

const Vektor Kamera::HoleBlickRichtung(void)
{
    return(n0);
}


void Kamera::SetzeLeinwandBreite(double wert)
{
    if(wert>0)
    {
        lwBreite = wert;
    }
	SichtBreiteBerechnen();
	return;
}

void Kamera::InkrLeinwandBreite(double wert)
{
    lwBreite += wert;
    if(lwBreite<1)
    {
        lwBreite = 1;
    }
	SichtBreiteBerechnen();
	return;
}

void Kamera::SichtBreiteBerechnen(void)
{
	sichtFkt = lwBreite / (tan(_FOV/2.0)*2);
	return;
}