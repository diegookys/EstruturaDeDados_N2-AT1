# 📡 Sistema para Consulta de Sensores

Esta aplicação busca simular um sistema de medição em uma planta industrial inteligente, com sensores distribuídos na linha de produção. O sistema permite gerar dados simulados, organizar leituras por sensor e consultar medições com base em instantes de tempo, utilizando busca binária para alto desempenho.

---

## 📁 Estrutura do Projeto

O sistema é dividido em **três programas escritos em linguagem C**:

1. [`gerador.c`](gerador.c) — Gera um arquivo de teste com leituras simuladas de sensores.
2. [`organizador.c`](organizador.c) — Organiza as leituras por sensor e ordena por timestamp.
3. [`consultar.c`](consultar.c) — Permite consultar a leitura mais próxima de um timestamp, usando **busca binária**.

---

## 🔧 Compilação

Use um compilador C como `gcc`:

```bash
gcc gerador.c -o gerador
gcc organizador.c -o organizador
gcc consultar.c -o consultar
```
## Como Usar
1. Gerar arquivo de teste (gerador)
```bash
./gerador
```
Informe:

- Timestamp de início e fim (formato Unix Epoch).
- Nome e tipo de cada sensor (int, real, bool, texto).
- Serão geradas 2000 leituras aleatórias por sensor no arquivo teste.txt.

2. Organizar dados (organizador)
```bash
./organizador
```
- Lê o arquivo teste.txt.
- Separa as leituras por sensor.
- Ordena cada arquivo por timestamp e salva como <sensor>.txt.

3. Consultar por timestamp (consultar)
```bash
./consultar
```
- Informe o nome do sensor e o timestamp desejado.
- O programa busca e exibe a leitura mais próxima, usando busca binária no arquivo <sensor>.txt.

## Técnicas Utilizadas
- Alocação dinâmica de memória (malloc, realloc)
- Structs compostos para representar sensores e leituras
- Ordenação com qsort
- Busca binária personalizada
- Manipulação de arquivos (fopen, fscanf, fprintf)
- Geração de valores aleatórios (rand, time)
