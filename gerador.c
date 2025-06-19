#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    long long ts;
    int tipoDeDado;
    char valorTexto[21];
    int sensorID;
} Leitura;

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    printf("\n       Gerando arquivo de teste...        \n");
    printf("==========================================\n");

    if(argc < 5 || (argc - 3) % 2 != 0){
        fprintf(stderr, "Ops: Uso incorreto.\n");
        fprintf(stderr, "Use: %s <ts_Inicial> <ts_Final> <nome_Sensor1> <TIPO1> [<nome_Sensor2> <TIPO2> ...]\n", argv[0]);
        fprintf(stderr, "Tipos validos: CONJ_Z, CONJ_Q, BINARIO, TEXTO\n");
        return 1;
    }

    long long ts_Inicial = atoll(argv[1]);
    long long ts_Final = atoll(argv[2]);

    if(ts_Final < ts_Inicial){
        fprintf(stderr, "O timestamp final (%lld) nao pode ser menor que o timestamp inicial (%lld).\n", ts_Final, ts_Inicial);
        return 1;
    }

    int qtdDeSensores = (argc - 3) / 2;
    char sensoresNome[15][30];
    int tiposDeSensores[15];

    if(qtdDeSensores > 15){
        fprintf(stderr, "Obs: O programa suporta no maximo 15 sensores.\n");
        return 1;
    }
    
    printf("Criando %d sensor(es)...\n", qtdDeSensores);

    for(int i = 0; i < qtdDeSensores; i++){
        strncpy(sensoresNome[i], argv[3 + i * 2], sizeof(sensoresNome[i]) - 1);
        sensoresNome[i][sizeof(sensoresNome[i]) - 1] = '\0'; // Garantir terminação nula

        char* sensorTipo = argv[3 + i * 2 + 1];

        if(strcmp(sensorTipo, "CONJ_Z") == 0){ // inteiro
            tiposDeSensores[i] = 0;
        } else if(strcmp(sensorTipo, "CONJ_Q") == 0){ // float
            tiposDeSensores[i] = 1;
        } else if(strcmp(sensorTipo, "BINARIO") == 0){
            tiposDeSensores[i] = 2;
        } else if(strcmp(sensorTipo, "TEXTO") == 0){
            tiposDeSensores[i] = 3;
        } else{
            fprintf(stderr, "\nObs: Tipo '%s' para o sensor '%s' eh invalido.\n\n", sensorTipo, sensoresNome[i]);
            return 1;
        }
        printf("  - Sensor #%d: '%s', Tipo: %s\n", i + 1, sensoresNome[i], sensorTipo);
        printf("==========================================\n");
    }

    int total_leituras = qtdDeSensores * 2000;
    if(total_leituras == 0) return 0;
    
    Leitura* leituras = (Leitura*) malloc(total_leituras * sizeof(Leitura));
    printf("\nGerando %d leituras...\n", total_leituras);

    for(int i = 0, k = 0; i < qtdDeSensores; i++){
        for(int j = 0; j < 2000; j++, k++){
            leituras[k].sensorID = i;
            leituras[k].ts = ts_Inicial + (rand() % (ts_Final - ts_Inicial + 1));
            leituras[k].tipoDeDado = tiposDeSensores[i];
            
            switch(leituras[k].tipoDeDado){ 
                case 0: sprintf(leituras[k].valorTexto, "%d", rand() % 1000); 
                break;
                case 1: sprintf(leituras[k].valorTexto, "%.2f", (double)rand() / RAND_MAX * 100.0); 
                break;
                case 2: sprintf(leituras[k].valorTexto, "%s", (rand() % 2) ? "true" : "false"); 
                break;
                case 3: sprintf(leituras[k].valorTexto, "ID-%d", rand() % 50000); 
                break;
            }
        }
    }

    for(int i = total_leituras - 1; i > 0; i--){
        int j = rand() % (i + 1);
        Leitura temp = leituras[i];
        leituras[i] = leituras[j];
        leituras[j] = temp;
    }

    FILE* f = fopen("teste.txt", "w");
    if(!f){
        fprintf(stderr, "Obs: Nao foi possivel criar o arquivo 'teste.txt'.\n");
        free(leituras);
        return 1;
    }
    for(int i = 0; i < total_leituras; i++){
        fprintf(f, "%lld %s %s\n", leituras[i].ts, sensoresNome[leituras[i].sensorID], leituras[i].valorTexto);
    }
    
    fclose(f);
    free(leituras);

    printf("Arquivo 'teste.txt' criado com sucesso!\n\n");

    return 0;
}
