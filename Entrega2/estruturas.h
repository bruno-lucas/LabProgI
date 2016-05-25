
/*
|---------------------------|
|Laborat�rio de Programa��o |
|---------------------------|
 */


/*
|----------------------------------------------|
|Bruno Guilherme Ricci Lucas      n�USP 4460596|
|Andr� Luiz Abdalla Silveira 	  n�USP 8030353|
|Matheus Takeshi Yabiku		  n�USP 7629949    |
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
