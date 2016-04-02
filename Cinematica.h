#ifndef cinematica
#define cinematica

#include <stdio.h>
#include <limits.h>

// fun��o respons�vel por modificar as velocidades e posi��o do corpo
void desloca_eixo (double pos, double vel, double acel, double frame) {
    // passo 1 -- modifica posi��o usando a f�rmula do MUV
     pos = pos + (vel*frame) + (acel*frame*frame)/2;

    // passo 2 -- modifica velocidade no eixo em quest�o
    vel = vel + acel*frame;
}

// fun��o que recebe as componentes x e y  do vetor posi��o, velocidade e resultante
// e determina os pr�ximos passos  dos objetos
void moving_eixo (double Fx, double Fy, Object *nave) {
    double ax, ay;

    ax = Fx/massa;
    desloca_eixo(&nave->posx, &nave->velx, ax, frame);

    ay = Fy/massa;
    desloca_eixo(&nave->posy, &nave->vely, ay, frame);
}



#endif
