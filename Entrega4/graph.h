/*
|---------------------------|
|Laboratório de Programação |
|---------------------------|
 */


/*
|----------------------------------------------|
|Bruno Guilherme Ricci Lucas      nºUSP 4460596
|André Luiz Abdalla Silveira 	  nºUSP 8030353
|Matheus Takeshi Yabiku		  nºUSP 7629949
|----------------------------------------------|
 */



#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "estruturas.h"
#include "xwc.h"


int direcao (double teta);

int escala (double pos);

void imprimetela(WINDOW *w1, PIC P, PIC P1, MASK msk1, PIC P2, MASK msk2, Object *nave1, Object *nave2, PIC Tiro, Fila *lista);

void insere (Fila *lista, Object *nave, int id, int total);

/*Apaga um projetil da lista */
void apaga(Fila *hash, Projectile proj, int total);

/*Verifica colisao entre um pojetil(7x7) e uma nave(35x35) */
void colisao_proj_nave(Projectile proj, Object *nave);

 /*Verifica colisao entre duas naves(35x35) */
void colisao_nave_nave(Object *nave1, Object *nave2);

/*Verifica colisao entre nave(35x35) e palneta(206x206) */
void colisao_nave_planeta(Object *planeta, Object * nave);

/*Verifica colisao entre projetil(7x7) e planeta(206x206) */
void colisao_proj_planeta(Fila *lista, Projectile proj, Object *planeta, int total);

/* recebe a tecla lida e faz as mudanças necessárias */
void keyboard(int key, Object *nave1, Object *nave2, Fila *lista, int id, int total);

#endif // GRAPH_H_INCLUDED
