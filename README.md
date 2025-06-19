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

Agora inicie um novo terminal no compilador escolhido ou em um prompt de comando e digite um de cada vez:

```gcc
gcc gerador.c -o output\gerador.exe
gcc organizador.c -o output\organizador.exe
gcc consultar.c -o output\consultar.exe
```
Para que os programas encontrem os arquivos uns dos outros, é crucial que você execute todos eles de dentro da mesma pasta.

Navegue para a pasta `output` no seu terminal:

```powershell
cd output
```
## Como Usar (Terminal)
**1.** Gere arquivo de teste

Exemplo de teste abaixo, aonde deve ser digitado primeiramente o `.exe`, o `timestamp inicial`, o `timestamp final`, o `sensor` e por fim o `tipo` dele, se quiser pode adicionar até 15 sensores usando `sensor` e `tipo` seguidamente.

Obs: Devem ser seguidos os tipos pré definidos, como;

- CONJ_Z:  para dados tipo inteiro
- CONJ_Q: para dados do tipo float
- TEXTO para dados do tipo string
- BINARIO: para dados do tipo booleano.
```powershell
.\gerador.exe 1718755200 1718758800 temperatura CONJ_Z umidade CONJ_Q
```
Informe:

- Timestamp inicial e final.
- Nome e tipo de cada sensor (CONJ_Z, CONJ_Q, TEXTO ou BINARIO).
- Serão geradas 2000 leituras aleatórias por sensor no arquivo teste.txt.

**2.** Organizar dados
```powershell
./organizador.exe
```
- Lê o arquivo teste.txt.
- Separa as leituras por sensor.
- Ordena cada arquivo por timestamp e salva como <sensor>.txt.

3. Consultar por timestamp (consultar.exe)
```powershell
./consultar.exe
```
- Informe o nome do sensor e o timestamp desejado.
- O programa busca e exibe a leitura mais próxima, usando busca binária no arquivo <sensor>.txt.
- O seguinte valor de exemplo deve ser impresso;
```powershell
Timestamp: 1718758735
Valor: 41.74
```

## Técnicas Utilizadas
- Alocação dinâmica de memória (malloc, realloc)
- Structs compostos para representar sensores e leituras
- Busca binária personalizada
- Manipulação de arquivos (fopen, fscanf, fprintf)
- Geração de valores aleatórios (rand, time)
