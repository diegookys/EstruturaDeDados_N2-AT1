# Sistema para Consulta de Sensores

Esta aplicação busca simular um sistema de medição em uma planta industrial, com sensores distribuídos na linha de produção. O sistema permite gerar dados simulados, organizar leituras por sensor e consultar medições com base em instantes de tempo, utilizando busca binária para alto desempenho.

---

## 📁 Estrutura do Projeto

O sistema é dividido em **três programas escritos em linguagem C**:

1. [`gerador.c`](gerador.c) — Gera um arquivo de teste com leituras simuladas de sensores.
2. [`organizador.c`](organizador.c) — Organiza as leituras por sensor e ordena por timestamp.
3. [`consultar.c`](consultar.c) — Permite consultar a leitura mais próxima de um timestamp, usando **busca binária**.

---

## 🔧 Compilação

Primeiro baixe os 3 programas e coloque-os em uma pasta de sua preferência

Use um compilador C como `gcc`

Se não houver nenhum instale ele clicando [`aqui`](https://sourceforge.net/projects/mingw/files/latest/download);

Agora inicie um novo terminal no compilador escolhido ou em um prompt de comando e digite:

```bash
gcc gerador.c -o output\gerador.exe
gcc organizador.c -o output\organizador.exe
gcc consultar.c -o output\consultar.exe
```
Para que os programas encontrem os arquivos uns dos outros, é crucial que você execute todos eles de dentro da mesma pasta.

Navegue para a pasta `output` no seu terminal:

```powershell
cd output
```
## Como Usar
1. Gere arquivo de teste (gerador.exe)
```bash (exemplo)
.\gerador.exe 1718755200 1718758800 temperatura CONJ_Z umidade CONJ_Q
```
Informe:

- Timestamp de início e fim (formato Unix Epoch).
- Nome e tipo de cada sensor (int, real, bool, texto).
- Serão geradas 2000 leituras aleatórias por sensor no arquivo teste.txt.

2. Organizar dados (organizador.exe)
```bash
./organizador
```
- Lê o arquivo teste.txt.
- Separa as leituras por sensor.
- Ordena cada arquivo por timestamp e salva como <sensor>.txt.

3. Consultar por timestamp (consultar.exe)
```bash
./consultar
```
- Informe o nome do sensor e o timestamp desejado.
- O programa busca e exibe a leitura mais próxima, usando busca binária no arquivo <sensor>.txt.

## Técnicas Utilizadas
- Alocação dinâmica de memória (malloc, realloc)
- Structs compostos para representar sensores e leituras
- Busca binária personalizada
- Manipulação de arquivos (fopen, fscanf, fprintf)
- Geração de valores aleatórios (rand, time)
