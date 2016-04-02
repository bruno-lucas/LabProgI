#include<stdio.h>
#include<stdlib.h>
/*
#include"cinematica.h"
#include"resultante.h"
*/
typedef struct{
    int posx;
    int posy;
    int velx;
    int vely;
    double mass;
}Projectile;

typedef struct {
   int life;
   char * name;
   double radius;
   int posx;
   int posy;
   int velx;
   int vely;
   double mass;
   int projectiles;
}Object;

/*
void update(){


}
*/

int main(){

Object * planeta;
Object * nave1;
Object * nave2;
double time;
double duration;
Projectile *projectile;
int projeteis;
int i;

/*Lê o arquivo e inicializa o programa*/

    FILE *arquivo = fopen("config.txt", "r");

    if (arquivo == NULL) {
        printf("Erro! Arquivo '%s' não encontrado!\n");
        return 0;
    }

    /* Recebe a primeira linha */
    fscanf(arquivo, "%f %f %f",
           &planeta->radius,
           &planeta->mass,
           &time
           );


    /*Recebe a nave1*/
    fscanf(arquivo, "%s %f %d %d %d %d",
           &nave1->name,
           &nave1->mass,
           &nave1->posx,
           &nave1->posy,
           &nave1->velx,
           &nave1->vely
           );

   /*Recebe a nave2*/
    fscanf(arquivo, "%s %f %d %d %d %d",
           &nave2->name,
           &nave2->mass,
           &nave2->posx,
           &nave2->posy,
           &nave2->velx,
           &nave2->vely
           );
    /*Recebe a linha 3*/
    fscanf(arquivo, "%d %f",
           &projeteis,
           &duration
           );

    for(i = 0; i < projeteis; i++){
        projectile[i] = malloc(projeteis * sizeof(Projectile));
    }

    for(i = 0; i < projeteis; i++){
        fscanf("%f %f %f %f %f",
               &projectile[i]->mass,
               &projectile[i]->posx,
               &projectile[i]->posy,
               &projectile[i]->velx,
               &projectile[i]->vely
               );
    }



    fclose(arquivo);

    for(i = 0; i<projeteis; i++)
        printf("%f %f %f %f %f \n", &projectile[i]->mass, &projectile[i]->posx, &projectile[i]->posy, &projectile[i]->velx, &projectile[i]->vely);
    printf("%f \n", &nave1->posy);
    printf("%f \n", &planeta->mass);
    printf("%f \n", &nave2->velx);

free(projectile);
return 0;
}
