#include <stdio.h>
#include <unistd.h>
#include "xwc.h"


int main(int ac, char **av)
{
	PIC P1, P2, P3, Aux, P; 
	WINDOW *w1;
	MASK msk, msknave;

	w1 = InitGraph(801,801, "NightSky");
	P = NewPic(w1, 801, 801); // será a pic que mantém o estado da janela (universo + lua)
	P1 = ReadPic(w1, "Sky.xpm", NULL); // pic do universo
	P2 = ReadPic(w1, "Moon.xpm", NULL); // pic da lua
	Aux = NewPic(w1, 205, 205);


	/* Máscara para a Lua */
	msk = NewMask(w1, 205, 205);
	WFillArc(msk, 0, 0, 0, 360*64, 205, 205, 1);

	/* Máscara para a nave */
	msknave = NewMask(w1, 35, 35);
	P3 = ReadPic(w1, "Nave0.xpm", msknave); // leitura da imagem da nave na orientação 0

	/* Desenha o arquivo Sky.xpm */
	puts("Desenhando a figura do arquivo Sky.xpm.");
	puts("Tecle <enter>"); getchar();
	PutPic(w1, P1, 0, 0, 800, 800, 0, 0);

	/* Desenha parte do Sky em Aux */
	PutPic(Aux, w1, 300, 300, 205, 205, 0, 0);
	
	/* Seta máscara para lua */
	SetMask(Aux,msk);
	puts("Tecle <enter>"); getchar();
	/* desenha lua em Aux */
	PutPic(Aux, P2, 0,0, 205, 205, 0, 0);
	/* desenha Aux na janela principal */
	PutPic(w1, Aux, 0, 0, 205, 205, 300, 300);

	/* copia o estado da janela principal para P, para apagar a tela posteriormente */
	puts("Tecle <enter>"); getchar();
	PutPic(P, w1, 0, 0, 801, 801, 0, 0);
	
	/* seta a máscara da nave e a desenha em (100, 60) << arbitrário */
	SetMask(w1, msknave); /* ATENÇÃO : essa máscara só serve pro Nave0.xpm, porque foi montada quando li a imagem */
	PutPic(w1, P3, 0, 0, 35, 35, 100, 60);

	/* tira a máscara, volta pra imagem só do céu com lua, e coloca máscara novamente */
	puts("Tecle <enter>"); getchar();
	UnSetMask(w1);
	PutPic(w1, P, 0, 0, 801, 801, 0, 0);
	SetMask(w1, msknave);
	/* e coloca outra nave em algum outro lugar, no caso (100, 100) */
	PutPic(w1, P3, 0, 0, 35, 35, 100, 100);

	/* novamente, agora para (350, 350) */
	puts("Tecle <enter>"); getchar();
	UnSetMask(w1);
	PutPic(w1, P, 0, 0, 801, 801, 0, 0);
	SetMask(w1, msknave);

	PutPic(w1, P3, 0, 0, 35, 35, 350, 350);
	puts("Tecle <enter>"); getchar();


	CloseGraph();

	return 0;
}
