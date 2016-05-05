#ifndef resultante
#define resultante

#include <math.h>
#define G 0.00000000667

/* recebe a posi��o e massa de um corpo1, posi��o e massa de outro corpo2 e calcula a for�a gravitacional no corpo 1*/
/* (apenas intensidade) */
double gravit(double x1, double y1, double m1, double x2, double y2, double m2);

/* decomp�e a for�a nos eixos x e y, respectivamente */
double resx(double F, double x1, double y1, double x2, double y2);

double resy(double F, double x1, double y1, double x2, double y2);

#endif