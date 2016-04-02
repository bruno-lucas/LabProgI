#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <math.h>

#define G 0.00000000667


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
   double resx;
   double resy;
}Object;

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


// função responsável por modificar as velocidades e posição do corpo
void desloca_eixo (double pos, double vel, double acel, double frame) {
    // passo 1 -- modifica posição usando a fórmula do MUV
     pos = pos + (vel*frame) + (acel*frame*frame)/2;

    // passo 2 -- modifica velocidade no eixo em questão
    vel = vel + acel*frame;
}

// função que recebe as componentes x e y  do vetor posição, velocidade e resultante
// e determina os próximos passos  dos objetos
void moving_eixo (double Fx, double Fy, Object *nave, double frame) {
    double ax, ay;

    ax = Fx/nave->mass;
    desloca_eixo(nave->posx, nave->velx, ax, frame);

    ay = Fy/nave->mass;
    desloca_eixo(nave->posy, nave->vely, ay, frame);
}


/*Calcula a posição das naves de acordo com as forças em ação */
void update(Object *nave1, Object *nave2, Object *planeta, double frame){
    double G1 /*gravidade entre naves */, G2 /*gravidade entre nave1 e planeta*/ ,G3 /*gravidade entre nave 2 e planeta*/;
    double Fx1 /*resultante x da nave 1*/, Fy1 /*resultante y na nave 1, etc*/, Fx2, Fy2;

    G1 = gravit(nave1->posx, nave1->posy, nave1->mass, nave2->posx, nave2->posy, nave2->mass);
    G2 = gravit(nave1->posx, nave1->posy, nave1->mass, planeta->posx, planeta->posy, planeta->mass);
    G1 = gravit(nave2->posx, nave2->posy, nave2->mass, planeta->posx, planeta->posy, planeta->mass);

    /*desloca o eixo de acordo com G1 */
    Fx1 = resx(G1, nave1->velx, nave1->vely, 0, 0);
    Fy1 = resy(G1, nave1->velx, nave1->vely, 0, 0);
    moving_eixo(Fx1, Fy1, nave1, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/

    Fx1 = resx(G2, nave1->velx, nave1->vely, 0, 0);
    Fy1 = resy(G2, nave1->velx, nave1->vely, 0, 0);
    moving_eixo(Fx1, Fy1, nave1, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/


    Fx2 = resx(G1, nave2->velx, nave2->vely, 0, 0);
    Fy2 = resy(G1, nave2->velx, nave2->vely, 0, 0);
    moving_eixo(Fx2, Fy2, nave2, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/

    Fx2 = resx(G3, nave2->velx, nave2->vely, 0, 0);
    Fy2 = resy(G3, nave2->velx, nave2->vely, 0, 0);
    moving_eixo(Fx2, Fy2, nave2, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/


}

/*Imprime as posições das naves 1 e 2 */
void imprime(Object *nave1, Object *nave2){
    printf("%f \n", &nave1->posx);
    printf("%f \n", &nave1->posy);
    printf("%f \n", &nave2->posx);
    printf("%f \n", &nave2->posy);
}


int main(){

Object * planeta;
Object * nave1;
Object * nave2;
double time;
double duration;
Projectile *projectile;
int projeteis;
double frame;
int i;
int n = 100;

/*Lê o arquivo e inicializa o programa*/

    FILE *arquivo = fopen("config.txt", "r");

    if (arquivo == NULL) {
        printf("Erro! Arquivo 'config.txt' não encontrado!\n");
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
    /*Aloca o array de projéteis */
    projectile = malloc(projeteis * sizeof(Projectile));

    /*Configura os projéteis */
    for(i = 0; i < projeteis; i++){
        fscanf("%f %d %d %d %d",
               &projectile[i].mass,
               &projectile[i].posx,
               &projectile[i].posy,
               &projectile[i].velx,
               &projectile[i].vely
               );
    }



    fclose(arquivo);

    i = 0;
    /*Vai chamar a função update n vezes (provisório) para simular as ações das forças */
    while(i < n){
        update(nave1, nave2, planeta, frame);
        imprime(nave1, nave2);
        i++;
    }

/* Da free no array de projéteis */
free(projectile);
return 0;
}
