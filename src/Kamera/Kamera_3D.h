#ifndef __KAMERA_3D_H
#define __KAMERA_3D_H

#include "..\Vektor\Vektor.h"
#include <cmath>

#define PI 3.14159265

struct _3D_Linie
{
    Vektor m_anfang, m_ende;
};

class Kamera
{
private:
    Vektor sPkt, n0, r0, h0; /*Standpunkt, Normale, Rechts, Hoch*/
    double w_Hoehe, w_Seite; /*Hoehenwinkel zur waagerechten, Seitenwinkel zur X-Achse*/
    double lwBreite, _FOV/*Sichtwinkel in RAD*/, sichtFkt;
    double gDet, detax, detay, detaz, detbx, detby, detbz, detcx, detcy, detcz; /*Matrizenvariablen*/
	
	void SichtBreiteBerechnen(void);
public:
    Kamera(Vektor& v_Standpunkt, double v_hoehenwinkel, double v_seitenwinkel, double v_FOV, double v_lwBreite);
    ~Kamera();
    double FOV(void)const{return (_FOV*180/PI);}/*Gibt den Winkel in DEG zurück*/
    void FOV(double v_FOV);/*Eingabe des Winkels in DEG*/
    void Verschieben(double, double, double);/*nach rechts, vorne, oben relativ zur Kamerablickrichtung*/
    void Drehen(double, double);/*Winkelaenderung gegen die waagerechte und gegen die X-Achse*/
    Vektor Aufnahme(const Vektor& realPkt);/*Umrechnung eines dreidimensionalen Punkts in ein zweidimensionales Abbild*/
    Vektor Aufnahme2(const Vektor& realPkt);/*Umrechnung eines dreidimensionalen Punkts in ein zweidimensionales Abbild*/
    const Vektor HoleOrt(void);
    const Vektor HoleBlickRichtung(void);
    const double HoleLeinwandBreite(void){return lwBreite;};
    void SetzeLeinwandBreite(double);
    void InkrLeinwandBreite(double);
};


#endif // __KAMERA_3D_H
