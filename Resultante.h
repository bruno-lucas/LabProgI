#ifndef resultante
#define resultante

#include <math.h>
#define G 0.00000000667

/* recebe a posição e massa de um corpo1, posição e massa de outro corpo2 e calcula a força gravitacional no corpo 1*/
/* (apenas intensidade) */
double gravit(double x1, double y1, double m1, double x2, double y2, double m2) {
    double d;

    d = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    return G*m1*m2/d;

}

/* decompõe a força nos eixos x e y, respectivamente */
double resx(double F, double x1, double y1, double x2, double y2){
    double d;
    double cos;

    d = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    d = sqrt(d);
    cos = (x2 - x1)/d;

    return F*cos;
}

double resy(double F, double x1, double y1, double x2, double y2){
    double d;
    double sen;

    d = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    d = sqrt(d);
    sen = (y2 - y1)/d;

    return F*sen;
}

#endif
