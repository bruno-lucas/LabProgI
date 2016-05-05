#ifndef cinematica
#define cinematica

#include <stdio.h>
#include <limits.h>
#include "estruturas.h"

// fun��o respons�vel por modificar as velocidades e posi��o do corpo
void desloca_eixo (double * pos, double * vel, double acel, double frame);

// fun��o que recebe as componentes x e y  do vetor posi��o, velocidade e resultante
// e determina os pr�ximos passos  dos objetos
void moving_eixo (double Fx, double Fy, Object *nave, double frame);



#endif
