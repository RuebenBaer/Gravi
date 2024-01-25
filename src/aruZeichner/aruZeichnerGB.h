/*TODO: Alphakanal?*/

#ifndef ARUZEICHNER_GB_HPP_INCLUDED
#define ARUZEICHNER_GB_HPP_INCLUDED

#include "px_font.h"

class aruZeichnerGB
{
public:
    aruZeichnerGB(unsigned char*, int, int);
    void HintergrundZeichnen(unsigned char, unsigned char, unsigned char);
    void ZeichneLinie(int, int, int, int);
    void ZeichneDreieck(int, int, int, int, int, int);
    void ZeichneKreis(int iXm, int iYm, int iRadius);
    void ZeichneBogen(int iXm, int iYm, int iRadius, float iAnfangsWinkel, float iEndWinkel);
    void ZeichneRechteck(int x1, int y1, int x2, int y2);
    void Schrift(int posX, int posY, char* text, int pxGroesse);
    void SkaliereSchrift(bool* bTextPause, unsigned int uiTPHoehe, unsigned int uiTPBreite, unsigned int uiNeueHoehe, float* fTextPause);
    void SetzeFarbe(unsigned char, unsigned char, unsigned char);
private:
    unsigned char *m_chZeichenFlaeche;
    unsigned char m_RGB_R, m_RGB_G, m_RGB_B;
    int m_iBreite, m_iHoehe;
    struct px_font m_pxSchrift;

    void ZeichneDreieckSenkrecht(int iXL, int iYLo, int iYLu, int iXR, int iYRo, int iYRu);

    void ZeichneGeradesDreieck(int iXL, int iYLo, int iYLu, int iXR, int iYRo, int iYRu);
    void ZeichneTrapezSenkrecht(int iMinX, int iMaxX, int iMinYu, int iMaxYu, int iMinYo, int iMaxYo);

    /*Logbuch*/
    void logSchreiben(const char*, ...);
    /*ENDE Logbuch*/
};


#endif // ARUZEICHNER_GB_HPP_INCLUDED
