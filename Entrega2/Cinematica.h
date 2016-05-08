#ifndef cinematica
#define cinematica

#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "estruturas.h"

// função responsável por modificar as velocidades e posição do corpo
void desloca_eixo (double * pos, double * vel, double acel, double frame);

// função que recebe as componentes x e y  do vetor posição, velocidade e resultante
// e determina os próximos passos  dos objetos
void moving_eixo (double Fx, double Fy, Object *nave, double frame);



#endif
