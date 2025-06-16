#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{ 
    long long ts; 
    char valor[20];
} Leitura;

typedef struct{
    char nome[30];
    Leitura* leituras;
    int qtd;
} SensorData;

int comparar_leituras(const void* a, const void* b){
    long long ts_a = ((Leitura*)a)->ts;
    long long ts_b = ((Leitura*)b)->ts;
    if (ts_a < ts_b) return -1;
    if (ts_a > ts_b) return 1;
    return 0;
}

int main(){
    printf("---- Organizando dados ----\n");
    FILE* f = fopen("teste.txt", "r");
    if(!f){
        printf("Erro: 'teste.txt' nao encontrado.\n"); return 1; 
    }

    SensorData* sensores = NULL;
    int qtdDeSensores = 0;
    char linha[100]; 

    while(fgets(linha, sizeof(linha), f)){
        long long ts;
        char nome_sensor[30];
        char valor[20];

        if(sscanf(linha, "%lld %s %s", &ts, nome_sensor, valor) != 3) continue;

        // Procurar se o sensor existe

        int sensorID = -1;
        for(int i = 0; i < qtdDeSensores; i++){
            if(strcmp(sensores[i].nome, nome_sensor) == 0){
                sensorID = i;
                break;
            }
        }

        if(sensorID == -1){
            sensorID = qtdDeSensores++;
            sensores = (SensorData*) realloc(sensores, qtdDeSensores * sizeof(SensorData));
            strcpy(sensores[sensorID].nome, nome_sensor);
            sensores[sensorID].leituras = NULL;
            sensores[sensorID].qtd = 0;
        }
        
        sensores[sensorID].qtd++;
        sensores[sensorID].leituras = (Leitura*) realloc(sensores[sensorID].leituras, sensores[sensorID].qtd * sizeof(Leitura));
        sensores[sensorID].leituras[sensores[sensorID].qtd - 1].ts = ts;
        strcpy(sensores[sensorID].leituras[sensores[sensorID].qtd - 1].valor, valor);
    }
    fclose(f);

    printf("Organizando e salvando %d sensor(es)...\n", qtdDeSensores);

    for(int i = 0; i < qtdDeSensores; i++){
        qsort(sensores[i].leituras, sensores[i].qtd, sizeof(Leitura), comparar_leituras);
        
        char nomeArquivo[55]; 
        sprintf(nomeArquivo, "%s.txt", sensores[i].nome);

        FILE* f_out = fopen(nomeArquivo, "w");
        for(int j = 0; j < sensores[i].qtd; j++){
            fprintf(f_out, "%lld %s\n", sensores[i].leituras[j].ts, sensores[i].leituras[j].valor);
        }
        fclose(f_out);
        free(sensores[i].leituras); // Libera memória após o uso
    }

    free(sensores);
    printf("Arquivo(s) de texto criados com sucesso!\n");
    return 0;
}