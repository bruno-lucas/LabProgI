#include <stdio.h>
#include <limits.h>


void moving_eixo (double Fx, double Fy, double posx, double posy, double velx, double vely, double massa) {
    double ax, ay;

    ax = Fx/massa;
    desloca_eixo(&posx, &velx, ax, frame);

    ay = Fy/massa;
    desloca_eixo(&posy, &vely, ay, frame);
}




private void desloca_eixo (double * pos, double * vel, double acel, double frame) {
    // passo 1 -- modifica posição usando a fórmula do MUV
     pos = pos + vel*frame + (acel*frame*frame)/2;

    // passo 2 -- modifica velocidade no eixo em questão
    vel = vel + acel*frame;
}