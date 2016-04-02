#include<stdio.h>
#include<string.h>

void parser(Object *nave1, Object *nave2, Object *planeta, float time){
    FILE *arquivo = fopen("config.txt", "r");

    if (arquivo == NULL) {
        printf("Erro! Arquivo '%s' não encontrado!\n", argv[1]);
        return 0;
    }

    /* Recebe raio do planeta */
    fscanf(arquivo, "%f", &planeta.raio);

    /* Recebe massa do planeta */
    fscanf(arquivo, "%f", &planeta.mass);

    /* Recebe raio do planeta */
    fscanf(arquivo, "%f", &time);


    fclose(arquivo);
}
