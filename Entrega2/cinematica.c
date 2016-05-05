#include "Cinematica.h"


void moving_eixo (double Fx, double Fy, Object *nave, double frame) {
    double ax, ay;

    ax = Fx/(nave->mass);
    desloca_eixo(&nave->posx, &nave->velx, ax, frame);

    ay = Fy/(nave->mass);
    desloca_eixo(&nave->posy, &nave->vely, ay, frame);
}

void desloca_eixo (double * pos, double * vel, double acel, double frame) {
    // passo 1 -- modifica posição usando a fórmula do MUV
    (* pos) = (* pos) + (* vel)*frame + (acel*frame*frame)/2;

    // passo 2 -- modifica velocidade no eixo em questão
    (* vel) = (* vel) + acel*frame;
}
