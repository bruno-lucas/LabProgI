
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

#define G 0.667
#define MAX 50

typedef struct{
    double posx;
    double posy;
    double velx;
    double vely;
    double mass;
    double time;
}Projectile;

struct _Celula{
	Projectile projectile;
	struct _Celula *next;
};

typedef struct _Celula Celula;

typedef struct {
   int life;
   char name[MAX];
   double radius;
   double posx;
   double posy;
   double velx;
   double vely;
   double mass;
   Celula projectile_hash[4];
   double resx;
   double resy;
}Object;

#endif
