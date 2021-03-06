#include <stdio.h>
#include <unistd.h>
#include "xwc.h"
#include <math.h>
#define PI 3.14159265

int direcao (double x, double y){
	double val, teta, section;
	int i;

	/* Pega o angulo de acordo com a velocidade da nave */
	val = 180.0 / PI;
	teta = atan2 (y,x) * val;
	if (teta < 0)
		teta = teta + 360;

	if (teta >= 348.75 || teta < 11.25)
		return 0;

	section = 11.25;
	for (i=1; i<16; i++){
		if (teta >= section && teta < section + 22.5)
			return i;
		section += 22.5;
	}

	return -1;
}


void imprimetela(WINDOW *w1, PIC P, PIC P1, MASK msk1, PIC P2, MASK msk2, int posx1, int posy1, int posx2, int posy2){
	PutPic(w1, P, 0, 0, 801, 801, 0, 0);
	SetMask(w1, msk1);
	PutPic(w1, P1, 0, 0, 35, 35, posx1, posy1);
	UnSetMask(w1);
	SetMask(w1, msk2);
	PutPic(w1, P2, 0, 0, 35, 35, posx2, posy2);
	UnSetMask(w1);
}




int main() {

	PIC P1, P2, P; 
	PIC Nave[16];
	WINDOW *w1;
	MASK msklua, msknave[16];

	/* posicoes e velocidades das naves */
	int posx1, posy1, posx2, posy2, i, dir1, dir2;
	double velx1, vely1, velx2, vely2;

	w1 = InitGraph(801,801, "NightSky");
	P = NewPic(w1, 801, 801); // será a pic que mantém o estado da janela (universo + lua)
	P1 = ReadPic(w1, "Sky.xpm", NULL); // pic do universo
	P2 = ReadPic(w1, "Moon.xpm", NULL); // pic da lua

	for (i=0; i<16; i++)
		msknave[i] = NewMask(w1, 35, 35);

	/* carrega as imagens da nave */
	Nave[0] = ReadPic(w1, "Nave0.xpm", msknave[0]);
	Nave[1] = ReadPic(w1, "Nave1.xpm", msknave[1]);
	Nave[2] = ReadPic(w1, "Nave2.xpm", msknave[2]);
	Nave[3] = ReadPic(w1, "Nave3.xpm", msknave[3]);
	Nave[4] = ReadPic(w1, "Nave4.xpm", msknave[4]);
	Nave[5] = ReadPic(w1, "Nave5.xpm", msknave[5]);
	Nave[6] = ReadPic(w1, "Nave6.xpm", msknave[6]);
	Nave[7] = ReadPic(w1, "Nave7.xpm", msknave[7]);
	Nave[8] = ReadPic(w1, "Nave8.xpm", msknave[8]);
	Nave[9] = ReadPic(w1, "Nave9.xpm", msknave[9]);
	Nave[10] = ReadPic(w1, "Nave10.xpm", msknave[10]);
	Nave[11] = ReadPic(w1, "Nave11.xpm", msknave[11]);
	Nave[12] = ReadPic(w1, "Nave12.xpm", msknave[12]);
	Nave[13] = ReadPic(w1, "Nave13.xpm", msknave[13]);
	Nave[14] = ReadPic(w1, "Nave14.xpm", msknave[14]);
	Nave[15] = ReadPic(w1, "Nave15.xpm", msknave[15]);

	/* Máscara para a Lua */
	msklua = NewMask(w1, 205, 205);
	WFillArc(msklua, 0, 0, 0, 360*64, 205, 205, 1);

	/* Desenha o arquivo Sky.xpm */
	PutPic(w1, P1, 0, 0, 800, 800, 0, 0);

	/* desenha Lua na janela principal */
	SetMask(w1,msklua);
	PutPic(w1, P2, 0, 0, 205, 205, 300, 300);
	UnSetMask(w1);

	/* P recebe tela base */
	PutPic(P, w1, 0, 0, 801, 801, 0, 0);


	/* Lê duas linhas (uma para nave 1 e outra para nave 2 e as desenha na tela (apagando o que tinha antes) */
	while (true)){
		scanf("%d %d %lf %lf", &posx1, &posy1, &velx1, &vely1);
		scanf("%d %d %lf %lf", &posx2, &posy2, &velx2, &vely2);

		dir1 = direcao(velx1, vely1);
		dir2 = direcao(velx2, vely2);

		imprimetela(w1, P, Nave[dir1], msknave[dir1], Nave[dir2], msknave[dir2], posx1, posy1, posx2, posy2);
	}

	CloseGraph();

	return 0;
}

	
	













