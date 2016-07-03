
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

#include "Cinematica.h"


void moving_eixo (double Fx, double Fy, Object *nave, double frame) {
    double ax, ay;

    ax = Fx/(nave->mass);
    desloca_eixo(&nave->posx, &nave->velx, ax, frame);

    ay = Fy/(nave->mass);
    desloca_eixo(&nave->posy, &nave->vely, ay, frame);
}

void moving_eixo_proj (double Fx, double Fy, Projectile *proj, double frame) {
	double ax, ay;

	ax = Fx/(proj->mass);
   desloca_eixo(&proj->posx, &proj->velx, ax, frame);

	ay = Fy/(proj->mass);
   desloca_eixo(&proj->posy, &proj->vely, ay, frame);
}

void desloca_eixo (double * pos, double * vel, double acel, double frame) {
    // passo 1 -- modifica posição usando a fórmula do MUV
    (* pos) = (* pos) + (* vel)*frame + (acel*frame*frame)/2;
    if ((* pos) > 25.6e6)
		(* pos) = (* pos) - 51.2e6;
	 if ((* pos) < -25.6e6)
		(* pos) = (* pos) + 51.2e6;

    // passo 2 -- modifica velocidade no eixo em questão
    (* vel) = (* vel) + acel*frame;
}

