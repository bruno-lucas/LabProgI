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
}Projectile;

typedef struct {
   int life;
   char name[MAX];
   double radius;
   double posx;
   double posy;
   double velx;
   double vely;
   double mass;
   int projectiles;
   double resx;
   double resy;
}Object;

#endif