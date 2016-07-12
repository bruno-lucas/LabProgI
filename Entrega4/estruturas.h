
/*
|---------------------------|
|Laboratório de Programação |
|---------------------------|
 */


/*
|----------------------------------------------|
|Bruno Guilherme Ricci Lucas      nºUSP 4460596|
|André Luiz Abdalla Silveira 	  nºUSP 8030353|
|Matheus Takeshi Yabiku		  nºUSP 7629949    |
|----------------------------------------------|
 */

#ifndef estruturas_H
#define estruturas_H
#include<time.h>

#define G 6.67e-11
#define MAX 50


typedef struct{
    double posx;
    double posy;
    double velx;
    double vely;
    double dir;
    double mass;
    time_t time;
    int accel;
	 int posxGraph;
	 int posyGraph;
	 int id;
}Projectile;

struct _Celula{
	Projectile projectile;
	struct _Celula *next;
};

typedef struct _Celula Celula;

typedef struct{
    Celula *ini;
    }Fila;

typedef struct {
   int life;
   char name[MAX];
   double radius;
   double posx;
   double posy;
   double velx;
   double vely;
   double mass;
   double resx;
   double resy;
   double dir;
   int accel;
	int posxGraph;
	int posyGraph;
}Object;

#endif
