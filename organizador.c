#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{ 
    long long ts; 
    char valor[21];
} Leitura;

typedef struct{
    char nome[30];
    Leitura* leituras;
    int qtd;
} Sensor_Data;

int comparar_leituras(const void* a, const void* b){
    long long ts_a = ((Leitura*)a)->ts;
    long long ts_b = ((Leitura*)b)->ts;
    if (ts_a > ts_b) return -1;
    if (ts_a < ts_b) return 1;
    return 0;
}

int main(){
    printf("\nOrganizando dados...\n");
    FILE* f = fopen("teste.txt", "r");
    if(!f){
        printf("\nObs: 'teste.txt' nao encontrado.\n");
        return 1; 
    }

    Sensor_Data* sensores = NULL;
    int qtdDeSensores = 0;
    char linha[100];
    int numero_Linha = 0;

    while(fgets(linha, sizeof(linha), f)){
        numero_Linha++;
        long long ts;
        char nome_Sensor[30];
        char valor[21];

        if(sscanf(linha, "%lld %29s %19s", &ts, nome_Sensor, valor) != 3){
            fprintf(stderr, "\nAviso: Linha #%d malformada no arquivo 'teste.txt'. Ignorando.\n", numero_Linha);
            continue;
        }

        int sensorID = -1;
        for(int i = 0; i < qtdDeSensores; i++){
            if(strcmp(sensores[i].nome, nome_Sensor) == 0){
                sensorID = i;
                break;
            }
        }

        if(sensorID == -1){
            sensorID = qtdDeSensores++;
            sensores = (Sensor_Data*) realloc(sensores, qtdDeSensores * sizeof(Sensor_Data));
            strcpy(sensores[sensorID].nome, nome_Sensor);
            sensores[sensorID].leituras = NULL;
            sensores[sensorID].qtd = 0;
        }
        
        sensores[sensorID].qtd++;
        sensores[sensorID].leituras = (Leitura*) realloc(sensores[sensorID].leituras, sensores[sensorID].qtd * sizeof(Leitura));
        sensores[sensorID].leituras[sensores[sensorID].qtd - 1].ts = ts;
        strcpy(sensores[sensorID].leituras[sensores[sensorID].qtd - 1].valor, valor);
    }
    fclose(f);

    printf("Salvando %d sensor(es)...\n", qtdDeSensores);

    for(int i = 0; i < qtdDeSensores; i++){
        qsort(sensores[i].leituras, sensores[i].qtd, sizeof(Leitura), comparar_leituras);
        
        char nomeArquivo[36]; 
        sprintf(nomeArquivo, "%s.txt", sensores[i].nome);

        FILE* f_out = fopen(nomeArquivo, "w");
        for(int j = 0; j < sensores[i].qtd; j++){
            fprintf(f_out, "%lld %s\n", sensores[i].leituras[j].ts, sensores[i].leituras[j].valor);
        }
        fclose(f_out);
        free(sensores[i].leituras);
    }

    free(sensores);
    printf("\nArquivo(s) de texto criados com sucesso!\n\n");
    return 0;
}
