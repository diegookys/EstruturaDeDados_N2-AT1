#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{ 
    long long ts; 
    char valor[20];
} Leitura;

int main(){
    printf("---- Consultar dados ----\n");
    char nome_sensor[30];
    long long ts_alvo;

    printf("Nome do sensor? ");
    scanf("%s", nome_sensor);
    printf("Qual o timestamp? ");
    scanf("%lld", &ts_alvo);
    
    char nomeArquivo[35]; 
    sprintf(nomeArquivo, "%s.txt", nome_sensor);
    FILE* f = fopen(nomeArquivo, "r");
    if(!f){ 
        printf("ERRO: arquivo '%s' não encontrado.\n", nomeArquivo); return 1;
    }

    Leitura* leituras = NULL;
    int qtd = 0;
    char linha[45]; 

    while(fgets(linha, sizeof(linha), f)){
        qtd++;
        leituras = (Leitura*) realloc(leituras, qtd * sizeof(Leitura));
        sscanf(linha, "%lld %s", &leituras[qtd - 1].ts, leituras[qtd - 1].valor);
    }
    fclose(f);

    if(qtd == 0){
        printf("Nenhum dado no arquivo.\n"); free(leituras); return 0;
    }

    int min = 0, max = qtd - 1, idx = 0;
    while(min <= max){
        int meio = min + (max - min) / 2;
        if(leituras[meio].ts == ts_alvo) { idx = meio; break;}
        if(leituras[meio].ts < ts_alvo) min = meio + 1;
        else max = meio - 1;
    }

    if(leituras[idx].ts != ts_alvo){
        if (min >= qtd) idx = max;
        else if (max < 0) idx = min;
        else idx = (llabs(ts_alvo - leituras[max].ts) < llabs(ts_alvo - leituras[min].ts)) ? max : min;
    }

    printf("\n---- Busca mais proxima achada ----\n");
    printf("Timestamp: %lld\n", leituras[idx].ts);
    printf("Valor    : %s\n", leituras[idx].valor);
    printf("-------------------------------------\n");
    
    free(leituras);
    return 0;
}