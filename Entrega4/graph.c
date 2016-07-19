/*
|---------------------------|
|Laboratório de Programaçăo |
|---------------------------|
 */


/*
-|--------------------------------------------------|
-|Bruno Guilherme Ricci Lucas		nUSP 4460596
-|André Luiz Abdalla Silveira		nUSP 8030353
-|Matheus Takeshi Yabiku		    nUSP 7629949
-|--------------------------------------------------|
- */

#include "graph.h"
#define PI 3.14159265


/* a biblioteca graph ira cuidar da parte grafica do jogo em geral, e dos controles */
int direcao (double teta){
	double section;
	int i;

	if (teta >= 348.75 || teta < 11.25)
		return 0;

	section = 11.25;
	for (i=1; i<16; i++){
		if (teta >= section && teta < section + 22.5)
			return (i -16) * (-1);
		section += 22.5;
	}

	return -1;
}

int escala (double pos){
	int graphPos;

	pos = pos + 25.6e6;
	graphPos = (int)pos/64000;

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


void insere (Fila *lista, Object *nave, int id, int total){
    Celula *p;
    Projectile proj;

    /* Gera um projetil */
	proj.mass = nave->mass/100;
    proj.time = clock();
    proj.id = id;

    /*Coloca a posicao inicial do projetil de acordo com a imagem da nave, para que o projetil saia sempre da ponta */
    if(direcao(nave->dir) == 0){
        proj.posx = nave->posx + (36*64000);
        proj.posy = nave->posy + (17.5*64000);
        proj.velx = nave->velx + 10000000;
		proj.vely = nave->vely + 0;
    }

    if(direcao(nave->dir) == 1){
        proj.posx = nave->posx + (36*64000);
        proj.posy = nave->posy + (8.75*64000);
        proj.velx = nave->velx + 7500000;
		proj.vely = nave->vely - 2500000;
    }

    if(direcao(nave->dir) == 2){
        proj.posx = nave->posx + (35.5*64000);
        proj.posy = nave->posy - (0.5*64000);
        proj.velx = nave->velx + 6000000;
		proj.vely = nave->vely - 4000000;
    }

    if(direcao(nave->dir) == 3){
        proj.posx = nave->posx + (26.25*64000);
        proj.posy = nave->posy - (0.5*64000);
        proj.velx = nave->velx + 4000000;
		proj.vely = nave->vely - 6000000;
    }

    if(direcao(nave->dir) == 4){
        proj.posx = nave->posx + (18*64000);
        proj.posy = nave->posy + (1*64000);
        proj.velx = nave->velx + 0;
		proj.vely = nave->vely - 10000000;
    }

    if(direcao(nave->dir) == 5){
        proj.posx = nave->posx + (8.75*64000);
        proj.posy = nave->posy - (1*64000);
        proj.velx = nave->velx - 2500000;
        proj.vely = nave->vely - 7500000; 
    }

    if(direcao(nave->dir) == 6){
        proj.posx = nave->posx - (1*64000);
        proj.posy = nave->posy - (1*64000);
        proj.velx = nave->velx - 4000000;
        proj.vely = nave->vely - 6000000;
    }

    if(direcao(nave->dir) == 7){
        proj.posx = nave->posx - (1*64000);
        proj.posy = nave->posy + (8.75*64000);
        proj.velx = nave->velx - 6000000;
        proj.vely = nave->vely - 4000000;
    }

    if(direcao(nave->dir) == 8){
        proj.posx = nave->posx - (1*64000);
        proj.posy = nave->posy + (17.5*64000);
        proj.velx = nave->velx - 10000000;
        proj.vely = nave->vely + 0;
    }

    if(direcao(nave->dir) == 9){
        proj.posx = nave->posx - (1*64000);
        proj.posy = nave->posy + (26.25*64000);
        proj.velx = nave->velx - 7500000;
        proj.vely = nave->vely + 2500000;
    }

    if(direcao(nave->dir) == 10){
        proj.posx = nave->posx - (0.5*64000);
        proj.posy = nave->posy + (35.5*64000);
        proj.velx = nave->velx - 6000000;
        proj.vely = nave->vely + 4000000;
    }

    if(direcao(nave->dir) == 11){
        proj.posx = nave->posx + (8.25*64000);
        proj.posy = nave->posy + (36*64000);
        proj.velx = nave->velx - 4000000;
        proj.vely = nave->vely + 6000000;
    }

    if(direcao(nave->dir) == 12){
        proj.posx = nave->posx + (17.5*64000);
        proj.posy = nave->posy + (36*64000);
        proj.velx = nave->velx + 0;
        proj.vely = nave->vely + 10000000;
    }

    if(direcao(nave->dir) == 13){
        proj.posx = nave->posx + (26.25*64000);
        proj.posy = nave->posy + (36*64000);
        proj.velx = nave->velx + 2500000;
        proj.vely = nave->vely + 7500000;
    }

    if(direcao(nave->dir) == 14){
        proj.posx = nave->posx + (35.5*64000);
        proj.posy = nave->posy + (35.5*64000);
        proj.velx = nave->velx + 4000000;
        proj.vely = nave->vely + 6000000;
    }

    if(direcao(nave->dir) == 15){
        proj.posx = nave->posx + (36*64000);
        proj.posy = nave->posy + (26.25*64000);
        proj.velx = nave->velx + 6000000;
        proj.vely = nave->vely + 4000000;
    }


    p = malloc(sizeof (*p));
    p->projectile = proj;

    p->next = lista->ini; /*p next recebe a primeira celula da lista */
    lista->ini = p; /* p é o novo 1o elem */
    id++;
    total ++;
}

/*Apaga um projetil da lista */
void apaga(Fila *lista, Projectile proj, int total){
	Celula *p = lista->ini;
	Celula *mata;
    /* Busca um projetil usando seu identificador (int id) e o apaga da lista */
    while (p != NULL) {
        if (p->projectile.id == proj.id) {
            mata = p;
            p = p->next;
            total --;
            break;
        }
        p = p->next;
    }
    free(mata);
}

/* As colisoes serao feitas por retangulos, ou seja, sera verificado se um dos vertices de uma imagem se encontra dentro de outra */
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
    if((nave1->posxGraph >= nave2->posxGraph && nave1->posxGraph <= nave2->posxGraph + 35 && nave1->posyGraph >= nave2->posyGraph && nave1->posyGraph <= nave2->posyGraph + 35)
       || (nave1->posxGraph + 35 >= nave2->posxGraph && nave1->posxGraph + 35 <= nave2->posxGraph + 35 && nave1->posyGraph >= nave2->posyGraph && nave1->posyGraph <= nave2->posyGraph + 35)
       || (nave1->posxGraph >= nave2->posxGraph && nave1->posxGraph <= nave2->posxGraph + 35 && nave1->posyGraph + 35 >= nave2->posyGraph && nave1->posyGraph + 35 <= nave2->posyGraph + 35)
       || (nave1->posxGraph + 35 >= nave2->posxGraph && nave1->posxGraph + 35 <= nave2->posxGraph + 35 && nave1->posyGraph + 35 >= nave2->posyGraph && nave1->posyGraph + 35 <= nave2->posyGraph + 35)){
        nave1->life = 0;
        nave2->life = 0;
     }
}

/*Verifica colisao entre nave(35x35) e planeta(206x206) */
void colisao_nave_planeta(Object *planeta, Object * nave){
    if((nave->posxGraph >= planeta->posxGraph && nave->posxGraph - 80 <= planeta->posxGraph + 80 && nave->posyGraph >= planeta->posyGraph - 80 && nave->posyGraph <= planeta->posyGraph + 80)
       || (nave->posxGraph + 35 >= planeta->posxGraph - 80 && nave->posxGraph + 35 <= planeta->posxGraph + 80 && nave->posyGraph >= planeta->posyGraph - 80 && nave->posyGraph <= planeta->posyGraph + 80)
       || (nave->posxGraph >= planeta->posxGraph - 80 && nave->posxGraph <= planeta->posxGraph + 80 && nave->posyGraph + 35 >= planeta->posyGraph - 80 && nave->posyGraph + 35 <= planeta->posyGraph + 80)
       || (nave->posxGraph + 35 >= planeta->posxGraph - 80 && nave->posxGraph + 35 <= planeta->posxGraph + 80 && nave->posyGraph + 35 >= planeta->posyGraph - 80 && nave->posyGraph + 35 <= planeta->posyGraph + 80))
        nave->life = 0;
}

/*Verifica colisao entre projetil(7x7) e planeta(206x206) */
void colisao_proj_planeta(Fila *lista, Projectile proj, Object *planeta, int total){
    if((proj.posxGraph >= 297 && proj.posxGraph <= 297 + 206 && proj.posyGraph >= 297 && proj.posyGraph <= 297 + 206)
       || (proj.posxGraph + 7 >= 297 && proj.posxGraph + 7 <= 297 + 206 &&  proj.posyGraph >= 297 && proj.posyGraph <= 297 + 206)
       || (proj.posxGraph >= 297 && proj.posxGraph <= 297 + 206 && proj.posyGraph + 7 >= 297 && proj.posyGraph + 7 <= 297 + 206)
       || (proj.posxGraph + 7 >= 297 && proj.posxGraph + 7 <= 297 + 206 && proj.posyGraph + 7 >= 297 && proj.posyGraph + 7 <= 297 + 206)){
       if(total > 0){ 
        apaga(lista, proj, total);
	   }
    }
}


/* recebe a tecla lida e faz as mudanças necessárias */
void keyboard(int key, Object *nave1, Object *nave2, Fila *lista, int id, int total){
    double v1, v2;

    /* tecla 'w' */
    if (key == 119)
        nave1->accel = 1;

    /* tecla 's' 
    else if (key == 115)
        nave1->accel = 0;*/

    /* tecla 'a' */
    else if (key == 97){
        nave1->dir -= 11.25;
        if (nave1->dir < 0)
            nave1->dir += 360;
        v1 = sqrt(pow(nave1->velx, 2) + pow(nave1->vely, 2));
        nave1->vely = v1 * sin((nave1->dir)*PI/180.0);
        nave1->velx = v1 * cos((nave1->dir)*PI/180.0);
    }

    /* tecla 'd' */
    else if (key == 100){
        nave1->dir += 11.25;
        if (nave1->dir >= 360)
            nave1->dir -= 360;
        v1 = sqrt(pow(nave1->velx, 2) + pow(nave1->vely, 2));
        nave1->vely = v1 * sin((nave1->dir)*PI/180.0);
        nave1->velx = v1 * cos((nave1->dir)*PI/180.0);
    }

    /*tecla 'espaco'*/
    else if (key == 32){
        insere(lista, nave1, id, total);
    }

    /* tecla 'cima' */
    else if (key == 65362)
        nave2->accel = 1;

    /* tecla 'baixo' */
    else if (key == 65364)
        nave2->accel = 0;

    /* tecla 'esquerda' */
    else if (key == 65361){
        nave2->dir -= 11.25;
        if (nave2->dir < 0)
            nave2->dir += 360;
        v2 = sqrt(pow(nave2->velx, 2) + pow(nave2->vely, 2));
        nave2->vely = v2 * sin((nave2->dir)*PI/180.0);
        nave2->velx = v2 * cos((nave2->dir)*PI/180.0);
    }

    /* tecla 'direita' */
    else if (key == 65363){
        nave2->dir += 11.25;
        if (nave2->dir >= 360)
            nave2->dir -= 360;
        v2 = sqrt(pow(nave2->velx, 2) + pow(nave2->vely, 2));
        nave2->vely = v2 * sin((nave2->dir)*PI/180.0);
        nave2->velx = v2 * cos((nave2->dir)*PI/180.0);
    }


	/*tecla '0' do teclado numérico*/

	else if (key == 65438){
        insere(lista, nave2, id, total);
	}
}
