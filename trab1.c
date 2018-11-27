
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//Retorna a parte inteira do maior numero do vetor
int maior(float vetor[], int n){
    int maior;
    for (int i = 0; i < n; i++){
        if (i == 0){
            maior = vetor[i];
        }
        if (vetor[i] > maior){
            maior = vetor[i];
        }
    }
    return maior;
}
// Returna o indice do maior numero no vetor
int maiorindex(float vetor[], int n){
    float maior;
    int j = 0;
    for (int i = 0; i < n; i++){
        if (i == 0){
            maior = vetor[i];
        }
        if (vetor[i] > maior){
            maior = vetor[i];
            j = i;
        }
    }
    return j;
}

void troca(float *n, float *m){
    float aux;
    aux = *n;
    *n = *m;
    *m = aux;
}

void bubblesort(float vetor[], int n, float rotulo[]){
    int i, j;
    for (i = 0; i< n  - 1; i++){
        for (j = 0; j < n - i -1; j++){
            if (vetor[j] > vetor[j+1]){
                troca(&vetor[j], &vetor[j+1]);
                troca(&rotulo[j], &rotulo[j+1]);
                }
        }
    }
}

int main(){
    FILE *config = fopen("config.txt", "r");
    char *pathteste = malloc(sizeof(char)*500), *pathtreino = malloc(sizeof(char)*500),
    *pathsaida = malloc(sizeof(char)*50), *pathaux = malloc(sizeof(char)*50);
    if (config == NULL) {
        printf ("Erro na abertura de arquivo\n");
        exit (1);
    }
    fscanf(config, "%s", pathtreino);
    // printf("%s\n", pathtreino);
    fscanf(config, "%s", pathteste);
    // printf("%s\n", pathteste);
    FILE *file = fopen(pathtreino, "r"), *file2 = fopen(pathteste, "r");
    char lixoc;
    int  linhas = 0, linhas2 = 0;
    // Calculo do numero de linhas de treino
    while(!feof(file)){
        fscanf(file, "%c,", &lixoc);
        if (lixoc == '\n'){
            linhas++;
        }
    }
    rewind(file);
    // Calculo do numero de linhas teste
    while(!feof(file2)){
        fscanf(file2, "%c,", &lixoc);
        if (lixoc == '\n'){
            linhas2++;
        }
    }
    rewind(file2);
    fscanf(config, "%s", pathsaida);
    strcpy(pathaux, pathsaida);
    int loop = 0;
    while(!feof(config)){
        int kcon;
        float r;
        char *conv = malloc(sizeof(char)*30), numero[20], tipod;
        fscanf(config, "%d, %c,", &kcon, &tipod);
        if (kcon == -1){
            break;
        }
        strcpy(pathsaida,pathaux);
        strcpy(conv,"predicao_");
        sprintf(numero, "%d", loop + 1);
        strcat(conv, numero);
        strcat(conv, ".txt");
        strcat(pathsaida, conv);
        free(conv);
        FILE *saida = fopen(pathsaida, "w");
        if (saida == NULL) {
        exit (1);
        }
        float lixo;
        if (file == NULL) {
        printf ("Erro na abertura de arquivo! Programa terminado...");
        exit (1);
        }
        int nvirgulas = 0, i, j = 0;

        do {
            fscanf(file, "%c", &lixoc);
            if (lixoc == ','){
                nvirgulas++;
            }
        }
        while(lixoc != '\n');
        printf("%d -- %d --- %d\n", linhas, linhas2, nvirgulas);
        rewind(file);
        //alocando memoria para a matriz de floats do arq 1
        float **vetor = malloc(sizeof(float*) * linhas);
        for (i = 0; i < linhas; i++){
            vetor[i] = malloc(sizeof(float)*(nvirgulas+1));
        }
        //alocando memoria para a matriz de floats do arq 2
        float **vetor2 = malloc(sizeof(float*) * linhas2);
        for (i = 0; i < linhas2; i++){
            vetor2[i] = malloc(sizeof(float)*(nvirgulas + 1));
        }
        //alocando memoria para o resultado da distancia
        float **vetor3 = malloc(sizeof(float*) * linhas2);
        for (i = 0; i < linhas2; i++){
            vetor3[i] = malloc(sizeof(float)*linhas);
        }
        //alocando memoria para o rotulo do vetor;
        float **vetor4 = malloc(sizeof(float*) * linhas2);
        for (i = 0; i < linhas2; i++){
            vetor4[i] = malloc(sizeof(float)*linhas);
        }
        // Colocando valores no vetor de treino
        for(i = 0; i < linhas; i++){
            for (j = 0; j < nvirgulas+1; j++){
                fscanf(file, "%f,", &vetor[i][j]);
            }
        }
        /* printar o vetor de treino */
        // for(i = 0; i < linhas; i++){
        //     for (j = 0; j < nvirgulas+1; j++){
        //         printf("%.2f ", vetor[i][j]);
        //     }
        //     putchar('\n');
        // }
        // Colocando valores no vetor de teste
        for(i = 0; i < linhas2; i++){
            for (j = 0; j < nvirgulas+1; j++){
                fscanf(file2, "%f,", &vetor2[i][j]);
            }
        }
        /* printar o vetor de teste */
        // for(i = 0; i < linhas2; i++){
        //     for (j = 0; j < nvirgulas+1; j++){
        //         printf("%.2f ", vetor2[i][j]);
        //     }
        //     putchar('\n');
        // }
        // Colocando rotulos no vetor 4
        for (i = 0; i < linhas2; i++){
            //  printf("Rotulos vetor %d:\n", i+1);
            for (j = 0; j < linhas; j++){
                vetor4[i][j] = vetor[j][nvirgulas];
            }
        }
        // Distancia Euclidiana
        if (tipod == 'E'){
            float soma = 0, subtracao;
            for(i = 0; i < linhas2; i++){
                for(j = 0; j < linhas; j++){
                    for (int k = 0; k < nvirgulas; k++){
                        subtracao = vetor2[i][k] - vetor[j][k];
                        subtracao = subtracao * subtracao;
                        soma = subtracao + soma;
                    }
                    vetor3[i][j] = sqrt(soma);
                    soma = 0;
                }
            }
        // print vetor de distancias euclidianas de cada ponto j em realção a estrela i
        // for (i = 0; i < linhas2; i++){
        //     printf("Vetor %d:\n", i+1);
        //     for (j = 0; j < linhas; j++){
        //         printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]);
        //     }
        // }
        //sorted(Euclidiana)
            for (i = 0; i < linhas2; i++){
                // printf("Vetor %d:\n", i+1);
                bubblesort(vetor3[i], linhas, vetor4[i]);
                for (j = 0; j < linhas; j++){
                    // printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]);
                }
            }
        }
        //Distancia de Mikowski 
        if (tipod == 'M'){
            fscanf(config, "%f", &r);
            float soma = 0;
            for(i = 0; i < linhas2; i++){
                for(j = 0; j < linhas; j++){
                    for (int k = 0; k < nvirgulas; k++){
                        soma = pow(fabs(vetor2[i][k] - vetor[j][k]), r) + soma;
                    }
                    vetor3[i][j] = pow(soma, 1/r);
                    soma = 0;
                }
            }
        // print vetor de distancias mikowskianas de cada ponto j em realção a estrela i
        // for (i = 0; i < linhas2; i++){
        //     printf("Vetor %d:\n", i+1);
        //     for (j = 0; j < linhas; j++){
        //         printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]);
        //     }
        // }
        //sorted(Mikowskiana)
            for (i = 0; i < linhas2; i++){
                // printf("Vetor %d:\n", i+1);
                bubblesort(vetor3[i], linhas, vetor4[i]);
                for (j = 0; j < linhas; j++){
                    // printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]);
                }
            }
        }
        // Distancia de Chebyshev
        if (tipod == 'C'){
            float max;
            for(i = 0; i < linhas2; i++){
                for(j = 0; j < linhas; j++){
                    for (int k = 0; k < nvirgulas; k++){
                        if (k == 0){
                        max = fabs(vetor2[i][k] - vetor[j][k]);
                        }
                        if (fabs(vetor2[i][k] - vetor[j][k]) > max){
                            max = fabs(vetor2[i][k] - vetor[j][k]);
                        }
                    }
                    vetor3[i][j] = max;
                }
            }
        //print vetor de distancias chebyshevianas de cada ponto j em realção a estrela i
        // for (i = 0; i < linhas2; i++){
        //     printf("Vetor %d:\n", i+1);
        //     for (j = 0; j < linhas; j++){
        //         printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]);
        //     }
        // }
        //sorted Chebyshev
            for (i = 0; i < linhas2; i++){
                // printf("Vetor %d:\n", i+1);
                bubblesort(vetor3[i], linhas, vetor4[i]);
                if (i == 1|| i == 16)
                for (j = 0; j < linhas; j++){
                    // printf("%.2f ---- %.2f\n", vetor3[i][j], vetor4[i][j]-1);
                }
            }
        }
        // k primeiros
        int nrotulos, aux;
        nrotulos = maior(vetor4[0], linhas);
        float **vetoraux = calloc(linhas2,sizeof(float*)), *rotulos = malloc(sizeof(float)*linhas2);
        for(i = 0; i < linhas2; i++){
            vetoraux[i] = calloc(nrotulos,sizeof(float));
        }

        for (i = 0; i < linhas2; i++){
            for (j = 0; j < kcon; j++){
                aux = vetor4[i][j] - 1;
                vetoraux[i][aux]++;
            }
            rotulos[i] = maiorindex(vetoraux[i], nrotulos);
        }
        // for (i = 0; i < linhas2; i++){
        //     printf("%.2f\n", rotulos[i]);
        // }
        //Comparando rotulos descobertos com rotulos testes
        int **confusao = malloc(sizeof(int*)*nrotulos);
        for (i = 0; i < nrotulos; i++){
            confusao[i] = malloc(sizeof(int)*nrotulos);
        }for(i = 0; i < nrotulos; i++){
            for(j = 0; j < nrotulos; j++){
                confusao[i][j] = 0;
            }
        }
        float correto = 0;
        for (i = 0; i < linhas2; i++){
            // printf("%.2f -- %.2f\n", rotulos[i], vetor2[i][n]-1);
            confusao[(int)vetor2[i][nvirgulas]-1][(int) rotulos[i]]++;
            // confusao[(int) rotulos[i]][(int)vetor2[i][n]-1]++;
            if (( rotulos[i] + 1) == vetor2[i][nvirgulas])
                correto++;
        }
        //printando no arquivo
        fprintf(saida, "%.2f\n\n",correto/linhas2);
        // printf("%.2f\n",correto/linhas2);
        for(i = 0; i < nrotulos; i++){
            for(j = 0; j < nrotulos; j++){
                fprintf(saida,"%d ", confusao[i][j]);
                //printf("%d ", confusao[i][j]);

            }
            fputc('\n', saida);
            // putchar('\n');
        }
        fputc('\n', saida);
        for (i = 0; i < linhas2; i++){
            fprintf(saida,"%d\n", (int) rotulos[i]);
            // printf("%d\n", (int) rotulos[i] );
        }
        //Printando a matriz 1
        // for(i = 0; i < linhas; i++){
        //     for (j = 0; j < n+1; j++){
        //          printf("%.2f ", vetor[i][j]);
        //     }
        //      putchar('\n');
        // }
        //Printando a matriz 2
        // for(i = 0; i < linhas2; i++){
        //     for (j = 0; j < n; j++){
        //         printf("%.2f ", vetor2[i][j]);
        //     }
        //     putchar('\n');
        // }
        //liberando memoria
        for(i = 0; i < linhas; i++){   
            free(vetor[i]);
        }

        for(i = 0; i < linhas2; i++){
            free(vetor2[i]);
            free(vetor3[i]);
            free(vetor4[i]);
            free(vetoraux[i]);
        }
        for(i = 0; i < nrotulos; i++){   
            free(confusao[i]);
        }
        // free(str);
        // free(str2);
        free(vetor);
        free(vetor2);
        free(vetor3);
        free(vetor4);
        free(confusao);
        free(vetoraux);
        free(rotulos);
        rewind(file);
        rewind(file2);
        fclose(saida);
        loop++;
        kcon = -1;
        puts("****");
        }
    free(pathtreino);
    free(pathteste);
    free(pathsaida);
    free(pathaux);
    fclose(file);
    fclose(file2);
    fclose(config);
}