#include <stdio.h>
#include <unistd.h>
#include "xwc.h"
#include <math.h>
#include <time.h>
#include "estruturas.h"
#include "Cinematica.h"
#include "resultante.h"
#include <string.h>
#include <stdlib.h>
#define PI 3.14159265

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

int escala (double pos){
	int graphPos;

	pos = pos + 25.6e6;
	graphPos = (int)pos/32000;

	return graphPos;
}


void imprimetela(WINDOW *w1, PIC P, PIC P1, MASK msk1, PIC P2, MASK msk2, Object *nave1, Object *nave2, PIC Tiro, Fila *lista){
	Celula *p;

	PutPic(w1, P, 0, 0, 801, 801, 0, 0);
	SetMask(w1, msk1);
	PutPic(w1, P1, 0, 0, 35, 35, nave1->posxGraph, nave1->posyGraph);
	UnSetMask(w1);
	SetMask(w1, msk2);
	PutPic(w1, P2, 0, 0, 35, 35, nave2->posxGraph, nave2->posyGraph);
	UnSetMask(w1);

    for(p = lista->ini; p != NULL; p = p->next)
		PutPic(w1, Tiro, 0, 0, 7, 7, p->projectile.posxGraph, p->projectile.posyGraph);
}

void inicia(Fila *lista){
    lista = malloc(sizeof(lista));
    lista->ini = NULL;
    lista->fim = NULL;
}

void insere (Fila *lista, Object *nave, int id){
    Celula *p;
    Projectile proj;

    /* Copia os parâmetros definidos no arquivo config e gera um projetil */
    proj.velx = nave->velx * 1.2;
    proj.vely = nave->vely * 1.2;
	 proj.mass = nave->mass/100;
    proj.time = clock();
    proj.id = id;

    if(direcao(nave->dir) == 0){
        proj.posx = nave->posx + (36*32000 - 25.6e6);
        proj.posy = nave->posy + (17.5*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 1){
        proj.posx = nave->posx + (36*32000 - 25.6e6);
        proj.posy = nave->posy + (8.75*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 2){
        proj.posx = nave->posx + (35.5*32000 - 25.6e6);
        proj.posy = nave->posy - (0.5*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 3){
        proj.posx = nave->posx + (26.25*32000 - 25.6e6);
        proj.posy = nave->posy - (1*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 4){
        proj.posx = nave->posx + (17.5*32000 - 25.6e6);
        proj.posy = nave->posy - (1*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 5){
        proj.posx = nave->posx + (8.75*32000 - 25.6e6);
        proj.posy = nave->posy - (1*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 6){
        proj.posx = nave->posx - (1*32000 - 25.6e6);
        proj.posy = nave->posy - (1*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 7){
        proj.posx = nave->posx - (1*32000 - 25.6e6);
        proj.posy = nave->posy + (8.75*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 8){
        proj.posx = nave->posx - (1*32000 - 25.6e6);
        proj.posy = nave->posy + (17.5*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 9){
        proj.posx = nave->posx - (1*32000 - 25.6e6);
        proj.posy = nave->posy + (26.25*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 10){
        proj.posx = nave->posx - (0.5*32000 - 25.6e6);
        proj.posy = nave->posy + (35.5*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 11){
        proj.posx = nave->posx + (8.25*32000 - 25.6e6);
        proj.posy = nave->posy + (36*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 12){
        proj.posx = nave->posx + (17.5*32000 - 25.6e6);
        proj.posy = nave->posy + (36*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 13){
        proj.posx = nave->posx + (26.25*32000 - 25.6e6);
        proj.posy = nave->posy + (36*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 14){
        proj.posx = nave->posx + (35.5*32000 - 25.6e6);
        proj.posy = nave->posy + (35.5*32000 - 25.6e6);
    }

    if(direcao(nave->dir) == 15){
        proj.posx = nave->posx + (36*32000 - 25.6e6);
        proj.posy = nave->posy + (26.25*32000 - 25.6e6);
    }


    p = malloc(sizeof (*p));
    p->projectile = proj;
    p->num = lista->fim->num;

    lista->fim->next = p;
    lista->fim = lista->fim->next;

    if(lista->ini == NULL){
        lista->ini = lista->fim;
    }
    id++;
}

/*Apaga um projetil da lista */
void apaga(Fila *hash, Projectile proj){
	Celula *p;
	Celula *mata;

	for (p = hash->ini; p->next->projectile.id != proj.id; p = p->next){
		if(p == hash->fim)
			return;
	}

	mata = p->next;
	p->next = p->next->next;

	free(mata);
}

/*Verifica colisao entre um pojetil(7x7) e uma nave(35x35) */
void colisao_proj_nave(Projectile proj, Object *nave){
    if((proj.posxGraph >= nave->posxGraph && proj.posxGraph <= nave->posxGraph + 35 && proj.posyGraph >= nave->posyGraph && proj.posyGraph <= nave->posyGraph + 35)
       || (proj.posxGraph + 7 >= nave->posxGraph && proj.posxGraph + 7 <= nave->posxGraph + 35 && proj.posyGraph >= nave->posyGraph && proj.posyGraph <= nave->posyGraph + 35)
       || (proj.posxGraph >= nave->posxGraph && proj.posxGraph <= nave->posxGraph + 35 && proj.posyGraph + 7 >= nave->posyGraph && proj.posyGraph + 7 <= nave->posyGraph + 35)
       || (proj.posxGraph + 7 >= nave->posxGraph && proj.posxGraph + 7 <= nave->posxGraph + 35 && proj.posyGraph + 7 >= nave->posyGraph && proj.posyGraph + 7 <= nave->posyGraph + 35))
        nave->life = 0;

}
 /*Verifica colisao entre duas naves(35x35) */
void colisao_nave_nave(Object *nave1, Object *nave2){
    if((nave1->posxGraph >= nave2->posxGraph && nave1->posxGraph <= nave2->posxGraph + 10 && nave1->posyGraph >= nave2->posyGraph && nave1->posyGraph <= nave2->posyGraph + 10)
       || (nave1->posxGraph + 7 >= nave2->posxGraph && nave1->posxGraph + 7 <= nave2->posxGraph + 10 && nave1->posyGraph >= nave2->posyGraph && nave1->posyGraph <= nave2->posyGraph + 10)
       || (nave1->posxGraph >= nave2->posxGraph && nave1->posxGraph <= nave2->posxGraph + 10 && nave1->posyGraph + 7 >= nave2->posyGraph && nave1->posyGraph + 7 <= nave2->posyGraph + 10)
       || (nave1->posxGraph + 7 >= nave2->posxGraph && nave1->posxGraph + 7 <= nave2->posxGraph + 10 && nave1->posyGraph + 7 >= nave2->posyGraph && nave1->posyGraph + 7 <= nave2->posyGraph + 10))
        nave1->life = 0;
        nave2->life = 0;
}

/*Verifica colisao entre nave(35x35) e palneta(206x206) */
void colisao_nave_planeta(Object *planeta, Object * nave){
    if((300 >= nave->posxGraph && 300 <= nave->posxGraph + 35 && 300 >= nave->posyGraph && 300 <= nave->posyGraph + 35)
       || (300 + 206 >= nave->posxGraph && 300 + 206 <= nave->posxGraph + 35 && 300 >= nave->posyGraph && 300 <= nave->posyGraph + 35)
       || (300 >= nave->posxGraph && 300 <= nave->posxGraph + 35 && 300 + 206 >= nave->posyGraph && 300 + 206 <= nave->posyGraph + 35)
       || (300 + 206 >= nave->posxGraph && 300 + 206 <= nave->posxGraph + 35 && 300 + 206 >= nave->posyGraph && 300 + 206 <= nave->posyGraph + 35))
        nave->life = 0;
}

/*Verifica colisao entre projetil(7x7) e planeta(206x206) */
void colisao_proj_planeta(Fila *lista, Projectile proj, Object *planeta){
    if((300 >= proj.posxGraph && 300 <= proj.posxGraph + 7 && 300 >= proj.posyGraph && 300 <= proj.posyGraph + 7)
       || (300 + 206 >= proj.posxGraph && 300 + 206 <= proj.posxGraph + 7 && 300 >= proj.posyGraph && 300 <= proj.posyGraph + 7)
       || (300 >= proj.posxGraph && 300 <= proj.posxGraph + 7 && 300 + 206 >= proj.posyGraph && 300 + 206 <= proj.posyGraph + 7)
       || (300 + 206 >= proj.posxGraph && 300 + 206 <= proj.posxGraph + 7 && 300 + 206 >= proj.posyGraph && 300 + 206 <= proj.posyGraph + 7))
        apaga(lista, proj);
}

/*Calcula a posicao das naves de acordo com as forca as em acao */
void update(Object *nave1, Object *nave2, Object *planeta, double frame, Fila *lista){

    time_t time2 = clock();
    Celula *p;
    double G1 /*gravidade entre naves */, G2 /*gravidade entre nave1 e planeta*/ ,G3 /*gravidade entre nave 2 e planeta*/;
    double G4 /*gravidade proj-nave1 */ , G5 /*gravidade proj-nave2*/, G6 /*gravidade proj-planeta*/;
    double Fx1 /*resultante x da nave 1*/, Fy1 /*resultante y na nave 1, etc*/, Fx2, Fy2, Fxp, Fyp;

	Fx1 = Fy1 = Fx2 = Fy2 = Fxp = Fyp = 0;

    G1 = gravit(nave1->posx, nave1->posy, nave1->mass, nave2->posx, nave2->posy, nave2->mass);
    G2 = gravit(nave1->posx, nave1->posy, nave1->mass, planeta->posx, planeta->posy, planeta->mass);
    G3 = gravit(nave2->posx, nave2->posy, nave2->mass, planeta->posx, planeta->posy, planeta->mass);


    /*desloca o eixo da nave 1 de acordo com forças da terra e da nave 2*/
    Fx1 += resx(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy, nave1->accel);
    Fy1 += resy(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy, nave1->accel);

    Fx1 += resx(G2, nave1->posx, nave1->posy, 0, 0, nave1->accel);
    Fy1 += resy(G2, nave1->posx, nave1->posy, 0, 0, nave1->accel);
    moving_eixo(Fx1, Fy1, nave1, frame);
	 nave1->posxGraph = escala(nave1->posx);
	 nave1->posyGraph = escala(nave1->posy);

    /*desloca o eixo da nave 2 de acordo com forças da terra e da nave 1 */
    Fx2 += resx(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy, nave2->accel);
    Fy2 += resy(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy, nave2->accel);

    Fx2 += resx(G3, nave2->posx, nave2->posy, 0, 0, nave2->accel);
    Fy2 += resy(G3, nave2->posx, nave2->posy, 0, 0, nave2->accel);
    moving_eixo(Fx2, Fy2, nave2, frame);
	 nave2->posxGraph = escala(nave2->posx);
	 nave2->posyGraph = escala(nave2->posy);

    for(p = lista->ini; p != NULL; p = p->next){
        G4 = gravit(p->projectile.posx, p->projectile.posy, p->projectile.mass, nave1->posx, nave1->posy, nave1->mass);
        G5 = gravit(p->projectile.posx, p->projectile.posy, p->projectile.mass, nave2->posx, nave2->posy, nave2->mass);
        G6 = gravit(p->projectile.posx, p->projectile.posy, p->projectile.mass, planeta->posx, planeta->posy, planeta->mass);

        Fxp += resx(G4, p->projectile.posx, p->projectile.posy, nave1->posx, nave1->posy, 0);
        Fxp += resx(G5, p->projectile.posx, p->projectile.posy, nave2->posx, nave2->posy, 0);
        Fxp += resx(G6, p->projectile.posx, p->projectile.posy, 0, 0, 0);

        Fyp += resy(G4, p->projectile.posx, p->projectile.posy, nave1->posx, nave1->posy, 0);
        Fyp += resy(G5, p->projectile.posx, p->projectile.posy, nave2->posx, nave2->posy, 0);
        Fyp += resy(G6, p->projectile.posx, p->projectile.posy, 0, 0, 0);
        moving_eixo_proj(Fxp, Fyp, &p->projectile, frame);
		  p->projectile.posxGraph = escala(p->projectile.posx);
		  p->projectile.posyGraph = escala(p->projectile.posy);
		  Fxp = 0;
		  Fyp = 0;
    }

    colisao_nave_nave(nave1, nave2);
    colisao_nave_planeta(planeta, nave1);
    colisao_nave_planeta(planeta, nave2);

	for (p = lista->ini; p != NULL; p = p->next){
        if(time2 - p->projectile.time >= 3){
            apaga(lista, p->projectile);
        }
		colisao_proj_nave(p->projectile, nave1);
		colisao_proj_nave(p->projectile, nave2);
		colisao_proj_planeta(lista, p->projectile, planeta);
	}


}

/* recebe a tecla lida e faz as mudanças necessárias */
void keyboard(int key, Object *nave1, Object *nave2, Fila *lista, int id){

	/* tecla 'w' */
	if (key == 119)
		nave1->accel = 1;

	/* tecla 's' */
	else if (key == 115)
		nave1->accel = 0;

	/* tecla 'a' */
	else if (key == 97){
		nave1->dir = nave1->dir + 11.25;
		if (nave1->dir >= 360)
			nave1->dir = nave1->dir - 360;
	}

	/* tecla 'd' */
	else if (key == 100){
		nave1->dir -= 11.25;
		if (nave1->dir < 0)
			nave1->dir += 360;
	}

	/*tecla 'espaco'*/
	else if (key == 32){
        insere(lista, nave1, id);
	}

	/* tecla 'cima' */
	else if (key == 65362)
		nave2->accel = 1;

	/* tecla 'baixo' */
	else if (key == 65364)
		nave2->accel = 0;

	/* tecla 'esquerda' */
	else if (key == 65361){
		nave2->dir = nave2->dir + 11.25;
		if (nave2->dir >= 360)
			nave2->dir = nave2->dir - 360;
	}

	/* tecla 'direita' */
	else if (key == 65363){
		nave2->dir -= 11.25;
		if (nave2->dir < 0)
			nave2->dir += 360;
	}


	/*tecla '0' do teclado numérico*/

	else if (key == 65438){
        insere(lista, nave2, id);
	}
}




int main() {
	PIC P1, P2, P, Tiro;
	PIC Nave[16];
	WINDOW *w1;
	MASK msklua, msknave[16];
	int key;
	PIC P1WIN, P2WIN, DRAW;
	MASK mskP1win, mskP2win, mskDraw;

	Object* planeta = malloc(sizeof	(*planeta));
	Object* nave1 = malloc(sizeof (*nave1));
	Object* nave2 = malloc(sizeof(*nave2));
	double time;
	int projs;
	double duration;
	Fila* lista;
	double frame;
	int dir1, dir2;
	int i;
	int id = 0;
	float n;
	char names[MAX];
	time_t time1, time2;
	time1 = clock();
	time2 = clock();
	Celula *p;
	Celula *aux;

	/* INICIALIZACAO DA PARTE GRAFICA */

		w1 = InitGraph(801,801, "NightSky");
		P = NewPic(w1, 801, 801); // será a pic que mantém o estado da janela (universo + lua)
		P1 = ReadPic(w1, "Sky.xpm", NULL); // pic do universo
		P2 = ReadPic(w1, "Moon.xpm", NULL); // pic da lua
		Tiro = ReadPic(w1, "tiro.xpm", NULL); // pic dos projeteis

		mskP1win = NewMask(w1, 400, 200);
		mskP2win = NewMask(w1, 400, 200);
		mskDraw = NewMask(w1, 400, 200);

		P1WIN = ReadPic(w1, "p1win.xpm", mskP1win);
		P2WIN = ReadPic(w1, "p2win.xpm", mskP2win);
		DRAW = ReadPic(w1, "draw.xpm", mskDraw);

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

		fclose(arquivo);

		nave1->dir = 180;
		nave2->dir = 0;
		nave1->accel = 0;
		nave2->accel = 0;
		nave1->life = nave2->life = 1;
		frame = 0.1;
	/* FIM DA INICIALIZACAO */


	while (time2 - time1 <= duration || (nave1->life != 0 || nave2->life != 0)){

		/* checando próxima tecla inserida (se houver) e tratando ela */
		if (WCheckKBD(w1)){
			key = WGetKey(w1);
			key = WLastKeySym();
			keyboard(key, nave1, nave2, lista, id);
		}


		update(nave1, nave2, planeta, frame, lista);

		/*programa espera um décimo de segundo para garantir jogabilidade */
		usleep(100000);

		dir1 = direcao(nave1->dir);
		dir2 = direcao(nave2->dir);


		/* antes daqui é necessário tratar as posições pra deixar num int dentro da janela, mesma coisa para os projeteis */

		imprimetela(w1, P, Nave[dir1], msknave[dir1], Nave[dir2], msknave[dir2], nave1, nave2, Tiro, lista);

		time2 = clock();

	}

	PutPic(w1, P, 0, 0, 801, 801, 0, 0);
	if (nave1->life == 1 && nave2->life == 0){
		SetMask(w1,mskP1win);
		PutPic(w1, P1WIN, 0, 0, 400, 200, 200, 300);
		UnSetMask(w1);
	}

	else if (nave1->life == 0 && nave2->life == 1){
		SetMask(w1,mskP2win);
		PutPic(w1, P2WIN, 0, 0, 400, 200, 200, 300);
		UnSetMask(w1);
	}

	else {
		SetMask(w1,mskDraw);
		PutPic(w1, DRAW, 0, 0, 400, 200, 200, 300);
		UnSetMask(w1);
	}



	  puts("Tecle <enter>"); getchar();





	CloseGraph();
	/* Da free nos structs e arrays */
	free(planeta);
	free(nave1);
	free(nave2);

	for(p = lista->ini; p != NULL; p = p->next){
        aux = p;
        free(aux);
	}

	free(lista);

	return 0;
}



