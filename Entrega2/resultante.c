
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

#include "Resultante.h"

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
