#include "aruZeichner.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdarg.h>
#include "px_font.h"

#define PI 3.1415926535897932384626433832795

aruZeichner::aruZeichner(unsigned char* zeichenFlaeche, int hoehe, int breite)
{
    m_chZeichenFlaeche = zeichenFlaeche;
    m_iHoehe = hoehe;
    m_iBreite = breite;
    m_RGB_R = m_RGB_G = m_RGB_B = 128;
    m_pxSchrift.FontIni("aruZeichner/Zeichensatz.zs");
}


void aruZeichner::ZeichneKreis(int iXm, int iYm, int iRadius)
{
    /*Kreis ausserhalb Zeichenflaeche*/
    if((iXm + iRadius < 0)||(iXm - iRadius >= m_iBreite)||(iYm + iRadius < 0)||(iYm - iRadius >= m_iHoehe))return;

    int iWehR = 0.7071067811865 * iRadius; //Wurzel 1/2

    int x, y, iStelle;
    for(x = iXm - iWehR - 1; x < iXm + iWehR + 1; x++)
    {
        if(x < 0 || x >= m_iBreite)continue;
        y = iYm + sqrt(iRadius * iRadius - (x - iXm) * (x - iXm));

        iStelle = (x + y * m_iBreite) * 3 * (y >= 0 && y < m_iHoehe);
        m_chZeichenFlaeche[iStelle] = m_RGB_R;
        m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
        m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;

        y = iYm - sqrt(iRadius * iRadius - (x - iXm) * (x - iXm));

        iStelle = (x + y * m_iBreite) * 3 * (y >= 0 && y < m_iHoehe);
        m_chZeichenFlaeche[iStelle] = m_RGB_R;
        m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
        m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;
    }

    for(y = iYm - iWehR - 1; y < iYm + iWehR + 1; y++)
    {
        if(y < 0 || y >= m_iHoehe)continue;
        x = iXm + sqrt(iRadius * iRadius - (y - iYm) * (y - iYm));

        iStelle = (x + y * m_iBreite) * 3 * (x >= 0 && x < m_iBreite);
        m_chZeichenFlaeche[iStelle] = m_RGB_R;
        m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
        m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;

        x = iXm - sqrt(iRadius*iRadius - (y - iYm) * (y - iYm));

        iStelle = (x + y * m_iBreite) * 3 * (x >= 0 && x < m_iBreite);
        m_chZeichenFlaeche[iStelle] = m_RGB_R;
        m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
        m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;
    }
    return;
}

void aruZeichner::ZeichneBogen(int iXm, int iYm, int iRadius, float iAnfangsWinkel, float iEndWinkel)
{
	/*Bogen au�erhalb Zeichenflaeche*/
    if((iXm + iRadius < 0)||(iXm - iRadius >= m_iBreite)||(iYm + iRadius < 0)||(iYm - iRadius >= m_iHoehe))return;

    int iWehR = 0.7071067811865 * iRadius; //Wurzel 1/2
	int x, y, iStelle;


	return;
}

void aruZeichner::ZeichneLinie(int p1x, int p1y, int p2x, int p2y)
{
    int yMax, yMin, xMax, xMin;

    xMin = xMax = p1x;
    if(p2x > xMax)(xMax = p2x);
    if(p2x < xMin)(xMin = p2x);
    if(xMin < 0) xMin = 0;
    if(xMax < 0) xMax = 0;
    if(xMin > m_iBreite) xMin = m_iBreite;
    if(xMax > m_iBreite) xMax = m_iBreite;

    yMin = yMax = p1y;
    if(p2y > yMax)(yMax = p2y);
    if(p2y < yMin)(yMin = p2y);
    if(yMin < 0) yMin = 0;
    if(yMax < 0) yMax = 0;
    if(yMin > m_iHoehe) yMin = m_iHoehe;
    if(yMax > m_iHoehe) yMax = m_iHoehe;

    double dSteigung, dx, dy;

    dx = p2x - p1x;
    dy = p2y - p1y;

    int x, y;

    if(abs(dx) < abs(dy))
    {
        dSteigung = dx / dy;
        for(y = yMin; y < yMax; y++)
        {
            x = p1x + dSteigung * (y - p1y);
            if((x < m_iBreite)&&(x >= 0))
            {
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3] = m_RGB_R;
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3 + 1] = m_RGB_G;
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3 + 2] = m_RGB_B;
            }
        }
    }else
    {
        dSteigung = dy/ dx;
        for(x = xMin; x < xMax; x++)
        {
            y = p1y + dSteigung * (x - p1x);
            if((y < m_iHoehe)&&(y >= 0))
            {
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3] = m_RGB_R;
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3 + 1] = m_RGB_G;
                m_chZeichenFlaeche[(x + y * m_iBreite) * 3 + 2] = m_RGB_B;
            }
        }
    }
    return;
}

void aruZeichner::SetzeFarbe(unsigned char r, unsigned char g, unsigned char b)
{
    m_RGB_R = r;
    m_RGB_G = g;
    m_RGB_B = b;

    return;
}

void aruZeichner::ZeichneDreieck(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y)
{
    int iXLinks, iXMitte, iXRechts;
    int iYLinks, iYMitte, iYRechts;
    /*Eckpunkte von links nach rechts ordnen*/
    iXLinks = iXMitte = iXRechts = p1x;
    iYLinks = iYMitte = iYRechts = p1y;
    if(p2x < iXLinks)
    {
        iXLinks = p2x;
        iYLinks = p2y;
    }
    else
    {
        iXMitte = iXRechts = p2x;
        iYMitte = iYRechts = p2y;
    }

    if(p3x < iXLinks)
    {
        if(iXLinks > iXRechts)
        {
            iXRechts = iXLinks;
            iYRechts = iYLinks;
        }
        else
        {
            iXMitte = iXLinks;
            iYMitte = iYLinks;
        }
        iXLinks = p3x;
        iYLinks = p3y;
    }else{
        if(p3x > iXRechts)
        {
            iXRechts = p3x;
            iYRechts = p3y;
        }
        else
        {
            iXMitte = p3x;
            iYMitte = p3y;
        }
    }
    /*ENDE Eckpunkte von links nach rechts ordnen*/
    if(iXRechts == iXLinks)return;

    /*Dreieck senkrecht in der Mitte durchschneiden*/
    int iYoben, iYunten;
    iYoben = iYLinks + (iYRechts - iYLinks) * (iXMitte - iXLinks) / (iXRechts - iXLinks);
    if(iYMitte > iYoben)
    {
        iYunten = iYoben;
        iYoben = iYMitte;
    }else
    {
        iYunten = iYMitte;
    }
    ZeichneGeradesDreieck(iXLinks, iYLinks, iYLinks, iXMitte, iYoben, iYunten);
    ZeichneGeradesDreieck(iXMitte, iYoben, iYunten, iXRechts, iYRechts, iYRechts);
    /*ENDE Dreieck senkrecht in der Mitte durchschneiden*/
    return;
}

void aruZeichner::ZeichneRechteck(int x1, int y1, int x2, int y2)
{
	int minX, maxX, minY, maxY, iStelle;
	minX = x1 * (x1 <= x2) + x2 * (x2 < x1);
	maxX = x1 * (x1 >= x2) + x2 * (x2 > x1);
	minY = y1 * (y1 <= y2) + y2 * (y2 < y1);
	maxY = y1 * (y1 >= y2) + y2 * (y2 > y1);

	if(minX < 0) minX = 0;
	if(maxX > m_iBreite) maxX = m_iBreite;
	if(minY < 0) minY = 0;
	if(maxY > m_iHoehe) maxY = m_iHoehe;

	for(int dx = minX; dx < maxX; dx++)
	{
		for(int dy = minY; dy < maxY; dy++)
		{
			iStelle = (dx + dy * m_iBreite)* 3;
            {
                m_chZeichenFlaeche[iStelle] = m_RGB_R;
                m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
                m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;
            }
		}
	}
	return;
}

void aruZeichner::ZeichneGeradesDreieck(int iXL, int iYLo, int iYLu, int iXR, int iYRo, int iYRu)
{
    /*Abbruchkriterien - Dreieck au�erhalb*/
    if(iXL > m_iBreite)return;
    if(iXR < 0)return;
    if((iYLu > m_iHoehe)&&(iYRu > m_iHoehe))return;
    if((iYLo < 0)&&(iYRo < 0))return;
    if(iXL == iXR)
    {
        ZeichneLinie(iXL, iYLo, iXL, iYLu);
        return;
    }
    /*ENDE Abbruchkriterien - Dreieck au�erhalb*/

    /*Schnitte mit R�ndern finden*/
    int iAnzAbteile = 0;
    int iX[6], iYu[6], iYo[6];

    /*Lage linker Rand*/
    iX[iAnzAbteile] = iXL;
    iYu[iAnzAbteile] = iYLu;
    iYo[iAnzAbteile] = iYLo;
    if(iXL < 0)
    {
        iX[iAnzAbteile] = 0;
        iYu[iAnzAbteile] = iYLu + (iYRu - iYLu) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
        iYo[iAnzAbteile] = iYLo + (iYRo - iYLo) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
    }
    if(iYu[iAnzAbteile] < 0)iYu[iAnzAbteile] = 0;
    if(iYo[iAnzAbteile] >= m_iHoehe)iYo[iAnzAbteile] = m_iHoehe - 1;
    if(!(iYu[iAnzAbteile] >= m_iHoehe) && !(iYo[iAnzAbteile] < 0))iAnzAbteile++;

    /*obere Linie schneidet oberen Rand*/
    if((m_iHoehe - 1 - iYLo) * (m_iHoehe - 1 - iYRo) < 0)
    {
        iYo[iAnzAbteile] = m_iHoehe - 1;
        iX[iAnzAbteile] = iXL + (iXR - iXL) * (iYo[iAnzAbteile] - iYLo) / (float)(iYRo - iYLo);
        if(!(iX[iAnzAbteile] < 0) && !(iX[iAnzAbteile] >= m_iBreite))
        {
            iYu[iAnzAbteile] = iYLu + (iYRu - iYLu) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
            if(iYu[iAnzAbteile] < 0)iYu[iAnzAbteile] = 0;
            iAnzAbteile++;
        }
    }

    /*obere Linie schneidet unteren Rand*/
    if((0 - iYLo) * (0 - iYRo) < 0)
    {
        iYo[iAnzAbteile] = 0;
        iYu[iAnzAbteile] = 0;
        iX[iAnzAbteile] = iXL + (iXR - iXL) * (iYo[iAnzAbteile] - iYLo) / (float)(iYRo - iYLo);
        if(!(iX[iAnzAbteile] < 0) && !(iX[iAnzAbteile] >= m_iBreite))
        {
            iAnzAbteile++;
        }
    }

    /*untere Linie schneidet oberen Rand*/
    if((m_iHoehe - 1 - iYLu) * (m_iHoehe - 1 - iYRu) < 0)
    {
        iYu[iAnzAbteile] = m_iHoehe;
        iYo[iAnzAbteile] = m_iHoehe;
        iX[iAnzAbteile] = iXL + (iXR - iXL) * (iYu[iAnzAbteile] - iYLu) / (float)(iYRu - iYLu);
        if(!(iX[iAnzAbteile] < 0) && !(iX[iAnzAbteile] >= m_iBreite))
        {
            iAnzAbteile++;
        }
    }

    /*untere Linie schneidet unteren Rand*/
    if((0 - iYLu) * (0 - iYRu) < 0)
    {
        iYu[iAnzAbteile] = 0;
        iX[iAnzAbteile] = iXL + (iXR - iXL) * (iYu[iAnzAbteile] - iYLu) / (float)(iYRu - iYLu);
        if(!(iX[iAnzAbteile] < 0) && !(iX[iAnzAbteile] >= m_iBreite))
        {
            iYo[iAnzAbteile] = iYLo + (iYRo - iYLo) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
            if(iYo[iAnzAbteile] >= m_iHoehe)iYo[iAnzAbteile] = m_iHoehe - 1;
            iAnzAbteile++;
        }
    }

    /*Lage rechter Rand*/
    iX[iAnzAbteile] = iXR;
    iYu[iAnzAbteile] = iYRu;
    iYo[iAnzAbteile] = iYRo;
    if(iXR >= m_iBreite)
    {
        iX[iAnzAbteile] = m_iBreite - 1;
        iYu[iAnzAbteile] = iYLu + (iYRu - iYLu) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
        iYo[iAnzAbteile] = iYLo + (iYRo - iYLo) * (iX[iAnzAbteile] - iXL) / (float)(iXR - iXL);
    }
    if(iYu[iAnzAbteile] < 0)iYu[iAnzAbteile] = 0;
    if(iYo[iAnzAbteile] >= m_iHoehe)iYo[iAnzAbteile] = m_iHoehe - 1;
    if(!(iYu[iAnzAbteile] > m_iHoehe) && !(iYo[iAnzAbteile] < 0))iAnzAbteile++;
    /*ENDE Schnitte mit R�ndern finden*/

    /*Abteile sortieren*/
    int *iIndex = new int[iAnzAbteile];
    for(int i = 0; i < iAnzAbteile; i++)
    {
        iIndex[i] = i;
    }
    for(int i = 0; i < iAnzAbteile - 1; i++)
    {
        for(int k = i+1; k < iAnzAbteile; k++)
            {
                if(iX[iIndex[k]] < iX[iIndex[i]])
                {
                    int iTemp = iIndex[k];
                    iIndex[k] = iIndex[i];
                    iIndex[i] = iTemp;
                }
            }
    }
    /*ENDE Abteile sortieren*/

    /*Trapeze zeichnen*/
    for(int i = 0; i < iAnzAbteile - 1; i++)
    {
        ZeichneTrapezSenkrecht(iX[iIndex[i]], iX[iIndex[i+1]], iYu[iIndex[i]], iYu[iIndex[i+1]], iYo[iIndex[i]], iYo[iIndex[i+1]]);
    }
    /*ENDE Trapeze zeichnen*/
    return;
}

void aruZeichner::ZeichneTrapezSenkrecht(int iMinX, int iMaxX, int iMinYu, int iMaxYu, int iMinYo, int iMaxYo)
{
    if(iMaxX == iMinX)return;
    int iStelle;
    for(int iTempX = iMinX; iTempX < iMaxX; iTempX++)
    {
        int iLocMinY = iMinYu + (iMaxYu - iMinYu) * (iTempX - iMinX) / (iMaxX - iMinX);
        int iLocMaxY = iMinYo + (iMaxYo - iMinYo) * (iTempX - iMinX) / (iMaxX - iMinX);
        for(int iTempY = iLocMinY; iTempY < iLocMaxY; iTempY++)
        {
            iStelle = (iTempX + iTempY * m_iBreite)* 3;
            //if((iStelle >= 0)&&(iStelle < (m_iHoehe * m_iBreite * 3)))
            {
                m_chZeichenFlaeche[iStelle] = m_RGB_R;
                m_chZeichenFlaeche[iStelle + 1] = m_RGB_G;
                m_chZeichenFlaeche[iStelle + 2] = m_RGB_B;
            }
        }
    }
    return;
}

void aruZeichner::Schrift(int posX, int posY, char* text, int pxGroesse)
{
  	int iGesBreite = 0;
    int iVerschub = 0;
    char c;
  	for(int i = 0; text[i] != '\0'; i++)
  	{
  		c = text[i] - 48;
      iGesBreite = m_pxSchrift.br[c] + 1;
    }
    iGesBreite -= 1;
    if(iGesBreite >0)
    {
      bool bTextPause[iGesBreite * _PX_FONT_HOEHE];
    }

    for(int i = 0; text[i] != '\0'; i++)
  	{
		std::vector<PaarePaar*> vZeichen = m_pxSchrift.px_zeichensatz[c];
		for(std::vector<PaarePaar*>::iterator it = vZeichen.begin(); ; it++)
		{
			if(it == vZeichen.end())
			{
			  break;
			}
			//bTextPause[]
			ZeichneRechteck(((*it)->a[0])  + posX + iVerschub,
							(-(*it)->a[1])  + posY,
							((*it)->a[2]) + posX + iVerschub,
							(-(*it)->a[3])  + posY);
		}
		iVerschub += (m_pxSchrift.br[c] + 1) * (pxGroesse / 7.0);
  	}
  	return;
}

void SkaliereSchrift(bool* bTextPause, unsigned int uiUrHoehe, unsigned int uiUrBreite, unsigned int uiNeueHoehe, unsigned int& uiNeueBreite, float* fTextPause)
{
  uiNeueBreite = (((uiUrBreite * uiNeueHoehe * 10) / uiUrHoehe) + 5) / 10;

  float ufRelLageReihe[uiNeueHoehe];
  float ufRelLageSpalte[uiNeueBreite];

  unsigned int uiIndexReihe[uiNeueHoehe];
  unsigned int uiIndexSpalte[uiNeueBreite];

  for(unsigned int i=0; i < uiNeueHoehe; i++)
  {
    ufRelLageReihe[i] = i * (uiUrHoehe - 1) / (uiNeueHoehe - 1);
    uiIndexReihe[i] = ufRelLageReihe[i]; //Lage abrunden
    ufRelLageReihe[i] -= uiIndexReihe[i]; //Lage auf Werte zwischen 0 und 1 beschränken
  }
  for(unsigned int i=0; i < uiNeueBreite; i++)
  {
    ufRelLageSpalte[i] = i * (uiUrBreite - 1) / (uiNeueBreite - 1);
    uiIndexSpalte[i] = ufRelLageSpalte[i]; //Lage abrunden
    ufRelLageSpalte[i] -= uiIndexSpalte[i]; //Lage auf Werte zwischen 0 und 1 beschränken
  }
  fTextPause = new float[uiNeueHoehe * uiNeueBreite];
  float p0, p1, p2, p3;
  for(unsigned int i = 0; i < uiNeueBreite - 1; i++)
  {
    for(unsigned int k = 0; i < uiNeueHoehe - 1; k++)
    {
      p0 = (float)(bTextPause[uiIndexSpalte[i] + uiIndexReihe[k] * uiUrBreite]);
      p1 = (float)(bTextPause[uiIndexSpalte[i] + 1 + uiIndexReihe[k] * uiUrBreite]);
      p2 = (float)(bTextPause[uiIndexSpalte[i] + 1 + (uiIndexReihe[k] + 1) * uiUrBreite]);
      p3 = (float)(bTextPause[uiIndexSpalte[i] + (uiIndexReihe[k] + 1) * uiUrBreite]);

      fTextPause[i + k * uiNeueBreite] = p0
          + (p1-p0) * ufRelLageSpalte[i]
          + (p3-p0) * ufRelLageReihe[k]
          + (p0 - p1 + p2 - p3) * ufRelLageSpalte[i] * ufRelLageReihe[k];
    }
  }
  return;
}

void aruZeichner::HintergrundZeichnen(unsigned char r, unsigned char g, unsigned char b)
{
    for(int i = 0; i < m_iBreite * m_iHoehe * 3; i += 3)
    {
        m_chZeichenFlaeche[i] = r;
        m_chZeichenFlaeche[i + 1] = g;
        m_chZeichenFlaeche[i + 2] = b;
    }
    return;
}

void aruZeichner::logSchreiben(const char* msg, ...)
{
    FILE *Logbuch;
    const char *pfad = "aruZeichner.log";
    Logbuch = fopen(pfad, "a");
    va_list args;
    va_start (args, msg);
    vfprintf (Logbuch, msg, args);
    va_end (args);
    fclose(Logbuch);
    return;
}
