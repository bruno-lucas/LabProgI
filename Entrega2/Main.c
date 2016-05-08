
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



#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <time.h>

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



/*Calcula a posição das naves de acordo com as forças em ação */
void update(Object *nave1, Object *nave2, Object *planeta, double frame){
    double G1 /*gravidade entre naves */, G2 /*gravidade entre nave1 e planeta*/ ,G3 /*gravidade entre nave 2 e planeta*/;
    double Fx1 /*resultante x da nave 1*/, Fy1 /*resultante y na nave 1, etc*/, Fx2, Fy2;

	Fx1 = Fy1 = Fx2 = Fy2 = 0;

    G1 = gravit(nave1->posx, nave1->posy, nave1->mass, nave2->posx, nave2->posy, nave2->mass);
    G2 = gravit(nave1->posx, nave1->posy, nave1->mass, planeta->posx, planeta->posy, planeta->mass);
    G3 = gravit(nave2->posx, nave2->posy, nave2->mass, planeta->posx, planeta->posy, planeta->mass);

    /*desloca o eixo da nave 1 de acordo com forças da terra e da nave 2*/
    Fx1 += resx(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);
    Fy1 += resy(G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);

    Fx1 += resx(G2, nave1->posx, nave1->posy, 0, 0);
    Fy1 += resy(G2, nave1->posx, nave1->posy, 0, 0);
    moving_eixo(Fx1, Fy1, nave1, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/

	/*desloca o eixo da nave 2 de acordo com forças da terra e da nave 1 */
    Fx2 += resx(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);
    Fy2 += resy(-G1, nave1->posx, nave1->posy, nave2->posx, nave2->posy);

    Fx2 += resx(G3, nave2->posx, nave2->posy, 0, 0);
    Fy2 += resy(G3, nave2->posx, nave2->posy, 0, 0);
    moving_eixo(Fx2, Fy2, nave2, frame);
    /*Espaço para o OpenGL renderizar (posteriormente)*/


}

/*Imprime as posições das naves 1 e 2 */
void imprime(Object *nave){
	int px = ((int) nave->posx);
	int py = ((int) nave->posy);
	printf("%d %d %.02f %.02f\n", px, py, nave->velx, nave->vely);
}


int main(){

	Object* planeta = malloc(sizeof	(*planeta));
	Object* nave1 = malloc(sizeof (*nave1));
	Object* nave2 = malloc(sizeof(*nave2));
	double time;
	double duration;
	Projectile *projectile;
	int projeteis;
	double frame;
	int i;
	float n;
	char names[MAX];
	time_t time1, time2; 
	float timedif;

	time1 = clock();


	/*Lê o arquivo e inicializa o programa*/

		FILE *arquivo = fopen("config.txt", "r");

		if (arquivo == NULL) {
			printf("Erro! Arquivo 'config.txt' não encontrado!\n");
			return 0;
		}

		/* Recebe a primeira linha */
		fscanf(arquivo, "%lf %lf %lf",
			   &planeta->radius,
			   &planeta->mass,
			   &time
			   );

		/*Recebe a nave1*/
		fscanf(arquivo, "%s %lf %lf %lf %lf %lf",
			   names,
			   &nave1->mass,
			   &nave1->posx,
			   &nave1->posy,
			   &nave1->velx,
			   &nave1->vely
			   );
		memset(nave1->name, 0, MAX);
		strncpy(nave1->name, names, MAX-1);

	   /*Recebe a nave2*/
		fscanf(arquivo, "%s %lf %lf %lf %lf %lf",
			   names,
			   &nave2->mass,
			   &nave2->posx,
			   &nave2->posy,
			   &nave2->velx,
			   &nave2->vely
			   );
		memset(nave2->name, 0, MAX);
		strncpy(nave2->name, names, MAX-1);


		/*Recebe a linha 3*/
		fscanf(arquivo, "%d %lf",
			   &projeteis,
			   &duration
			   );
		/*Aloca o array de projéteis */
		projectile = malloc(projeteis * sizeof(Projectile));

		/*Configura os projéteis */
		for(i = 0; i < projeteis; i++){
			fscanf(arquivo, "%lf %lf %lf %lf %lf",
				   &projectile[i].mass,
				   &projectile[i].posx,
				   &projectile[i].posy,
				   &projectile[i].velx,
				   &projectile[i].vely
				   );
		}



		fclose(arquivo);

		printf("Digite o tempo que durara a rodada (em segundos):");
		scanf("%f", &n);

		frame = 1; /*provisório*/
		while(timedif < n){
			update(nave1, nave2, planeta, frame);
			imprime(nave1);
			imprime(nave2);
			time2 = clock();
			timedif = (float) (time2 - time1) / (float)CLOCKS_PER_SEC;
			printf("%f \n", timedif);
		}

	/* Da free nos structs e arrays */
	free(projectile);
	free(planeta);
	free(nave1);
	free(nave2);
	return 0;
}
