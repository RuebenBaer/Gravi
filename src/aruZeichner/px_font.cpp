#include "px_font.h"
#include <stdarg.h>

px_font::px_font()
{
	px_zeichensatz[0] = (px_0);
	px_zeichensatz[1] = (px_1);
	px_zeichensatz[2] = (px_2);
	px_zeichensatz[3] = (px_3);
	px_zeichensatz[4] = (px_4);
	px_zeichensatz[5] = (px_5);
	px_zeichensatz[6] = (px_6);
	px_zeichensatz[7] = (px_7);
	px_zeichensatz[8] = (px_8);
	px_zeichensatz[9] = (px_9);
	px_zeichensatz[10] = (px_DopelPunkt);
	px_zeichensatz[11] = (px_Semikolon);
	px_zeichensatz[12] = (px_kleiner);
	px_zeichensatz[13] = (px_gleich);
	px_zeichensatz[14] = (px_groesser);
	px_zeichensatz[15] = (px_Frage);
	px_zeichensatz[16] = (px_at);
	px_zeichensatz[17] = (px_A);
	px_zeichensatz[18] = (px_B);
	px_zeichensatz[19] = (px_C);
	px_zeichensatz[20] = (px_D);
	px_zeichensatz[21] = (px_E);
	px_zeichensatz[22] = (px_F);
	px_zeichensatz[23] = (px_G);
	px_zeichensatz[24] = (px_H);
	px_zeichensatz[25] = (px_I);
	px_zeichensatz[26] = (px_J);
	px_zeichensatz[27] = (px_K);
	px_zeichensatz[28] = (px_L);
	px_zeichensatz[29] = (px_M);
	px_zeichensatz[30] = (px_N);
	px_zeichensatz[31] = (px_O);
	px_zeichensatz[32] = (px_P);
	px_zeichensatz[33] = (px_Q);
	px_zeichensatz[34] = (px_R);
	px_zeichensatz[35] = (px_S);
	px_zeichensatz[36] = (px_T);
	px_zeichensatz[37] = (px_U);
	px_zeichensatz[38] = (px_V);
	px_zeichensatz[39] = (px_W);
	px_zeichensatz[40] = (px_X);
	px_zeichensatz[41] = (px_Y);
	px_zeichensatz[42] = (px_Z);
	px_zeichensatz[43] = (px_EKlAuf);
	px_zeichensatz[44] = (px_slash);
	px_zeichensatz[45] = (px_EKlZu);
	px_zeichensatz[46] = (px_Hut);
	px_zeichensatz[47] = (px__);
	px_zeichensatz[48] = (px_Akzent);
	px_zeichensatz[49] = (px_a);
	px_zeichensatz[50] = (px_b);
	px_zeichensatz[51] = (px_c);
	px_zeichensatz[52] = (px_d);
	px_zeichensatz[53] = (px_e);
	px_zeichensatz[54] = (px_f);
	px_zeichensatz[55] = (px_g);
	px_zeichensatz[56] = (px_h);
	px_zeichensatz[57] = (px_i);
	px_zeichensatz[58] = (px_j);
	px_zeichensatz[59] = (px_k);
	px_zeichensatz[60] = (px_l);
	px_zeichensatz[61] = (px_m);
	px_zeichensatz[62] = (px_n);
	px_zeichensatz[63] = (px_o);
	px_zeichensatz[64] = (px_p);
	px_zeichensatz[65] = (px_q);
	px_zeichensatz[66] = (px_r);
	px_zeichensatz[67] = (px_s);
	px_zeichensatz[68] = (px_t);
	px_zeichensatz[69] = (px_u);
	px_zeichensatz[70] = (px_v);
	px_zeichensatz[71] = (px_w);
	px_zeichensatz[72] = (px_x);
	px_zeichensatz[73] = (px_y);
	px_zeichensatz[74] = (px_z);
}

px_font::~px_font()
{
	for(int it = 0; it < MAX_ZEICHEN; it++)
	{
		for(std::vector<PaarePaar*>::iterator it_pP = px_zeichensatz[it].begin(); it_pP != px_zeichensatz[it].end(); it_pP++)
				delete *it_pP;
	}
}

void px_font::FontIni(const char* fontDatei)
{
	FILE* fZeichensatz = fopen(fontDatei, "r");
	if(fZeichensatz != NULL)
	{
		int iZeichen, iMinPos, iMaxPos;
		int iNummer = 0;
		for(int it = 0; it < MAX_ZEICHEN; it++)
		{
			iMinPos = 999999;//quasi unendlich ;)
			iMaxPos = 0;
			do
			{
				PaarePaar pP;
				iZeichen = fgetc(fZeichensatz);
				if(iZeichen=='\n')
				{
					br[it] = iMaxPos - iMinPos; //Zeichenbreite
					break;
				}
				pP.a[iNummer++] = (int)((char)(iZeichen-48));
				if(iNummer == 4)
				{
					if(iMinPos > pP.a[0])iMinPos = pP.a[0];
					if(iMinPos > pP.a[2])iMinPos = pP.a[2];
					if(iMaxPos < pP.a[0])iMaxPos = pP.a[0];
					if(iMaxPos < pP.a[2])iMaxPos = pP.a[2];
					PaarePaar* ptr_pP = new PaarePaar();
					if(ptr_pP)
					{
						for(int i = 0; i<4; i++)
							ptr_pP->a[i] = pP.a[i];
						px_zeichensatz[it].push_back(ptr_pP);
					}
					iNummer = 0;
				}
			}while(iZeichen != EOF);
			if(iZeichen == EOF)
			{
				fclose(fZeichensatz);
				break;
			}
		}
	}
	fclose(fZeichensatz);
}

void px_font::logSchreiben(const char* msg, ...)
{
    FILE *Logbuch;
    const char *pfad = "px_font.log";
    Logbuch = fopen(pfad, "a");
    va_list args;
    va_start (args, msg);
    vfprintf (Logbuch, msg, args);
    va_end (args);
    fclose(Logbuch);
    return;
}
