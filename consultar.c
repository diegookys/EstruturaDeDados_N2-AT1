#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{ 
    long long ts; 
    char valor[21];
} Leitura;

int main(){
    printf("==== Consultar dados ====\n");
    char nome_Sensor[30];
    long long ts_Alvo;

    printf("Nome do sensor? ");
    scanf("%29s", nome_Sensor); 

    printf("Qual o timestamp? ");
    scanf("%lld", &ts_Alvo);
    
    char nomeArquivo[35]; 
    sprintf(nomeArquivo, "%s.txt", nome_Sensor);
    FILE* f = fopen(nomeArquivo, "r");
    if(!f){ 
        printf("Obs: arquivo '%s' nao encontrado.\n\n", nomeArquivo);
        return 1;
    }

    Leitura* leituras = NULL;
    int qtd = 0;
    char linha[45]; 

    while(fgets(linha, sizeof(linha), f)){
        qtd++;
        leituras = (Leitura*) realloc(leituras, qtd * sizeof(Leitura));
        sscanf(linha, "%lld %19s", &leituras[qtd - 1].ts, leituras[qtd - 1].valor);
    }
    fclose(f);

    if(qtd == 0){
        printf("\nNenhum dado no arquivo.\n\n"); free(leituras); return 0;
    }

    int min = 0, max = qtd - 1, resultado = 0;
    while(min <= max){
        int meio = min + (max - min) / 2;
        if(leituras[meio].ts == ts_Alvo){ resultado = meio; break;}
        if(leituras[meio].ts > ts_Alvo) min = meio + 1;
        else max = meio - 1;
    }

    if(resultado < qtd && leituras[resultado].ts != ts_Alvo){
        if (min >= qtd) resultado = max > -1 ? max : 0;
        else if (max < 0) resultado = min < qtd ? min : 0;
        else resultado = (llabs(ts_Alvo - leituras[max].ts) < llabs(ts_Alvo - leituras[min].ts)) ? max : min;
    }

    printf("\n===== Valor mais proximo encontrado =====\n");
    if(qtd > 0){
        printf("Timestamp: %lld\n", leituras[resultado].ts);
        printf("Valor: %s\n", leituras[resultado].valor);
    }
    printf("=========================================\n");
    
    
    free(leituras);
    return 0;
}
