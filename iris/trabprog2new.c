#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"distancias.h"

void subtracao(float **Amostra, float **Vizinhos, float **subtracoes, int linhasamostras, int linhasVizinhos, int colunasVizinhos){
    int i=0, j=0, l=0, m=0;
    while(l<linhasamostras){
        while(i<linhasVizinhos){
            while(j<(colunasVizinhos-1)){
                subtracoes[m][j] = Amostra[l][j] - Vizinhos[i][j];
                j++;
            }
            subtracoes[m][j] = Vizinhos[i][j];
            m++;
            i++;
            j=0;
        }
        l++;
        i=0;
        j=0;
    }
}

void subtracaovet(float **Amostra, float **Vizinhos, float **subtracoes, int linhasamostras, int linhasVizinhos){
    int i=0, j=0, l=0, m=0;
    while(l<linhasamostras){
        while(i<linhasVizinhos){
            while(j<1){
                subtracoes[m][j] = Amostra[l][j] - Vizinhos[i][j];
                j++;
            }
            subtracoes[m][j] = Vizinhos[i][j];
            m++;
            i++;
            j=0;
        }
        l++;
        i=0;
        j=0;
    }
}

void subtracaomodulo(float **Amostra, float **Vizinhos, float **subtracoes, int linhasamostras, int linhasVizinhos, int colunasVizinhos){
    int i=0, j=0, l=0, m=0;
    while(l<linhasamostras){
        while(i<linhasVizinhos){
            while(j<(colunasVizinhos-1)){
                subtracoes[m][j] = abs(Amostra[l][j] - Vizinhos[i][j]);
                j++;
            }
            subtracoes[m][j] = Vizinhos[i][j];
            m++;
            i++;
            j=0;
        }
        l++;
        i=0;
        j=0;
    }
}


void multiplicacao(float **Entrada, float **multiplicacoes, int linhasamostras, int linhasVizinhos, int colunasVizinhos, float n){
    int i, j;
    for(i=0; i<(linhasamostras * linhasVizinhos); i++){
        for(j=0; j<(colunasVizinhos-1); j++){
            multiplicacoes[i][j] = pow(Entrada[i][j],n);
        }
        multiplicacoes[i][j] = Entrada[i][j];
    }
}

void soma(float **Entrada, float **Saida, int linhasamostras, int linhasVizinhos, int colunasVizinhos){
    int i, j, k=0;
    for(i=0; i<(linhasamostras * linhasVizinhos); i++){
        for(j=0; j<2; j++){
            Saida[i][j] = 0;
        }
    }
    for(i=0; i<(linhasamostras * linhasVizinhos); i++){
        for(j=0; j<(colunasVizinhos-1); j++){
            Saida[i][k] = Saida[i][k] + Entrada[i][j];
        }
        k++;
        Saida[i][k] = Entrada[i][j];
        k=0;
    }
}

void somamat(float **Entrada, float **Saida, int linhasamostras, int colunasVizinhos){
    int i, j, k=0;
    for(i=0; i<linhasamostras; i++){
        for(j=0; j<2; j++){
            Saida[i][j] = 0;
        }
    }
    for(i=0; i<linhasamostras; i++){
        for(j=0; j<(colunasVizinhos-1); j++){
            Saida[i][k] = Saida[i][k] + Entrada[i][j];
        }
        k++;
        Saida[i][k] = Entrada[i][j];
        k=0;
    }
}

void multiplicacaovet(float **Entrada, float **multiplicacoes, int linhasamostras, int linhasVizinhos, float n){
    int i, j=0;
    for(i=0; i<(linhasamostras * linhasVizinhos); i++){
        multiplicacoes[i][j] = pow(Entrada[i][j],n);
        j++;
        multiplicacoes[i][j] = Entrada[i][j];
        j=0;
    }
}

void troca(float *n, float *m){
    float aux;
    aux = *n;
    *n = *m;
    *m = aux;
}

void bubblesort(float **vetor, int n, int w){
    int i, j;
    for (j = 0; j< n  - 1; j++){
        for (i = w; i < n - j -1; i++){
            if (vetor[i][0] > vetor[i+1][0]){
                troca(&vetor[i][0], &vetor[i+1][0]);
                troca(&vetor[i][1], &vetor[i+1][1]);
            }
        }
    }
}

void bubblesortmat(float **matriz, int n, int linhasteste, int linhastreino){
    int i, j, k;
    for(k=0; k<(linhastreino * linhasteste); k++){
        for (i = 0; i< n  - 1; i++){
            for (j = 0; j < n - i -1; j++){
                if (matriz[k][j] > matriz[k][j+1]){
                    troca(&matriz[k][j], &matriz[k][j+1]);
                }
            }
        }
    }
}

void kmenores(int k, float **distancias, float **kDistanciasMenores,int linhasTeste, int linhasTreino){
    int i, j, l=0;

    kDistanciasMenores = (float **) malloc(k * linhasTeste * sizeof(float*));
    for(i=0; i<(k * linhasTeste); i++){
        kDistanciasMenores[i] = (float *) malloc(2 * sizeof(float));
    }

    for(i=0; i<linhasTeste ; i++){
        for(j=0; (j + i*linhasTreino)<(k + i*linhasTreino); j++){
            kDistanciasMenores[j][0] = distancias[l][0];
            kDistanciasMenores[j][1] = distancias[l][1];
            l++;
        }
    }
}

void matrizrotulos(int linhasTeste, int linhasTreino, float **kDistanciasMenores, float **rotulos){
    int i=0, j, k=0;
    rotulos = (float **) malloc(linhasTeste * sizeof(float *));
    for(i=0; i<linhasTeste; i++){
        rotulos[i] = (float *) malloc(linhasTreino * sizeof(float));
    }
    while(i<(linhasTeste * linhasTreino)){
        for(j=0; j<linhasTreino; j++){
            rotulos[k][j] = kDistanciasMenores[i][1];
            i++;
        }
        k++;
    }
}

void maioresmat(int linhasTeste, int linhasTreino, int n, float **subtracoes, float **distancias){
    int i. j;
    for(i=0; i<(linhasTeste * linhasTreino); i++){
        distancias[i][0] = subtracoes[i][n-2];
        distancias[i][1] = subtracoes[i][n-1];
    }
}

void classificacao(float **rotulos, float *classificado, int linhasTeste, int linhasTreino){
    int i, j, k, n=0, **numeroRotulos;
    numeroRotulos = (float **) malloc(linhasTeste * sizeof(float *));
    for(i=0; i<linhasTeste; i++){
        numeroRotulos[i] = (float *) malloc(linhasTreino * sizeof(float));
    }
    classificado = (float *) malloc(linhasTeste * sizeof(float));
    for(i=0; i<linhasTeste; i++){
        for(k=0; k<linhasTreino; k++){
            for(j=0; j<linhasTreino; j++){
                if(rotulos[i][k] == rotulos[i][j]){
                    n++;
                }
                numeroRotulos[i][k] = n;
                n=0;
            }    
        }
    }
    for(i=0; i<linhasTeste; i++){
        for(k=0; k<linhasTreino; k++){
            for(j=0; j<linhasTreino; j++){
                if(numeroRotulos[i][k] <= numeroRotulos[i][j]){
                    k++;
                }
            }    
        }
        classificado[i] = numeroRotulos[i][k];
    }

}

int main(){

    char c, url[]="config.txt";
    int colunas=0, i=0, j=0, linhas=0, *todasColunas;
    int y;

    todasColunas = (int *) malloc(1 * sizeof(int));

    FILE *arq;
    arq = fopen(url, "r");
    if(arq == NULL){
        printf("Erro");
        exit(1);
    }
    //Conta o número de linhas e colunas
    while(fread (&c, sizeof(char), 1, arq)) {
        if(c != '\n') {
            colunas++;
        }else{
            y = linhas + 1;
            todasColunas = (int *) realloc(todasColunas, y * sizeof(int));
            if(linhas<3){
                todasColunas[linhas] = colunas + 1;
                linhas++;
                colunas = 0;
            }else{
                todasColunas[linhas] = colunas ;
                linhas++;
                colunas = 0;
            }
        }
    
    }

    char *arquivotreino, *arquivoteste, *predicoes, *modoDecalcular;
    int *numeroDeVizinhos;
    float **kDistanciasMenores, *raio, **distancia, **somastreino, **somasteste, **somas, **multiplicacoes, **subtracoes, **rotulos;

    arquivotreino = (char *) malloc(todasColunas[0] * sizeof(char));
    arquivoteste = (char *) malloc(todasColunas[1] * sizeof(char));
    predicoes = (char *) malloc(todasColunas[2] * sizeof(char));
    modoDecalcular = (char *) malloc((linhas - 2) * sizeof(char));
    numeroDeVizinhos = (int *) malloc((linhas - 3) * sizeof(int));
    raio = (float *) malloc((linhas - 3) * sizeof(float));
    
    rewind(arq);
    int linhas1 = 0;
    //Aloca os vetores de arquivos e de entradas
    while(linhas1<linhas){
        while(fread (&c, sizeof(char), 1, arq) && linhas1 <3){
            if(c != '\n'){
                switch(linhas1){
                    case 0: arquivotreino[i] = c;
                            i++;
                            break;
                    case 1: arquivoteste[i] = c;                            
                            i++;
                            break;
                    case 2: predicoes[i] = c;                           
                            i++;
                            break;
                }
            }else{
                linhas1++;
                i=0;
            }
        }
        if(linhas1 == 3){
            numeroDeVizinhos[i] = c -'0';
            fscanf(arq, " , %c", &modoDecalcular[i]);
            if(modoDecalcular[i] == 'M'){
            fscanf(arq, ", %f", &raio[i]);
            }else{
                raio[i]=0;
            }
            i++;
            linhas1++;
        }else{
            fscanf(arq, "%i, %c", &numeroDeVizinhos[i], &modoDecalcular[i]);
            if(modoDecalcular[i] == 'M'){
                fscanf(arq, ", %f", &raio[i]);
            }else{
                raio[i]=0;
            }
            i++;
            linhas1++;
        }
    }
        
    for(i=0; i<strlen(arquivotreino); i++){
        printf("%c", arquivotreino[i]);
    }
    printf("\n");
    for(i=0; i<strlen(arquivoteste); i++){
        printf("%c", arquivoteste[i]);
    }
    printf("\n");
    for(i=0; i<strlen(predicoes); i++){
        printf("%c", predicoes[i]);
    }
    printf("\n");
    for(i=0; i<(linhas-3); i++){
        printf("%i, %c, %.2f\n", numeroDeVizinhos[i], modoDecalcular[i], raio[i]);
    }
    putchar('\n');
    fclose(arq);

    FILE *filetreino = fopen(arquivotreino, "r");
    char *str = malloc(sizeof(char)*1000);
    if (filetreino == NULL) {
    printf ("Erro na abertura de arquivo! Programa terminado...");
    exit (1);
    }
    int n = 0, linhas2 = 0, quebra = 0;
    j = 0;
    while(!feof(filetreino)){
        //fscanf(file, "%[^\n]", str);
        fgets(str, 1000, filetreino);
        if( quebra == 0){
            for(i = 0; i < strlen(str); i++){
                if (str[i] == ','){
                    n++;
                }
            }
            quebra++;
        }
        linhas2++;
    }
    int linhasTreino;
    linhasTreino = linhas2 -1;
    rewind(filetreino);
    float **matrizTreino = malloc(sizeof(float*) * linhasTreino);
    for (i = 0; i < linhasTreino; i++){
        matrizTreino[i] = malloc(sizeof(float)*(n+1));
    }
    for (i = 0; i < linhasTreino; i++){
        //fscanf(file, "%[^\n]", str);
        fgets(str, 1000, filetreino);
        char *strnew = NULL;
        strnew = strtok(str, ",\n");
        while(strnew != NULL){
            matrizTreino[i][j] = atof(strnew);
            strnew = strtok(NULL, ",\n");
            j++;
        }
        j = 0;
    }
    for(i = 0; i < linhasTreino; i++){
        for (j = 0; j < n+1; j++)
            printf("%.2f ", matrizTreino[i][j]);
        putchar('\n');
    }
    putchar('\n');
    
    fclose(filetreino);

    FILE *fileteste = fopen(arquivoteste, "r");
    char *str1 = malloc(sizeof(char)*1000);
    if (fileteste == NULL) {
    printf ("Erro na abertura de arquivo! Programa terminado...");
    exit (1);
    }
    int m = 0, linhas3 = 0;
    j = 0;
    quebra = 0;
    while(!feof(fileteste)){
        //fscanf(file, "%[^\n]", str);
        fgets(str1, 1000, fileteste);
        if( quebra == 0){
            for(i = 0; i < strlen(str1); i++){
                if (str1[i] == ','){
                    m++;
                }
            }
            quebra++;
        }
        linhas3++;
    }
    int linhasTeste;
    linhasTeste = linhas3 -1;
    rewind(fileteste);
    float **matrizTeste = malloc(sizeof(float*) * linhasTeste);
    for (i = 0; i < linhasTeste; i++){
        matrizTeste[i] = malloc(sizeof(float)*(m+1));
    }
    j=0;
    for (i = 0; i < linhasTeste; i++){
        //fscanf(file, "%[^\n]", str);
        fgets(str1, 1000, fileteste);
        char *strnew1 = NULL;
        strnew1 = strtok(str1, ",\n");
        while(strnew1 != NULL){
            matrizTeste[i][j] = atof(strnew1);
            strnew1 = strtok(NULL, ",\n");
            j++;
        }
        j = 0;
    }
    for(i = 0; i < linhasTeste; i++){
        for (j = 0; j < m+1; j++)
            printf("%.2f ", matrizTeste[i][j]);
        putchar('\n');
    }
    
    fclose(fileteste);

    subtracoes = (float **) malloc(sizeof(float *) * linhasTeste * linhasTreino);
    for(i=0; i<(linhasTeste * linhasTreino); i++){
        subtracoes[i] = (float *) malloc(sizeof(float) * (n+1));
    }
    multiplicacoes = (float **) malloc(sizeof(float *) * linhasTeste * linhasTreino);
    for(i=0; i<(linhasTeste * linhasTreino); i++){
        multiplicacoes[i] = (float *) malloc(sizeof(float) * (n+1));
    }
    somas = (float **) malloc(sizeof(float *) * linhasTeste * linhasTreino);
    for(i=0; i<(linhasTeste * linhasTreino); i++){
        somas[i] = (float *) malloc(sizeof(float) * 2);
    }
    somasteste = (float **) malloc(sizeof(float *) * linhasTeste);
    for(i=0; i<linhasTeste; i++){
        somasteste[i] = (float *) malloc(sizeof(float) * 2);
    }
    somastreino = (float **) malloc(sizeof(float *) * linhasTreino);
    for(i=0; i<linhasTreino; i++){
        somastreino[i] = (float *) malloc(sizeof(float) * 2);
    }
    distancia = (float **) malloc(sizeof(float *) * linhasTeste * linhasTreino);
    for(i=0; i<(linhasTeste * linhasTreino); i++){
        distancia[i] = (float *) malloc(sizeof(float) * 2);
    }

    int k;
    for(k=0; k<(linhas - 3); k++){
        switch(modoDecalcular[i]){
            //distancia euclidiana
            case 'E':
                    subtracao(matrizTeste, matrizTreino, subtracoes, linhasTeste, linhasTreino, (n+1));
                    multiplicacao(subtracoes, multiplicacoes, linhasTeste, linhasTreino, (n+1), 2);
                    soma(multiplicacoes, somas, linhasTeste, linhasTreino, (n+1));
                    multiplicacaovet(somas, distancia, linhasTeste, linhasTreino, 0.5);
                    for(i=0; i<linhasTeste; i++){
                        bubblesort(distancia, (i+1)*linhasTreino, i*linhasTreino);
                    }
                    kmenores(numeroDeVizinhos[k], distancia, kDistanciasMenores, linhasTeste, linhasTreino);
                    matrizrotulos(linhasTeste, linhasTreino, kDistanciasMenores, rotulos);
                    for(i=0; i<(numeroDeVizinhos[k] * linhasTeste); i++){
                        for(j=0; j<2; j++){
                            printf("%.2f ", kDistanciasMenores[i][j]);
                        }
                        printf("\n");
                    }

                    break;
            //distância de Minkowsky
            case 'M':
                    subtracaomodulo(matrizTeste, matrizTreino, subtracoes, linhasTeste, linhasTreino, (n+1));
                    multiplicacao(subtracoes, multiplicacoes, linhasTeste, linhasTreino, (n+1), raio[k]);
                    soma(multiplicacoes, somas, linhasTeste, linhasTreino, (n+1));
                    multiplicacaovet(somas, distancia, linhasTeste, linhasTreino, (1/raio[k]));
                    for(i=0; i<linhasTeste; i++){
                        bubblesort(distancia, (i+1)*linhasTreino, i*linhasTreino);
                    }
                    kmenores(numeroDeVizinhos[k], distancia, kDistanciasMenores, linhasTeste, linhasTreino);
                    matrizrotulos(linhasTeste, linhasTreino, kDistanciasMenores, rotulos);
                    for(i=0; i<(numeroDeVizinhos[k] * linhasTeste); i++){
                        for(j=0; j<2; j++){
                            printf("%.2f ", kDistanciasMenores[i][j]);
                        }
                        printf("\n");
                    }
                    break;
            //distância de Chebyshev
            case 'C':
                    subtracaomodulo(matrizTeste, matrizTreino, subtracoes, linhasTeste, linhasTreino, (n+1));
                    bubblesortmat(subtracoes, (n+1), linhasTeste, linhasTreino);
                    maioresmat(linhasTeste, linhasTreino, colunastreino, subtracoes,distancia);
                    for(i=0; i<linhasTeste; i++){
                        bubblesort(distancia, (i+1)*linhasTreino, i*linhasTreino);
                    }
                    kmenores(numeroDeVizinhos[k], distancia, kDistanciasMenores, linhasTeste, linhasTreino);
                    matrizrotulos(linhasTeste, linhasTreino, kDistanciasMenores, rotulos);
                    for(i=0; i<(linhasTeste * linhasTreino); i++){
                        for(j=0; j<(n+1); j++){
                            printf("%.2f ", subtracoes[i][j]);
                        }
                        printf("\n");
                    }
                    break;
        }
    }

    free(str);
    for(i = 0; i < linhasTreino; i++){
        free(matrizTreino[i]);
    }
    free(matrizTreino);

    free(str1);
    for(i = 0; i < linhasTeste; i++){
        free(matrizTeste[i]);
    }
    free(matrizTreino);

    free(todasColunas);

    free(arquivoteste);
    free(arquivotreino);
    free(predicoes);
    free(modoDecalcular);
    free(numeroDeVizinhos);
    free(raio);

    return 0;
}