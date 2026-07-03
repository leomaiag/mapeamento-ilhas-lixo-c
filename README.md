# Mapeamento de Ilhas de Lixo Oceânico em C

Algoritmo desenvolvido em C para identificar aglomerados (ilhas) de lixo em uma matriz bidimensional, calcular a profundidade total de cada ilha e encontrar a combinação exata de ilhas para preencher um contêiner de coleta.

## Funcionalidades
- **Busca em Grafos (DFS):** Utiliza *Depth-First Search* recursiva (Flood-fill) para mapear elementos adjacentes na matriz e calcular o tamanho da ilha.
- **Soma de Subconjuntos (Backtracking):** Implementa um algoritmo recursivo de *Subset Sum* para encontrar uma combinação exata de profundidades que atinja a capacidade alvo do contêiner.
- **Processamento de Matrizes:** Leitura de matrizes via arquivos `.txt` através de argumentos de linha de comando (`argc`, `argv`).
- **Ordenação:** Utilização da função `qsort` para otimizar a busca decrescente dos elementos.

## Como executar
```bash
./EP1 <profundidade_container> <linhas> <colunas> <arquivo.txt>
```
## Exemplo de Execução

**Comando de Execução:**
```bash
./EP1 26 8 8 teste1.txt
Entrada (teste1.txt)
4 5 0 8 0 0 0 3
1 2 78 7 0 0 4 5
4 0 0 0 44 3 5 0
0 0 0 0 0 0 0 0
1 4 0 0 0 0 3 0
5 8 9 4 0 0 2 1
0 0 0 0 0 1 0 0
4 6 9 0 0 0 0 0

Saída
6
1 1 3 5 10 18 
3 5 18
