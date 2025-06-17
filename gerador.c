#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    long long ts;
    int tipoDeDado;
    char valorTexto[20];
    int sensorID;
} Leitura;

int main(){
    srand(time(NULL));

    printf("----- Gerar Arquivo de Teste ----\n");
    long long ts_inicio, ts_fim;
    printf("Digite o timestamp do inicio: ");
    scanf("%lld", &ts_inicio);
    printf("Digite o timestamp do fim: ");
    scanf("%lld", &ts_fim);

    char sensoresNome[10][50];
    int tiposDeSensores[10];
    int qtdDeSensores = 0;
    char mais = 's';

    while(mais == 's' && qtdDeSensores < 10){
        printf("\n---- Sensor #%d ----\n", qtdDeSensores + 1);
        printf("Nome do sensor: ");

        scanf("%s", sensoresNome[qtdDeSensores]);

        printf("Tipo (Digite 0 = CONJ_Z, 1 = CONJ_Q, 2 = BINARIO, 3 = TEXTO): ");
        scanf("%d", &tiposDeSensores[qtdDeSensores]);
        qtdDeSensores++;

        if(qtdDeSensores < 10){
            printf("Adicionar outro sensor? (s/n): ");
            scanf(" %c", &mais);
        }
    }

    int total_leituras = qtdDeSensores * 2000;
    if(total_leituras == 0) return 0;
    
    Leitura* leituras = (Leitura*) malloc(total_leituras * sizeof(Leitura));
    printf("\nGerando %d leituras...\n", total_leituras);

    for(int i = 0, k = 0; i < qtdDeSensores; i++){
        for (int j = 0; j < 2000; j++, k++) {
            leituras[k].sensorID = i;
            leituras[k].ts = ts_inicio + (rand() % (ts_fim - ts_inicio + 1));
            leituras[k].tipoDeDado = tiposDeSensores[i];
            
            switch(leituras[k].tipoDeDado){ 
                case 0: sprintf(leituras[k].valorTexto, "%d", rand() % 1000); break;
                case 1: sprintf(leituras[k].valorTexto, "%.2f", (double)rand() / RAND_MAX * 100.0); break;
                case 2: sprintf(leituras[k].valorTexto, "%s", (rand() % 2) ? "true" : "false"); break;
                case 3: sprintf(leituras[k].valorTexto, "ID-%d", rand() % 50000); break;
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
    for(int i = 0; i < total_leituras; i++){
        fprintf(f, "%lld %s %s\n", leituras[i].ts, sensoresNome[leituras[i].sensorID], leituras[i].valorTexto);
    }
    
    fclose(f);
    free(leituras);
    printf("Arquivo 'teste.txt' criado com sucesso!\n");
    return 0;
}
