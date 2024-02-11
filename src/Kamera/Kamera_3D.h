#ifndef __KAMERA_3D_H
#define __KAMERA_3D_H

#include "..\Vektor\Vektor.h"
#include <cmath>

#define PI 3.1415926535897932384626433832795

/**
* # Kamera
* Zur Berechnung von perspektivischen Abbildungen gegebener 3D-Punkte, die als 3-dimensionale
* Vektoren übergeben werden.
* ## Die Berechnung
* erfolgt als Ermittlung von Durchstoßpunkten von Sehhstrahlen zwischen Kamera
* und Realpunkten durch die Abbildungsebene mit Einheitsabstand von der Kamera. Die Abbildung wird
* anhand der zu übergebenen Parameter
* 1. FOV: Öffnungswinkel des Blickfeldes
* 2. Leinwandbreite: Breite des Device Context der übergeordneten Applikation
*/
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
	
	/**
	* Gibt den aktuellen Öffnungswinkel des Blickfeldes in DEG zurück.  
	* Mithilfe diese Wertes werden *u*. *a*. die Koordinaten der Projektion skaliert.
	*/
    double FOV(void)const{return (_FOV*180/PI);}
    
	/**
	* Eingabe des Öffnungswinkels des Blickfeldes in DEG  
	* Mithilfe diese Wertes werden *u*. *a*. die Koordinaten der Projektion skaliert.
	*/
	void FOV(double v_FOV);
	
	/**
	* Verschiebt die Kameraposition  
	* jeweils nach rechts, nach vorne und nach oben bei positiven Werten  
	* bzw. nach links, nach hinten und nach unten bei negativen Werten
	*/
    void Verschieben(double nachRechts, double nachVorne, double nachOben);
	
	/**Dreht die Kamera um HW (Höhenwinkel) um die Waagerechte und um SW (Seitenwinkel) um die Senkrechte*/
    void Drehen(double HW, double SW);
    
	/**Berechnet die perspektivische Abbildung des 3D-Punktes auf eine Projektionsfläche.  
	* Der Rückgabewert ist ein 3D-Vektor; die erste Koordinate beinhaltet die x-Koordinate der Abbildung,
	* die zweite Koordinate die y-Koordinate. Die Bildpunkte werden mithilfe der gesetzten Leinwandbreite
	* (SetzeLeinwandBreite) und des vorgegebenen Blickfeldes so skaliert, dass die größte sichtbare Koordinate
	* am Rand der Zeichenfläche des Device contexts zu liegen kommt.  
	* Die dritte Koordinate gibt den Abstand der Abbildung von der Kameraposition wieder, d. h. dass
	* negative Werte ***hinter*** der Kamera liegen - mit diesem Wert kann entschieden werden, ob der Punkt
	* von der rendernden Applikation überhaupt gezeichnet, weil nicht sichtbar ist oder zu nah an der Kamera
	* liegt.
	*/
	Vektor Aufnahme(const Vektor& realPkt);

	/**
	* Gibt die Kameraposition in 3D-Koordinaten wieder
	*/
    const Vektor HoleOrt(void);
    
	/**
	* Gibt die Blickrichtung der Kamera als Richtungsvektor wieder;  
	* Die Blickrichtung ist zugleich die Normale der Projektionsebene.
	*/
    const Vektor HoleBlickRichtung(void);
    
	/**
	* Legt die sichtbare Breite der rendernden Applikation fest.  
	* Mithilfe diese Wertes werden *u*. *a*. die Koordinaten der Projektion skaliert.
	*/
    void SetzeLeinwandBreite(double);
	
	/**
	* Gibt die gesetzte sichtbare Breite der rendernden Applikation wieder, die vorher über
	* SetzeLeinwandBreite gesetzt wurde.
	*/
    const double HoleLeinwandBreite(void){return lwBreite;};
    
	/**
	* Inkrementiert die sichtbare Breite der rendernden Applikation.  
	* Mithilfe der resultierenden Breite werden *u*. *a*. die Koordinaten der Projektion skaliert.
	*/
    void InkrLeinwandBreite(double);
};


#endif // __KAMERA_3D_H
