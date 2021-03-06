﻿#include "Ellipse.h"
#include <time.h>
#include <iostream>

void InitStrongRNG(csprng *Rng)
{
	srand(time(NULL));
	char raw[100];
	for (int i = 0; i < 100; i++)
		raw[i] = (char)rand();
	strong_init(Rng, 100, raw, time(NULL));
}

int GenEC(EC_CONSTANTS_F2m_POLY EC, big a, big b, pepoint G, big x, big y, big n)
{
	a->w[0] = EC.a;
	if (cinstr(b, EC.b) != strlen(EC.b)) return 1;
	if (cinstr(x, EC.Gx) != strlen(EC.Gx)) return 1;
	if (cinstr(y, EC.Gy) != strlen(EC.Gy)) return 1;
	if (cinstr(n, EC.n) != strlen(EC.n)) return 1;
	if (!ecurve2_init(EC.m, EC.k3, EC.k2, EC.k1, a, b, 1, MR_PROJECTIVE))
		return 1;
	if (!epoint2_set(x, y, 0, G)) return 1;
}

void cotnumEp(pepoint P) {
	epoint2_norm(P);
	std::cout << "\tx: "; cotnum(P->X, stdout);
	std::cout << "\ty: "; cotnum(P->Y, stdout);
	std::cout << std::endl;
}

void GetConstainsEC(EC_CONSTANTS_F2m_POLY &EC, unsigned int m) {

	EC_CONSTANTS_F2m_POLY ECm[5];
	switch (m)
	{
	case 163: EC = { 163, 7, 6, 3, 1, 2, //  ВАРИАНТ 1  
		"20A601907B8C953CA1481EB10512F78744A3205FD",	// 41 hex, 6 dw
		"40000000000000000000292FE77E70C12A4234C33",	// 41 hex, 6 dw
		"3F0EBA16286A2D57EA0991168D4994637E8343E36",	// 41 hex, 6 dw
		"D51FBC6C71A0094FA2CDD545B11C5C0C797324F1" };	// 40 hex, 5 dw
		break;
	case 233: EC = { 233,74,0,0,1,2, //  ВАРИАНТ 2  
		"66647EDE6C332C7F8C0923BB58213B333B20E9CE4281FE115F7D8F90AD",	// 58 hex, 8 dw
		"1000000000000000000000000000013E974E72F8A6922031D2603CFE0D7",	// 59 hex, 8 dw
		"FAC9DFCBAC8313BB2139F1BB755FEF65BC391F8B36F8F8EB7371FD558B",	// 58 hex, 8 dw
		"1006A08A41903350678E58528BEBF8A0BEFF867A7CA36716F7E01F81052" };// 59 hex, 8 dw
		break;
	case 283: EC = { 283,12,7,5,1,2, //  ВАРИАНТ 3  
		"27B680AC8B8596DA5A4AF8A19A0303FCA97FD7645309FA2A581485A"
		"F6263E313B79A2F5",	// 71 hex, 9 dw
		"3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEF90399660FC938A9016"
		"5B042A7CEFADB307",
		"5F939258DB7DD90E1934F8C70B0DFEC2EED25B8557EAC9C80E2E198"
		"F8CDBECD86B12053",
		"3676854FE24141CB98FE6D4B20D02B4516FF702350EDDB0826779C8"
		"13F0DF45BE8112F4" };
		break;
	case 409: EC = { 409,87,0,0,1,2, //  ВАРИАНТ 4  
		"21A5C2C8EE9FEB5C4B9A753B7B476B7FD6422EF1F3DD674761FA99"
		"D6AC27C8A9A197B272822F6CD57A55AA4F50AE317B13545F",	// 102 hex, 13 dw
		"10000000000000000000000000000000000000000000000000001E2AAD6A612"
		"F33307BE5FA47C3C9E052F838164CD37D9A21173",	// 103 hex, 13 dw
		"15D4860D088DDB3496B0C6064756260441CDE4AF1771D4DB01FFE5B"
		"34E59703DC255A868A1180515603AEAB60794E54BB7996A7",	// 103 hex, 13 dw
		"61B1CFAB6BE5F32BBFA78324ED106A7636B9C5A7BD198D0158AA4F"
		"5488D08F38514F1FDF4B4F40D2181B3681C364BA0273C706" };	// 102 hex, 13 dw
		break;
	case 571: EC = { 571,10,5,2,1,2, //  ВАРИАНТ 5  
		"2F40E7E2221F295DE297117B7F3D62F5C6A97FFCB8CEFF1CD6BA8CE"
		"4A9A18AD84FFABBD8EFA59332BE7AD6756A66E294AFD185A"
		"78FF12AA520E4DE739BACA0C7FFEFF7F2955727A",	// 143 hex, 18 dw
		"3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
		"FFFFFFFFFFFFFFFFE661CE18FF55987308059B186823851E"
		"C7DD9CA1161DE93D5174D66E8382E9BB2FE84E47",
		"303001D34B856296C16C0D40D3CD7750A93D1D2955FA80AA5F40FC8"
		"DB7B2ABDBDE53950F4C0D293CDD711A35B67FB1499AE6003"
		"8614F1394ABFA3B4C850D927E1E7769C8EEC2D19",
		"37BF27342DA639B6DCCFFFEB73D69D78C6C27A6009CBBCA1980F853"
		"3921E8A684423E43BAB08A576291AF8F461BB2A8B3531D2F"
		"0485C19B16E2F1516E23DD3C1A4827AF1B8AC15B" };
		break;
	default: EC = {};
		break;
	}
}
