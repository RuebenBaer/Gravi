#ifndef __PX_FONT__INCLUDED
#define __PX_FONT__INCLUDED

#include<stdio.h>
#include<vector>

#define _PX_FONT_HOEHE 7

struct PaarePaar{
	int a[4];
};

static const int MAX_ZEICHEN = 75;

struct px_font
{
	std::vector<PaarePaar*>px_0;
	std::vector<PaarePaar*>px_1;
	std::vector<PaarePaar*>px_2;
	std::vector<PaarePaar*>px_3;
	std::vector<PaarePaar*>px_4;
	std::vector<PaarePaar*>px_5;
	std::vector<PaarePaar*>px_6;
	std::vector<PaarePaar*>px_7;
	std::vector<PaarePaar*>px_8;
	std::vector<PaarePaar*>px_9;
	std::vector<PaarePaar*>px_DopelPunkt;
	std::vector<PaarePaar*>px_Semikolon;
	std::vector<PaarePaar*>px_kleiner;
	std::vector<PaarePaar*>px_gleich;
	std::vector<PaarePaar*>px_groesser;
	std::vector<PaarePaar*>px_Frage;
	std::vector<PaarePaar*>px_at;
	std::vector<PaarePaar*>px_A;
	std::vector<PaarePaar*>px_B;
	std::vector<PaarePaar*>px_C;
	std::vector<PaarePaar*>px_D;
	std::vector<PaarePaar*>px_E;
	std::vector<PaarePaar*>px_F;
	std::vector<PaarePaar*>px_G;
	std::vector<PaarePaar*>px_H;
	std::vector<PaarePaar*>px_I;
	std::vector<PaarePaar*>px_J;
	std::vector<PaarePaar*>px_K;
	std::vector<PaarePaar*>px_L;
	std::vector<PaarePaar*>px_M;
	std::vector<PaarePaar*>px_N;
	std::vector<PaarePaar*>px_O;
	std::vector<PaarePaar*>px_P;
	std::vector<PaarePaar*>px_Q;
	std::vector<PaarePaar*>px_R;
	std::vector<PaarePaar*>px_S;
	std::vector<PaarePaar*>px_T;
	std::vector<PaarePaar*>px_U;
	std::vector<PaarePaar*>px_V;
	std::vector<PaarePaar*>px_W;
	std::vector<PaarePaar*>px_X;
	std::vector<PaarePaar*>px_Y;
	std::vector<PaarePaar*>px_Z;
	std::vector<PaarePaar*>px_EKlAuf;
	std::vector<PaarePaar*>px_slash;
	std::vector<PaarePaar*>px_EKlZu;
	std::vector<PaarePaar*>px_Hut;
	std::vector<PaarePaar*>px__;
	std::vector<PaarePaar*>px_Akzent;
	std::vector<PaarePaar*>px_a;
	std::vector<PaarePaar*>px_b;
	std::vector<PaarePaar*>px_c;
	std::vector<PaarePaar*>px_d;
	std::vector<PaarePaar*>px_e;
	std::vector<PaarePaar*>px_f;
	std::vector<PaarePaar*>px_g;
	std::vector<PaarePaar*>px_h;
	std::vector<PaarePaar*>px_i;
	std::vector<PaarePaar*>px_j;
	std::vector<PaarePaar*>px_k;
	std::vector<PaarePaar*>px_l;
	std::vector<PaarePaar*>px_m;
	std::vector<PaarePaar*>px_n;
	std::vector<PaarePaar*>px_o;
	std::vector<PaarePaar*>px_p;
	std::vector<PaarePaar*>px_q;
	std::vector<PaarePaar*>px_r;
	std::vector<PaarePaar*>px_s;
	std::vector<PaarePaar*>px_t;
	std::vector<PaarePaar*>px_u;
	std::vector<PaarePaar*>px_v;
	std::vector<PaarePaar*>px_w;
	std::vector<PaarePaar*>px_x;
	std::vector<PaarePaar*>px_y;
	std::vector<PaarePaar*>px_z;

	std::vector<PaarePaar*> px_zeichensatz[MAX_ZEICHEN];
	int br[MAX_ZEICHEN];

	px_font();
	~px_font();
	void FontIni(const char* fontDatei);
	void logSchreiben(const char* msg, ...);
};

#endif //__PX_FONT__INCLUDED
