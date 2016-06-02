#include <stdio.h>
#include <unistd.h>
#include "xwc.h"
#include <math.h>
#include <time.h>
#include "estruturas.h"
#define PI 3.14159265

#define G 6.67e10-11
#define MAX 50

int direcao (double teta){
	double section;
	int i;

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

/*Calcula a posicao das naves de acordo com as forca as em acao */
void update(Object *nave1, Object *nave2, Object *planeta, double frame){
    double G1 /*gravidade entre naves */, G2 /*gravidade entre nave1 e planeta*/ ,G3 /*gravidade entre nave 2 e planeta*/;
    double Fx1 /*resultante x da nave 1*/, Fy1 /*resultante y na nave 1, etc*/, Fx2, Fy2;

	Fx1 = Fy1 = Fx2 = Fy2 = 0;

    G1 = gravit(nave1->posx, nave1->posy, nave1->mass, nave2->posx, nave2->posy, nave2->mass);
    G2 = gravit(nave1->posx, nave1->posy, nave1->mass, planeta->posx, planeta->posy, planeta->mass);
    G3 = gravit(nave2->posx, nave2->posy, nave2->mass, planeta->posx, planeta->posy, planeta->mass);

    /*desloca o eixo da nave 1 de acordo com forças da terra e da nave 2*/
    Fx1 += resx(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);
    Fy1 += resy(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);

    Fx1 += resx(G2, nave1->posx, nave1->posy, 0, 0);
    Fy1 += resy(G2, nave1->posx, nave1->posy, 0, 0);
    moving_eixo(Fx1, Fy1, nave1, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/

	/*desloca o eixo da nave 2 de acordo com forças da terra e da nave 1 */
    Fx2 += resx(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);
    Fy2 += resy(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);

    Fx2 += resx(G3, nave2->posx, nave2->posy, 0, 0);
    Fy2 += resy(G3, nave2->posx, nave2->posy, 0, 0);
    moving_eixo(Fx2, Fy2, nave2, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/


}

/* recebe a tecla lida e faz as mudanças necessárias */
void keyboard(int key, Object *nave1, Object *nave2){
	
	/* tecla 'w' */
	if (key == 119) 
		nave1->accel = 1;

	/* tecla 's' */
	else if (key == 115)
		nave1->accel = 0;

	/* tecla 'a' */
	else if (key == 97)
		nave1->dir = (nave1->dir + 11.25)%360;

	/* tecla 'd' */
	else if (key == 100){
		nave1->dir -= 11.25;
		if (nave1->dir < 0)
			nave1->dir += 360;
	}

	/* tecla 'cima' */
	else if (key == 65362)
		nave2->accel = 1;

	/* tecla 'baixo' */
	else if (key == 65364)
		nave2->accel = 0;

	/* tecla 'esquerda' */
	else if (key == 65361)
		nave2->dir = (nave2->dir + 11.25)%360;

	/* tecla 'direita' */
	else if (key == 65363){
		nave2->dir -= 11.25;
		if (nave2->dir < 0)
			nave2->dir += 360;
	}

}








int main() {
	PIC P1, P2, P; 
	PIC Nave[16];
	WINDOW *w1;
	MASK msklua, msknave[16];
	int key;

	Object* planeta = malloc(sizeof	(*planeta));
	Object* nave1 = malloc(sizeof (*nave1));
	Object* nave2 = malloc(sizeof(*nave2));
	double time;
	double duration;
	int projs;
	double frame;
	int dir1, dir2;
	int i;
	float n;
	char names[MAX];
	time_t time1, time2; 
	float timedif;
	Projectile *model;
	time1 = clock();

	/* INICIALIZACAO DA PARTE GRAFICA */
		
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

		InitKBD(w1);

	/* FIM DA INICIALIZACAO DA PARTE GRAFICA */

	/* INICIALIZACAO */

		FILE *arquivo = fopen("config.txt", "r");

		if (arquivo == NULL) {
			printf("Erro! Arquivo 'config.txt' não encontrado!\n");
			return 0;
		}

		/* Recebe a primeira linha */
		fscanf(arquivo, "%lf %lf %lf",
			   &planeta->radius,
			   &planeta->mass,
			   &time
			   );

		/*Recebe a nave1*/
		fscanf(arquivo, "%s %lf %lf %lf %lf %lf",
			   names,
			   &nave1->mass,
			   &nave1->posx,
			   &nave1->posy,
			   &nave1->velx,
			   &nave1->vely
			   );
		memset(nave1->name, 0, MAX);
		strncpy(nave1->name, names, MAX-1);

	   /*Recebe a nave2*/
		fscanf(arquivo, "%s %lf %lf %lf %lf %lf",
			   names,
			   &nave2->mass,
			   &nave2->posx,
			   &nave2->posy,
			   &nave2->velx,
			   &nave2->vely
			   );
		memset(nave2->name, 0, MAX);
		strncpy(nave2->name, names, MAX-1);


		/*Recebe a linha 3*/
		fscanf(arquivo, "%d %lf",
			   &projs,
			   &duration
			   );
		/*Aloca o array de projeteis */
		model = malloc(projs * sizeof(Projectile));

		/*Configura os projeteis */
		for(i = 0; i < projs; i++){
			fscanf(arquivo, "%lf %lf %lf %lf",
				   &model[i].mass,
				   &model[i].velx,
				   &model[i].vely,
				   &model[i].time
				   );
		} 



		fclose(arquivo);

		nave1->dir = 180;
		nave2->dir = 0;
		nave1->accel = 0;
		nave2->accel = 0;
	
	/* FIM DA INICIALIZACAO */

	/* colocar direcao, tratamento das teclas, controle */

	while (nave1->life != 0 && nave2->life != 0){

		if (WCheckKBD(w1)){
			key = WGetKey(w1);
			key = WLastKeySym();
			keyboard(key, nave1, nave2);
		}

		if (nave1->accel == 1){
		/* colocar velocidade dependendo da nave1->dir */
		}
		
		if (nave2->accel == 1){
		/* colocar velocidade dependendo da nave2->dir */
		}
		update(nave1, nave2, planeta, frame);

		/* como faz o programa esperar um pouco? */

		dir1 = direção(nave1->dir);
		dir2 = direção(nave2->dir);
		
		imprimetela(w1, P, Nave[dir1], msknave[dir1], Nave[dir2], msknave[dir2], posx1, posy1, posx2, posy2);

		/* verificação de colisões */

	}












	/* Da free nos structs e arrays */
	free(model);
	free(planeta);
	free(nave1);
	free(nave2);
	return 0;
}


